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

#ifndef YAPE_BITFONT_HPP
#define YAPE_BITFONT_HPP

#include <cstdint>
#include <unordered_map>
#include <vector>
#include <components/Serialize/Serializable.hpp>

struct BitFontHeader
{
    uint16_t magic;
    char name[16];
    uint8_t size_width;
    uint8_t size_height;
    uint8_t s_count;
    enum MAGIC_VERSIONS
    {
        DEFAULT = 0x0B0F,
    };
    enum SIZE
    {
        FONT8x8,
        FONT8x16
    };
};

struct BitFontChar
{
    uint8_t index;
    uint8_t size;
    uint8_t *data;
};

class BitFont : public Serializable
{
public:
    BitFont(const char* font);
    virtual ~BitFont();

    BitFontChar* GetSymbol(uint8_t sym);
    uint8_t GetWidth();
    uint8_t GetHeight();

    BitFont &Save();
    BitFont &Load();

    BitFontChar *CreateChar(uint8_t index);
    bool ShrinkChar(BitFontChar *chr);

    void SetChar(const BitFontChar& chr);
    void SetHeader(const BitFontHeader& hdr);
    const BitFontHeader& GetHeader() const;

    virtual size_t serialize_size() const;
    virtual void serialize(char *dataOut) const;
    virtual void deserialize(const char *dataIn);

private:
    const char *fontPath;
    BitFontHeader header;
    std::unordered_map<uint8_t, BitFontChar> table;
};

#endif //YAPE_BITFONT_HPP
