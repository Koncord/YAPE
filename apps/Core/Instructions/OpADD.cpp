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
 * File:   OpTEST.cpp
 * Author: Koncord
 * 
 * Created on 10 сентября 2015 г., 8:21
 */

#include "OpADD.hpp"
#include "../ControlUnit.hpp"
#include "../RegisterController.hpp"
#include "../Environment.hpp"

void OpADD::Execute()
{
    auto reg = Environment::get().GetReg();
    auto cu = Environment::get().GetCU();
    
    const uint16_t ddata = cu->GetOperandData(0);
    const uint16_t sdata = cu->GetOperandData(1);
    const uint16_t result = ddata + sdata;

    reg->SetFlag(Flag::Overflow, static_cast<uint32_t> (ddata + sdata) != result);
    reg->CheckCarry(ddata);
    reg->CheckZero(result);
    reg->CheckSign(result);
    reg->CheckAuxiliaryCarry(ddata, result);
    reg->CheckParity(result);

    cu->SetOperandData(0, result);
}

int OpADD::GetOpcode() const
{
    return Opcode::ADD;
}
