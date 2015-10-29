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

#ifndef YAPE_SERIALIZABLE_HPP
#define YAPE_SERIALIZABLE_HPP

#include<cstddef>

#include "SerializablePOD.hpp"

class Serializable
{
public:
    virtual size_t serialize_size() const = 0;
    virtual void serialize(char* dataOut) const = 0;
    virtual void deserialize(const char* dataIn) = 0;
};


#endif //YAPE_SERIALIZABLE_HPP
