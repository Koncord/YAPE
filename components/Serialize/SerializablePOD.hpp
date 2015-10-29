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

#ifndef YAPE_SERIALIZABLEPOD_HPP
#define YAPE_SERIALIZABLEPOD_HPP

#include <cstring>

template <typename POD>
class SerializablePOD
{
public:
    static size_t serialize_size(POD str)
    {
        (void)(str);
        return sizeof(POD);
    }
    static char* serialize( char* target, POD value )
    {
        memcpy(target, &value, serialize_size(value) );
        return target+serialize_size(value);
    }
    static const char* deserialize( const char* source, POD& target )
    {
        memcpy( &target, source, serialize_size(target) );
        return source + serialize_size(target);
    }
};

/*template<>
size_t SerializablePOD<char*>::serialize_size(char* str)
{
    return sizeof(size_t) + strlen(str);
}

template<>
const char* SerializablePOD<char*>::deserialize( const char* source, char*& target )
{
    size_t length;
    memcpy( &length, source, sizeof(size_t) );
    memcpy( &target, source + sizeof(size_t), length );
    return source + sizeof(size_t) + length;
}*/

#endif //YAPE_SERIALIZABLEPOD_HPP
