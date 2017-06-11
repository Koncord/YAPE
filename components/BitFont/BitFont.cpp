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

#include "BitFont.hpp"
#include <fstream>
#include <iostream>

using namespace std;

BitFont::BitFont(const char *font) : fontPath(font)
{

}

BitFontChar* BitFont::GetSymbol(uint8_t sym)
{
    if(table.find(sym) != table.end())
        return &table[sym];
    else
        return nullptr;
}

uint8_t BitFont::GetWidth()
{
    return header.size_width;
}

uint8_t BitFont::GetHeight()
{
    return header.size_height;
}

BitFont::~BitFont()
{
    for(auto sym : table)
        delete[] sym.second.data;
}

size_t BitFont::serialize_size() const
{
    size_t size = 0;
    for(auto e : table)
    {
        size += e.second.size + 2;
    }
    return sizeof(BitFontHeader) + size;
}

void BitFont::serialize(char *dataOut) const
{
    char *p = dataOut;
    p = SerializablePOD<BitFontHeader>::serialize(p, header);
    for(const auto& element : table)
    {

        p = SerializablePOD<uint8_t>::serialize(p, element.second.index);
        p = SerializablePOD<uint8_t>::serialize(p, element.second.size);
        for(int i = 0; i < element.second.size;i++)
            p = SerializablePOD<uint8_t>::serialize(p, element.second.data[i]);
    }
}

void BitFont::deserialize(const char *dataIn)
{
    dataIn = SerializablePOD<BitFontHeader>::deserialize(dataIn, header);
    if(header.magic != BitFontHeader::MAGIC_VERSIONS::DEFAULT)
        throw runtime_error("unknown font format");
    for(int i = 0; i < header.s_count; i++)
    {
        BitFontChar element;
        dataIn = SerializablePOD<uint8_t>::deserialize(dataIn, element.index);
        dataIn = SerializablePOD<uint8_t>::deserialize(dataIn, element.size);
        element.data = new uint8_t[element.size];
        for(int i = 0; i < element.size;i++)
            dataIn = SerializablePOD<uint8_t>::deserialize(dataIn, element.data[i]);
        table[element.index] = element;
    }
}

void BitFont::SetChar(const BitFontChar &chr)
{
    table[chr.index] = chr;
}

void BitFont::SetHeader(const BitFontHeader &hdr)
{
    header = hdr;
}

BitFontChar *BitFont::CreateChar(uint8_t index)
{
    if(table[index].size)
        delete[] table[index].data;
    else
        header.s_count++;
    table[index].index = index;
    table[index].size = header.size_height * header.size_width;
    table[index].data = new uint8_t[table[index].size];
    memset(table[index].data, 0, table[index].size);

    return &table[index];
}

bool BitFont::ShrinkChar(BitFontChar *chr)
{
    bool ok = false;
    uint8_t i;
    for(i = chr->size - 1; i != 0; i--)
        if(chr->data[i] != 0)
            break;

    uint8_t *newChr = nullptr;
    if(i)
    {
        newChr = new uint8_t[i];
        copy(chr->data, chr->data + i, newChr);
    }

    delete chr->data;
    chr->data = newChr;
    if(chr->size != i + 1)
        ok = true;
    chr->size = i;
    return ok;
}

BitFont &BitFont::Save()
{
    ofstream file(fontPath, ofstream::binary);
    vector<char> tmp;
    size_t size = serialize_size();
    tmp.resize(size);

    serialize(&tmp[0]);

    file.write(&tmp[0], size);

    return *this;
}

BitFont &BitFont::Load()
{
    ifstream file(fontPath, ifstream::binary);
    if(!file.is_open())
        throw invalid_argument("Font not found or permissions denied");

    if (!file.eof() && !file.fail())
    {
        vector<char> tmp;
        file.seekg(0, std::ios_base::end);
        std::streampos fileSize = file.tellg();
        tmp.resize(static_cast<unsigned long>(fileSize));

        file.seekg(0, std::ios_base::beg);
        file.read(&tmp[0], fileSize);

        deserialize(&tmp[0]);
    }

    return *this;
}

const BitFontHeader &BitFont::GetHeader() const
{
    return header;
}
