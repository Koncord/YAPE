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

#include "../PipeAPI.hpp"
#include "InternalFunc.hpp"
#include "../PluginInfo.hpp"

#include <algorithm>

using namespace std;

uint32_t PipeAPI::IDByName(const string& pluginName)
{
    Plugin::const_iterator iter = find_if(plugins.begin(), plugins.end(), [pluginName](const Plugin::value_type& vt) {
       return vt.second == pluginName;
    });
    return iter->first;
}

const std::string& PipeAPI::NameByID(uint32_t id)
{
    return plugins[id];
}

int PipeAPI::Send(uint32_t id, void *data, uint32_t size)
{
    static uint32_t myid = IDByName(PluginInfo::get().name());
    if(id == myid)
        return PipeAPI::LOOPID;
    return internal_PipeSend(id, data, size);
}

int PipeAPI::Send(const std::string &plugin, void *data, uint32_t size)
{
    uint32_t id = IDByName(plugin);
    return Send(id, data, size);
}

PipeAPI::PipeAPI()
{
    internal_GetPluginSearchReset();
    while(true)
    {
        uint32_t id = 0;
        char *name = nullptr;

        internal_GetPluginSearchNext(&id, &name);
        if(name == nullptr)
            break;

        plugins[id] = string(name);
    }
}