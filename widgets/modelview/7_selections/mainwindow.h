// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>


QT_BEGIN_NAMESPACE
// 前向声明 QTreeView 类， 这对于减少编译时间和避免循环依赖很有用
class QTreeView;
class QStandardItemModel;
class QItemSelection;

QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    // 一个私有槽函数，它将在 QTreeView 的选择发生变化时被调用
    void selectionChangedSlot(const QItemSelection &newSelection, const QItemSelection &oldSelection);

private:

    QTreeView *treeView;  // 树视图
    QStandardItemModel *standardModel;   // 为 treeView 提供数据模型
};

#endif // MAINWINDOW_H
