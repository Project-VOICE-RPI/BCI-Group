////////////////////////////////////////////////////////////////////////////////
// $Id: CoreModule.cpp 8296 2024-08-01 16:12:02Z mellinger $
// Authors: schalk@wadsworth.org, juergen.mellinger@uni-tuebingen.de
// Description: A class that represents functionality common to all BCI2000
//          core modules.
//
// $BEGIN_BCI2000_LICENSE$
//
// This file is part of BCI2000, a platform for real-time bio-signal research.
// [ Copyright (C) 2000-2023: BCI2000 team and many external contributors ]
//
// BCI2000 is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// BCI2000 is distributed in the hope that it will be useful, but
//                         WITHOUT ANY WARRANTY
// - without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
// $END_BCI2000_LICENSE$
////////////////////////////////////////////////////////////////////////////////
#include "CoreModule.h"

#include "BCIStream.h"
#include "ExceptionCatcher.h"
#include "Lib/FileUtils.h"
#include "GenericFilter.h"
#include "GenericSignal.h"
#include "GenericVisualization.h"
#include "MeasurementUnits.h"
#include "ProcessUtils.h"
#include "ProtocolVersion.h"
#include "Sockets.h"
#include "Status.h"
#include "StringUtils.h"
#include "SysCommand.h"
#include "VersionInfo.h"
#include "BCIEvent.h"

#include <cstdlib>
#include <sstream>
#include <string>

#undef bcierr
#define bcierr (bcierr_(sModuleName))

static const int cLargeSignalSizeBytes = 2048;
static const std::string sModuleName = FileUtils::ExtractBase(FileUtils::ExecutablePath());

CoreModule::CoreModule()
    : mFiltersInitialized(false), mTerminating(false), mRunning(false), mActiveResting(false),
      mNeedStopRun(false), mReceivingNextModuleInfo(false),
      mGlobalID(NULL),
      mOperatorBackLink(false), mAutoConfig(false), mOperator(*this), mPreviousModule(*this), mNextModule(*this),
      mInitialStatevector(0, 0), mEnvironment(*Environment::Context::GlobalInstance()),
      mBCIEvents(0)
{
    BCIEvent::SetEventQueue(&mBCIEvents);

    mOperatorSocket.SetFlushAfterWrite(true);
    mOperator.SetIO(&mOperatorSocket, CoreConnection::AsyncSend);
    mNextModuleSocket.SetFlushAfterWrite(true);
    mNextModule.SetIO(&mNextModuleSocket);
    mPreviousModuleSocket.SetFlushAfterWrite(true);
    mPreviousModule.SetIO(&mPreviousModuleSocket);

    std::shared_ptr<Runnable> p(new MemberCall<void(CoreModule *)>(&CoreModule::InitializeStatevector, this));
    MeasurementUnits::AddInitializeCallback(p);

    GenericFilter::Chain::AddFilterHook(&mVisualizationHook);
    GenericFilter::Chain::AddFilterHook(&mSignalSharingHook);
}

CoreModule::~CoreModule()
{
    GenericFilter::Chain::RemoveFilterHook(&mSignalSharingHook);
    GenericFilter::Chain::RemoveFilterHook(&mVisualizationHook);

    BCIEvent::DenyEvents();
    BCIEvent::SetEventQueue(nullptr);
}

void CoreModule::DoRun(int &ioArgc, char **ioArgv)
{
    if (Initialize(ioArgc, ioArgv))
        MainMessageLoop();
}

bool CoreModule::Run(int &ioArgc, char **ioArgv)
{
    struct : ExceptionCatcher
    {
      void OnReportException(const std::string& msg) override
      {
        bcierr__ << msg << "\nTerminating " << sModuleName << " module";
        // make sure message is received by Operator before connection is closed
        ThreadUtils::SleepFor(Time::OneSecond());
      }
    } catcher;
    MemberCall<void(CoreModule *, int &, char **)> doRunCall(&CoreModule::DoRun, this, ioArgc, ioArgv);
    catcher.Run(doRunCall);
    MemberCall<void(CoreModule *)> shutdownSystemCall(&CoreModule::ShutdownSystem, this);
    catcher.Run(shutdownSystemCall);
    return (bcierr__.Flushes() == 0);
}

