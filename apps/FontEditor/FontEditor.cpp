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

#include "FontEditor.hpp"
#include "SymbolSelector.hpp"
#include <QMouseEvent>
#include <QPixmap>
#include <QPainter>
#include <components/Utils/Utils.hpp>
#include <QFileDialog>
#include <limits>

MainForm *MainForm::mThis = nullptr;
MainForm::MainForm(QWidget *parent)
{
    mThis = this;
    Q_UNUSED(parent)
    setupUi(this);
    fontHeader.size_height = 8;
    fontHeader.size_width = 8;
    connect(actionLoad, SIGNAL(triggered()), this, SLOT(load()));
}

MainForm::~MainForm()
{
    mThis = nullptr;
}

QPoint MainForm::GetMouseCoord(QMouseEvent *event)
{
    QPoint mcoords {-1,-1};

    if(event->x() >= 0 && event->x() < canvas->width() && event->y() >= 0 && event->y() < canvas->height())
    {
        mcoords.setX(Utils::map(event->x(), canvas->width(), fontHeader.size_width));
        mcoords.setY(Utils::map(event->y(), canvas->height(), fontHeader.size_height));
    }

    return mcoords;
}
unsigned int buttonStatus;
void MainForm::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
        buttonStatus = event->button();
    else if(event->button() == Qt::MouseButton::RightButton)
        buttonStatus = event->button();

    mouseEvent(event);
    QWidget::mousePressEvent(event);
}

void MainForm::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == buttonStatus)
        buttonStatus = 0;

    mouseEvent(event);
    QWidget::mouseReleaseEvent(event);
}

void MainForm::mouseMoveEvent(QMouseEvent *event)
{
    mouseEvent(event);
    QWidget::mouseMoveEvent(event);
}


void MainForm::mouseEvent(QMouseEvent *event)
{
    if(buttonStatus)
    {
        QString btn;

        if(buttonStatus == Qt::MouseButton::LeftButton)
            btn = "LMB";
        else if(buttonStatus == Qt::MouseButton::RightButton)
            btn = "RMB";

        const QPoint coords = GetMouseCoord(event);
        if(coords.x() != -1 && coords.y() != -1)
        {
            canvas->SetPixel(coords.x(), coords.y(), buttonStatus == Qt::MouseButton::LeftButton);
            QString qstr = QString::number(coords.x()) + " : " + QString::number(coords.y()) + " | " + btn;
            statusbar->showMessage(qstr);
        }
    }
}

void MainForm::load()
{
    //QMessageBox::information(this, "test", "test");
    QString qstr = QFileDialog::getOpenFileName(this, tr("Open Font"), "", tr("Font (*.bfnt)"));
    if(!qstr.isEmpty())
    {
        const char *str = qstr.toLatin1().data();
        BitFont fnt(str);
        fnt.Load();
        fontHeader = fnt.GetHeader();
        for(uint8_t i = 0; i < std::numeric_limits<uint8_t>::max(); i++)
        {
            BitFontChar *chr = fnt.GetSymbol(i);
            if(chr != nullptr)
            {
                // load char
                SymbolSelector::AddSymbol(*chr);
            }
        }
    }
}

MainForm::MainForm(uint8_t *data, uint8_t size, QWidget *parent) : MainForm(parent)
{
    Q_UNUSED(data)
    Q_UNUSED(size)
}

MainForm *MainForm::get()
{
    return mThis;
}

void MainForm::SetChar(uint8_t *data, uint16_t size)
{
    uint16_t x = 0;
    uint16_t y = 0;
    for(uint16_t i = 0; i < size; i++)
    {
        if(y >= fontHeader.size_height)
            break;
        canvas->SetPixel(x,y, data[i] == 1);
        x++;
        if(x == fontHeader.size_width)
        {
            x = 0;
            y++;
        }
    }
}
