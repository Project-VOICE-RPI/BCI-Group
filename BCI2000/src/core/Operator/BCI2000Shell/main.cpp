////////////////////////////////////////////////////////////////////
// $Id: main.cpp 8268 2024-07-23 16:38:37Z mellinger $
// Author: juergen.mellinger@uni-tuebingen.de
// Description: A script shell that may be used to start up and
//   control BCI2000.
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
////////////////////////////////////////////////////////////////////
#include "BCI2000Connection.h"

#include "EnvVariable.h"
#include "FileUtils.h"
#include "VersionInfo.h"

#include <cstring>
#include <iostream>

static const std::string sShebang = "#!";
#if _WIN32
static const char *sOperatorName = "Operator.exe";
#else
static const char *sOperatorName = "Operator";
#endif
static const std::string sShellName = FileUtils::ExtractBase(FileUtils::ExecutablePath());
static const std::string sPrompt = sShellName + "> ";

int main(int argc, char **argv)
{
    enum
    {
        execute,
        ping,
        command,
        interactive,
        help,
        version
    } mode = execute;
    int idx = 1;
    while (idx < argc && *argv[idx] == '-')
    {
        if (!::strcmp(argv[idx], "-c"))
            mode = command;
        else if (!::strcmp(argv[idx], "-i"))
            mode = interactive;
        else if (!::strcmp(argv[idx], "-p") || !::stricmp(argv[idx], "--ping"))
            mode = ping;
        else if (!::strcmp(argv[idx], "-h") || !::stricmp(argv[idx], "--help"))
            mode = help;
        else if (!::strcmp(argv[idx], "-v") || !::stricmp(argv[idx], "--version"))
            mode = version;
        ++idx;
    }
    if (mode == execute && idx >= argc)
        mode = interactive;
    std::string script = "";
    if (mode == execute)
        script = FileUtils::AbsolutePath(argv[idx++]);

    std::string additionalArgs, telnetAddress;
    EnvVariable::Get("BCI2000TelnetAddress", telnetAddress);
    while (idx < argc && argv[idx] != sShebang)
    {
        if (!::stricmp(argv[idx], "--Telnet") && idx++ < argc)
        {
            telnetAddress = argv[idx];
        }
        else
        {
            std::string arg = argv[idx++];
            if (mode != command && arg.find('\"') == std::string::npos)
                arg = "\"" + arg + "\"";
            additionalArgs += " ";
            additionalArgs += arg;
        }
    }
    struct : BCI2000Connection
    {
        bool OnInput(std::string &s)
        {
            return !!std::getline(std::cin, s);
        }
        bool OnOutput(const std::string &s)
        {
            return !!(std::cout << s << std::endl);
        }
    } bci;
    bci.OperatorPath("");
    bci.TelnetAddress(telnetAddress);
    bool alreadyRunning = bci.Connect();
    if (mode == ping)
        return (alreadyRunning ? 0 : 1);
    if (!alreadyRunning)
    {
        if (!bci.Run(FileUtils::InstallationDirectory() + sOperatorName, additionalArgs) || !bci.Connect())
        {
            std::cerr << bci.Result() << std::endl;
            return -1;
        }
    }
    bci.Execute("cd \"" + FileUtils::WorkingDirectory() + "\"", 0);
    int exitCode = 0;
    if (mode == interactive)
    {
        std::cout << sPrompt << std::flush;
        std::string line;
        while (bci.Connected() && std::getline(std::cin, line))
        {
            if (bci.Connected() && bci.Execute(line, &exitCode))
            {
                if (!bci.Result().empty())
                    std::cerr << bci.Result() << '\n';
            }
            else
            {
                std::cout << "[Lost connection to Operator module]" << std::endl;
            }
            if (bci.Connected())
                std::cout << sPrompt << std::flush;
        }
    }
    else
    {
        switch (mode)
        {
        case help:
            script = "help";
            break;
        case version:
            std::cout << sShellName << " version:\n";
            VersionInfo::Current.InsertInto(std::cout, true);
            std::cout << "Connected to:\n";
            script = "get system version";
            break;
        case command:
            script = additionalArgs;
            break;
        case execute:
            script = "execute script \"" + script + "\"" + additionalArgs;
            break;
        default:
            ;
        }
        bci.Execute(script, &exitCode);
        if (!bci.Result().empty())
            std::cerr << bci.Result() << '\n';
    }
    return exitCode;
}