void CoreModule::Terminate()
{
    mTerminating = true;
    if (mNeedStopRun)
        StopRunFilters();
    GenericFilter::HaltFilters();
    mEnvironment.EnterPhase(Environment::destruction);
}

// Internal functions.
bool CoreModule::IsFirstModule() const
{
#if IS_FIRST_MODULE
  return true;
#else
  return false;
#endif
}

bool CoreModule::IsLastModule() const
{
#if IS_LAST_MODULE
    return true;
#else
    return false;
#endif
}

bool CoreModule::Initialize(int &ioArgc, char **ioArgv)
{
    // Make sure there is only one instance of each module running at a time.
    if (!ProcessUtils::AssertSingleInstance(ioArgc, ioArgv, THISMODULE "Module", 5000))
    {
        bcierr << "Another " THISMODULE " Module is currently running.\n"
               << "Only one instance of each module may run at a time.\n"
               << "Adding --AllowMultipleInstances as a command line parameter will disable this behavior.\n";
        return false;
    }
    ProcessUtils::InitializeDesktopIntegration("org.bci2000.OnlineModules", FileUtils::ApplicationTitle());
    ProcessUtils::RequestPrecisionTiming();
    OnInitialize(ioArgc, ioArgv);

    std::string operatorAddress;
    bool printVersion = false, printHelp = false, printExtensions = false;
    int i = 1;
    while (i < ioArgc)
    {
        std::string curArg(ioArgv[i]);
        if (curArg == "--version" || curArg == "-v")
        {
            printVersion = true;
        }
        else if (curArg == "--help" || curArg == "-?" || curArg == "?")
        {
            printHelp = true;
        }
        else if (curArg == "--Extensions")
        {
            printExtensions = true;
        }
        else if (curArg == "--local")
        {
            if (!mParamlist.Exists("/ListeningAddress"))
                mParamlist.Add("System string /ListeningAddress= 127.0.0.1 // ");
        }
        else if (curArg == "--AllowMultipleInstances")
        { // Do not add to parameter list
        }
        else if (curArg.find("--") == 0)
        {
            std::string paramDef = curArg.substr(2);
            size_t nameEnd = paramDef.find_first_of("-=:");
            std::string paramName = paramDef.substr(0, nameEnd), paramValue;
            if (paramName == THISMODULE "IP")
                paramName = "ListeningAddress";
            if (nameEnd != std::string::npos)
                paramValue = paramDef.substr(nameEnd + 1);
            Param param("/" + paramName, "System", "variant", paramValue, paramValue, paramValue,
                        paramValue);
            param.Sections().push_back("Command Line Arguments");
            mParamlist.Add(param);
        }
        else if (curArg == "AUTOSTART")
        { /* do nothing */
        }
        else if (operatorAddress.empty())
        {
            operatorAddress = curArg;
        }
        else
        {
            printHelp = true;
        }
        ++i;
    }

    if (printVersion)
    {
        const VersionInfo &info = VersionInfo::Current;
        std::cout << "\nBCI2000 " << sModuleName << " \n\n"
                  << " Framework: " << info[VersionInfo::VersionID] << " \n";
        if (!info[VersionInfo::Revision].empty())
            std::cout << " Revision: " << info[VersionInfo::Revision] << ", " << info[VersionInfo::SourceDate] << " \n";
        if (!info[VersionInfo::Config].empty())
            std::cout << " Config: " << info[VersionInfo::Config] << " \n";
        std::cout << " Build: " << info[VersionInfo::Build] << " \n";
        std::cout << std::flush;
        return true;
    }
    if (printHelp)
    {
        std::string executableName = FileUtils::ExtractBase(FileUtils::ExecutablePath());
        std::cout << "Usage:\n"
                  << executableName << " [<address>:<port>] [--<option>[=<value>]] ...\n"
                  << " address  IP address of operator module (default 127.0.0.1)\n"
                  << " port     operator port (default " THISOPPORT ")\n"
                  << "Options are:\n"
                  << " --help    display this help\n"
                  << " --version display version information\n"
                  << " --local   listen on 127.0.0.1 only -- recommended,\n"
                  << "           avoids triggering firewall dialog\n"
                  << " --Extensions display extensions\n"
                  << " --ListeningAddress=<ip address> listen on specified address\n"
                  << " --AllowMultipleInstances allows multiple modules of the same kind\n"
                  << "           to run simultaneously\n"
                  << "Any additional options will appear as parameters in the System section.\n"
                  << std::endl;
        return false;
    }
    if (printExtensions)
    {
        PrintExtensions();
        return false;
    }
#if _WIN32 // increasing priority requires root privileges on Linux/macOS
    int priority = +1;
    if (mParamlist.Exists("/ProcessPriority"))
        priority = ::atoi(mParamlist.ByPath("/ProcessPriority").Value().c_str());
    ProcessUtils::Priority::Set(ProcessUtils::Priority::Normal);
    if (!ProcessUtils::Priority::ChangeBy(priority))
        bciwarn << "Could not adjust process priority by " << std::showpos << priority << " relative to normal";
#endif

    if (mParamlist.Exists("/OperatorIP"))
        operatorAddress = mParamlist.ByPath("/OperatorIP").Value().ToString();

    if (operatorAddress.empty())
        operatorAddress = "127.0.0.1";
    if (operatorAddress.find(":") == std::string::npos)
        operatorAddress += ":" THISOPPORT;

    InitializeOperatorConnection(operatorAddress);

    return (bcierr__.Flushes() == 0);
}

