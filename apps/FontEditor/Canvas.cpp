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

#include "Canvas.hpp"
#include <QPainter>
#include <QPixmap>
#include <QTimer>

void Canvas::SetPixel(int x, int y, bool state)
{
    QPainter p(pixmap);
    if(state)
        p.setPen(Qt::white);
    else
        p.setPen(Qt::black);
    p.drawPoint(x,y);
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, width(), height(), *pixmap);
    QWidget::paintEvent( event );
}

Canvas::Canvas(QWidget *parent, Qt::WindowFlags f)
{
    pixmap = new QPixmap(8, 8);

    QPainter p(pixmap);
    p.fillRect(0,0,8,8, QBrush(Qt::black));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(5);
}

void Canvas::Resize(int w, int h)
{
    QPixmap *old = pixmap;
    pixmap = new QPixmap(pixmap->scaled(w, h, Qt::IgnoreAspectRatio, Qt::FastTransformation));
    delete old;
}
