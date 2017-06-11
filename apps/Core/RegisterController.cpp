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

#include <stdexcept>

#include "RegisterController.hpp"
#include "Environment.hpp"
#include <components/Opcode/Opcode.hpp>
#include <limits>
#include <cmath>
#include <iostream>

using namespace std;

RegisterController::RegisterController() : ax(0), bx(0), cx(0), dx(0),
si(0), di(0), bp(0), sp(0), cs(0), ds(0), es(0), ss(0), ip(0), flags(0)
{

}

uint16_t RegisterController::Get(unsigned short regId) const
{
    switch (regId)
    {
        case Register::AX: return ax;
        case Register::BX: return bx;
        case Register::CX: return cx;
        case Register::DX: return dx;
        case Register::SI: return si;
        case Register::DI: return di;

        case Register::BP: return bp;
        case Register::SP: return sp;

        case Register::CS: return cs;
        case Register::DS: return ds;
        case Register::ES: return es;
        case Register::SS: return ss;
        case Register::IP: return ip;
        case Register::FLAGS: return flags;
        default:
            throw invalid_argument("unknown register id: " + std::to_string(regId));
    }
}

void RegisterController::Set(unsigned short regId, uint16_t data)
{
    switch (regId)
    {
        case Register::AX: ax = data; break;
        case Register::BX: bx = data; break;
        case Register::CX: cx = data; break;
        case Register::DX: dx = data; break;
        case Register::SI: si = data; break;
        case Register::DI: di = data; break;

        case Register::BP: bp = data; break;
        case Register::SP: sp = data; break;

        case Register::CS: cs = data; break;
        case Register::DS: ds = data; break;
        case Register::ES: es = data; break;
        case Register::SS: ss = data; break;
        case Register::IP: ip = data; break;
        case Register::FLAGS: flags = data; break;
        default:
            throw invalid_argument("unknown register id: " + std::to_string(regId));
    }
}

bool RegisterController::GetFlag(uint16_t flagId) const
{
    if(flagId > Flag::End())
        throw invalid_argument("unknown flag id: " + std::to_string(flagId));
    return (bool) (flags & flagId);
}

void RegisterController::SetFlag(uint16_t flagId, bool state)
{
    if(flagId > Flag::End())
        throw invalid_argument("unknown flag id: " + std::to_string(flagId));

    if (state)
        flags |= flagId;
    else
        flags &= ~flagId;
}

bool RegisterController::CheckCarry(uint32_t x)
{

    uint32_t limit = numeric_limits<uint16_t>().max();
    
    bool result = x > limit;
    
    SetFlag(Flag::Carry, result);
    
    return result;
}

bool RegisterController::CheckOverflow(uint16_t x, uint16_t y)
{
    int limit = numeric_limits<int16_t>().max();
    bool result = ((~(x ^ y)) & (x & y) & limit) > 0;
    SetFlag(Flag::Overflow, result);
    
    return result;
}

bool RegisterController::CheckZero(uint16_t x)
{
    bool result = !x && !GetFlag(Flag::Carry);

    SetFlag(Flag::Zero, result);
    return result;
}

bool RegisterController::CheckSign(uint16_t x)
{
    bool result = ((x >> 15) & 1) == 1;
    SetFlag(Flag::Sign, result);
    return result;
}
bool RegisterController::CheckParity(uint16_t x)
{
    (void)(x);
    return 0;
}


bool RegisterController::CheckAuxiliaryCarry(uint16_t _prev, uint16_t _new)
{
    bool result = ((_prev >> 3) & 1) != ((_new >> 3) & 1);
    SetFlag(Flag::Auxiliary, result);
    return result;
}
