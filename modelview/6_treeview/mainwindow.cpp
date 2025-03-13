// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//! [Quoting ModelView Tutorial]
// modelview.cpp
#include "mainwindow.h"

#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , treeView(new QTreeView(this)) // 创建 QTreeView 对象，并将其父对象设置为当前 MainWindow
    , standardModel(new QStandardItemModel(this)) // 创建 QStandardItemModel 对象，并将其父对象设置为当前 MainWindow
{
    // 将 treeView 设置为 MainWindow 的中心部件
    setCentralWidget(treeView);

    // 准备一行数据
    QList<QStandardItem *> preparedRow = prepareRow("first", "second", "third");

    // 获取模型的不可见根项（即模型的顶层项，它本身不显示）
    QStandardItem *item = standardModel->invisibleRootItem();

    // 向不可见根项添加一行数据，这将作为模型的根元素显示
    item->appendRow(preparedRow);

    // 准备第二行数据
    QList<QStandardItem *> secondRow = prepareRow("111", "222", "333");

    // 将第二行数据添加到第一行数据的第一个单元格对应的项下，这将创建一个子树
    preparedRow[0]->appendRow(secondRow);

    // 为 treeView 设置模型
    treeView->setModel(standardModel);

    // 展开 treeView 中的所有项
    treeView->expandAll();
}

// prepareRow 成员函数，用于准备一行数据
QList<QStandardItem *> MainWindow::prepareRow(const QString &first,
                                              const QString &second,
                                              const QString &third) const
{
    // 创建一个包含三个 QStandardItem 对象的列表，并将它们分别初始化为 first, second, third 字符串
    return {new QStandardItem(first),
            new QStandardItem(second),
            new QStandardItem(third)};
}
//! [Quoting ModelView Tutorial]
