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
#include "OpIMUL3.hpp"
#include "../ControlUnit.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"

void OpIMUL3::Execute()
{
    auto reg = Environment::get().GetReg();
    auto cu = Environment::get().GetCU();

    const int16_t sdata = cu->GetOperandData(1);
    const int16_t sdata2 = cu->GetOperandData(2);
    const int32_t result = sdata * sdata2;

    reg->SetFlag(Flag::Carry | Flag::Overflow, result > std::numeric_limits<uint16_t>().max());
    cu->SetOperandData(0, static_cast<uint16_t>(result));
}

int OpIMUL3::GetOpcode() const
{
    return Opcode::IMUL3;
}

bool OpIMUL3::isConstArgsAllowed() const
{
    return false;
}