void CoreModule::PrintExtensions()
{
    std::cout << "Extensions:" << std::endl;
    const auto& extensions = Environment::Context::GlobalInstance()->Extensions();
    for (const auto pExtension : extensions) {
        if (!pExtension->Enablers().empty()) {
            std::cout << ClassName(typeid(*pExtension));
            for (const auto& enabler : pExtension->Enablers()) {
                std::cout << "\t" << enabler;
            }
            std::cout << std::endl;
        }
    }

    ParamList params;
    StateList states;
    UnbufferedIO streambuf;
    MessageChannel channel(streambuf);
    GenericVisualization::SetOutputChannel(&channel);
    Environment::Context::GlobalInstance()->EnterPhase(Environment::construction, &params, &states);
    GenericFilter::InstantiateFilters();
    Environment::Context::GlobalInstance()->EnterPhase(Environment::nonaccess);
    const auto& filters = GenericFilter::AllFilters();
    for (const auto pFilter : filters) {
        if (!pFilter->Enablers().empty()) {
            std::cout << ClassName(typeid(*pFilter));
            for (const auto& enabler : pFilter->Enablers()) {
                std::cout << "\t" << enabler;
            }
            std::cout << std::endl;
        }
    }
    Environment::Context::GlobalInstance()->EnterPhase(Environment::destruction);
    GenericFilter::DisposeFilters();
    Environment::Context::GlobalInstance()->EnterPhase(Environment::nonaccess);
    GenericVisualization::SetOutputChannel(nullptr);
}

// This function contains the main event handling loop.
// It will be entered once when the program starts,
// and only be left when the program exits.
void CoreModule::MainMessageLoop()
{
    // max time a GUI event needs to wait before it gets processed
    const Time::Interval bciMessageTimeout = Time::Seconds(0.1);
    Waitables inputs;
    inputs.Add(mOperator).Add(mPreviousModule);

    while (!mTerminating)
    {
        inputs.Wait(bciMessageTimeout);
        ProcessBCIAndGUIMessages();
        if (mOperator.Bad() || !mOperatorSocket.Connected())
            Terminate();
    }
}

void CoreModule::ProcessBCIAndGUIMessages()
{
    bool repeat = true;
    while (repeat)
    {
        mPreviousModule.HandleMessages();
        mOperator.HandleMessages();

        repeat = false;
        if (mActiveResting && !mTerminating)
        {
            ProcessFilters();
            mActiveResting &= bcierr__.Empty();
            repeat |= mActiveResting;
        }
        // Allow for the GUI to process messages from its message queue if there are any.
        OnProcessGUIMessages();
        repeat |= OnGUIMessagesPending();
        repeat = repeat && mOperator.Good();

#if 0
        if (mOperator.Bad())
            bcierr << "Lost connection to operator: " << mOperator.DescribeIOState();
#endif
        if (mPreviousModule.Bad())
            bcierr << "Lost connection to " PREVMODULE ": " << mPreviousModule.DescribeIOState();
        if (mNextModule.Bad())
            bcierr << "Lost connection to " NEXTMODULE ": " << mNextModule.DescribeIOState();
    }
}

