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

#include "OpPUSH.hpp"
#include "../ControlUnit.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"

void OpPUSH::Execute()
{
    auto cu = Environment::get().GetCU();

    const uint16_t ddata = cu->GetOperandData(0);

    cu->PushStack(ddata);
}

int OpPUSH::GetOpcode() const
{
    return Opcode::PUSH;
}

bool OpPUSH::isConstDestinationAllowed() const
{
    return true;
}
