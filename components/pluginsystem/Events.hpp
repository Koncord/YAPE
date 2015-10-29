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

#ifndef YAPE_EVENTS_HPP
#define YAPE_EVENTS_HPP
#ifndef _NDEVICE
#include "DeviceAPI.hpp"
extern "C"
{
    // events
    DEVICE bool LoadBIOS() noexcept;
    DEVICE void OnIRQ() noexcept; // if interrupt catched
    DEVICE void OnIRQChanged() noexcept;
    DEVICE void OnUnload() noexcept;
    DEVICE void OnPortActivity(uint16_t port, uint16_t data) noexcept;
    // threads
    DEVICE void Runner() noexcept; // run as while thread
}
#endif

#endif // YAPE_EVENTS_HPP