void CoreModule::InitializeOperatorConnection(const std::string &inOperatorAddress)
{
    // creating connection to the operator
    mOperatorSocket.Open(inOperatorAddress);
    if (!mOperatorSocket.IsOpen())
    { // wait if connection to operator module fails
        ThreadUtils::SleepFor(Time::Seconds(2));
        mOperatorSocket.Open(inOperatorAddress);
    }
    if (!mOperatorSocket.Connected())
    {
        bcierr << "Could not connect to operator module";
        return;
    }

    mParamlist.Delete("/OperatorAddress");
    mParamlist.Add("System:Core%20Connections string /OperatorAddress= % // (noedit)");
    mParamlist.ByPath("/OperatorAddress").Value() = StringUtils::String() << inOperatorAddress;

    if (mOperatorSocket.Input().Wait(Time::Seconds(0.5)))
    { // By immediately sending a neutral message, the operator module indicates that it
        // is able to deal with more recent versions of the protocol.
        mOperator.HandleMessages();
        mOperator.Send(ProtocolVersion::Current());
        // The Operator module must be of the same version as the core module, or newer,
        // so we can set its channel's protocol version to current.
        mOperator.SetProtocol(ProtocolVersion::Current());
    }
    else
    {
        bciwarn << "Operator module did not indicate support for protocol negotiation.\n\n"
                << "If you experience problems, please make sure that the Operator module's version "
                << "matches the most recent core module.";
        mOperator.Send(ProtocolVersion::Current().Major());
    }
    mOperator.SetIsLocal(mOperatorSocket.Connected() == Socket::local);
    BCIStream::SetOutputChannel(&mOperator);
    GenericVisualization::SetOutputChannel(&mOperator);

    if (mParamlist.Exists("/ListeningAddress"))
        mServerSocket.Open(mParamlist.ByPath("/ListeningAddress").Value().ToString());
    else
        mServerSocket.Open(Socket::LocalIPs().back());
    mOperator.SetIO(&mOperatorSocket, CoreConnection::AsyncReceive);
    mParamlist.Add("System string /ModuleName= " THISMODULE);

    mParamlist.Delete("/ListeningAddress");
    mParamlist.Add("System string /ListeningAddress= %");
    mParamlist.ByPath("/ListeningAddress").Value() = mServerSocket.LocalAddress();

    mParamlist.Add( // internally used
        "System:Core%20Connections string /OperatorIP= x"
        " 127.0.0.1 % % // the Operator module's IP (noedit)(readonly)");
    mParamlist.ByPath("/OperatorIP").Value() = mOperatorSocket.RemoteIP();

    mEnvironment.EnterPhase(Environment::construction, &mParamlist, &mStatelist);
    GenericFilter::InstantiateFilters();
    mEnvironment.EnterPhase(Environment::nonaccess);
    mEnvironment.EnterPhase(Environment::publication, &mParamlist, &mStatelist);
    GenericFilter::PublishFilters();
    mEnvironment.EnterPhase(Environment::nonaccess);
    if (bcierr__.Flushes() > 0)
        return;

    { // Version info
        const VersionInfo &info = VersionInfo::Current;
        mParamlist.Add("System:Version matrix /" THISMODULE "Version= "
                       "{ Framework Revision Build Config Protocol } 1 "
                       " % % % % % // " THISMODULE " version information (noedit)(readonly)");
        Param &p = mParamlist.ByPath("/" THISMODULE "Version");
        p.Value("Framework") = info[VersionInfo::VersionID];
        std::string revision = info[VersionInfo::Revision] + ", " + info[VersionInfo::SourceDate];
        if (revision.front() == ',')
            revision = revision.substr(2);
        p.Value("Revision") = revision;
        p.Value("Build") = info[VersionInfo::Build];
        p.Value("Config") = info[VersionInfo::Config];
        std::ostringstream oss;
        oss << ProtocolVersion::Current();
        p.Value("Protocol") = oss.str();
    }
    { // Filter chain documentation
        mParamlist.Add("System:Configuration matrix /" THISMODULE "FilterChain= "
                       "0 { Filter%20Name Position%20String } "
                       " % % % // " THISMODULE " filter chain (noedit)(readonly)");
        Param &p = mParamlist.ByPath("/" THISMODULE "FilterChain");
        const GenericFilter::ChainInfo &chain = GenericFilter::GetChainInfo();
        p.SetNumRows(chain.size());
        for (size_t row = 0; row < chain.size(); ++row)
        {
            p.Value(row, "Filter Name") = chain[row].name;
            p.Value(row, "Position String") = chain[row].position;
        }
    }
    { // Filter directory documentation
        mParamlist.Add("System:Configuration matrix /Filters= 0 1 % % % // Filter Directory (noedit)(readonly)");
        AppendFilterDirectory(mParamlist.ByPath("/Filters"));
    }
    // Now, publish parameters ...
    mParamlist.Sort();
    mOperator.Send(mParamlist);
    mOperator.Send(SysCommand::EndOfParameter);
    // ... and states.
    mOperator.Send(mStatelist);
    mOperator.Send(SysCommand::EndOfState);

    mOperator.Send(Status("Waiting for configuration ...", Status::plainMessage));
}

