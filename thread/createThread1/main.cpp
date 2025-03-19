#include <QCoreApplication>
#include "Mythread.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Mythread thread1;

    // 启动 thread1 线程
    thread1.start();

    for (int i = 0; i < 5; ++i) {
        qDebug() << "Main thread is running... (" << i << ")";
        QThread::sleep(1); // 模拟耗时操作
    }

    thread1.wait(); // 等待直到thread1线程结束
    return a.exec();
}
