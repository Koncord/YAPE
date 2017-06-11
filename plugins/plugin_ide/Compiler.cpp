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

#include "Compiler.hpp"

#include <components/Opcode/Opcode.hpp>
#include <QDebug>

#define SWITCH(tok) 
#define CASE0(str) if(_caseStr == str)
#define CASE1(str) if(_caseStr == str)

Code ParseArg(QStringList &str)
{
    Code data;
    data.push_back(0); // reserve 1 byte
    for(int i = 0; i < str.size() ; i++)
    {
        int shift = 2*i;
        bool isModIndirect = false;
        QString _tmp = str[i].trimmed();

        if (_tmp[0] == '[')
        {
            if (_tmp[_tmp.length() - 1] != ']')
                throw;

            _tmp = _tmp.mid(1, _tmp.length() - 2);

            //data.push_back(Operand::Memory);
            data[0] |= Operand::Memory << shift;
            isModIndirect = true;
        }

        if (_tmp[0].isDigit())
        {
            //if (!isModIndirect) data.push_back(Operand::Immediate);
            if (!isModIndirect) data[0] |= Operand::Immediate << shift;
            uint16_t tmp;
            if (_tmp[_tmp.length() - 1] == 'h')
                tmp = _tmp.mid(0, _tmp.length() - 1).toUShort(0, 16);
            else tmp = _tmp.toUShort();
            data.push_back(tmp % 0x100);
            data.push_back(tmp >> 0x08);
            return data;
        }
        else
        {
#define R(r) if(_tmp.toUpper() == #r) { data.push_back(0); data.push_back(Register::r); continue;}

            //if (isModIndirect) data[0] = Operand::Register;
            //else data.push_back(Operand::Register);

            if (isModIndirect) data[0] = Operand::Register;
            else data[0] |= Operand::Register << shift;

            R(AX);
            R(BX);
            R(CX);
            R(DX);

            R(SI);
            R(DI);

            R(SP);
            R(BP);
            R(CS);
            R(DS);
            R(SS);
            R(ES);
            R(IP);
#undef R
        }
        throw std::invalid_argument(_tmp.toStdString());
    }
    return data;
}

template <class T>
Code Data(QString str)
{
    if (std::numeric_limits<T>::max() > std::numeric_limits<uint16_t>::max())
        throw;
    QRegExp rxData("\\b,\\s*");
    QRegExp rxDigits("\\d*"); // a digit (\d), zero or more times (*)
    QString _tmp = str.trimmed();
    Code data;
    uint32_t byte = 0;
    QStringList tokens = _tmp.split(rxData, QString::SkipEmptyParts);

    foreach(QString token, tokens)
    {
        if (!rxDigits.exactMatch(token))
            throw;
        byte = token.toUInt();
        if (byte > std::numeric_limits<T>::max()) // если значение больше максимального для типа
            throw;
        if (std::numeric_limits<T>::max() > 0xFF)
            data.push_back(byte >> 8);
        data.push_back(byte % 0x100);
    }
    return data;
}

Code CompLine(QString str)
{
    Code data;
    if(str == "") return data;
    const QRegExp rxArgSeparator("\\,");
    QStringList tokens = str.split(QRegExp("\\b\\s+"), QString::SkipEmptyParts);
    QString command = tokens.at(0).toUpper();
    if (command != "")
    {
#define SEPARATE_ARGS(n) tokens = tokens.at(1).split(rxArgSeparator, QString::SkipEmptyParts); if(tokens.size() != n) throw;
#define COM(com) if(command == #com) {\
         int args = Opcode::Args(Opcode::com);\
         if(args > 0 && tokens.size() != 2) throw;\
         data.push_back(Opcode::com);\
         if(args > 0) {\
            SEPARATE_ARGS(args);\
            data += ParseArg(tokens); }\
         goto _RET; }

/****** 2 args ******/
        COM(ADD)
        COM(MOV)
        COM(SUB)
        COM(CMP)
        COM(AND)
        COM(XCHG)
        COM(TEST)
        COM(OR)
        COM(XOR)
        COM(SHL)
        COM(ADC)
        COM(SBB)
        COM(SAL)
        COM(SHR)
        COM(SAR)
        COM(IMUL2)

/****** 1 args ******/
        COM(JMP)
        COM(JNZ)
        COM(JNE)
        COM(JZ)
        COM(JE)
        COM(JC)
        COM(JNAE)
        COM(JB)
        COM(JNC)
        COM(JAE)
        COM(JNB)
        COM(JS)
        COM(JNS)
        COM(JO)
        COM(JNO)
        COM(JA)
        COM(JNBE)
        COM(JNA)
        COM(JBE)
        COM(JP)
        COM(JNP)
        COM(JG)
        COM(JNLE)
        COM(JGE)
        COM(JNL)
        COM(JL)
        COM(JNGE)
        COM(JLE)
        COM(JNG)
        COM(JCXZ)
        COM(JECXZ)
        COM(NOT)
        COM(NEG)
        COM(CALL)
        COM(PUSH)
        COM(POP)
        COM(MUL)
        COM(DIV)
        COM(LOOP)
        COM(LOOPNZ)
        COM(LOOPZ)
        COM(RET)
        COM(RETN)
        COM(RETF)
        COM(IRET)
        COM(INC)
        COM(IDIV)
        COM(IMUL1)
        COM(INT)
        COM(DEC)

/****** 0 args ******/
        COM(HLT)
        COM(CLC)
        COM(CLD)
        COM(CLI)
        COM(CMC)
        COM(STC)
        COM(STD)
        COM(STI)
        COM(PUSHA)
        COM(POPA)
        COM(CWD)
        COM(INT3)
        COM(NOP)

/****** 3 args ******/
        COM(IMUL3)

        if (command == "DB")
        {
            if (tokens.size() != 2)
                throw;
            data += Data<uint8_t>(tokens.at(1));
        }
        else if (command == "DW")
        {
            if (tokens.size() != 2)
                throw;
            data += Data<uint16_t>(tokens.at(1));
        }

#undef COM
#undef SEPARATE_ARGS

        if (command == "DB")
        {
            if (tokens.size() != 2)
                throw;
            data += Data<uint8_t>(tokens.at(1));
        }
        else if (command == "DW")
        {
            if (tokens.size() != 2)
                throw;
            data += Data<uint16_t>(tokens.at(1));
        }
    }
