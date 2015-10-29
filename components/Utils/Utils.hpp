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

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <type_traits>

namespace Utils
{

    template<size_t N>
    constexpr unsigned int hash(const char(&str)[N], size_t I = N)
    {
        return (I == 1 ? ((2166136261u ^ str[0]) * 16777619u) : ((hash(str, I - 1) ^ str[I - 1]) * 16777619u));
    }

    inline unsigned int hash(const char* str, std::size_t I)
    {
        return (I == 1 ? ((2166136261u ^ str[0]) * 16777619u) : ((hash(str, I - 1) ^ str[I - 1]) * 16777619u));
    }

    template<size_t N>
    static constexpr unsigned int StringHash(const char(&str)[N])
    {
        return hash(str);
    }

    inline unsigned short toUShort(const char *op)
    {
        return *(static_cast<const unsigned short*> (static_cast<const void*> (op)));
    }

    /**
     * \brief re-map value from one range to another range
     * \param value the number to map
     * \param inMax the upper bound of the current value range
     * \param outMax the upper bound of the new value range
     * \return new value
     */
    inline int map(int value, int inMax, int outMax)
    {
        return value * outMax / inMax;
    }
}

#endif /* UTILS_HPP */

