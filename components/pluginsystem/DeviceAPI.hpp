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

#ifndef YAPE_DEVICEAPI_HPP
#define YAPE_DEVICEAPI_HPP

#ifndef __WIN32__
    #ifndef __cdecl
        #ifdef  __x86_64__
            #define __cdecl
        #else
            #define __cdecl __attribute__((__cdecl__))
        #endif
    #endif
    #define DEVICEVAR __attribute__ ((__visibility__("default")))
    //void __attribute__ ((constructor)) LibLoad(void);
    //void __attribute__  ((destructor)) LibUnload(void);
#else
    #define DEVICEVAR __declspec(dllexport)
#endif

#define DEVICE DEVICEVAR __cdecl

#include "Functions.hpp"
#include "Events.hpp"

#endif //YAPE_DEVICEAPI_HPP
