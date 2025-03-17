// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


#include <QApplication>
#include <QTableView>   // 引入的视图类，用于以表格形式显示数据。
#include "mymodel.h"    // 引入自定义的模型类头文件,用于提供数据给视图。

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    // 创建QTableView对象tableView
    QTableView tableView;
    // 创建自定义模型对象myModel
    MyModel myModel;
    // 通过调用tableView的setModel方法，将自定义模型myModel设置为tableView的数据源。
    // 这样，tableView就可以从myModel中获取数据并进行显示了。
    tableView.setModel(&myModel);
    // 调用tableView的show方法，显示表格视图。
    tableView.show();
    return a.exec();
}
