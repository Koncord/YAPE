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

#include "../DeviceAPI.hpp"
#include "InternalFunc.hpp"
#include <cstdint>
#include <components/Memory/Memory.hpp>

#define DEVICEAPI(...) c##__VA_ARGS__
#define DEVICEAPI_PREFIX 'c'
#define DEVICECODE(...) __VA_ARGS__

extern "C"
{
    DEVICEVAR char prefix = DEVICEAPI_PREFIX;

    DEVICE uint8_t (*DEVICEAPI(GetIRQ))();
    DEVICE void (*DEVICEAPI(SetIRQ))(uint8_t irq) noexcept;

    DEVICE uint16_t (*DEVICEAPI(GetRegister))(uint16_t regID) noexcept;
    DEVICE void (*DEVICEAPI(SetRegister))(uint16_t regID, uint16_t data) noexcept;

    DEVICE bool (*DEVICEAPI(GetFlag))(uint16_t) noexcept;

    DEVICE uint16_t (*DEVICEAPI(GetMemWord))(uint32_t addr) noexcept;
    DEVICE void (*DEVICEAPI(SetMemWord))(uint16_t regID, uint16_t data) noexcept;
    DEVICE Memory *(*DEVICEAPI(GetMemoryPtr))() noexcept;
    DEVICE void (*DEVICEAPI(SetPortData))(uint16_t port, uint16_t data) noexcept;

    DEVICE int (*DEVICEAPI(internal_PipeSend))(uint32_t id, void *data, uint32_t size) noexcept;
    DEVICE void (*DEVICEAPI(internal_GetPluginSearchNext))(uint32_t *id, char **name) noexcept;
    DEVICE void (*DEVICEAPI(internal_GetPluginSearchReset))() noexcept;

    DEVICE void (*DEVICEAPI(Start))() noexcept;
    DEVICE void (*DEVICEAPI(Quit))() noexcept;
    DEVICE void (*DEVICEAPI(Pause))(bool state) noexcept;
    DEVICE bool (*DEVICEAPI(IsPaused))() noexcept;
    DEVICE void (*DEVICEAPI(Step))() noexcept;
}

uint8_t GetIRQ() noexcept {return DEVICEAPI(GetIRQ)(); }
void  SetIRQ(uint8_t irq) noexcept {return DEVICEAPI(SetIRQ)(irq); }

void SetRegister(uint16_t regID, uint16_t data) noexcept {return DEVICEAPI(SetRegister)(regID, data); }
uint16_t GetRegister(uint16_t regID) noexcept {return DEVICEAPI(GetRegister)(regID); }

bool GetFlag(uint16_t flagID) noexcept {return DEVICEAPI(GetFlag)(flagID); }

void SetMemWord(uint32_t addr, uint16_t data) noexcept {return DEVICEAPI(SetMemWord)(addr, data); }
uint16_t GetMemWord(uint32_t addr) noexcept {return DEVICEAPI(GetMemWord)(addr); }

Memory *GetMemoryPtr() noexcept {return DEVICEAPI(GetMemoryPtr)();}
void SetPortData(uint16_t port, uint16_t data) noexcept {return DEVICEAPI(SetPortData)(port, data);}

int internal_PipeSend(uint32_t id, void *data, uint32_t size) noexcept {return DEVICEAPI(internal_PipeSend)(id, data, size);}
void internal_GetPluginSearchNext(uint32_t *id, char **name) noexcept {return DEVICEAPI(internal_GetPluginSearchNext)(id, name); }
void internal_GetPluginSearchReset() noexcept {return DEVICEAPI(internal_GetPluginSearchReset)();}

void Start() noexcept {return DEVICEAPI(Start)(); }
void Quit() noexcept {return DEVICEAPI(Quit)(); }
void Pause(bool state) noexcept {return DEVICEAPI(Pause)(state); }
bool IsPaused() noexcept {return DEVICEAPI(IsPaused)(); }
void Step() noexcept {return DEVICEAPI(Step)(); }