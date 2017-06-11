/*
 *
 *  Copyright (c) 2015-2017 Stanislav Zhukov
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

#include <limits>
#include "OpMUL.hpp"
#include "../ControlUnit.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"

void OpMUL::Execute()
{
    auto reg = Environment::get().GetReg();
    auto cu = Environment::get().GetCU();

    const uint16_t ddata =reg->Get(Register::AX);
    const uint16_t sdata = cu->GetOperandData(1);
    const uint32_t result = ddata * sdata;

    bool flags = false;

    if(result > std::numeric_limits<uint16_t>().max())
    {
        flags = true;
        reg->Set(Register::DX, static_cast<uint16_t>(result >> 16));
    }
    reg->SetFlag(Flag::Carry | Flag::Overflow, flags);
    reg->Set(Register::AX, static_cast<uint16_t>(result));
}

int OpMUL::GetOpcode() const
{
    return Opcode::MUL;
}
