#include <QCoreApplication>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QDebug>

int heavyTask(int value) {
    QThread::sleep(2);  // 模拟耗时任务
    return value * 2;
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QFutureWatcher<int> watcher;

    // 监听任务完成信号
    QObject::connect(&watcher, &QFutureWatcher<int>::finished, [&]() {
        qDebug() << "Async result:" << watcher.future().result();
        QCoreApplication::quit();  // 任务完成后退出应用
    });

    // 启动异步任务
    QFuture<int> future = QtConcurrent::run(heavyTask, 10);
    watcher.setFuture(future);  // 关联 watcher

    qDebug() << "Main thread is running...";

    return app.exec();  // 进入事件循环
}
