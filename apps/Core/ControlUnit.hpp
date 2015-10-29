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

#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <unordered_map>
#include <memory>
#include <cstdint>
#include <components/Opcode/Opcode.hpp>

#include "LexicalInterpreter.hpp"

class BaseInstruction;
class IOSystem;

class ControlUnit
{
    friend class IOSystem;
public:
    ControlUnit();
    virtual ~ControlUnit();
    void Step(const LexicalInterpreter& cmd);
    static void RegisterOp(BaseInstruction *instruction);
    
    uint16_t GetOperandData(uint8_t arg) const;
    void SetOperandData(uint8_t arg, uint16_t data);

    uint8_t GetExtra() const;

    Operand GetOperand(uint8_t arg) const;
    void SetOperand(uint8_t arg, Operand op);


    void PushStack(uint16_t data);
    uint16_t PopStack();

private:
    ControlUnit(ControlUnit&);
    static std::unordered_map< int, std::unique_ptr<BaseInstruction> > sInstructions;
    Operand dest, source, source2;
    uint8_t extra;
    uint8_t flagMIO;
};

#endif /* MACHINE_HPP */

