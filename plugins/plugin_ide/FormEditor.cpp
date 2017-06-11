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

#include "FormEditor.hpp"
#include "Compiler.hpp"
#include <DeviceAPI.hpp>
#include <components/Memory/Memory.hpp>

FormEditor::FormEditor()
{
    widget.setupUi(this);
    setWindowModality(Qt::NonModal);
    connect(widget.actionBuild, SIGNAL(triggered()), this, SLOT(build()));
    connect(widget.actionClose, SIGNAL(triggered()), this, SLOT(hide()));
    widget.actionNew->setEnabled(0);
    widget.actionHelp->setEnabled(0);
    widget.actionOpen->setEnabled(0);
    widget.actionSave->setEnabled(0);
}

FormEditor::~FormEditor()
{
}

void FormEditor::build()
{
    QString plainTextEditContents = widget.plainTextEdit->toPlainText();
    QStringList source = plainTextEditContents.split("\n");
    Compiler c(&source);
    Code code = c.exec();
    auto mem = GetMemoryPtr();
    for(int i = 0; i < code.size(); i++)
        mem->SetByte((unsigned)i, code.at(i));
}
