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

#ifndef YAPE_FUNCTIONS_HPP
#define YAPE_FUNCTIONS_HPP

#include <cstdint>

class Memory;

void SetRegister(uint16_t regID, uint16_t data) noexcept;
uint16_t GetRegister(uint16_t regID) noexcept;

void SetMemWord(uint32_t addr, uint16_t data) noexcept;
uint16_t GetMemWord(uint32_t addr) noexcept;

uint8_t GetIRQ() noexcept;
void  SetIRQ(uint8_t irq) noexcept;

Memory *GetMemoryPtr() noexcept;
void SetPortData(uint16_t port, uint16_t data) noexcept;


#endif // YAPE_FUNCTIONS_HPP
