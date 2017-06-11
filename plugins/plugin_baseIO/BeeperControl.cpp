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

#include "BeeperControl.hpp"

BeeperControl::BeeperControl()
{
    baseAmp = getAmplitude();
    run = false;
}

BeeperControl::~BeeperControl()
{
    stop();
    if(thrBeeper.joinable())
        thrBeeper.join();
}

void BeeperControl::ThreadBeep()
{
    run = true;
    beep(freq, duration); // (double freq, int duration)
    wait();
    run = false;
}

void BeeperControl::Beep(double fr, int dur)
{
    duration = dur;
    freq = fr;

    if(run)
        stop();
    thrBeeper = std::move(std::thread(&BeeperControl::ThreadBeep, this));
}

void BeeperControl::SetAmpScale(int scale)
{
    setAmplitude(baseAmp * scale);
}

void BeeperControl::Stop()
{
    stop();
}
