#include "consumer.h"
#include <QDebug>
#include <QThread>


Consumer::Consumer(QObject *parent) : QObject(parent) {}


void Consumer::consume() {
    for (int i = 0; i < 10; ++i) {
        fullSlots.acquire();  // 等待有可消费的数据，如果有fullSlots计数-1
        int data = buffer[i % BufferSize];  // 现在 BufferSize 可用
        qDebug() << "Consumed:" << data << "by thread" << QThread::currentThread();
        emptySlots.release(); // 释放空槽位emptySlots计数+1
        QThread::msleep(1000);
    }
}
