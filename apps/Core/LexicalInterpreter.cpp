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

#include "LexicalInterpreter.hpp"

#include <components/Utils/Utils.hpp>
#include <stdexcept>

using namespace std;

LexicalInterpreter::LexicalInterpreter(const std::string& op)
{
    parse(op);
}

LexicalInterpreter::LexicalInterpreter(const std::vector<uint8_t>& op)
{
    parse(string(op.begin(), op.end())); // temp hack =.
}

void LexicalInterpreter::parse(const std::string& op)
{

    opcode = op[0];
    args = Opcode::Args(opcode);
    if(args > 0)
    {
        dest.mod = op[1] & 0x3; // first mod
        dest.data = Utils::toUShort(&op[2]);
        if(args >= 2)
        {
            source.mod = (op[1] >> 2) & 0x3; // second mod
            source.data = Utils::toUShort(&op[4]);
        }
        extra = (op[1] >> 4) & 0xF;
    }
    if(args == 3)
    {
        source2.mod = (op[1] >> 4) & 0x3;
        source2.data = Utils::toUShort(&op[6]);
        extra = (op[1] >> 6) & 0x3;
    }
}


int LexicalInterpreter::GetOpcode() const
{
    return opcode;
}

Operand LexicalInterpreter::getDest() const
{
    return dest;
}

Operand LexicalInterpreter::getSource() const
{
    return source;
}

Operand LexicalInterpreter::getSource2() const
{
    return source2;
}


uint8_t LexicalInterpreter::getExtra() const
{
    return extra;
}

void LexicalInterpreter::setDest(Operand operand)
{
    dest = operand;
}

void LexicalInterpreter::setSource(Operand operand)
{
    source = operand;
}

void LexicalInterpreter::setSource2(Operand operand)
{
    source2 = operand;
}

void LexicalInterpreter::setExtra(uint8_t extra)
{
    this->extra = extra;
}


const vector<uint8_t> LexicalInterpreter::serialization() const
{
    vector<uint8_t> serial;
    serial.push_back(opcode);
    if(args > 0)
    {
        //serial.push_back()
        dest.serialization(&serial);
        if(args >= 2)
            source.serialization(&serial);
        if(args == 3)
            source2.serialization(&serial);
    }
    return serial;
}
