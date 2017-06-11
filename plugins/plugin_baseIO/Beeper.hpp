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

#ifndef BEEPER_HPP
#define BEEPER_HPP
#include <queue>
#include <cstdint>

struct BeepObject
{
    double freq;
    int samplesLeft;
};

class Beeper
{
private:
    double v;
    std::queue<BeepObject> beeps;
    int amplitude;
public:
    Beeper();
    virtual ~Beeper();

    void beep(double freq, int duration);
    void generateSamples(int16_t *stream, int length);
    void wait();
    void stop();

    int getAmplitude();
    void setAmplitude(int ampl);
};

#endif
