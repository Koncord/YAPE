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

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP


class Memory;
class RegisterController;
class ControlUnit;


class Environment
{
public:
    Environment();
    virtual ~Environment();
    
    static Environment& get();
    
    RegisterController *GetReg() const;
    void SetReg(RegisterController *);
    
    Memory *GetMemory() const;
    void SetMemory(Memory *mem);
    
    ControlUnit *GetCU() const;
    void SetCU(ControlUnit * cu);
    
    
private:
    Environment(const Environment&);
    Environment& operator= (const Environment&);
    
    RegisterController *mReg;
    Memory *mMem;
    ControlUnit *mCU;
};

#endif /* ENVIRONMENT_HPP */
