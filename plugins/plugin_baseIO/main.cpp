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

#include <SDL2/SDL.h>
#include <DeviceAPI.hpp>
#include "Beeper.hpp"
#include "Display.hpp"
#include <memory>
#include <thread>


std::unique_ptr<Display> display;

class BeepControl
{
    std::thread thrBeeper;
    bool run;
    Beeper beeper;
    int baseAmp;

    int duration;
    double freq;

public:
    BeepControl()
    {
        baseAmp = beeper.getAmplitude();
        run = false;
    }

    ~BeepControl()
    {
        beeper.stop();
        if(thrBeeper.joinable())
            thrBeeper.join();
    }

    void ThreadBeep()
    {
        run = true;
        beeper.beep(freq, duration); // (double freq, int duration)
        beeper.wait();
        run = false;
    }

    void Beep(double fr = 440, int dur = 100)
    {
        duration = dur;
        freq = fr;

        if(run)
            beeper.stop();
        thrBeeper = std::move(std::thread(&BeepControl::ThreadBeep, this));
    }

    void SetAmpScale(int scale)
    {
        beeper.setAmplitude(baseAmp * scale);
    }

    void Stop()
    {
        beeper.stop();
    }

};

BeepControl beeper;

DEVICE bool LoadBIOS() noexcept
{
    printf("Hello from plugin!\n");
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    display = std::make_unique<Display>(GetMemoryPtr());

    display->SetMode(Display::MODE::SuperVideo);

    return true;
}

DEVICE void OnUnload() noexcept
{
    SDL_Quit();
}

DEVICE void OnIRQ() noexcept
{

}

DEVICE void OnIRQChanged() noexcept // threads
{

}

DEVICE void OnPortActivity(uint16_t port, uint16_t data) noexcept
{

    if(port == 0x01)
    {
        // SuperVideo mode
        // sequence X,Y, RRGG, 00BB
        // size 8 bytes per pixel
        //
        // SuperText mode
        // sequence [command byte] + char
        // size 2 bytes (if control byte 0, this is text, else control sequence)
        display->Render(data);
    }
    else if(port == 0x02)
    {
        static bool magic = false;
        static uint16_t freq, duration;
        if(magic)
        {
            duration = data;
            beeper.Beep(freq, duration);
            return;
        }
        magic = true;
        freq = data;
    }
}

class Timer
{
    uint16_t data;
    public:
        void LoadData(uint16_t data);
        void Step();
        bool Out();
};
Timer t;

DEVICE void Runner() noexcept // run as while safe thread
{
    // если отправить 0x182 в порт 0x43 - это вызовит загрузку данных в таймер 2
    // 0x42 - 16 битный порт это означает что вы можете генерировать частоту между 18.21 Hz (номер частоты = 65,535) и 1,193,180 Hz (номер частоты = 1).
    // 0x62 6 бит в порту подключен на прямую к выходу таймера

    /* Порт 0x61
     * разряд 0 - включение громкоговорителя через таймер 2
     * разряд 1 - наличие данных для работы громкоговорителя
     * разряд 2 - чтение ключа размера оперативной памяти или чтение резервного ключа (A20)
     * разряд 3 - выключение двигателя накопителя на мини-кассете
     * разряд 4 - блокировка оперативной памяти
     * разряд 5 - блокировка контроля ввода-вывода
     * разряд 6 - поддержание низкой тактовой частоты задающего генератора клавиатуры
     * разряд 7 - сброс клавиатуры и разрешение опроса программно-опрашиваемых переключателей
     * */

     /*
      * Порты 0x60 - 0x63 используются параллельным контроллером Intel 8255
      * Порт 0x63 - порт программирования 8255
      */

    /*if(GetPortData(0x61) & 0x2 == true) // таймер включен
    {

    }*/
}