void CoreModule::InitializeCoreConnections()
{
    std::string nextModuleAddress, address = "/NextModuleAddress";
    if (mNextModuleInfo.Exists(address))
        nextModuleAddress = mNextModuleInfo.ByPath(address).Value();
    else
    {
        std::string ip = "/" NEXTMODULE "IP";
        if (mParamlist.Exists(ip))
        {
            ip = mParamlist.ByPath(ip).Value();
            std::string port = "/" NEXTMODULE "Port";
            if (mParamlist.Exists(port))
            {
                port = mParamlist.ByPath(port).Value();
                nextModuleAddress = ip + ":" + port;
            }
        }
    }
    if (nextModuleAddress.empty())
    {
        bcierr << "Next module's IP/Port parameters not available";
        return;
    }
    mNextModuleSocket.Open(nextModuleAddress);
    if (!mNextModuleSocket.IsOpen())
    {
        bcierr << "Could not make a connection to the next module at " << nextModuleAddress;
        return;
    }
    mNextModule.SetIsLocal(mNextModuleSocket.Connected() == Socket::local);

    if (!mServerSocket.WaitForAccept(mPreviousModuleSocket, cInitialConnectionTimeout))
        bcierr << "Connection to previous module timed out after " << float(cInitialConnectionTimeout) / 1e3 << "s";
    mServerSocket.Close();
}

void CoreModule::ShutdownSystem()
{
    BCIStream::SetOutputChannel(0);
    GenericVisualization::SetOutputChannel(0);
    mOperatorSocket.Close();
    mPreviousModuleSocket.Close();
    mNextModuleSocket.Close();
    GenericFilter::DisposeFilters();
}

void CoreModule::InitializeStatevector()
{
    int sampleBlockSize = ::atoi(mParamlist.ByPath("/SampleBlockSize").Value().c_str());
    mBCIEvents.SetMaxCount(sampleBlockSize * 1000);

    if (sampleBlockSize > 0 && sampleBlockSize + 1 != mStatevector.Samples())
    {
        // The state vector holds an additional sample which is used to initialize
        // the subsequent state vector at the beginning of a new block.
        mStatevector = StateVector(mStatelist, sampleBlockSize + 1);
        // If this is not the first initialization, we need to preserve the initial state vector
        // across the change in length.
        if (mInitialStatevector.Samples() > 0) {
            for (const auto& state : mStatelist) {
                auto value = mInitialStatevector.CarryoverValue(state.Location(), state.Length());
                mStatevector.SetStateValue(state.Location(), state.Length(), value);
            }
        }
        mInitialStatevector = mStatevector;
        mStatevector.CommitStateChanges();
    }
}

void CoreModule::ResetStatevector()
{
    State::ValueType sourceTime = mStatevector.StateValue("SourceTime");
    mStatevector = mInitialStatevector;
    mStatevector.SetStateValue("SourceTime", sourceTime);
    mStatevector.CommitStateChanges();
}

