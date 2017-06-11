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

#include <stdexcept>

#include "BaseInstruction.hpp"
#include "LexicalInterpreter.hpp"

void BaseInstruction::Execute()
{
    throw std::runtime_error("not implemented");
}

int BaseInstruction::GetOpcode() const
{
    return -1;
}

int BaseInstruction::NumArgs() const
{
    return Opcode::Args(GetOpcode());
}

bool BaseInstruction::isConstDestinationAllowed() const
{
    return false;
}

bool BaseInstruction::isConstArgsAllowed() const
{
    return true;
}
bool BaseInstruction::isMemToMemAllowed() const
{
    return false;
}
