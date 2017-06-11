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

#ifndef YAPE_PIPEAPI_HPP
#define YAPE_PIPEAPI_HPP

#include <cstdint>
#include <string>
#include <unordered_map>

class PipeAPI
{
public:
    enum SenderRetCode
    {
        LOOPID = -4,
        UNKNOWNID = -3,
        BUFFEROVERFLOW = -2,
        ERROR = -1,
        OK = 0,
        RETN = 1,
    };
    using Plugin = std::unordered_map<uint32_t, std::string>;

    PipeAPI();
    uint32_t IDByName(const std::string& pluginName);
    const std::string& NameByID(uint32_t id);

    /**
     * \brief Send data to other plugins
     * \param id reciever
     * \param data data sent data
     * \param size size of sent data
     **/
    int Send(uint32_t id, void *data, uint32_t size);

    /**
     * \brief Send data to other plugins
     * \param plugin reciever
     * \param data data sent data
     * \param size size of sent data
     **/
    int Send(const std::string &plugin, void *data, uint32_t size);

private:
    Plugin plugins;
};


#endif //YAPE_PIPEAPI_HPP
