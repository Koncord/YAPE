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

#ifndef OPCODE_HPP
#define OPCODE_HPP

#include <cstdint>
#include <vector>

namespace Register
{

    enum
    {
        // GENERAL PURPOSE REGISTERS
        AX = 0, // accumulator register.
        BX, // base address register.
        CX, // count register.
        DX, // data register.

        SI, // source index register.
        DI, // destination index register.

        BP, // base pointer.
        SP, // stack pointer.

        // SEGMENT REGISTERS
        CS, // points at the segment containing the current program.
        DS, // generally points at segment where variables are defined.
        ES, // extra segment register, it's up to a coder to define its usage.
        SS, // points at the segment containing the stack.

        // SPECIAL PURPOSE REGISTERS
        IP,    // the instruction pointer.
        FLAGS, // determines the current state of the processor
    };
}
namespace Flag
{

    enum
    {
        Carry = 0,
        Parity = 1,
        Auxiliary = 2,
        Zero = 4,
        Sign = 8,
        Trap = 16,
        Interrupt = 32,
        Direction = 64,
        Overflow = 128
    };

    inline uint16_t Begin()
    {
        return Carry;
    }

    inline uint16_t End()
    {
        return Overflow;
    }
}

struct Operand
{

    enum MOD
    {
        Empty = 0,
        Register = 1,
        Memory = 2,
        Immediate = 3,
    };
    enum EXTRA
    {
        Near = 0,
        Short = 1,
        Far = 2,
    };

    void serialization(std::vector<uint8_t> *serial) const
    {
        serial->push_back(mod);
        serial->push_back(data);
    }
    uint8_t mod;
    uint16_t data;
};

namespace Opcode
{
    enum Opcode
    {
/****** 2 args ******/
        ADD = 0x00, // ADD r/m, r/m
        MOV, // MOV r/m, r/m (m to m not allowed)
        SUB,
        CMP,
        AND,
        XCHG,
        TEST,
        OR,
        XOR,
        SHL,
        ADC,
        SBB,
        SAL = SHL,
        SHR,
        SAR,
        IMUL2,

/****** 1 args ******/
        JMP,
        JNZ,
        JNE = JNZ,
        JZ,
        JE = JZ,
        JC,
        JNAE = JC,
        JB = JC,
        JNC,
        JAE = JNC,
        JNB = JNC,
        JS,
        JNS,
        JO,
        JNO,
        JA,
        JNBE = JA,
        JNA,
        JBE = JNA,
        JP,
        JNP,
        JG,
        JNLE = JG,
        JGE,
        JNL = JGE,
        JL,
        JNGE = JL,
        JLE,
        JNG = JLE,
        JCXZ,
        JECXZ=JCXZ,
        NOT,
        NEG,
        CALL,
        PUSH,
        POP,
        MUL,
        DIV,
        LOOP,
        LOOPNZ,
        LOOPZ,
        RET,    // hack =.
        RETN=RET,
        RETF=RET,
        IRET,
        INC,
        IDIV,
        IMUL1,
        INT,
        DEC,

/****** 0 args ******/
        HLT,
        CLC,
        CLD,
        CLI,
        CMC,
        STC,
        STD,
        STI,
        PUSHA,
        POPA,
        CWD,
        INT3,
        NOP,

/****** 3 args ******/
        IMUL3
    };

    inline uint8_t Args(int opcode)
    {
        if(opcode >= JMP && opcode <= DEC)
            return 1;
        if(opcode >= HLT && opcode <= NOP)
            return 0;
        else if(opcode == IMUL3)
            return 3;
        else
            return 2;
    }
}

#endif /* OPCODE_HPP */
