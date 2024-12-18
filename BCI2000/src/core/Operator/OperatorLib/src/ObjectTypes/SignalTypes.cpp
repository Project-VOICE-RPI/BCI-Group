////////////////////////////////////////////////////////////////////////////////
// $Id: SignalTypes.cpp 8246 2024-07-09 19:11:31Z mellinger $
// Authors: juergen.mellinger@uni-tuebingen.de
// Description: A signal object type for the script interpreter.
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
#include "SignalTypes.h"

#include "BCIException.h"
#include "CommandInterpreter.h"
#include "Lockable.h"
#include "StateMachine.h"
#include <cstdlib>

namespace Interpreter
{

//// SignalType
Interpreter::SignalType Interpreter::SignalType::sInstance;
const ObjectType::MethodEntry Interpreter::SignalType::sMethodTable[] = 
{
  METHOD(Get),
  METHOD(Freeze),
  METHOD(Thaw), {"Unfreeze", Thaw},
  END
};

bool Interpreter::SignalType::Get(CommandInterpreter &inInterpreter)
{
    WithLock(inInterpreter.StateMachine())
    {
        void* data = inInterpreter.GetAuxData("FrozenSignal");
        const GenericSignal &signal = data ? 
            *static_cast<const GenericSignal*>(data) : 
            inInterpreter.StateMachine().ControlSignal();
        std::string name = inInterpreter.GetToken();
        if (!::stricmp(name.c_str(), "Channels"))
        {
            inInterpreter.Out() << signal.Channels();
        }
        else if (!::stricmp(name.c_str(), "Elements"))
        {
            inInterpreter.Out() << signal.Elements();
        }
        else
        {
            CommandInterpreter::ArgumentList args;
            inInterpreter.ParseArguments(name, args);
            if (::stricmp(name.c_str(), "Signal"))
                throw bciexception << "Use 'Signal' to address the signal";
            if (args.size() != 1 || args[0].size() != 2)
                throw bciexception << "Expected two signal indices";
            int idx1 = ::atoi(args[0][0].c_str()) - 1, idx2 = ::atoi(args[0][1].c_str()) - 1;
            if (idx1 < 0 || idx2 < 0 || idx1 >= signal.Channels() || idx2 >= signal.Elements())
                throw bciexception << "Signal index out of range";
            inInterpreter.Out() << signal(idx1, idx2);
        }
    }
    return true;
}

bool Interpreter::SignalType::Freeze(CommandInterpreter& inInterpreter)
{
    WithLock(inInterpreter.StateMachine())
    {
        void* data = inInterpreter.GetAuxData("FrozenSignal");
        if (data)
            throw bciexception << "Signal is frozen already";

        GenericSignal* pCopy = new GenericSignal(inInterpreter.StateMachine().ControlSignal());
        pCopy->EnsureDeepCopy();
        inInterpreter.SetAuxData("FrozenSignal", pCopy, [](void* data){delete static_cast<GenericSignal*>(data);});
    }
    return true;
}

bool Interpreter::SignalType::Thaw(CommandInterpreter& inInterpreter)
{
    WithLock(inInterpreter.StateMachine())
    {
        void* data = inInterpreter.GetAuxData("FrozenSignal");
        if (!data)
            throw bciexception << "Signal has not been frozen";
        inInterpreter.ClearAuxData("FrozenSignal");
    }
    return true;
}

} // namespace Interpreter