_RET:
    return data;
}

int CalcSizeStr(QString str)
{
    if(str == "") return 0;
    int size = 0;
    const QRegExp rxSeparator("\\b\\s+");

    QStringList tokens = str.split(rxSeparator, QString::SkipEmptyParts);
    QString command = tokens.at(0).toUpper();
    if (command != "")
    {
#define COM(com) if(command == #com) { size += 1 + 3*Opcode::Args(Opcode::com); goto _RET;}

/****** 2 args ******/
        COM(ADD)
        COM(MOV)
        COM(SUB)
        COM(CMP)
        COM(AND)
        COM(XCHG)
        COM(TEST)
        COM(OR)
        COM(XOR)
        COM(SHL)
        COM(ADC)
        COM(SBB)
        COM(SAL)
        COM(SHR)
        COM(SAR)
        COM(IMUL2)

/****** 1 args ******/
        COM(JMP)
        COM(JNZ)
        COM(JNE)
        COM(JZ)
        COM(JE)
        COM(JC)
        COM(JNAE)
        COM(JB)
        COM(JNC)
        COM(JAE)
        COM(JNB)
        COM(JS)
        COM(JNS)
        COM(JO)
        COM(JNO)
        COM(JA)
        COM(JNBE)
        COM(JNA)
        COM(JBE)
        COM(JP)
        COM(JNP)
        COM(JG)
        COM(JNLE)
        COM(JGE)
        COM(JNL)
        COM(JL)
        COM(JNGE)
        COM(JLE)
        COM(JNG)
        COM(JCXZ)
        COM(JECXZ)
        COM(NOT)
        COM(NEG)
        COM(CALL)
        COM(PUSH)
        COM(POP)
        COM(MUL)
        COM(DIV)
        COM(LOOP)
        COM(LOOPNZ)
        COM(LOOPZ)
        COM(RET)
        COM(RETN)
        COM(RETF)
        COM(IRET)
        COM(INC)
        COM(IDIV)
        COM(IMUL1)
        COM(INT)
        COM(DEC)

/****** 0 args ******/
        COM(HLT)
        COM(CLC)
        COM(CLD)
        COM(CLI)
        COM(CMC)
        COM(STC)
        COM(STD)
        COM(STI)
        COM(PUSHA)
        COM(POPA)
        COM(CWD)
        COM(INT3)
        COM(NOP)

/****** 3 args ******/
        COM(IMUL3)

        if (command == "DB")
        {
            if (tokens.size() != 2)
                throw;
            size += Data<uint8_t>(tokens.at(1)).size();
        }
        else if (command == "DW")
        {
            if (tokens.size() != 2)
                throw;
            size += Data<uint8_t>(tokens.at(1)).size();
        }

#undef COM
    }

_RET:
    return size;
}

int FindLabelIdByLine(Labels labels, int line)
{
    for (int i = 0; i < labels.size(); i++)
    {
        if (labels[i].sourceLine == line)
            return i;
    }
    return -1;
}

int FindAndReplaceLabelInLine(Labels labels, QString *line)
{
    for (int i = 0; i < labels.size(); i++)
    {
        int pos = line->indexOf(labels[i].name);
        if (pos >= 0)
        {
            line->replace(pos, labels[i].name.length(), QString::number(labels[i].pos));
            return 1;
        }
    }
    return 0; // если в строкке нет меток
}

Labels PreparseLabels(QStringList source)
{
    Labels labels;
    QRegExp rxLbl("(^[\\w\\s])\\w+:");

    int size = 0;
    for (int i = 0; i < source.size(); i++)
    {
        size+= CalcSizeStr(source.at(i));
        if(rxLbl.indexIn(source.at(i)) > -1)
        {
            QString lbl = rxLbl.cap();
            Label label = {lbl.mid(0, lbl.length() - 1), i, size};
            labels.push_back(label);
        }
    }
    return labels;
}

Compiler::Compiler(QStringList *src)
{
    source = *src;
    labels = PreparseLabels(source);
}

Code Compiler::exec()
{
    Code code;
    for (int i = 0; i < source.size(); i++)
    {
        QString srcLine = source.at(i);
        Code line;

        int lblId = FindLabelIdByLine(labels, i);
        if (lblId >= 0) srcLine = srcLine.mid(labels[lblId].name.length() + 1); // "отрезание" метки (например: "label:") от кода

        if (srcLine.size() > 0)
        {
            FindAndReplaceLabelInLine(labels, &srcLine);
            line = CompLine(srcLine);
        }
        code += line;
    }
    return code;
}
