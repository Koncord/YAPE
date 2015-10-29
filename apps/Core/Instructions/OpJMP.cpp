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

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OpJMP.cpp
 * Author: Koncord
 * 
 * Created on 13 сентября 2015 г., 15:43
 */

#include "OpJMP.hpp"

#include "../ControlUnit.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"

void OpJMP::Execute()
{
    auto cu = Environment::get().GetCU();
    auto *reg = Environment::get().GetReg();

    if(Condition())
    {
        const uint16_t offset = cu->GetOperandData(0);

        if(cu->GetExtra() == Operand::Near)
            reg->Set(Register::IP, reg->Get(Register::IP) + offset);
        else
        {
            uint16_t segment = 0;
            if(cu->GetExtra() == Operand::Far)
                segment = cu->GetOperandData(1);

            reg->Set(Register::CS, segment);
            reg->Set(Register::IP, offset);
        }
    }
}

int OpJMP::GetOpcode() const
{
    return Opcode::JMP;
}

bool OpJMP::Condition() const
{
    return 1;
}

bool OpJMP::isConstDestinationAllowed() const
{
    return true;
}
