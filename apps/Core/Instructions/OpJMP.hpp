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

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OpJMP.hpp
 * Author: Koncord
 *
 * Created on 13 сентября 2015 г., 15:43
 */

#ifndef OPJMP_HPP
#define OPJMP_HPP

#include "../BaseInstruction.hpp"

class OpJMP : public BaseInstruction
{
public:
    void Execute() final;
    int GetOpcode() const override;
    virtual bool Condition() const;
    bool isConstDestinationAllowed() const override;

};


#endif /* OPJMP_HPP */

