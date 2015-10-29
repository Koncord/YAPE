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

#include "OpADC.hpp"
#include "../ControlUnit.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"

void OpADC::Execute()
{
    auto reg = Environment::get().GetReg();
    auto cu = Environment::get().GetCU();

    const uint16_t ddata = cu->GetOperandData(0);
    const uint16_t sdata = cu->GetOperandData(1);
    const uint16_t result = ddata + sdata + reg->GetFlag(Flag::Carry);

    reg->SetFlag(Flag::Overflow, static_cast<uint32_t> (ddata + sdata) != result);
    reg->CheckCarry(ddata);
    reg->CheckZero(result);
    reg->CheckSign(result);
    reg->CheckAuxiliaryCarry(ddata, result);
    reg->CheckParity(result);

    cu->SetOperandData(0, result);
}

int OpADC::GetOpcode() const
{
    return Opcode::ADC;
}
