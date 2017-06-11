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

#include "OpSHL.hpp"
#include "../ControlUnit.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"
#include <stdexcept>

void OpSHL::Execute()
{
    throw std::runtime_error("rewrite this");
    auto cu = Environment::get().GetCU();
    auto reg = Environment::get().GetReg();

    const uint16_t ddata = cu->GetOperandData(0);
    const uint16_t sdata = cu->GetOperandData(1);
    uint16_t result = ddata;
    for(int i = 0; i != sdata; i++)
    {
        reg->SetFlag(Flag::Carry, static_cast<bool>((result >> 15) & 1));
        result = ddata << 1;
    }

    reg->CheckOverflow(ddata, sdata);
    reg->CheckZero(result);
    reg->CheckSign(result);
    reg->CheckAuxiliaryCarry(ddata, result);
    reg->CheckParity(result);

    cu->SetOperandData(0, result);
}

int OpSHL::GetOpcode() const
{
    return Opcode::SHL;
}
