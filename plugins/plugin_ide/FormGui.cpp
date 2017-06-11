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

#include "FormGui.hpp"
#include <DeviceAPI.hpp>
#include <components/Opcode/Opcode.hpp>
#include <components/Memory/Memory.hpp>
#include <QCloseEvent>
#include <QMessageBox>

FormGui::FormGui()
{
    widget.setupUi(this);

    fmem = new FormMem();
    feditor = new FormEditor();
    connect(widget.actionStep, SIGNAL(triggered()), this, SLOT(handleStep()));
    connect(widget.rbDEC, SIGNAL(toggled(bool)), this, SLOT(handleRadio(bool)));
    connect(widget.actionMemory, SIGNAL(triggered()), this, SLOT(openMem()));
    connect(widget.actionPause, SIGNAL(triggered()), this, SLOT(handlePause()));
    connect(widget.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(widget.actionCode_Editor, SIGNAL(triggered()), this, SLOT(editor()));
    connect(widget.actionReset, SIGNAL(triggered()), this, SLOT(reset()));


    switchPauseIcon(IsPaused());
    DataUpdater();
}

FormGui::~FormGui()
{

}

void FormGui::reset()
{
    GetMemoryPtr()->Reset();

    SetRegister(Register::AX, 0);
    SetRegister(Register::BX, 0);
    SetRegister(Register::CX, 0);
    SetRegister(Register::DX, 0);
    SetRegister(Register::SI, 0);
    SetRegister(Register::DI, 0);
    SetRegister(Register::SP, 0xFFFE);
    SetRegister(Register::BP, 0);
    SetRegister(Register::CS, 0);
    SetRegister(Register::DS, 0);
    SetRegister(Register::SS, 0);
    SetRegister(Register::ES, 0);
    SetRegister(Register::IP, 0);
    SetRegister(Register::FLAGS, 0);
    DataUpdater();
}

void FormGui::about()
{
    QMessageBox::about(this, "Computer::About", tr("<b>Computer</b> is open source frontend for YAPE.<br>"
                                                           "See <b>License</b> for details.<br><br>"
                                                           "Copyright 2014-2017 (C) Robot With Axe Studio"));
    QMessageBox::aboutQt(this);
}

void FormGui::switchPauseIcon(bool sw)
{
    if (!sw)
    {
        widget.actionPause->setIcon(QIcon(":/Icons/icons/Pause_256x256.png"));
        widget.actionPause->setText(tr("&Pause"));
    }
    else
    {
        widget.actionPause->setIcon(QIcon(":/Icons/icons/Play_256x256.png"));
        widget.actionPause->setText(tr("&Unpause"));
    }
}

void FormGui::handlePause()
{
    if (IsPaused())
    {
        Pause(0);
    }
    else
    {
        Pause(1);
    }
    switchPauseIcon(IsPaused());
}

void FormGui::handleStep()
{
    Step();
    switchPauseIcon(1);
}

void FormGui::editor()
{
    feditor->isHidden() ? feditor->show() : feditor->hide();
}

void FormGui::openMem()
{
    fmem->isHidden() ? fmem->show() : fmem->hide();
}

void FormGui::handleRadio(bool state)
{
    if (state)
    {
#define _REG_(r)widget.lcd##r->setDecMode()
        _REG_(AX);
        _REG_(BX);
        _REG_(CX);
        _REG_(DX);
        _REG_(SI);
        _REG_(DI);
        _REG_(SP);
        _REG_(BP);
        _REG_(CS);
        _REG_(DS);
        _REG_(SS);
        _REG_(ES);
        _REG_(IP);
#undef  _REG_
    }
    else
    {
#define _REG_(r)widget.lcd##r->setHexMode()
        _REG_(AX);
        _REG_(BX);
        _REG_(CX);
        _REG_(DX);
        _REG_(SI);
        _REG_(DI);
        _REG_(SP);
        _REG_(BP);
        _REG_(CS);
        _REG_(DS);
        _REG_(SS);
        _REG_(ES);
        _REG_(IP);
#undef _REG_
    }
}

void FormGui::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(this, QApplication::applicationName(), tr("Do you want to close program?"),
                                QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret == QMessageBox::No)
        event->ignore();
    else
        Quit();
}

void FormGui::DataUpdater()
{
#define _REG_(r)widget.lcd##r->display(GetRegister(Register::r))
    _REG_(AX);
    _REG_(BX);
    _REG_(CX);
    _REG_(DX);
    _REG_(SI);
    _REG_(DI);
    _REG_(SP);
    _REG_(BP);
    _REG_(CS);
    _REG_(DS);
    _REG_(SS);
    _REG_(ES);
    _REG_(IP);
#undef _REG_
#define _FLG_(f) widget.cb##f->setChecked(GetFlag(Flag::f));
    _FLG_(Overflow);
    _FLG_(Direction);
    _FLG_(Interrupt);
    _FLG_(Trap);
    _FLG_(Sign);
    _FLG_(Zero);
    _FLG_(Auxiliary);
    _FLG_(Parity);
    _FLG_(Carry);
#undef _FLG_
}
