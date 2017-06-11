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

#ifndef YAPE_OPCODES_HPP
#define YAPE_OPCODES_HPP

#include <components/Memory/Memory.hpp>
#include <components/Opcode/Opcode.hpp>


void ops(Memory *prog, uint16_t *pos, uint8_t mod1, uint16_t data1, uint8_t mod2 = 0, uint16_t data2 = 0, uint8_t extra = 0)
{
    prog->SetByte(*pos, (extra << 4) | (mod2 << 2) | mod1);
    *pos += 1;
    prog->SetWord(*pos, data1);
    *pos += 2;
    if(mod2 != 0)
    {
        prog->SetWord(*pos, data2);
        *pos += 2;
    }
}

void ops3(Memory *prog, uint16_t *pos, uint8_t mod1, uint16_t data1, uint8_t mod2 = 0, uint16_t data2 = 0, uint8_t mod3 = 0, uint16_t data3 = 0, uint8_t extra = 0)
{
    prog->SetByte(*pos, (extra << 6)| (mod2 << 4) | (mod2 << 2) | mod1);
    *pos += 1;
    if(mod1 != 0)
    {
        prog->SetWord(*pos, data1);
        *pos += 2;
        if(mod2 != 0)
        {
            prog->SetWord(*pos, data2);
            *pos += 2;
            if(mod3 != 0)
            {
                prog->SetWord(*pos, data3);
                *pos += 2;
            }
        }
    }
    
}

void _instr(Memory *prog, uint16_t *pos, uint8_t opcode, Operand *op1 = 0, Operand *op2 = 0, Operand *op3 = 0, uint8_t extra = 0)
{
    prog->SetByte(*pos, op);
    *pos += 1;
    if(op1 != 0)
    {
        if(op2 != 0)
        {
            if(op3 != 0)
                ops3(prog, pos, op1->mod, op1->data, op2->mod, op2->data, op3->mod, op3->data extra);
            else
                ops(prog, pos, op1->mod, op1->data, op2->mod, op2->data, extra);
        }
        else
            ops(prog, pos, op1->mod, op1->data, 0, 0, extra);
    }
    
}

void add(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::ADD);
    *pos += 1;
    ops(prog, pos, Operand::Register, Register::AX, Operand::Immediate, value);
}

void mova(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::MOV);
    *pos += 1;
    ops(prog, pos, Operand::Register, Register::AX, Operand::Immediate, value);
}

void movb(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::MOV);
    *pos += 1;
    ops(prog, pos, Operand::Register, Register::BX, Operand::Immediate, value);
}

void movc(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::MOV);
    *pos += 1;
    ops(prog, pos, Operand::Register, Register::CX, Operand::Immediate, value);
}

void sub(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::SUB);
    *pos += 1;
    ops(prog, pos, Operand::Register, Register::AX, Operand::Immediate, value);
}

void jnz(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::JNZ);
    *pos += 1;
    ops(prog, pos, Operand::Immediate, value, 0, 0, Operand::EXTRA::Short);
}

void div(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::DIV);
    *pos += 1;
    ops(prog, pos, Operand::Register, value);
}

void idiv(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::IDIV);
    *pos += 1;
    ops(prog, pos, Operand::Register, value);
}

void imul(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::IMUL1);
    *pos += 1;
    ops(prog, pos, Operand::Register, value);
}

void imul3(Memory *prog, uint16_t *pos)
{
    prog->SetByte(*pos, Opcode::IMUL3);
    *pos += 1;
    ops3(prog, pos, Operand::Register, Register::AX, Operand::Register, Register::BX, Operand::Register, Register::CX);
}

void hlt(Memory *prog, uint16_t *pos)
{
    prog->SetByte(*pos, Opcode::HLT);
    *pos += 1;
}

#endif // YAPE_OPCODES_HPP
