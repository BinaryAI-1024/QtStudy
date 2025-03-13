// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "mymodel.h"

#include <QTime>

//! [quoting mymodel_a]
MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
    , timer(new QTimer(this))
{
    // 超时信号，时间间隔设置为1000ms(1s)
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout , this, &MyModel::timerHit);
    timer->start();
}
//! [quoting mymodel_a]
//-------------------------------------------------------
int MyModel::rowCount(const QModelIndex & /*parent */) const
{
    return 2;
}

//-------------------------------------------------------
int MyModel::columnCount(const QModelIndex & /*parent */) const
{
    return 3;
}

//-------------------------------------------------------
//! [quoting mymodel_QVariant ]
QVariant MyModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole && row == 0 && col == 0)
        return QTime::currentTime().toString();

    return QVariant();
}
//! [quoting mymodel_QVariant ]
//-------------------------------------------------------
//! [quoting mymodel_b ]
void MyModel::timerHit()
{

    QModelIndex topLeft = createIndex(0,0);
    //发出信号，使视图重新读取topLeft中已识别的数据
    emit dataChanged(topLeft, topLeft, {Qt::DisplayRole});
}
//! [quoting mymodel_b ]
