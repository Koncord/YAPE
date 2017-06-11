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

#ifndef YAPE_PLUGININFO_HPP
#define YAPE_PLUGININFO_HPP

#include <vector>
#include <string>

#define PLUGIN_INFO(major, minor, fix, name) {auto &pi = PluginInfo::get(); pi.setName(name); pi.setVersion(major, minor, fix);}
#define PLUGIN_ADD_DEPENDENCY(dep) {PluginInfo::get().addDependency(dep);}

class PluginInfo
{
public:
    void setName(std::string name);
    void setVersion(int major, int minor, int fix);
    void addDependency(std::string dep);

    const std::string& name() const;
    std::vector<std::string> depends() const;
    int majorVersion() const;
    int minorVersion() const;
    int fixVersion() const;

    static PluginInfo &get();

private:
    PluginInfo();

protected:
    int mMajor;
    int mMinor;
    int mFix;
    std::string mName;
    std::vector<std::string> mDepends;
};

#endif //YAPE_PLUGININFO_HPP
