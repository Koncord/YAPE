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

#include <stdexcept>

#include "Memory.hpp"
#include <components/Utils/Utils.hpp>
#include <cassert>

using namespace std;

Memory::Memory() : Memory(1024*256) // default 256 KB RAM
{

}

Memory::Memory(unsigned maxSize)
{
    size = maxSize;
    memory = new uint8_t[size]();
    endIter = memory + size;
}


Memory::~Memory()
{
    delete[] memory;
    memory = 0;
    size = 0;
}

uint8_t Memory::GetByte(unsigned pos) const
{
    if(pos >= size)
        throw invalid_argument("end of memory");
    return memory[pos];
    
}

uint16_t Memory::GetWord(unsigned pos) const
{
    if(pos+1 >= size)
        throw invalid_argument("end of memory");
    return Utils::toUShort(reinterpret_cast<const char*>(&memory[pos]));
}

void Memory::Reset()
{
    std::fill(memory, endIter, 0);
}


unsigned Memory::GetSize() const
{
    return size;
}

void Memory::SetByte(unsigned pos, uint8_t byte)
{
    if(pos >= size)
        throw invalid_argument("end of memory");
    memory[pos] = byte;
}

void Memory::SetWord(unsigned pos, uint16_t word)
{
    if(pos+1 >= size)
        throw invalid_argument("end of memory");
    uint16_t *tmp_it = reinterpret_cast<uint16_t*>(&memory[pos]);
    *tmp_it = word;
}


void Memory::Insert(unsigned pos, const uint8_t* array, unsigned arr_size)
{
    if(arr_size + pos > size)
        throw invalid_argument("end of memory");
    
    std::copy(array, array + arr_size, memory + pos);
}

uint8_t *Memory::GetPart(unsigned pos, uint8_t* buffer, unsigned buff_size)
{
    if(buff_size + pos > size)
        throw invalid_argument("end of memory");
    
    const uint8_t *begin_ptr = memory + pos;
    const uint8_t *end_ptr = begin_ptr + buff_size;
    
    return std::copy(begin_ptr, end_ptr, buffer );
}
