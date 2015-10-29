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

#include <iostream>
#include <sstream>
#include <iomanip>
#include <thread>

#include "ControlUnit.hpp"
#include <components/Memory/Memory.hpp>
#include "RegisterController.hpp"
#include "Environment.hpp"

#include "BaseInstructions.hpp"
#include "pluginsystem/Plugin.hpp"

#ifdef __x86_64__
#define CPU_ARCH "x64"
#else
#define CPU_ARCH "x86"
#endif

#include <boost/filesystem.hpp>

using namespace std;

/*
 * 
 */

void test_ops(Memory *prog, uint16_t *pos, uint8_t mod1, uint16_t data1, uint8_t mod2 = 0, uint16_t data2 = 0, uint8_t extra = 0)
{
    prog->SetByte(*pos, (extra << 4) | (mod2 << 2) | mod1);
    *pos += 1;
    prog->SetWord(*pos, data1);
    *pos += 2;
    if(mod2 != 0)
    {
        prog->SetWord(*pos, data2);
        *pos += 2;
    }
}

void test_ops3(Memory *prog, uint16_t *pos, uint8_t mod1, uint16_t data1, uint8_t mod2 = 0, uint16_t data2 = 0, uint8_t mod3 = 0, uint16_t data3 = 0, uint8_t extra = 0)
{
    prog->SetByte(*pos, (extra << 6)| (mod2 << 4) | (mod2 << 2) | mod1);
    *pos += 1;
    if(mod1 != 0)
    {
        prog->SetWord(*pos, data1);
        *pos += 2;
    }
    if(mod2 != 0)
    {
        prog->SetWord(*pos, data2);
        *pos += 2;
    }
    if(mod3 != 0)
    {
        prog->SetWord(*pos, data3);
        *pos += 2;
    }
}

void test_add(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::ADD);
    *pos += 1;
    test_ops(prog, pos, Operand::Register, Register::AX, Operand::Immediate, value);
}

void test_mova(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::MOV);
    *pos += 1;
    test_ops(prog, pos, Operand::Register, Register::AX, Operand::Immediate, value);
}

void test_movb(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::MOV);
    *pos += 1;
    test_ops(prog, pos, Operand::Register, Register::BX, Operand::Immediate, value);
}

void test_movc(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::MOV);
    *pos += 1;
    test_ops(prog, pos, Operand::Register, Register::CX, Operand::Immediate, value);
}

void test_sub(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::SUB);
    *pos += 1;
    test_ops(prog, pos, Operand::Register, Register::AX, Operand::Immediate, value);
}

void test_jnz(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::JNZ);
    *pos += 1;
    test_ops(prog, pos, Operand::Immediate, value, 0, 0, Operand::EXTRA::Short);
}

void test_div(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::DIV);
    *pos += 1;
    test_ops(prog, pos, Operand::Register, value);
}

void test_idiv(Memory *prog, uint16_t *pos, uint16_t value)
{
    prog->SetByte(*pos, Opcode::IDIV);
    *pos += 1;
    test_ops(prog, pos, Operand::Register, value);
}

void test_imul3(Memory *prog, uint16_t *pos)
{
    prog->SetByte(*pos, Opcode::IMUL3);
    *pos += 1;
    test_ops3(prog, pos, Operand::Register, Register::AX, Operand::Register, Register::BX, Operand::Register, Register::CX);
}

void test_hlt(Memory *prog, uint16_t *pos)
{
    prog->SetByte(*pos, Opcode::HLT);
    *pos += 1;
}

inline string Hex(unsigned short t)
{
    stringstream sstr;
    sstr << "0x" << setfill('0') << setw(4) << hex << t << dec;
    return sstr.str();
}

inline string Bool(bool b)
{
    return b ? "True" : "False";
}

