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

#include "BaseInstructions.hpp"

#include "ControlUnit.hpp"
#include "Instructions/OpADD.hpp"
#include "Instructions/OpMOV.hpp"
#include "Instructions/OpSUB.hpp"
#include "Instructions/OpJMP.hpp"
#include "Instructions/OpJZ.hpp"
#include "Instructions/OpHLT.hpp"
#include "Instructions/OpJNZ.hpp"
#include "Instructions/OpXCHG.hpp"
#include "Instructions/OpJC.hpp"
#include "Instructions/OpJNC.hpp"
#include "Instructions/OpJS.hpp"
#include "Instructions/OpJNS.hpp"
#include "Instructions/OpJNO.hpp"
#include "Instructions/OpJO.hpp"
#include "Instructions/OpJA.hpp"
#include "Instructions/OpJNA.hpp"
#include "Instructions/OpINC.hpp"
#include "Instructions/OpDEC.hpp"
#include "Instructions/OpCMP.hpp"
#include "Instructions/OpAND.hpp"
#include "Instructions/OpTEST.hpp"
#include "Instructions/OpOR.hpp"
#include "Instructions/OpNOT.hpp"
#include "Instructions/OpXOR.hpp"
#include "Instructions/OpCLC.hpp"
#include "Instructions/OpNEG.hpp"
#include "Instructions/OpSHL.hpp"
#include "Instructions/OpSTI.hpp"
#include "Instructions/OpSTD.hpp"
#include "Instructions/OpSTC.hpp"
#include "Instructions/OpMUL.hpp"
#include "Instructions/OpDIV.hpp"
#include "Instructions/OpPUSH.hpp"
#include "Instructions/OpPOP.hpp"
#include "Instructions/OpPUSHA.hpp"
#include "Instructions/OpPOPA.hpp"
#include "Instructions/OpCALL.hpp"
#include "Instructions/OpRET.hpp"
#include "Instructions/OpCLD.hpp"
#include "Instructions/OpCLI.hpp"
#include "Instructions/OpCMC.hpp"
#include "Instructions/OpLOOP.hpp"
#include "Instructions/OpJG.hpp"
#include "Instructions/OpJGE.hpp"
#include "Instructions/OpJL.hpp"
#include "Instructions/OpJLE.hpp"
#include "Instructions/OpJP.hpp"
#include "Instructions/OpJNP.hpp"
#include "Instructions/OpJCXZ.hpp"
#include "Instructions/OpLOOPNZ.hpp"
#include "Instructions/OpLOOPZ.hpp"
#include "Instructions/OpADC.hpp"
#include "Instructions/OpSBB.hpp"
#include "Instructions/OpIDIV.hpp"
#include "Instructions/OpCWD.hpp"
#include "Instructions/OpIMUL1.hpp"
#include "Instructions/OpIMUL2.hpp"
#include "Instructions/OpIMUL3.hpp"
#include "Instructions/OpINT.hpp"
#include "Instructions/OpINT3.hpp"


void InstructionSet_base()
{
    ControlUnit::RegisterOp(new OpADC);
    ControlUnit::RegisterOp(new OpADD);
    ControlUnit::RegisterOp(new OpAND);
    ControlUnit::RegisterOp(new OpCALL);
    ControlUnit::RegisterOp(new OpCLC);
    ControlUnit::RegisterOp(new OpCLD);
    ControlUnit::RegisterOp(new OpCLI);
    ControlUnit::RegisterOp(new OpCMC);
    ControlUnit::RegisterOp(new OpCMP);
    ControlUnit::RegisterOp(new OpCWD);
    ControlUnit::RegisterOp(new OpDEC);
    ControlUnit::RegisterOp(new OpDIV);
    ControlUnit::RegisterOp(new OpHLT);
    ControlUnit::RegisterOp(new OpIDIV);
    ControlUnit::RegisterOp(new OpIMUL1);
    ControlUnit::RegisterOp(new OpIMUL2);
    ControlUnit::RegisterOp(new OpIMUL3);
    ControlUnit::RegisterOp(new OpINC);
    ControlUnit::RegisterOp(new OpINT);
    ControlUnit::RegisterOp(new OpINT3);
    ControlUnit::RegisterOp(new OpJA);
    ControlUnit::RegisterOp(new OpJC);
    ControlUnit::RegisterOp(new OpJCXZ);
    ControlUnit::RegisterOp(new OpJG);
    ControlUnit::RegisterOp(new OpJGE);
    ControlUnit::RegisterOp(new OpJL);
    ControlUnit::RegisterOp(new OpJLE);
    ControlUnit::RegisterOp(new OpJMP);
    ControlUnit::RegisterOp(new OpJNA);
    ControlUnit::RegisterOp(new OpJNC);
    ControlUnit::RegisterOp(new OpJNO);
    ControlUnit::RegisterOp(new OpJNP);
    ControlUnit::RegisterOp(new OpJNS);
    ControlUnit::RegisterOp(new OpJNZ);
    ControlUnit::RegisterOp(new OpJO);
    ControlUnit::RegisterOp(new OpJP);
    ControlUnit::RegisterOp(new OpJS);
    ControlUnit::RegisterOp(new OpJZ);
    ControlUnit::RegisterOp(new OpLOOP);
    ControlUnit::RegisterOp(new OpLOOPNZ);
    ControlUnit::RegisterOp(new OpLOOPZ);
    ControlUnit::RegisterOp(new OpMOV);
    ControlUnit::RegisterOp(new OpMUL);
    ControlUnit::RegisterOp(new OpNEG);
    ControlUnit::RegisterOp(new OpNOT);
    ControlUnit::RegisterOp(new OpOR);
    ControlUnit::RegisterOp(new OpPOP);
    ControlUnit::RegisterOp(new OpPOPA);
    ControlUnit::RegisterOp(new OpPUSH);
    ControlUnit::RegisterOp(new OpPUSHA);
    ControlUnit::RegisterOp(new OpRET);
    ControlUnit::RegisterOp(new OpSBB);
    ControlUnit::RegisterOp(new OpSHL);
    ControlUnit::RegisterOp(new OpSTC);
    ControlUnit::RegisterOp(new OpSTD);
    ControlUnit::RegisterOp(new OpSTI);
    ControlUnit::RegisterOp(new OpSUB);
    ControlUnit::RegisterOp(new OpTEST);
    ControlUnit::RegisterOp(new OpXCHG);
    ControlUnit::RegisterOp(new OpXOR);

    //ControlUnit::RegisterOp(new OpROL);
    //ControlUnit::RegisterOp(new OpROR);
    //ControlUnit::RegisterOp(new OpSHR);
    //ControlUnit::RegisterOp(new OpSHL);
    //ControlUnit::RegisterOp(new OpSAR);
    //ControlUnit::RegisterOp(new OpSAL);
    //ControlUnit::RegisterOp(new OpRCR);
    //ControlUnit::RegisterOp(new OpRCL);

    //ControlUnit::RegisterOp(new OpENTER);
    //ControlUnit::RegisterOp(new OpLEAVE);
    //ControlUnit::RegisterOp(new OpBOUND);

    //ControlUnit::RegisterOp(new OpIN);
    //ControlUnit::RegisterOp(new OpOUT);
    //ControlUnit::RegisterOp(new OpINS);
    //ControlUnit::RegisterOp(new OpOUTS);
}
