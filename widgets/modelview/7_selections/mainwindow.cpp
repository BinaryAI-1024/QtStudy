// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//! [quoting modelview_a]
#include "mainwindow.h"

#include <QTreeView>
#include <QStandardItemModel>
#include <QItemSelectionModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , treeView(new QTreeView(this))
    , standardModel(new QStandardItemModel(this))
{
    setCentralWidget(treeView);
    auto *rootNode = standardModel->invisibleRootItem();


    // 让我们创建几个`QStandardItem`：
    auto *americaItem = new QStandardItem("America");
    auto *mexicoItem =  new QStandardItem("Canada");
    auto *usaItem =     new QStandardItem("USA");
    auto *bostonItem =  new QStandardItem("Boston");
    auto *europeItem =  new QStandardItem("Europe");
    auto *italyItem =   new QStandardItem("Italy");
    auto *romeItem =    new QStandardItem("Rome");
    auto *veronaItem =  new QStandardItem("Verona");

    // 建立层次结构
    rootNode->    appendRow(americaItem);
    rootNode->    appendRow(europeItem);
    americaItem-> appendRow(mexicoItem);
    americaItem-> appendRow(usaItem);
    usaItem->     appendRow(bostonItem);
    europeItem->  appendRow(italyItem);
    italyItem->   appendRow(romeItem);
    italyItem->   appendRow(veronaItem);

    // 将模型设置给 treeView
    treeView->setModel(standardModel);
    treeView->expandAll();  // 展开树视图中的所有项

    // 连接选择模型的 selectionChanged 信号到 MainWindow 的 selectionChangedSlot 槽函数
    QItemSelectionModel *selectionModel = treeView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged,
            this, &MainWindow::selectionChangedSlot);
}
//! [quoting modelview_a]

//------------------------------------------------------------------------------------

//! [quoting modelview_b]
void MainWindow::selectionChangedSlot(const QItemSelection & /*newSelection*/, const QItemSelection & /*oldSelection*/)
{
    // 不使用 newSelection 和 oldSelection 参数，因此用注释标记为未使用
    // 获取当前选中的项的 QModelIndex
    const QModelIndex index = treeView->selectionModel()->currentIndex();

    // 从 QModelIndex 中获取显示数据（通常是文本），并将其转换为 QString
    QString selectedText = index.data(Qt::DisplayRole).toString();

    // 初始化层级级别为 1，因为顶层项（直接挂在根节点下的项）的层级为 1
    int hierarchyLevel = 1;

    // 从当前选中项的 QModelIndex 开始，向上遍历其父节点
    QModelIndex seekRoot = index;
    while (seekRoot.parent().isValid()) // 当父节点存在时继续循环
    {
        seekRoot = seekRoot.parent(); // 移动到父节点
        hierarchyLevel++; // 每向上移动一级，层级级别加 1
    }

    // 构建一个包含选中项文本和层级级别的字符串
    QString showString = QString("%1, Level %2").arg(selectedText).arg(hierarchyLevel);

    // 将构建的字符串设置为 MainWindow 的窗口标题
    setWindowTitle(showString);
}
//! [quoting modelview_b]


