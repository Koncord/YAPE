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

#include "CoreTest.hpp"


TEST_F(CoreTest, test_adding)
{
    add(mem, &pos, 0x3);
    add(mem, &pos, 0x3);
    hlt(mem, &pos);
    DoProgram();
    ASSERT_EQ(reg->Get(Register::AX), 0x6);
}

TEST_F(CoreTest, test_idiv)
{
    mova(mem, &pos, 5);
    movb(mem, &pos, -2);
    idiv(mem, &pos, Register::BX);
    hlt(mem, &pos);
    DoProgram();
    short quotient = reg->Get(Register::AX);
    short remainder = reg->Get(Register::DX);
    ASSERT_EQ(quotient, -2);
    ASSERT_EQ(remainder, 1);
}

TEST_F(CoreTest, test_imul)
{
    mova(mem, &pos, 2);
    movb(mem, &pos, 4);
    imul(mem, &pos, Register::BX);
    hlt(mem, &pos);
    DoProgram();
    ASSERT_EQ(reg->Get(Register::AX), 0x8);
    ASSERT_EQ(reg->Get(Register::DX), 0);
}

TEST_F(CoreTest, test_jnz)
{
    add(mem, &pos, 5);
    const int label = pos;
    sub(mem, &pos, 1);
    jnz(mem, &pos, label);
    hlt(mem, &pos);

    DoStep(); // add ax,5
    ASSERT_EQ(reg->Get(Register::AX), 0x5);

    for(int i = 8; i > 0; i--)
        DoStep(); // repeating sub-jnz 4 times

    ASSERT_EQ(reg->Get(Register::AX), 1);

    ASSERT_EQ(reg->Get(Register::IP), label); // next step sub
    ASSERT_EQ(machine->isHalted(), false); // the halt instruction can not to be invoked after 9 steps

    for(int i = 3; i > 0; i--)
        DoStep(); // sub, jnz, hlt

    ASSERT_EQ(reg->Get(Register::AX), 0x0);
    ASSERT_EQ(machine->isHalted(), true);
}