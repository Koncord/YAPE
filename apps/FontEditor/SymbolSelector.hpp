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

#ifndef YAPE_SYMBOLSELECTOR_HPP
#define YAPE_SYMBOLSELECTOR_HPP

#include <components/BitFont/BitFont.hpp>
#include <QtGui/qevent.h>

#include "ui_SymbolSelector.h"
#include "FontModel.hpp"

class SymbolSelector: public QDialog, private Ui::SymbolSelector
{
    Q_OBJECT
public:
    explicit SymbolSelector(QWidget *parent = 0);
    virtual ~SymbolSelector();
    static void AddSymbol(BitFontChar symb);
private slots:
    void createNewSymbol();
    void loadSymbol();
    void deleteSymbol();
    void saveSymbol();
    virtual void closeEvent(QCloseEvent *event);
private:
    static FontModel *model;
};


#endif //YAPE_SYMBOLSELECTOR_HPP
