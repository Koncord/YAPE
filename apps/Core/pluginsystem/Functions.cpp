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

#include "Plugin.hpp"

#include <components/Memory/Memory.hpp>
#include <vector>
#include "../ControlUnit.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"

void SetRegister(uint16_t regID, uint16_t data) noexcept
{
	auto reg = Environment::get().GetReg();
    reg->Set(regID, data);
}

uint16_t GetRegister(uint16_t regID) noexcept
{
    auto reg = Environment::get().GetReg();
    return reg->Get(regID);
}

bool GetFlag(uint16_t flagID) noexcept
{
    return Environment::get().GetReg()->GetFlag(flagID);
}

void SetMemWord(uint32_t addr, uint16_t data) noexcept
{
    auto mem = Environment::get().GetMemory();
    mem->SetWord(addr, data);
}

uint16_t GetMemWord(uint32_t addr) noexcept
{
    auto mem = Environment::get().GetMemory();
    return mem->GetWord(addr);
}

uint8_t GetIRQ() noexcept
{
	return 0;
}
void  SetIRQ(uint8_t irq) noexcept
{
    (void)(irq);
}

Memory *GetMemoryPtr() noexcept
{
    return Environment::get().GetMemory();
}

void Start() noexcept
{

}

void Pause(bool state) noexcept
{
    if(state)
        Environment::get().GetCU()->Halt();
    else
        Environment::get().GetCU()->Restart();
}

bool IsPaused() noexcept
{
    return Environment::get().GetCU()->isHalted();
}

void Step() noexcept
{

    Environment::get().GetCU()->Step();
}

void Quit() noexcept
{
    exit(0);
}
