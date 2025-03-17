// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef MYMODEL_H
#define MYMODEL_H


#include <QAbstractTableModel>

// 声明MyModel类，它继承自QAbstractTableModel
class MyModel : public QAbstractTableModel {
    Q_OBJECT

public:

    explicit MyModel(QObject *parent = nullptr);
    // 重写rowCount函数，返回模型中的行数
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // 重写columnCount函数，返回模型中的列数
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    // 重写data函数，用于提供模型中特定单元格的数据
    // index参数指定了单元格的位置（行和列），role参数指定了所需数据的类型（如显示文本、工具提示等）
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // MYMODEL_H
