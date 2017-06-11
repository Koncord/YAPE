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

#ifndef PLUGIN_HPP
#define PLUGIN_HPP
#ifdef __WIN32__
#include <winsock2.h>
#else
#include <dlfcn.h>
#endif
#include <unordered_map>
#include <vector>
#include <memory>
#include <stack>

#include <components/Utils/Utils.hpp>
#include <components/pluginsystem/Functions.hpp>
#include <components/pluginsystem/private/InternalFunc.hpp>

#include "Helper.hpp"

class Plugin
{
private:
    Plugin(const char *path);
    Plugin(const Plugin&) = delete;
    Plugin& operator=(const Plugin&) = delete;
public:
    virtual ~Plugin();
    static void LoadPlugin(const char* plugin);
    static void UnloadPlugins();
    static void LoadPlugins(std::string plugindir);


    template<typename R>
    R GetFunction(const char* name)
    {
        return SystemInterface<R>(lib, name).result;
    }

    template<typename R>
    bool SetFunction(const std::string& name, R value);

    static constexpr FunctionData functions[]{
            {"SetRegister", SetRegister},
            {"GetRegister", GetRegister},

            {"GetFlag", GetFlag},

            {"SetMemWord", SetMemWord},
            {"GetMemWord", GetMemWord},

            {"Start", Start},
            {"Quit", Quit},
            {"Pause", Pause},
            {"IsPaused", IsPaused},
            {"Step", Step},

            {"GetIRQ", GetIRQ},
            {"SetIRQ", SetIRQ},

            //{"SetPortData", SetPortData},
            {"GetMemoryPtr", GetMemoryPtr}/*,

            {"internal_PipeSend", internal_PipeSend},
            {"internal_GetPluginSearchNext", internal_GetPluginSearchNext},
            {"internal_GetPluginSearchReset", internal_GetPluginSearchReset},*/

    };
    static constexpr FunctionCallbackData callbacks[]{
            {"OnLoad", Function<bool>()},
            {"OnIRQ", Function<void>()},
            {"OnIRQChanged", Function<void>()},
            {"Runner", Function<void>()},
            {"OnUnload", Function<void>()},
            {"OnStep", Function<void>()},

            {"OnPortActivity", Function<void, uint16_t, uint16_t>()},
            {"PipeReciver", Function<int, uint32_t, void*, uint32_t>()},

            {"internal_GetPluginVersion", Function<int, int>()},
            {"internal_GetPluginName", Function<const char*>()},
            {"internal_GetPluginDependNext", Function<const char*>()},
            {"internal_GetPluginDependClear", Function<void>()},
    };

    const static constexpr FunctionCallbackData &CallbackData(const unsigned int I, const unsigned int N = 0)
    {
        return callbacks[N].index == I ? callbacks[N] : CallbackData(I, N + 1);
    }

    template<unsigned int I>
    using CallbackReturn = typename ReturnType<CallbackData(I, 0).callback.ret>::type;

    template<size_t N>
    static constexpr unsigned int Hash(const char(&str)[N])
    {
        return Utils::hash(str);
    }

    template<unsigned int I, typename... Args>
    static constexpr unsigned int Call(std::stack<CallbackReturn<I>&> result, Args&&... args)
    {
        constexpr FunctionCallbackData const& data = CallbackData(I);
        static_assert(data.callback.matches(TypeString<typename std::remove_reference<Args>::type...>::value), "Wrong number or types of arguments");

        unsigned int count = 0;

        for (auto& plugin : plugins)
        {
            if (!plugin->callbacks_.count(I))
                plugin->callbacks_.emplace(I, plugin->GetFunction<FunctionEllipsis<void>>(data.name));

            auto callback = plugin->callbacks_[I];

            if (!callback)
                continue;


            result.push(reinterpret_cast<FunctionEllipsis<CallbackReturn< I>>>(callback) (std::forward<Args>(args)...));
            ++count;
        }

        return count;
    }

    template<unsigned int I, typename... Args>
    static constexpr unsigned int Call(Args&&... args)
    {
        constexpr FunctionCallbackData const& data = CallbackData(I);
        static_assert(data.callback.matches(TypeString<typename std::remove_reference<Args>::type...>::value), "Wrong number or types of arguments");

        unsigned int count = 0;

        for (auto& plugin : plugins)
        {
            if (!plugin->callbacks_.count(I))
                plugin->callbacks_.emplace(I, plugin->GetFunction<FunctionEllipsis<void>>(data.name));

            auto callback = plugin->callbacks_[I];

            if (!callback)
                continue;

            reinterpret_cast<FunctionEllipsis<CallbackReturn< I>>>(callback) (std::forward<Args>(args)...);

            ++count;
        }

        return count;
    }

private:
    SystemInterface<>::lib_t lib;
    typedef std::vector<std::unique_ptr<Plugin>> PluginList;
    static PluginList plugins;
    std::unordered_map<unsigned int, FunctionEllipsis<void>> callbacks_;
};

#endif // PLUGIN_HPP
