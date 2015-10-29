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

#include "OpDIV.hpp"
#include "../ControlUnit.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"

void OpDIV::Execute() // TODO: Need interrupts.
{
    auto reg = Environment::get().GetReg();
    auto cu = Environment::get().GetCU();

    const uint16_t ddata = reg->Get(Register::AX);
    const uint16_t sdata = cu->GetOperandData(0);

    reg->Set(Register::DX, static_cast<uint16_t>(ddata % sdata));
    reg->Set(Register::AX, static_cast<uint16_t>(ddata / sdata));
}

int OpDIV::GetOpcode() const
{
    return Opcode::DIV;
}
