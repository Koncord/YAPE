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

#include "SymbolSelector.hpp"
#include "FontEditor.hpp"
#include <QMessageBox>
#include <QInputDialog>
#include <assert.h>

FontModel *SymbolSelector::model = nullptr;
static QWidget *hParent = nullptr;

SymbolSelector::SymbolSelector(QWidget *parent)
{
    setupUi(this);

    assert(!model);
    model = new FontModel;

    hParent = parent;

    listSymbols->setModel(model);

    connect(btnNew, SIGNAL(released()), this, SLOT(createNewSymbol()));
    connect(btnDelete, SIGNAL(released()), this, SLOT(deleteSymbol()));
    connect(btnSelect, SIGNAL(released()), this, SLOT(loadSymbol()));
    connect(btnSave, SIGNAL(released()), this, SLOT(saveSymbol()));
}

SymbolSelector::~SymbolSelector()
{

}

void SymbolSelector::createNewSymbol()
{
    //listSymbols->addItem("test" + QString::number(listSymbols->count()));
    BitFontChar ch;
    ch.index = static_cast<uint8_t>(QInputDialog::getInt(this, "Symbol index", "", 0, 0, 255));
    //if(!model->GetList().contains(ch))
    model->insertRow(ch.index);
    model->setData(model->index(ch.index, 0), ch.index);
    model->setData(model->index(ch.index, 1), ch.size);
}

void SymbolSelector::loadSymbol()
{
    if(listSymbols->selectionModel()->selectedIndexes().isEmpty()) return;
    int row = listSymbols->selectionModel()->selectedIndexes().begin()->row();
    uint8_t size = static_cast<uint8_t>(model->data(model->index(row, 1)).toInt(0));
    uint8_t *data = static_cast<uint8_t*>(model->data(model->index(row, 2)).value<void*>());
    MainForm::get()->SetChar(model->data(model->index(row, 0)).toInt(0), data, size);
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

void SymbolSelector::closeEvent(QCloseEvent *event)
{
    hParent->close();
}

void SymbolSelector::saveSymbol()
{
    if(listSymbols->selectionModel()->selectedIndexes().isEmpty()) return;
    int row = listSymbols->selectionModel()->selectedIndexes().begin()->row();

    const BitFontHeader &fontHeader = MainForm::get()->fontHeader;

    int size = fontHeader.size_width * fontHeader.size_height;

    uint16_t x = 0;
    uint16_t y = 0;

    BitFontChar chr;
    chr.index = model->data(model->index(row, 0)).value<uint8_t>();
    chr.size = model->data(model->index(row, 1)).value<uint8_t>();
    chr.data = new uint8_t[chr.size];

    for(int i = 0; i < size; i++)
    {
        if(y >= fontHeader.size_height)
            break;
        chr.data[i] = MainForm::get()->canvas->GetPixel(x,y) ? 1 : 0;
        x++;
        if(x == fontHeader.size_width)
        {
            x = 0;
            y++;
        }
    }
    AddSymbol(chr);
}
