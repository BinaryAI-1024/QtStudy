#include "myworker.h"

// 静态成员初始化
QMutex MyWorker::mutex;
int MyWorker::counter = 0;

MyWorker::MyWorker(QObject *parent)
    : QObject(parent)
{
}

void MyWorker::doWork(int id)
{
    qDebug() << "Worker" << id << "started work.";

    for (int i = 0; i < 100000; ++i) {
        QMutexLocker locker(&mutex); // // 加锁以保护数据
        ++counter;
    }


    emit finished(); // 发送完成信号
}

int MyWorker::getCounter()
{
    return counter;
}
