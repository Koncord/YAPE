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

#include <gtest/gtest.h>
#include <components/BitFont/BitFont.hpp>
#include <cstring>

class BitFontSerializationTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        bitfont = new BitFont("TestFont.bfnt");

        header.magic = BitFontHeader::MAGIC_VERSIONS::DEFAULT;
        memset(header.name, 0, sizeof(header.name));
        strcpy(header.name, "TestFont");
        header.s_count = 0;
        header.size_height = 8;
        header.size_width = 8;
        bitfont->SetHeader(header);
    }

    virtual void TearDown()
    {
        delete bitfont;
    }
    BitFont *bitfont;
    BitFontHeader header;
};

TEST_F(BitFontSerializationTest, serialization_test_header)
{
    char *serial = new char[sizeof(BitFontHeader)+16];
    ASSERT_NO_THROW(bitfont->serialize(serial));
    delete[] serial;
}

TEST_F(BitFontSerializationTest, serialization_test_shrinkChar)
{
    BitFontChar *chr = bitfont->CreateChar('a');
    bool changed;
    ASSERT_NO_THROW(changed = bitfont->ShrinkChar(chr));
    ASSERT_TRUE(changed);
}

TEST_F(BitFontSerializationTest, serialization_test_charCreation)
{
    BitFontChar *chr = bitfont->CreateChar('a');
    ASSERT_EQ (chr->index, 'a');
    ASSERT_EQ (chr->size, header.size_height * header.size_width);
    ASSERT_NE (chr->data, nullptr) << "chr->data not initialized";

    bitfont->Save();
}

TEST_F(BitFontSerializationTest, deserialization_test)
{
    BitFontChar *chr = bitfont->GetSymbol('a');
    ASSERT_EQ(chr, nullptr);

    bitfont->Load();
    chr = bitfont->GetSymbol('a');
    ASSERT_NE(chr, nullptr);
    ASSERT_EQ(chr->index, 'a');
}
