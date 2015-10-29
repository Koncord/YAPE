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

#include "OpCMP.hpp"
#include "../ControlUnit.hpp"
#include "../Environment.hpp"

using namespace std;

void OpCMP::Execute()
{
    auto cu = Environment::get().GetCU();
    uint16_t data = cu->GetOperandData(0);

    OpSUB::Execute();

    cu->SetOperandData(0, data);
}

int OpCMP::GetOpcode() const
{
    return Opcode::CMP;
}
