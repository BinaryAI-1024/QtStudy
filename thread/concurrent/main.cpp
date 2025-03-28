#include <QCoreApplication>
#include <QtConcurrent>
#include <QDebug>
#include <QThread>
#include <QFuture>
// 模拟耗时任务
int heavyTask(int value) {
    QThread::sleep(2);  // 模拟耗时任务
    return value * 2;
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // 使用 QtConcurrent::run 启动异步任务
    QFuture<int> future = QtConcurrent::run(heavyTask, 10);

    // 这里可以执行其他任务，不会阻塞主线程
    qDebug() << "Main thread is running...";

    // 获取结果（阻塞，直到任务完成）
    int result = future.result();
    qDebug() << "Async result:" << result;

    return 0;
}
