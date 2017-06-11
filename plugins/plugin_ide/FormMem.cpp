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

#include "FormMem.hpp"
#include <DeviceAPI.hpp>
#include <components/Opcode/Opcode.hpp>
#include <components/Memory/Memory.hpp>
#include <QTableWidgetItem>
#include <iostream>
#include <QInputDialog>
#include <QTimer>
#include <QMessageBox>
#define GetCellId(sX, sY) sY * widget.tableWidget->columnCount() + sX
#define GetCellPosX(cell)  (int)(cell % widget.tableWidget->columnCount())
#define GetCellPosY(cell)  (int)(cell / widget.tableWidget->columnCount())
using namespace std;

FormMem::FormMem()
{
    widget.setupUi(this);
    setWindowModality(Qt::NonModal);

    uint32_t memSize = GetMemoryPtr()->GetSize();
    widget.tableWidget->setColumnCount(16);
    widget.tableWidget->setRowCount(memSize / 16);
    connect(widget.tableWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(handleDClick(int, int)));
    connect(widget.actionSearch, SIGNAL(triggered()), this, SLOT(search()));
    uint32_t r = widget.tableWidget->rowCount();
    uint32_t c = widget.tableWidget->columnCount();
    QString str = QString::number(0, 16);
    for (uint32_t y = 0; y < r; y++)
        for (uint32_t x = 0; x < c; x++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(str.toUpper());
            item->setTextAlignment(Qt::AlignCenter);
            widget.tableWidget->setItem(y, x, item);
        }
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(handleUpdate()));
    timer->start(250);
}

FormMem::~FormMem()
{

}

void FormMem::handleUpdate()
{
    Update();
}

void FormMem::search()
{
    bool ok;
    int target = QInputDialog::getInt(this, tr("Find"),
                                      tr("Cell:"), 0, 0, GetMemoryPtr()->GetSize()-1, 1, &ok);

    uint32_t row = widget.tableWidget->rowCount();
    uint32_t col = widget.tableWidget->columnCount();
    for (uint32_t r = 0; r < row; r++)
        for (uint32_t c = 0; c < col; c++)
            widget.tableWidget->item(r, c)->setSelected(false);
    QTableWidgetItem *item = widget.tableWidget->item(GetCellPosY(target), GetCellPosX(target));
    item->setSelected(true);
    widget.tableWidget->scrollToItem(item);
}

void FormMem::handleDClick(int row, int col)
{
    bool ok;
    int cellid = GetCellId(col, row);
    cout << "row: " << row << " col: " << col << " cell: " << cellid << endl;
    uint8_t def = GetMemoryPtr()->GetByte(cellid);
    uint8_t i = QInputDialog::getInt(this, tr("Cell"),
                                     tr("Cell:"), def, 0, 0xFF, 1, &ok);
    if (ok)
    {
        QString str = QString::number(i, 16);
        widget.tableWidget->item(row, col)->setText(str.toUpper());

        GetMemoryPtr()->SetByte(cellid, i);
    }

}

void FormMem::Update()
{
    uint32_t r = widget.tableWidget->rowCount();
    uint32_t c = widget.tableWidget->columnCount();

    auto mem = GetMemoryPtr();

    uint32_t memSize = mem->GetSize();
    for (uint32_t y = 0; y < r; y++)
    {
        for (uint32_t x = 0; x < c; x++)
        {
            uint32_t cell = GetCellId(x, y);
            if (cell < memSize)
            {
                QString str = QString::number(mem->GetByte(cell), 16);

                widget.tableWidget->item(y, x)->setText(str.toUpper());
            }
        }
    }
}
