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

#include "Environment.hpp"
#include <cassert>

#include <components/Memory/Memory.hpp>
#include "RegisterController.hpp"
#include "ControlUnit.hpp"

Environment::Environment() : mReg(0), mMem(0), mCU(0)
{
}

Environment::~Environment()
{
}

Environment& Environment::get()
{
    static Environment env;
    return env;
}

RegisterController* Environment::GetReg() const
{
    assert(mReg);
    return mReg;
}

void Environment::SetReg(RegisterController *con)
{
    mReg = con;
}

Memory* Environment::GetMemory() const
{
    assert(mMem);
    return mMem;
}

void Environment::SetMemory(Memory* mem)
{
    mMem = mem;
}

ControlUnit* Environment::GetCU() const
{
    assert(mCU);
    return mCU;
}

void Environment::SetCU(ControlUnit* cu)
{
    mCU = cu;
}