namespace
{
struct AppendFilter
{
    bool operator()(const Directory::Node *pNode)
    {
        if (pNode->Children().empty())
        {
            int idx = param.NumRows();
            param.SetNumRows(idx + 1);
            param.Value(idx, 0) = pNode->Path();
        }
        return true;
    }
    Param &param;
};
} // namespace

void CoreModule::AppendFilterDirectory(Param &p) const
{
    AppendFilter append = {p};
    Directory::Traverse(GenericFilter::Directory(), append);
}

void CoreModule::InitializeFilterChain(const SignalProperties &Input)
{
    bcierr__.Clear();
    GenericFilter::HaltFilters();
    InitializeInputSignal(Input);

    // Does the Operator module accept the AutoConfig protocol?
    if (mParamlist.Exists("AutoConfig"))
        mAutoConfig = ::atoi(mParamlist.ByPath("/AutoConfig").Value().c_str());

    AutoConfigFilters();
    if (bcierr__.Empty())
        InitializeFilters();
}

void CoreModule::InitializeInputSignal(const SignalProperties &Input)
{
#ifdef TODO
#error The inputPropertiesFixed variable may be removed once property messages contain an UpdateRate field.
#endif // TODO
  try {
    SignalProperties inputFixed(Input);
    if (!IsFirstModule()) {
      MeasurementUnits::Initialize(mParamlist);
      inputFixed.SetUpdateRate(1.0 / MeasurementUnits::SampleBlockDuration());
    }
    mInputSignal = GenericSignal(inputFixed);
  }
  catch (const Tiny::Exception& e) {
    bcierr__ << e.What();
  }
}

void CoreModule::AutoConfigFilters()
{
    mParamlist.Unchanged();

    ParamList restoreParams;
    if (!mAutoConfig)
    {
        restoreParams = mParamlist;
        if (restoreParams.Exists("SubjectRun"))
            restoreParams.Delete("SubjectRun"); // special case for backward compatibility reasons
    }

    mEnvironment.EnterPhase(Environment::preflight, &mParamlist, &mStatelist);
    SignalProperties Output(0, 0);
    GenericFilter::PreflightFilters(mInputSignal.Properties(), Output);
    mEnvironment.EnterPhase(Environment::nonaccess);
    mOutputSignal = GenericSignal(Output);

    if (!IsLastModule())
    { // sharing the output signal in the last module might result in a race condition between operator
      // and source module, so we never share the last module's output signal
        if (mNextModule.IsLocal() && mNextModule.Protocol().Provides(ProtocolVersion::SharedSignalStorage))
            mOutputSignal.ShareAcrossModules();
    }
    for (const auto& restore : restoreParams)
    {
        Param &p = mParamlist.ByPath(restore.Path());
        if (p.Changed())
        {
            p = restore;
            p.Unchanged();
        }
    }
    if (mParamlist.Exists("/DebugLevel") && ::atoi(mParamlist.ByPath("/DebugLevel").Value().c_str()))
    {
      bciout << mParamlist.ByPath(THISMODULE "Version");
      bciout << mParamlist.ByPath("/Filters");
      for (const auto& param : mParamlist)
            if (param.Changed())
                bciout << "AutoConfig: " << param;
    }
    if (mAutoConfig && bcierr__.Empty())
    {
        BroadcastParameterChanges();
        if (!mOperator.Send(Output))
            bcierr << "Could not send output properties to Operator module";
    }
}

void CoreModule::InitializeFilters()
{
    mLargeSignals.clear();
    if (bcierr__.Empty())
    {
        if (mParamlist.Exists("/OperatorBackLink"))
            mOperatorBackLink = ::atoi(mParamlist.ByPath("/OperatorBackLink").Value().c_str());
        if (!mAutoConfig)
        {
            if (IsLastModule())
            {
                if (mOperatorBackLink && !mOperator.Send(mOutputSignal.Properties()))
                    bcierr << "Could not send output properties to Operator module";
            }
            else
            {
                if (!mNextModule.Send(mOutputSignal.Properties()))
                    bcierr << "Could not send output properties to " NEXTMODULE " module";
            }
        }
        mEnvironment.EnterPhase(Environment::initialization, &mParamlist, &mStatelist, &mStatevector);
        GenericFilter::InitializeFilters();
        mEnvironment.EnterPhase(Environment::nonaccess);
    }
    if (bcierr__.Empty())
    {
        mOperator.Send(Status(sModuleName + " initialized", Status::firstInitializedMessage + MODTYPE - 1));
        mFiltersInitialized = true;
        mActiveResting = IsFirstModule();
    }
}

