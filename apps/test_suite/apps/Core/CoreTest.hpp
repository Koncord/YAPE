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

#ifndef YAPE_CORETEST_HPP
#define YAPE_CORETEST_HPP

#include <gtest/gtest.h>
#include "opcodes.hpp"
#include <components/Memory/Memory.hpp>
#include <apps/Core/RegisterController.hpp>
#include <apps/Core/ControlUnit.hpp>
#include <apps/Core/Environment.hpp>
#include <apps/Core/BaseInstructions.hpp>

class CoreTest : public ::testing::Test
{
protected:
    CoreTest()
    {
        InstructionSet_base();
    }
    ~CoreTest()
    {
        ControlUnit::FreeOps();
    }
    virtual void SetUp()
    {
        Environment::get().SetMemory(new Memory);
        Environment::get().SetReg(new RegisterController);
        Environment::get().SetCU(new ControlUnit);

        machine = Environment::get().GetCU();
        reg = Environment::get().GetReg();
        mem = Environment::get().GetMemory();

        // default segment initialize
        reg->Set(Register::SS, 0);
        reg->Set(Register::ES, 0);
        reg->Set(Register::CS, 0);
        reg->Set(Register::DS, 0);

        reg->Set(Register::IP, 0); // instruction pointer
        reg->Set(Register::BP, 0); // base pointer
        reg->Set(Register::SP, 0xFFFE); // stack pointer

        pos = machine->GetNextInstructionAddr();
    }

    virtual void TearDown()
    {
        delete environment;
        environment = 0;
        machine = 0;
        reg = 0;
        mem = 0;
    }

    void DoProgram()
    {
        while (!DoStep())
        {
            // empty while
        }
    }

    bool DoStep()
    {
        if(machine->isHalted())
            return true;

        const uint32_t cur_pos = machine->GetNextInstructionAddr();
        const uint16_t cmd_len = LexicalInterpreter::length(mem->GetByte(cur_pos));

        if(reg->Get(Register::IP) + cmd_len >= mem->GetSize())
            throw;

        std::vector<uint8_t> cmd(cmd_len);
        mem->GetPart(cur_pos, &cmd[0], cur_pos + cmd_len);

        machine->Step(cmd);

        return false;
    }

    Environment *environment;
    ControlUnit *machine;
    RegisterController *reg;
    Memory *mem;
    uint16_t pos;
};

#endif // YAPE_CORETEST_HPP
