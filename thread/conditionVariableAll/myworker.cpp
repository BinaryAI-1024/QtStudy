#include "myworker.h"
#include <QMutexLocker>
// 共享变量初始化
QMutex MyWorker::mutex;
QWaitCondition MyWorker::condition;
bool MyWorker::ready = false;

MyWorker::MyWorker(QObject *parent) : QObject(parent) {}

MyWorker::~MyWorker() {
    qDebug() << QThread::currentThread() << "Worker destroyed";
}

void MyWorker::doWork() {
    qDebug() << QThread::currentThread() << "Worker waiting...";

    {
        QMutexLocker locker(&mutex);  // 加锁
        while (!ready) {  // 等待被唤醒
            condition.wait(&mutex);
        }
    }


    qDebug() << QThread::currentThread() << "Worker processing...";
    QThread::msleep(2000);
    qDebug() << QThread::currentThread() << "Worker finished!";
    emit finished();
}


void MyWorker::startWork() {
    QMutexLocker locker(&mutex);
    ready = true;
    condition.wakeAll();  // 唤醒所有等待的线程
}
