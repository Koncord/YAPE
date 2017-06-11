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

#include <cassert>
#include "BeeperControl.hpp"
#include "Display.hpp"
#include "DeviceController.hpp"

DeviceController::DeviceController() : mDisplay(0), mBeeperControl(0)
{
}

DeviceController::~DeviceController()
{
    if(mBeeperControl)
        delete mBeeperControl;
    if(mDisplay)
        delete mDisplay;
}

DeviceController &DeviceController::get()
{
    static DeviceController dc;
    return dc;
}

Display *DeviceController::getDisplay() const
{
    assert (mDisplay);
    return mDisplay;
}

BeeperControl *DeviceController::getBeeperControl() const
{
    assert (mBeeperControl);
    return mBeeperControl;
}

void DeviceController::setDisplay(Display *display)
{
    mDisplay = display;
}

void DeviceController::setBeeperControl(BeeperControl *beeperControl)
{
    mBeeperControl = beeperControl;
}
