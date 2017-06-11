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

#ifndef _MAINFORM_HPP
#define	_MAINFORM_HPP

#include <QPoint>
#include <components/BitFont/BitFont.hpp>
#include <unordered_map>
#include "SymbolSelector.hpp"

#include "ui_FontEditor.h"

class MainForm : public QMainWindow,  private Ui::FontEditor
{
    Q_OBJECT
    friend class SymbolSelector;
public:
    explicit MainForm(QWidget *parent = 0);
    MainForm(uint8_t *data, uint8_t size, QWidget *parent);
    virtual ~MainForm();
    static MainForm *get();
    void SetChar(uint8_t id, uint8_t *data, uint16_t size);
protected:
    QPoint GetMouseCoord(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseEvent(QMouseEvent *event);
protected slots:
    void load();
    virtual void closeEvent(QCloseEvent *event);
private:
    static MainForm *mThis;
    BitFontHeader fontHeader;
    SymbolSelector *selector;
};

#endif	/* _MAINFORM_HPP */
