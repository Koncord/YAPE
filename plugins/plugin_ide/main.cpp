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

#include <DeviceAPI.hpp>

#include <QApplication>
#include <thread>
#include <QtPlugin>
#include <iostream>
#include <components/pluginsystem/PluginInfo.hpp>

#include "FormGui.hpp"
#ifdef _WIN32_
Q_IMPORT_PLUGIN (QWindowsIntegrationPlugin)
#endif

using namespace std;

int argc = 0;
std::thread tGui;
FormGui *gui = nullptr;

DEVICE bool OnLoad() noexcept
{
    PLUGIN_INFO(1, 0, 0, "BaseIO");
    //GetMPUVersion();

    tGui = std::thread([](){
        QApplication app(argc, NULL);
        gui = new FormGui;
        gui->show();
        app.setWindowIcon(QIcon(":/Icons/icons/mode_Output.png"));
        app.exec();
        gui->deleteLater();
        delete gui;
    });
    return true;
}

void DEVICE OnUnload() noexcept
{
    QApplication::quit();
    tGui.join();
}

void DEVICE OnHalt() noexcept
{
    
}

void DEVICE OnStep() noexcept
{
    gui->DataUpdater();
}

void DEVICE OnInterrupt(unsigned char /*id*/) noexcept
{
    
}

void DEVICE OnCallOpcode(unsigned char /*code*/) noexcept
{
    gui->DataUpdater();
}
