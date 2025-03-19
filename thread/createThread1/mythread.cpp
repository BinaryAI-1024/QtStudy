#include "Mythread.h"

Mythread::Mythread(QObject *parent) : QThread(parent)
{

}


void Mythread::run(){

    // 在新线程中执行的代码
    for (int i = 0; i < 5; ++i) {
        qDebug() << "Worker thread is running... (" << i << ")";
        QThread::sleep(1); // 模拟耗时操作
    }
}



