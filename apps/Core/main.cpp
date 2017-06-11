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

#include <boost/program_options.hpp>

#include <boost/filesystem/operations.hpp>
#include <fstream>
#include <vector>
#include <csignal>

#ifdef __x86_64__
#define CPU_ARCH "64"
#else
#define CPU_ARCH ""
#endif

using namespace std;

/*
 *
 */
static bool debug = false;

void DebugOutput()
{
    const RegisterController &reg = *Environment::get().GetReg();

    const auto RHex = [&reg](unsigned short r)
    {
        stringstream sstr;
        sstr << "0x" << setfill('0') << setw(4) << hex << reg.Get(r) << dec;
        return sstr.str();
    };
    const auto FBool = [&reg](uint16_t f)
    {
        return reg.GetFlag(f) ? "True" : "False";
    };

    cout << "---------------- Registers ----------------" << endl;
    cout << "AX: " << RHex(Register::AX) << " BX: " << RHex(Register::BX) << " CX: " << RHex(Register::CX) << " DX: " << RHex(Register::DX) << endl;
    cout << "SI: " << RHex(Register::SI) << " DI: " << RHex(Register::DI) << " BP: " << RHex(Register::BP) << " SP: " << RHex(Register::SP) << endl;
    cout << "CS: " << RHex(Register::CS) << " DS: " << RHex(Register::DS) << " ES: " << RHex(Register::ES) << " SS: " << RHex(Register::SS) << endl;
    cout << "IP: " << RHex(Register::IP) << endl;
    cout << "------------------ Flags ------------------" << endl;
    cout << "Carry:\t\t"   << FBool(Flag::Carry)     << "\t\t" << "Parity:\t\t"  << FBool(Flag::Parity)    << endl;
    cout << "Auxiliary:\t" << FBool(Flag::Auxiliary) << "\t\t" << "Zero:\t\t"    << FBool(Flag::Zero)      << endl;
    cout << "Sign:\t\t"    << FBool(Flag::Sign)      << "\t\t" << "Trap:\t\t"    << FBool(Flag::Trap)      << endl;
    cout << "Interrupt:\t" << FBool(Flag::Interrupt) << "\t\t" << "Direction:\t" << FBool(Flag::Direction) << endl;
    cout << "Overflow:\t"  << FBool(Flag::Overflow)  << endl;
}

bool stop = false;

void TestProgram()
{
    auto &env = Environment::get();
    auto machine = env.GetCU();
    auto reg = env.GetReg();
    auto mem = env.GetMemory();

    // default segment initialize
    reg->Set(Register::SS, 0);
    reg->Set(Register::ES, 0);
    reg->Set(Register::CS, 0);
    reg->Set(Register::DS, 0);

    reg->Set(Register::IP, 0); // instruction pointer
    reg->Set(Register::BP, 0); // base pointer
    reg->Set(Register::SP, 0xFFFE); // stack pointer
    machine->Halt();
    try
    {
        while (!stop)
        {
            if(!machine->isHalted())
            {
                const uint32_t cur_pos = machine->GetNextInstructionAddr();
                const uint16_t cmd_len = LexicalInterpreter::length(mem->GetByte(cur_pos));

                if (reg->Get(Register::IP) + cmd_len >= mem->GetSize())
                    throw runtime_error("IP + cmd_len > memsize");

                std::vector<uint8_t> cmd(cmd_len);
                mem->GetPart(cur_pos, &cmd[0], cur_pos + cmd_len);

                machine->Step(cmd);
                if (debug)
                    DebugOutput();
            }
            this_thread::sleep_for(chrono::milliseconds(5));
        }
    }
    catch(...)
    {
        if(debug)
            DebugOutput();
        throw;
    }
}

void loadProgram(std::string &file)
{
    if(!boost::filesystem::exists(file))
        throw invalid_argument("file is not exist.");

    ifstream ifs(file, ifstream::binary);

    auto *m = Environment::get().GetMemory();

    char byte;

    for(uint32_t i = 0; ifs.read(reinterpret_cast<char*>(&byte), 1); i++)
        m->SetByte(i, (uint8_t) byte);
}

bool options(int argc, char **argv)
{
    namespace popt = boost::program_options;
    popt::options_description desc;
    std::string input;
    desc.add_options()
            ("file,f", popt::value<std::string>(&input), "*.yape file for execution")
            ("debug,d", "debug output from parser");


    popt::variables_map vm;
    try
    {
        popt::parsed_options parsed = popt::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
        popt::store(parsed, vm);
        popt::notify(vm);
        if (!input.empty())
        {
            cout << "opening: " << input;
            if (vm.count("debug"))
            {
                cout << " with debug output";
                debug = true;
            }

            loadProgram(input);
            cout << endl;
        }
        else
            std::cout << desc << std::endl;
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return false;
    }
    return true;
}

void onExit()
{
    Plugin::UnloadPlugins();
    stop = true;
}

int main(int argc, char** argv)
{
    atexit(onExit);

    auto &env = Environment::get();

    unique_ptr<Memory> mem(new Memory);

    env.SetMemory(mem.get());

    if(!options(argc, argv))
        return 0;

    unique_ptr<RegisterController> reg(new RegisterController);
    unique_ptr<ControlUnit> cu(new ControlUnit);
    env.SetReg(reg.get());
    env.SetCU(cu.get());

    Plugin::LoadPlugins("plugins");
    //atexit(Plugin::UnloadPlugins);

    try
    {
        InstructionSet_base();

        TestProgram();
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}

