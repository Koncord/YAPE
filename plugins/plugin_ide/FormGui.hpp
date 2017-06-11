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

#ifndef _FORMGUI_HPP
#define	_FORMGUI_HPP

#include "ui_FormGui.h"
#include "FormMem.hpp"
#include "FormEditor.hpp"
class FormGui : public QMainWindow
{
    Q_OBJECT
public:
    FormGui();
    virtual ~FormGui();
    void DataUpdater(); 
    private slots:
        void handleStep();
        void handleRadio(bool state);
        void openMem();
        void handlePause();
        void about();
        void editor();
        void reset();
        void switchPauseIcon(bool sw = 1);
private:
    Ui::FormGui widget;
    FormMem *fmem;
    FormEditor *feditor;
    void closeEvent(QCloseEvent *);
};

#endif	/* _FORMGUI_HPP */
