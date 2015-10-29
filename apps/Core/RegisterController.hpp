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

#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <cstdint>
//#include <Memory.hpp>
#include <vector>

class ControlUnit;

class RegisterController
{
    friend class ControlUnit;
private:
    // GENERAL PURPOSE REGISTERS
    uint16_t ax; // accumulator register.
    uint16_t bx; // base address register.
    uint16_t cx; // count register.
    uint16_t dx; // data register.
    
    uint16_t si; // source index register.
    uint16_t di; // destination index register.
    
    uint16_t bp; // base pointer.
    uint16_t sp; // stack pointer.
    
    // SEGMENT REGISTERS
    uint16_t cs; // points at the segment containing the current program.
    uint16_t ds; // generally points at segment where variables are defined.
    uint16_t es; // extra segment register, it's up to a coder to define its usage.
    uint16_t ss; // points at the segment containing the stack.
    
    // SPECIAL PURPOSE REGISTERS
    uint16_t ip; // the instruction pointer.
    uint16_t flags; // determines the current state of the processor
    
public:
    RegisterController();
    
    uint16_t Get(uint16_t regId) const;
    void Set(uint16_t regId, uint16_t data);
    
    bool GetFlag(uint16_t flagId) const;
    void SetFlag(uint16_t flagId, bool state);
    
    bool CheckCarry(uint32_t x);
    bool CheckAuxiliaryCarry(uint16_t prev, uint16_t _new);
    bool CheckOverflow(uint16_t x, uint16_t y);
    bool CheckZero(uint16_t x);
    bool CheckSign(uint16_t x);
    bool CheckParity(uint16_t x);
private:
    RegisterController(const RegisterController&);
};

#endif /* REGISTERS_HPP */

