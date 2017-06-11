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

#include "OpPOPA.hpp"

#include "../ControlUnit.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"

void OpPOPA::Execute()
{
    auto cu = Environment::get().GetCU();
    auto reg = Environment::get().GetReg();

    reg->Set(Register::DI, cu->PopStack());
    reg->Set(Register::SI, cu->PopStack());
    reg->Set(Register::BP, cu->PopStack());
    const uint16_t _sp = cu->PopStack();
    reg->Set(Register::BX, cu->PopStack());
    reg->Set(Register::DX, cu->PopStack());
    reg->Set(Register::CX, cu->PopStack());
    reg->Set(Register::AX, cu->PopStack());
    reg->Set(Register::SP, _sp);
}

int OpPOPA::GetOpcode() const
{
    return Opcode::POPA;
}
