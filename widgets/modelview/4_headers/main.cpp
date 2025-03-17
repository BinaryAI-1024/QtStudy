// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QApplication>
#include <QTableView>
#include "mymodel.h"
#include <QHeaderView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;
    MyModel myModel;
    tableView.setModel(&myModel);
//    tableView.horizontalHeader()->hide();  // 隐藏水平标头
//    tableView.verticalHeader()->hide();    // 隐藏垂直标头
    tableView.show();
    return a.exec();
}
