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

#include "OpNEG.hpp"

#include "../ControlUnit.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"

void OpNEG::Execute()
{
    auto reg = Environment::get().GetReg();
    auto cu = Environment::get().GetCU();

    const uint16_t ddata = cu->GetOperandData(0);

    uint16_t result = ddata;

    if(ddata != 0)
    {
        result = ~ddata + 1;
        reg->SetFlag(Flag::Carry, true);
    }
    else
        reg->SetFlag(Flag::Carry, false);
    reg->CheckOverflow(ddata, result);
    reg->CheckZero(result);
    reg->CheckSign(result);
    reg->CheckAuxiliaryCarry(ddata, result);
    reg->CheckParity(result);

    cu->SetOperandData(0, result);
}

int OpNEG::GetOpcode() const
{
    return Opcode::NEG;
}
