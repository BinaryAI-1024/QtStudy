// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "mymodel.h"

#include <QFont>
#include <QBrush>
#include <QDebug>

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int MyModel::rowCount(const QModelIndex & /*parent */) const
{
    return 2;
}

int MyModel::columnCount(const QModelIndex & /*parent */) const
{
    return 3;
}

QVariant MyModel::data(const QModelIndex &index, int role) const {
    int row = index.row();    // 从QModelIndex对象中获取当前行的索引
    int col = index.column(); // 从QModelIndex对象中获取当前列的索引


    switch (role) {
    case Qt::DisplayRole: // 处理显示角色的数据
        // 为特定单元格设置自定义显示文本
        if (row == 0 && col == 1) return QString("<--left");
        if (row == 1 && col == 1) return QString("right-->");
        // 为其他单元格返回默认的行列信息文本
        return QString("Row%1, Column%2")
                .arg(row + 1)
                .arg(col + 1);

    case Qt::FontRole: // 处理字体角色的数据
        // 仅为单元格(0,0)设置粗体字体
        if (row == 0 && col == 0) {
            QFont boldFont;
            boldFont.setBold(true);
            return boldFont;
        }
        break;

    case Qt::BackgroundRole: // 处理背景角色的数据
        // 仅为单元格(1,2)设置红色背景
        if (row == 1 && col == 2)
            return QBrush(Qt::red);
        break;

    case Qt::TextAlignmentRole: // 处理文本对齐角色的数据
        // 仅为单元格(1,1)设置文本对齐方式（右对齐和垂直居中）
        if (row == 1 && col == 1)
            return int(Qt::AlignRight | Qt::AlignVCenter);
        break;

    case Qt::CheckStateRole: // 处理复选框状态角色的数据
        // 在单元格(1,0)中添加一个已选中的复选框
        if (row == 1 && col == 0)
            return Qt::Checked;
        break;
    }

    return QVariant();
}
