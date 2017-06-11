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

#include "OpPUSHA.hpp"
#include "../ControlUnit.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"

void OpPUSHA::Execute()
{
    auto cu = Environment::get().GetCU();
    auto reg = Environment::get().GetReg();

    const uint16_t _sp = reg->Get(Register::SP);

    cu->PushStack(reg->Get(Register::AX));
    cu->PushStack(reg->Get(Register::CX));
    cu->PushStack(reg->Get(Register::DX));
    cu->PushStack(reg->Get(Register::BX));
    cu->PushStack(_sp);
    cu->PushStack(reg->Get(Register::BP));
    cu->PushStack(reg->Get(Register::SI));
    cu->PushStack(reg->Get(Register::DI));
}

int OpPUSHA::GetOpcode() const
{
    return Opcode::PUSHA;
}
