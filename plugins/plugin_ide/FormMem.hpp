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

#ifndef _FORMMEM_HPP
#define	_FORMMEM_HPP

#include "ui_FormMem.h"

class FormMem : public QMainWindow
{
    Q_OBJECT
public:
    FormMem();
    virtual ~FormMem();
    void Update();
    private slots:
        void handleDClick(int, int);
        void handleUpdate();
        void search();
private:
    Ui::FormMem widget;
};

#endif	/* _FORMMEM_HPP */