void CoreModule::StartRunFilters()
{
    mActiveResting = false;
    mEnvironment.EnterPhase(Environment::startRun, &mParamlist, &mStatelist, &mStatevector);
    GenericFilter::StartRunFilters();
    mEnvironment.EnterPhase(Environment::nonaccess);
    mNeedStopRun = true;
    if (bcierr__.Empty())
        mOperator.Send(Status(sModuleName + " running", Status::firstRunningMessage + 2 * (MODTYPE - 1)));
}

void CoreModule::StopRunFilters()
{
    mEnvironment.EnterPhase(Environment::stopRun, &mParamlist, &mStatelist, &mStatevector);
    GenericFilter::StopRunFilters();
    mEnvironment.EnterPhase(Environment::nonaccess);
    mNeedStopRun = false;
    ResetStatevector();
    if (bcierr__.Empty() && !mTerminating)
    {
        BroadcastParameterChanges();
        if (IsFirstModule())
            mOperator.Send(SysCommand::Suspend);
        mOperator.Send(Status(sModuleName + " suspended", Status::firstSuspendedMessage + 2 * (MODTYPE - 1)));
    }
    if (!mTerminating)
    {
        mEnvironment.EnterPhase(Environment::resting, &mParamlist, &mStatelist, &mStatevector);
        GenericFilter::RestingFilters();
        mEnvironment.EnterPhase(Environment::nonaccess);
        mActiveResting = IsFirstModule();
    }
}

void CoreModule::BroadcastParameterChanges()
{
    ParamList changedParameters;
    for (const auto& param : mParamlist)
        if (param.Changed())
            changedParameters.Add(param);
    mParamlist.Unchanged();

    if (!changedParameters.Empty())
    {
        mOperator.Send(changedParameters);
        if (!mOperator.Send(SysCommand::EndOfParameter))
            bcierr << "Could not publish changed parameters";
    }
}

void CoreModule::ProcessFilters()
{
    mStatevector.CommitStateChanges();
#if !IS_FIRST_MODULE // In the source module, this is called by DataIOFilter immediately after Acquire()
    mBCIEvents.ProcessEvents(&mStatevector, MeasurementUnits::SampleBlockDuration());
#endif

    bool wasRunning = mRunning;

    bool isRunning1 = mStatevector.StateValue("Running"); // check "Running" before processing filters
    bool startRunPending = isRunning1 && !wasRunning;
    if (startRunPending)
        StartRunFilters();

    mEnvironment.EnterPhase(Environment::processing, &mParamlist, &mStatelist, &mStatevector);
    bool resting = !(isRunning1 || wasRunning);
    GenericFilter::ProcessFilters(mInputSignal, mOutputSignal, resting);
    mEnvironment.EnterPhase(Environment::nonaccess);

    if (bcierr__.Empty() && (isRunning1 || wasRunning))
        SendOutput();

    bool isRunning2 = mStatevector.StateValue("Running"); // check "Running" after processing filters
    bool stopRunPending = wasRunning && !isRunning2;
    if (bcierr__.Empty() && stopRunPending)
        StopRunFilters();

    mRunning = isRunning2;
    if (!bcierr__.Empty())
        Terminate();
}

void CoreModule::SendOutput()
{
    if (IsLastModule() && mOperatorBackLink)
    {
        mOperator.Send(mStatevector);
        mOperator.Send(mOutputSignal);
    }
    mNextModule.Send(mStatevector);
    if (!IsLastModule())
        mNextModule.Send(mOutputSignal);
}

void CoreModule::OnReceive(CoreConnection &, const Param &p)
{
    if (mRunning)
        bcierr << "Unexpected Param message";

    ParamList &list = mReceivingNextModuleInfo ? mNextModuleInfo : mParamlist;
    list.ByPath(p.Path()) = p;
}

