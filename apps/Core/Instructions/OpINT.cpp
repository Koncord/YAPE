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

#include "OpINT.hpp"
#include <components/Memory/Memory.hpp>
#include "../ControlUnit.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"

void OpINT::Execute()
{
    auto reg = Environment::get().GetReg();
    auto cu = Environment::get().GetCU();
    auto mem = Environment::get().GetMemory();

    const uint8_t int_num = cu->GetOperandData(0);
    const uint16_t vector_addr = int_num << 2;

    const uint16_t vector_cs = mem->GetWord(vector_addr);
    const uint16_t vector_ip = mem->GetWord(vector_addr + 2);

    cu->PushStack(reg->Get(Register::FLAGS));
    cu->PushStack(reg->Get(Register::CS));
    cu->PushStack(reg->Get(Register::IP));

    reg->Set(Register::CS, vector_cs);
    reg->Set(Register::IP, vector_ip);
}

int OpINT::GetOpcode() const
{
    return Opcode::INT;
}

bool OpINT::isConstDestinationAllowed() const
{
    return true;
}
