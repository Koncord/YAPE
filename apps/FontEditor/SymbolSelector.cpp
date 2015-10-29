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

#include "SymbolSelector.hpp"
#include <QMessageBox>
#include <QInputDialog>
#include <assert.h>

FontModel *SymbolSelector::model = nullptr;

SymbolSelector::SymbolSelector()
{
    setupUi(this);

    model = new FontModel;

    listSymbols->setModel(model);

    connect(btnNew, SIGNAL(released()), this, SLOT(createNewSymbol()));
    connect(btnDelete, SIGNAL(released()), this, SLOT(deleteSymbol()));
}

SymbolSelector::~SymbolSelector()
{

}

void SymbolSelector::createNewSymbol()
{
    //listSymbols->addItem("test" + QString::number(listSymbols->count()));
    BitFontChar ch;
    ch.index = static_cast<char>(QInputDialog::getInt(this, "Symbol index", "", 0, 0, 255));
    //if(!model->GetList().contains(ch))
    model->insertRow(0);
    model->setData(model->index(0, 0), ch.index);
    model->setData(model->index(0, 1), ch.size);
}

void SymbolSelector::loadSymbol()
{

}

void SymbolSelector::deleteSymbol()
{

    /*foreach(QListWidgetItem * item, listSymbols->selectedItems())
    {
        //listSymbols->removeItemWidget(item);
        delete item;
    }*/

}

void SymbolSelector::AddSymbol(BitFontChar symb)
{
    assert(model);
    model->insertRows(symb.index, 1);
    model->setData(model->index(symb.index, 0), symb.index);
    model->setData(model->index(symb.index, 1), symb.size);
    model->setData(model->index(symb.index, 2), static_cast<const void *>(symb.data));
}
