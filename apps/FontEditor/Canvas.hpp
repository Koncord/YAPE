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

#ifndef YAPE_CANVAS_HPP
#define YAPE_CANVAS_HPP

#include <QWidget>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget* parent = 0, Qt::WindowFlags f = 0);
    void SetPixel(int x, int y, bool state);
    bool GetPixel(int x, int y);
    void Resize(int w, int h);
    void Clear();
private:
    void paintEvent(QPaintEvent * event);
    QPixmap *pixmap;
};


#endif //YAPE_CANVAS_HPP
