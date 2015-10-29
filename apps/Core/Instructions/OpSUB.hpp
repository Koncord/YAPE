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
 * File:   opSUB.hpp
 * Author: Koncord
 *
 * Created on 13 сентября 2015 г., 15:24
 */

#ifndef OPSUB_HPP
#define OPSUB_HPP

#include "../BaseInstruction.hpp"

class OpSUB : public BaseInstruction
{
public:
    void Execute() override;
    int GetOpcode() const override;
};

#endif /* OPSUB_HPP */

