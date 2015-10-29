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

#ifndef LEXICALINTERPRETER_HPP
#define LEXICALINTERPRETER_HPP

#include <vector>
#include <string>
#include <cstdint>

#include <components/Opcode/Opcode.hpp>

class LexicalInterpreter
{
    uint8_t opcode;
    Operand dest, source, source2;
    uint8_t extra;
    int args;
public:

    LexicalInterpreter(const std::string& op);
    LexicalInterpreter(const std::vector<uint8_t>& op);
    
    void parse(const std::string& op);

    Operand getDest() const;
    Operand getSource() const;
    Operand getSource2() const;
    uint8_t getExtra() const;

    void setDest(Operand operand);
    void setSource(Operand operand);
    void setSource2(Operand operand);
    void setExtra(uint8_t extra);

    int GetOpcode() const;
    const std::vector<uint8_t> serialization() const;
    
    static inline uint8_t ArgLength() { return 2; }
    static inline uint8_t CmdLength() { return 1; }
};

#endif /* LEXICALINTERPRETER_HPP */

