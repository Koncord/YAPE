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

#include "FormDisplay.hpp"
#include <QtGui>

FormDisplay::FormDisplay()
{
    widget.setupUi(this);
}

FormDisplay::~FormDisplay()
{
    
}

void FormDisplay::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect rect(0,0,16,16);
    painter.fillRect(rect, QBrush(QColor(128, 128, 255, 128)));
}