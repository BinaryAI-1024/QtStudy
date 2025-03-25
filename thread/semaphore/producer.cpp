#include "producer.h"
#include <QDebug>
#include <QThread>


Producer::Producer(QObject *parent) : QObject(parent) {}


void Producer::produce() {
    for (int i = 0; i < 10; ++i) {
        emptySlots.acquire();  //  等待，直到缓冲区有空位,如果有emptySlots计数-1
        buffer[i % BufferSize] = i;
        qDebug() << "Produced:" << i << "by thread" << QThread::currentThread();
        fullSlots.release();   // 生产了一个数据:fullSlots计数+1
        QThread::msleep(500);
    }
}
