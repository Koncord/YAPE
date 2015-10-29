/*
 *
 *  Copyright (c) 2015 Stanislav Zhukov (koncord@rwa.su)
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#include "OpLOOPNZ.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"


bool OpLOOPNZ::Condition() const
{
    auto reg = Environment::get().GetReg();
    const uint16_t _cx = reg->Get(Register::CX);

    if(_cx == 0 || reg->GetFlag(Flag::Zero))
        return false;
    else
    {
        reg->Set(Register::CX, _cx - 1);
        return true;
    }
}

int OpLOOPNZ::GetOpcode() const
{
    return Opcode::LOOPNZ;
}