#ifdef TODO
# error Remove this overload once it is guaranteed that core modules do not receive State messages
        any more (rather than State2 messages).
#endif
void CoreModule::OnReceive(CoreConnection &, const State &s)
{
    if (mStatevector.Length() > 0)
    {
        // Changing a state's value via mStatevector.PostStateChange()
        // will buffer the change, and postpone it until the next call to
        // mStatevector.CommitStateChanges(). That call happens
        // after arrival of a StateVector message to make sure that
        // changes are not overwritten with the content of the previous
        // state vector when it arrives from the application module.
        mStatevector.PostStateChange(s.Name(), s.Value());
    }
    else
    {
#ifdef TODO
#error Remove saving of State::Kind once the protocol has been modified
#endif // TODO
        int kind = State::StateKind;
        if (mStatelist.Exists(s.Name()))
            kind = mStatelist.ByName(s.Name()).Kind();
        mStatelist.Delete(s.Name());
        State state = s;
        state.SetKind(kind);
        mStatelist.Add(state);
    }
}

void CoreModule::OnReceive(CoreConnection&, const State2& s)
{
    if (mStatevector.Length() > 0)
    {
        // Changing a state's value via mStatevector.PostStateChange()
        // will buffer the change, and postpone it until the next call to
        // mStatevector.CommitStateChanges(). That call happens
        // after arrival of a StateVector message to make sure that
        // changes are not overwritten with the content of the previous
        // state vector when it arrives from the application module.
        mStatevector.PostStateChange(s.Name(), s.Value());
    }
    else
    {
        mStatelist.Delete(s.Name());
        mStatelist.Add(s);
    }
}

void CoreModule::OnReceive(CoreConnection &, const VisSignal &s)
{
    if (s.VisID().Empty())
    {
        mInputSignal.AssignValues(s);
        if (!mFiltersInitialized)
            bcierr << "Unexpected VisSignal message";
        else
            ProcessFilters();
    }
}

void CoreModule::OnReceive(CoreConnection &, const VisSignalProperties &s)
{
    if (s.VisID().Empty())
    {
        if (!mFiltersInitialized)
            InitializeFilterChain(s.SignalProperties());
    }
}

bool CoreModule::OnStateVector(CoreConnection &, std::istream &is)
{
    StateVector buffer(mStatevector);
    buffer.Unserialize(is);
    if (buffer.StateValue("Running") || mStatevector.StateValue("Running"))
    {
        mStatevector = buffer;
        if (IsFirstModule() && !mTerminating)
            ProcessFilters();
    }
    return true;
}

void CoreModule::OnReceive(CoreConnection &, const SysCommand &s)
{
    if (s == SysCommand::EndOfState)
    {
        InitializeCoreConnections();
    }
    else if (s == SysCommand::EndOfParameter)
    {
        mReceivingNextModuleInfo = false;
        mFiltersInitialized = false;
        mActiveResting = false;
    }
    else if (s == SysCommand::Start)
    {
        /* do nothing */
    }
    else if (s == SysCommand::Reset)
    {
        Terminate();
    }
    else
    {
        bcierr << "Unexpected SysCommand";
    }
}

void CoreModule::OnReceive(CoreConnection &, const ProtocolVersion &p)
{
    if (mOperator.Protocol().Provides(ProtocolVersion::NextModuleInfo))
    {
        mReceivingNextModuleInfo = true;
        mNextModule.SetProtocol(p);
    }
}

bool CoreModule::OnSend(CoreConnection &inConnection, const VisSignal &inSignal)
{
    const GenericSignal *pSignal = &inSignal.Signal();
    if (pSignal->Channels() * pSignal->Elements() * sizeof(float) > cLargeSignalSizeBytes)
    {
        if (++mLargeSignals[pSignal] == 2)
        {
            bool share = inConnection.IsLocal();
            share &= inConnection.Protocol().Provides(ProtocolVersion::SharedSignalStorage);
            if (share)
                const_cast<GenericSignal *>(pSignal)->ShareAcrossModules();
        }
    }
    return true;
}
