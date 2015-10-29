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

#include "Plugin.hpp"

Plugin::PluginList Plugin::plugins;
bool init = false;
template<typename... Types>
constexpr char TypeString<Types...>::value[];
constexpr FunctionData Plugin::functions[];
constexpr FunctionCallbackData Plugin::callbacks[];

using namespace std;

Plugin::Plugin(const char *path)
{
    FILE* file = fopen(path, "rb");

    if (!file)
        throw runtime_error("Script not found: " + string(path));
    fclose(file);

    SystemInterface<>::lib_t handle;
    try
    {
#ifdef __WIN32__
        handle = LoadLibrary(path);
#else
        handle = dlopen(path, RTLD_LAZY);
#endif
        lib = handle;

        const char* prefix = GetFunction<const char*>("prefix");
        string ppf(prefix);
        for (const auto& func : functions)
            if (!SetFunction(string(ppf + func.name).c_str(), func.func.addr))
                printf("Script function pointer not found: %s\n", func.name);
    }
    catch(...)
    {
#ifdef __WIN32__
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif
        throw;
    }
}


Plugin::~Plugin()
{
#ifdef __WIN32__
    FreeLibrary(lib);
#else
    dlclose(lib);
#endif
}


template<typename R>
bool Plugin::SetFunction(const char* name, R value)
{
    SystemInterface<R*> result(lib, name);

    if (result)
        *result.result = value;

    return result.operator bool();
}

void Plugin::LoadPlugin(const char* plugin)
{
    try
    {
        Plugin::plugins.emplace_back(new Plugin(plugin));
    }
    catch (...)
    {
        UnloadPlugins();
        throw runtime_error("plugin " + string(plugin)+" not loaded!");
    }
}

void Plugin::UnloadPlugins()
{
    Plugin::Call<Plugin::Hash("OnUnload")>();
    plugins.clear();
}
