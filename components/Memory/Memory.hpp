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

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>


class Memory
{
public:
    Memory();
    Memory(unsigned maxSize);
    virtual ~Memory();
    
    uint8_t GetByte(unsigned pos) const;
    uint16_t GetWord(unsigned pos) const;
    
    void SetByte(unsigned pos, uint8_t byte);
    void SetWord(unsigned pos, uint16_t word);
    
    unsigned GetSize() const;
    void Reset();
    void Insert(unsigned pos, const uint8_t * array, unsigned size);
    uint8_t *GetPart(unsigned pos, uint8_t *buffer, unsigned buff_size);
private:
    Memory(const Memory&);
    uint8_t *memory;
    uint8_t *endIter;
    unsigned size;
};

#endif /* MEMORY_HPP */

