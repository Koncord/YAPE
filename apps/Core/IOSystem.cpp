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

#include "IOSystem.hpp"
#include "ControlUnit.hpp"
#include "Environment.hpp"

bool IOSystem::GetIOFlag() const
{
    auto cu = Environment::get().GetCU();
    return cu->flagMIO;
}

void IOSystem::SetIOFlag(bool flag) const
{
    auto cu = Environment::get().GetCU();
    cu->flagMIO = flag;
}

bool IOSystem::ReadWord(uint8_t portAddr, uint16_t *word)
{
    (void)(portAddr);
    (void)(word);
    return false;
}

bool IOSystem::SendWord(uint8_t portAddr, uint16_t word)
{
    (void)(portAddr);
    (void)(word);
    auto cu = Environment::get().GetCU();
    (void)(cu);
    SetIOFlag(true);

    SetIOFlag(false);
    return false;
}
