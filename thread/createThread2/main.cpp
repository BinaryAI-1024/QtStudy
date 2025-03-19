#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include "myworker.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread thread1;
    MyWorker worker;

    // 将 worker 对象移动到 thread1 线程中，以便 working 函数在 thread1 中执行
    worker.moveToThread(&thread1);

    // 连接 QThread 的 started 信号到 MyWorker 的 working 槽函数
    // 当 thread1 启动时，worker 的 working 函数会被调用
    QObject::connect(&thread1, &QThread::started, &worker, &MyWorker::working);
    // 启动 thread1 线程
    thread1.start();


    for (int i = 0; i < 5; ++i) {
        qDebug() << "Main thread is running... (" << i << ")";
        QThread::sleep(1); // 模拟耗时操作
    }

    thread1.wait();

    return a.exec();
}
