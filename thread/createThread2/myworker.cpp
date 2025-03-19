#include <QDebug>
#include <QThread>
#include "myworker.h"

MyWorker::MyWorker(QObject *parent) : QObject(parent)
{

}


void MyWorker:: working(){
    // 在新线程中执行的代码
    for (int i = 0; i < 5; ++i) {
        qDebug() << "Worker thread is running... (" << i << ")";
        QThread::sleep(1); // 模拟耗时操作
    }

}
