// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "mymodel.h"


MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

// 实现rowCount函数，返回模型中的行数
int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
    // 表格模型没有使用父/子结构，
    // 所以我们可以忽略parent参数（它通常用于树形或层次结构模型）
    // 在这个例子中，我们简单地返回2，表示模型有两行
    return 2;
}

// 实现columnCount函数，返回模型中的列数
int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    // 与rowCount同样地，忽略parent参数
    // 简单地返回3，表示模型有三列
    return 3;
}

// 实现data函数，用于提供模型中特定单元格的数据
QVariant MyModel::data(const QModelIndex &index, int role) const
{
    // 我们只对Qt::DisplayRole感兴趣，这是用于在视图中显示的数据
    if (role == Qt::DisplayRole) {
        // 使用QString的arg函数来格式化字符串，
        // QModelIndex是Qt中用于定位数据模型数据的一个类，调用其方法
        // 将行号和列号（都加1以符合人类阅读习惯，从1开始计数）插入到字符串中
        return QString("Row%1, Column%2")
                   .arg(index.row() + 1)
                   .arg(index.column() + 1);
    }
    // 对于其他类型的role（如编辑、工具提示等），我们返回QVariant的默认值，
    // 表示没有提供这些数据
    return QVariant();
}
