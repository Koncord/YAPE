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

#include "Display.hpp"
#include <SDL2/SDL.h>

SDL_Window *window;
SDL_Renderer *renderer;

static void SetPixel(int x, int y, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, x, y);
}

Display::Display(Memory *mem)
{
    const int scale = 4;
    this->mem = mem;
    SDL_DisplayMode displayMode;
    window = SDL_CreateWindow("Display", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320 * scale, 200 * scale, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    SDL_RenderSetLogicalSize(renderer, 320, 200);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

Display::~Display()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    mem = nullptr;
}

short Display::GetMode() const
{
    return mode;
}

void Display::SetMode(short mod)
{
    mode = mod;
}

void Display::Render(uint16_t data)
{
    static int magic = 0;
    static short x, y;
    static SDL_Color color;
    if(mode == SuperVideo)
    {
        switch(magic)
        {
            case 0:
                x = data;
                break;
            case 1:
                y = data;
                break;
            case 2:
                color.r = (data >> 0x8) & 0xFF;
                color.g = data & 0xFF;
                break;
            default:
                color.b = data & 0xFF;

                SetPixel(x, y, color);

                SDL_RenderPresent(renderer);

                magic = 0;
        }
        magic++;
    }
    else if(mode == SuperText)
    {
        uint8_t comm = (data >> 0x8) & 0xFF;
        char c = data & 0xFF;
        /*if(comm == 0)
        {
            printchar(c)
            x += getCharWidth(c);
            if(x > DisplayWidth)
            {
                x = 0;
                if(y > DisplayHeight)
                    y = 0;
                y += GetCharHeight(c);
            }
        }
        else if(comm == 1)
            x = data;
        else if(comm == 2)
            y = data;
        else if(comm == 3)
            DisplayClear();
        */
    }
}
