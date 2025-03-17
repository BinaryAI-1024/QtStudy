// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Qt 的命名空间开始，这里使用了前向声明来减少头文件的依赖
QT_BEGIN_NAMESPACE
class QTreeView;       // QTreeView 类的前向声明，用于在 MainWindow 中作为成员变量
class QStandardItemModel; // QStandardItemModel 类的前向声明，用于存储树形视图的数据
class QStandardItem;    // QStandardItem 类的前向声明，通常用于构建 QStandardItemModel 的内容
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

private:
    // 辅助函数，用于准备一行数据，并返回一个包含三个 QStandardItem* 的列表
    // 这些 QStandardItem 分别对应于行中的第一、第二和第三个数据项
    QList<QStandardItem*> prepareRow(const QString &first,
                                     const QString &second,
                                     const QString &third) const;

    // 成员变量
    QTreeView *treeView;          // 指向 QTreeView 的指针，用于显示树形结构的数据
    QStandardItemModel *standardModel; // 指向 QStandardItemModel 的指针，作为树形视图的数据源
};

#endif // MAINWINDOW_H
