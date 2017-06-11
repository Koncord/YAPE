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

#include "OpINT3.hpp"

#include "../ControlUnit.hpp"
#include "../Environment.hpp"

void OpINT3::Execute()
{
    auto cu = Environment::get().GetCU();

    Operand op;
    op.mod = Operand::Immediate;
    op.data = 3;
    cu->SetOperand(0, op);
    OpINT::Execute();
}

int OpINT3::GetOpcode() const
{
    return Opcode::INT3;
}
