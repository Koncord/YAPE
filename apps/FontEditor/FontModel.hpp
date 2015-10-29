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

#ifndef YAPE_FONTMODEL_HPP
#define YAPE_FONTMODEL_HPP

#include <QObject>
#include <QAbstractListModel>
#include <components/BitFont/BitFont.hpp>

class FontModel: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FontModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QList<BitFontChar> GetList();
    bool insertRows(int row, int count, const QModelIndex &index = QModelIndex());
public:
    QList<BitFontChar> symbols;
    QHash<int, QByteArray> roles;
};


#endif //YAPE_FONTMODEL_HPP
