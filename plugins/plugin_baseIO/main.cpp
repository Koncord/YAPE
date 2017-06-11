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

#include <SDL2/SDL.h>
#include <DeviceAPI.hpp>
#include <components/pluginsystem/PluginInfo.hpp>
#include "Display.hpp"
#include "BeeperControl.hpp"
#include "DeviceController.hpp"

DEVICE bool OnLoad() noexcept
{
    PLUGIN_INFO(1, 0, 0, "BaseIO");
    //PLUGIN_ADD_DEPENDENCY("");
    printf("Hello from plugin %s!\n", PluginInfo::get().name().c_str());
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    auto &deviceControl = DeviceController::get();
    deviceControl.setDisplay(new Display(GetMemoryPtr()));
    deviceControl.setBeeperControl(new BeeperControl);

    return true;
}

DEVICE void OnUnload() noexcept
{
    printf("Bye-bye!\n");
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
    const DeviceController &controller = DeviceController::get();
    if (port == 0x01)
    {
        // SuperVideo mode
        // sequence X,Y, RRGG, 00BB
        // size 8 bytes per pixel
        //
        // SuperText mode
        // sequence [command byte] + char
        // size 2 bytes (if control byte 0, this is text, else control sequence)
        controller.getDisplay()->Render(data);
    }
    else if (port == 0x02)
    {
        static bool magic = false;
        static uint16_t freq;
        if (magic)
        {
            controller.getBeeperControl()->Beep(freq, data);
            magic = false;
        }
        else
        {
            freq = data;
            magic = true;
        }
    }
}

DEVICE int PipeReciver(uint32_t /*senderID*/, void * /*data*/, uint32_t /*size*/) noexcept
{
    return 0;
}

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