void DebugOutput()
{
    const RegisterController& reg = *Environment::get().GetReg();
    cout << "---------------- Registers ----------------" << endl;
    cout << "AX: " << Hex(reg.Get(Register::AX)) << " BX: " << Hex(reg.Get(Register::BX)) << " CX: " << Hex(reg.Get(Register::CX)) << " DX: " << Hex(reg.Get(Register::DX)) << endl;
    cout << "SI: " << Hex(reg.Get(Register::SI)) << " DI: " << Hex(reg.Get(Register::DI)) << " BP: " << Hex(reg.Get(Register::BP)) << " SP: " << Hex(reg.Get(Register::SP)) << endl;
    cout << "CS: " << Hex(reg.Get(Register::CS)) << " DS: " << Hex(reg.Get(Register::DS)) << " ES: " << Hex(reg.Get(Register::ES)) << " SS: " << Hex(reg.Get(Register::SS)) << endl;
    cout << "IP: " << Hex(reg.Get(Register::IP)) << endl;
    cout << "------------------ Flags ------------------" << endl;
    cout << "Carry:\t\t" << Bool(reg.GetFlag(Flag::Carry)) << "\t\t" << "Parity:\t\t" << Bool(reg.GetFlag(Flag::Parity)) << endl;
    cout << "Auxiliary:\t" << Bool(reg.GetFlag(Flag::Auxiliary)) << "\t\t" << "Zero:\t\t" << Bool(reg.GetFlag(Flag::Zero)) << endl;
    cout << "Sign:\t\t" << Bool(reg.GetFlag(Flag::Sign)) << "\t\t" << "Trap:\t\t" << Bool(reg.GetFlag(Flag::Trap)) << endl;
    cout << "Interrupt:\t" << Bool(reg.GetFlag(Flag::Interrupt)) << "\t\t" << "Direction:\t" << Bool(reg.GetFlag(Flag::Direction)) << endl;
    cout << "Overflow:\t" << Bool(reg.GetFlag(Flag::Overflow)) << endl;
}

void TestProgram()
{
    auto machine = Environment::get().GetCU();
    auto reg = Environment::get().GetReg();
    auto mem = Environment::get().GetMemory();

    // default segment initialize
    reg->Set(Register::SS, 0);
    reg->Set(Register::ES, 0);
    reg->Set(Register::CS, 0);
    reg->Set(Register::DS, 0);

    reg->Set(Register::IP, 0); // instruction pointer
    reg->Set(Register::BP, 0); // base pointer
    reg->Set(Register::SP, 0xFFFE); // stack pointer

    {
        uint16_t pos = (reg->Get(Register::CS) << 4) + reg->Get(Register::IP);

        /*test_add(mem, &pos, 3);
        const int label = pos;
        test_sub(mem, &pos, 1);
        test_jnz(mem, &pos, label);
        test_hlt(mem, &pos);*/

        /*test_mova(mem, &pos, 5);
        test_movb(mem, &pos, -2);
        test_idiv(mem, &pos, Register::BX);
        test_hlt(mem, &pos);*/

        /*test_movb(mem, &pos, 2);
        test_movc(mem, &pos, 2);
        test_imul3(mem, &pos);*/
        test_mova(mem, &pos, 0x1B8);
        test_movb(mem, &pos, 0x3E8);

        test_hlt(mem, &pos);
    }
    
    try
    {
        while (true)
        {
            const uint32_t pos = (reg->Get(Register::CS) << 4) + reg->Get(Register::IP);

            const uint16_t args_len = LexicalInterpreter::ArgLength() * Opcode::Args(mem->GetByte(pos));
            const uint16_t cmd_len = LexicalInterpreter::CmdLength() + (args_len ? args_len + 1 : 0);

            if(reg->Get(Register::IP) + cmd_len >= mem->GetSize())
                break;

            vector<uint8_t> tmp(cmd_len);
            mem->GetPart(pos, &tmp[0], pos + cmd_len);

            reg->Set(Register::IP, reg->Get(Register::IP) + cmd_len);

            machine->Step(tmp);

            DebugOutput();
            this_thread::sleep_for(chrono::milliseconds(5));
        }
    }
    catch(...)
    {
        DebugOutput();
        throw;
    }
}

void LoadPlugins(string plugindir);

int main(int argc, char** argv)
{
    (void)(argc); // ignore argc
    (void)(argv); // ignore argv

    unique_ptr<Environment> env(new Environment);

    env->SetMemory(new Memory);
    env->SetReg(new RegisterController);
    env->SetCU(new ControlUnit);

    LoadPlugins("plugins");
    Plugin::Call<Plugin::Hash("LoadBIOS")>();
    atexit(Plugin::UnloadPlugins);
    getchar();
    /*try
    {
        InstructionSet_base();

        TestProgram();
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }*/

    return 0;
}

void LoadPlugins(string plugindir)
{
    namespace fs = boost::filesystem;
    try
    {
        string basepath = fs::current_path()/*.parent_path()*/.string();

        fs::path someDir(basepath + fs::path::preferred_separator + plugindir);
        fs::directory_iterator end_iter;

        if (fs::exists(someDir) && fs::is_directory(someDir))
            for (fs::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter)
            {
                if (dir_iter->path().string().find(".so") != std::string::npos)
                    Plugin::LoadPlugin(dir_iter->path().string().c_str());
            }
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
}
