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

#include "Plugin.hpp"

#include <boost/filesystem.hpp>
#include <iostream>

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
        if(!prefix)
            printf("Prefix not found. %s\n", path);
        string ppf(prefix);
        for (const auto& func : functions)
            if (!SetFunction(string(ppf + func.name), func.func.addr))
                printf("Script function pointer not found: %s\n", func.name);
    }
    catch(exception &e)
    {
#ifdef __WIN32__
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif
        printf("Exception: %s\n", e.what());
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
bool Plugin::SetFunction(const string& name, R value)
{
    SystemInterface<R*> result(lib, name.c_str());

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

void Plugin::LoadPlugins(string plugindir)
{
    namespace fs = boost::filesystem;
    try
    {
        string basepath = fs::current_path()/*.parent_path()*/.string();

        fs::path someDir(basepath + static_cast<char>(fs::path::preferred_separator) + plugindir);
        fs::directory_iterator end_iter;

        if (fs::exists(someDir) && fs::is_directory(someDir))
            for (fs::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter)
            {
                if (dir_iter->path().string().find(".so") != std::string::npos)
                    Plugin::LoadPlugin(dir_iter->path().string().c_str());
            }
        Plugin::Call<Plugin::Hash("OnLoad")>();
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
}

