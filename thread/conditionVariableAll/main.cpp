#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include "myworker.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    const int numThreads = 3;
    QThread* threads[numThreads];
    MyWorker* workers[numThreads];

    for (int i = 0; i < numThreads; ++i) {
        threads[i] = new QThread();
        workers[i] = new MyWorker();

        workers[i]->moveToThread(threads[i]);

        // 线程启动时，工作对象执行 doWork()
        QObject::connect(threads[i], &QThread::started, workers[i], &MyWorker::doWork);

        // 任务完成后退出线程的事件循环
        QObject::connect(workers[i], &MyWorker::finished, threads[i], &QThread::quit);

        // 任务完成后删除工作对象
        QObject::connect(workers[i], &MyWorker::finished, workers[i], &QObject::deleteLater);

        // 线程退出后删除线程对象
        QObject::connect(threads[i], &QThread::finished, threads[i], &QObject::deleteLater);

        threads[i]->start();
    }

    // 2 秒后唤醒所有线程
    QTimer::singleShot(2000, [=]() {
        workers[0]->startWork();  // 让所有 worker 线程醒来
    });

    return app.exec();
}
