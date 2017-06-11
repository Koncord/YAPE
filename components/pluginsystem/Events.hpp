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

#ifndef YAPE_EVENTS_HPP
#define YAPE_EVENTS_HPP
#ifndef _NDEVICE
#include "DeviceAPI.hpp"
extern "C"
{
    // events
    DEVICE bool OnLoad() noexcept;
    DEVICE void OnIRQ() noexcept; // if interrupt catched
    DEVICE void OnIRQChanged() noexcept;
    DEVICE void OnUnload() noexcept;
    DEVICE void OnPortActivity(uint16_t port, uint16_t data) noexcept;
    DEVICE void OnStep() noexcept;
    DEVICE void OnCallOpcode(uint8_t code) noexcept;

    /**
     * \brief Data pipe receiver from others plugin
     * \param senderID sender identifier
     * \param data received data
     * \param size size of data
     * \return EPipeCode
     **/
    DEVICE int PipeReciver(uint32_t senderID, void* data, uint32_t size) noexcept;

    // threads
    DEVICE void Runner() noexcept; // run as while thread
}
#endif

#endif // YAPE_EVENTS_HPP
