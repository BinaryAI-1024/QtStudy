#include <QCoreApplication>
#include <QThread>
#include "producer.h"
#include "consumer.h"

// 定义全局变量
const int BufferSize = 5;
QSemaphore emptySlots(BufferSize); // 管理缓冲区的空闲空间
QSemaphore fullSlots(0);           // 管理缓冲区的已用空间
int buffer[BufferSize];

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // 创建线程
    QThread producerThread, consumerThread;

    // 创建生产者和消费者对象
    Producer producer;
    Consumer consumer;

    // 将对象移动到线程
    producer.moveToThread(&producerThread);
    consumer.moveToThread(&consumerThread);

    // 连接线程启动信号
    QObject::connect(&producerThread, &QThread::started, &producer, &Producer::produce);
    QObject::connect(&consumerThread, &QThread::started, &consumer, &Consumer::consume);

    // 启动线程
    producerThread.start();
    consumerThread.start();



    return a.exec();
}
