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

#include "../PluginInfo.hpp"
#include "../DeviceAPI.hpp"

PluginInfo::PluginInfo(): mMajor(0), mMinor(0), mFix(0), mName(""), mDepends()
{

}

void PluginInfo::setName(std::string name)
{
    mName = name;
}

void PluginInfo::setVersion(int major, int minor, int fix)
{
    mMajor = major;
    mMinor = minor;
    mFix   = fix;
}

void PluginInfo::addDependency(std::string dep)
{
    mDepends.push_back(dep);
}


const std::string &PluginInfo::name() const
{
    return mName;
}

std::vector<std::string> PluginInfo::depends() const
{
    return std::vector<std::string>();
}

int PluginInfo::majorVersion() const
{
    return mMajor;
}

int PluginInfo::minorVersion() const
{
    return mMinor;
}

int PluginInfo::fixVersion() const
{
    return mFix;
}

PluginInfo &PluginInfo::get()
{
    static PluginInfo pi;
    return pi;
}

extern "C"
{
    // events
    DEVICE int internal_GetPluginVersion(int v) noexcept;
    DEVICE const char *internal_GetPluginName() noexcept;
    DEVICE const char *internal_GetPluginDependNext() noexcept;
    DEVICE void internal_GetPluginDependClear() noexcept;
}

DEVICE int internal_GetPluginVersion(int i) noexcept
{
    const PluginInfo& pluginInfo = PluginInfo::get();
    int ver = 0;
    switch(i)
    {
        case 1:
            ver = pluginInfo.minorVersion();
            break;
        case 2:
            ver = pluginInfo.fixVersion();
            break;
        default:
            ver = pluginInfo.majorVersion();
    }
    return ver;
}

DEVICE const char *internal_GetPluginName() noexcept
{
    return PluginInfo::get().name().c_str();
}

static unsigned long depend_iterator = 0;
DEVICE const char *internal_GetPluginDependNext() noexcept
{
    if(depend_iterator > PluginInfo::get().depends().size())
        depend_iterator = 0;
    return PluginInfo::get().depends().at(depend_iterator++).c_str();
}

DEVICE void internal_GetPluginDependClear() noexcept
{
    depend_iterator = 0;
}
