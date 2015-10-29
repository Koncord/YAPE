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

#include <iostream>

#include <components/Memory/Memory.hpp>

#include "BaseInstruction.hpp"
#include "Environment.hpp"
#include "RegisterController.hpp"


#include "ControlUnit.hpp"

using namespace std;

unordered_map<int, std::unique_ptr<BaseInstruction>> ControlUnit::sInstructions;

ControlUnit::ControlUnit()
{
}

ControlUnit::~ControlUnit()
{

}

void ControlUnit::Step(const LexicalInterpreter& cmd)
{
    auto comm = sInstructions[cmd.GetOpcode()].get();
    if (comm == nullptr)
        throw runtime_error("Unknown opcode: " + to_string(cmd.GetOpcode()));
    
    if (comm->NumArgs() > 0)
    {
        dest = cmd.getDest();
        extra = cmd.getExtra();
        if (!comm->isConstDestinationAllowed() && dest.mod == Operand::Immediate)
            throw runtime_error("destination cannot be constant");
        if (comm->NumArgs() >= 2)
        {
            source = cmd.getSource();

            if (!comm->isConstArgsAllowed() && source.mod == Operand::Immediate)
                throw runtime_error("argument cannot be constant");
            if (!comm->isMemToMemAllowed() && dest.mod == Operand::Memory && source.mod == Operand::Memory)
                throw runtime_error("wrong operation");
            if(comm->NumArgs() == 3)
            {
                source2 = cmd.getSource2();
                if (!comm->isConstArgsAllowed() && source2.mod == Operand::Immediate)
                    throw runtime_error("argument cannot be constant");
                if (!comm->isMemToMemAllowed() && source2.mod == Operand::Memory)
                    throw runtime_error("wrong operation");
            }
        }
    }
    comm->Execute();
}

void ControlUnit::RegisterOp(BaseInstruction *com)
{
    if (com->GetOpcode() == -1)
        throw invalid_argument("wrong opcode");

    if (sInstructions[com->GetOpcode()].get() != nullptr)
        throw invalid_argument("opcode " + std::to_string(com->GetOpcode()) + " is already taken");
    sInstructions[com->GetOpcode()] = unique_ptr<BaseInstruction>(com);
}

void ControlUnit::SetOperandData(uint8_t arg, uint16_t data)
{
    auto reg = Environment::get().GetReg();
    Operand op;
    if(arg == 0)
        op = dest;
    else if(arg == 1)
        op = source;
    else
        op = source2;

    if (op.mod == Operand::Immediate)
        throw runtime_error("cannot be pack constant");
    else if (op.mod == Operand::Register)
        reg->Set(op.data, data);
    else if (op.mod == Operand::Memory)
    {
        const uint16_t segment = reg->Get(Register::DS);
        Environment::get().GetMemory()->SetWord((segment << 4) + op.data, data);
    }
    else
        throw runtime_error("unknown operand");
}

uint16_t ControlUnit::GetOperandData(uint8_t arg) const
{
    const auto& reg = *Environment::get().GetReg();
    Operand op;
    if(arg == 0)
        op = dest;
    else if(arg == 1)
        op = source;
    else
        op = source2;

    uint16_t data;

    if (op.mod == Operand::Immediate)
        data = op.data;
    else if (op.mod == Operand::Register)
        data = reg.Get(op.data);
    else if (op.mod == Operand::Memory)
    {
        const uint16_t segment = reg.Get(Register::DS);
        data = Environment::get().GetMemory()->GetWord((segment << 4) + op.data);
    }
    else
        throw runtime_error("unknown operand: mod(" + to_string(op.mod) + ") data(" + to_string(op.data) + ")");
    return data;
}

uint8_t ControlUnit::GetExtra() const
{
    return extra;
}

Operand ControlUnit::GetOperand(uint8_t arg) const
{
    Operand op;
    if(arg == 0)
        op = dest;
    else if(arg == 1)
        op = source;
    else
        op = source2;
    return op;
}

void ControlUnit::SetOperand(uint8_t arg, Operand op)
{
    if(arg == 0)
        dest = op;
    else if(arg == 1)
        source = op;
    else
        source2 = op;
}

void ControlUnit::PushStack(uint16_t data)
{
    auto reg = Environment::get().GetReg();
    auto mem = Environment::get().GetMemory();
    const uint16_t segment = reg->Get(Register::SS);
    reg->sp -= sizeof(data);
    mem->SetWord((segment << 4) + reg->sp, data);
}

uint16_t ControlUnit::PopStack()
{
    auto reg = Environment::get().GetReg();
    auto mem = Environment::get().GetMemory();
    const uint16_t segment = reg->Get(Register::SS);
    const uint16_t data = mem->GetWord((segment << 4) + reg->sp);
    reg->sp += sizeof(data);
    return data;
}
