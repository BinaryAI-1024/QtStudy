#include <QCoreApplication>
#include <QThreadPool>
#include <QRunnable>
#include <QDebug>
#include <QThread>

class MyTask : public QRunnable {
public:
    void run() override {
        qDebug() << "Task running on thread:" << QThread::currentThread();
        QThread::sleep(1);  // 模拟任务执行
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QThreadPool *threadPool = QThreadPool::globalInstance();
    threadPool->setMaxThreadCount(4);  // 设置最大并发线程数

    for (int i = 0; i < 10; ++i) {
        MyTask *task = new MyTask();
        task->setAutoDelete(true);  // 任务执行完成后自动删除
        threadPool->start(task);
    }

    threadPool->waitForDone();  // 等待所有任务完成
    return 0;
}
