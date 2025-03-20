#include <QCoreApplication>
#include <QThread>
#include "myworker.h"
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QMutex mutex;                  // 创建一个互斥锁
    const int numThreads = 3;      // 定义要启动的线程数量
    QThread *threads[numThreads];  // 创建一个 QThread 指针数组，用于存储线程对象
    MyWorker *workers[numThreads]; // 创建一个 MyWorker 指针数组，用于存储工作对象
    int finishedCount = 0;         // 初始化一个计数器，用于跟踪完成的线程数量

    // 循环创建和启动线程
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = new QThread; // 创建一个新线程
        workers[i] = new MyWorker; // 创建一个新工作对象

        workers[i]->moveToThread(threads[i]); // 将工作对象移动到新线程中

        // 连接线程的 started 信号到工作对象的 doWork 槽，使用 QTimer 确保在事件循环开始后执行
        QObject::connect(threads[i], &QThread::started, workers[i], [=]() {
            QTimer::singleShot(0, workers[i], [=]() { workers[i]->doWork(i); });
        });

        // 连接工作对象的 finished 信号到线程的 quit 槽，以便任务完成后退出线程的事件循环
        QObject::connect(workers[i], &MyWorker::finished, threads[i], &QThread::quit);

        // 连接工作对象的 finished 信号到工作对象的 deleteLater 槽，以便任务完成后删除工作对象
        QObject::connect(workers[i], &MyWorker::finished, workers[i], &QObject::deleteLater);

        // 连接线程的 finished 信号到线程的 deleteLater 槽，以便线程退出后删除线程对象
        QObject::connect(threads[i], &QThread::finished, threads[i], &QObject::deleteLater);

        // 连接工作对象的 finished 信号到一个 lambda 表达式，用于更新计数器并检查所有线程是否完成
        QObject::connect(workers[i], &MyWorker::finished, [&finishedCount, &mutex, i]() {
            QMutexLocker locker(&mutex); // 加锁以保护计数器的访问
            ++finishedCount; // 增加已完成线程的计数
            qDebug() << "Worker" << i << "finished. ";
            if (finishedCount == numThreads) { // 检查是否所有线程都已完成
                qDebug() << "counter:" << MyWorker::getCounter(); // 每个线程使counter增加100000，正确结果应该是：numThreads*100000
            }
        });

        threads[i]->start(); // 启动线程
    }


    return app.exec();
}
