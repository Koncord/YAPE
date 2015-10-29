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

#include <QtWidgets/qmessagebox.h>
#include "FontModel.hpp"

FontModel::FontModel(QObject *parent) : QAbstractListModel(parent)
{
}

/*QHash<int, QByteArray> FontModel::roleNames() const
{
    return roles;
}*/

QVariant FontModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() < 0 || index.row() > symbols.count())
        return QVariant();

    const BitFontChar &ch = symbols.value(index.row());

    if(role == Qt::DisplayRole)
    {
        QVariant var;
        switch (index.column())
        {
            case 0:
                var = ch.index;
                break;
            case 1:
                var = ch.size;
                break;
            case 2:
                var.fromValue(static_cast<void *>(ch.data));
                break;
        }
        return var;
    }
    return QVariant();
}

int FontModel::rowCount(const QModelIndex &) const
{
    return symbols.count();
}

bool FontModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        int row = index.row();
        int col = index.column();

        BitFontChar sym = symbols.value(row);
        if(col == 0)
            sym.index = value.value<char>();
        else if(col == 1)
            sym.size = value.value<uint8_t>();
        else if(col == 2)
            sym.data = static_cast<uint8_t*>(value.value<void*>());

        symbols.replace(row, sym);

        emit(dataChanged(index, index));
        return true;
    }
    return false;
}

QList<BitFontChar> FontModel::GetList()
{
    return symbols;
}

bool FontModel::insertRows(int position, int count, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + count - 1);

    for (int row = position; row < (position + count); row++)
    {
        BitFontChar bfc;
        bfc.index = 0;
        bfc.size = 0;
        bfc.data = nullptr;
        symbols.insert(row, bfc);
    }
    endInsertRows();
    return true;
}
