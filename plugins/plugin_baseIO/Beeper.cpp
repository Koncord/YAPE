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

#include "Beeper.hpp"

#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_timer.h>
#include <cmath>

const int FREQUENCY = 44100;


void audio_callback(void *_beeper, uint8_t *_stream, int _length)
{

    int length = _length / 2;
    Beeper* beeper = (Beeper*) _beeper;

    int16_t *stream = (int16_t*) _stream;

    beeper->generateSamples(stream, length);
}


Beeper::Beeper()
{

    SDL_AudioSpec desiredSpec;

    desiredSpec.freq = FREQUENCY;
    desiredSpec.format = AUDIO_S16SYS;
    desiredSpec.channels = 1;
    desiredSpec.samples = 2048;
    desiredSpec.callback = audio_callback;
    desiredSpec.userdata = this;

    SDL_AudioSpec obtainedSpec;

    // you might want to look for errors here
    SDL_OpenAudio(&desiredSpec, &obtainedSpec);

    // start play audio
    SDL_PauseAudio(0);

    amplitude = 28000;

}

Beeper::~Beeper()
{
    SDL_CloseAudio();
}

void Beeper::generateSamples(int16_t *stream, int length)
{
    int i = 0;
    while (i < length) {

        if (beeps.empty()) {
            while (i < length) {
                stream[i] = 0;
                i++;
            }
            return;
        }
        BeepObject& bo = beeps.front();

        int samplesToDo = std::min(i + bo.samplesLeft, length);
        bo.samplesLeft -= samplesToDo - i;

        while (i < samplesToDo) {
            stream[i] = amplitude * std::sin(v * 2 * M_PI / FREQUENCY);
            i++;
            v += bo.freq;
        }

        if (bo.samplesLeft == 0) {
            beeps.pop();
        }
    }
}

void Beeper::beep(double freq, int duration)
{
    BeepObject bo;
    bo.freq = freq;
    bo.samplesLeft = duration * FREQUENCY / 1000;

    SDL_LockAudio();
    beeps.push(bo);
    SDL_UnlockAudio();
}

void Beeper::wait()
{
    int size;
    do {
        SDL_Delay(5);
        SDL_LockAudio();
        size = beeps.size();
        SDL_UnlockAudio();
    } while (size > 0);
}

void Beeper::stop()
{
    SDL_LockAudio();
    std::queue<BeepObject> empty;
    std::swap( beeps, empty );
    SDL_UnlockAudio();
}

void Beeper::setAmplitude(int amp)
{
    amplitude = amp;
}

int Beeper::getAmplitude()
{
    return amplitude;
}
