#include <QCoreApplication>
#include <QAtomicInteger>
#include <QThread>
#include <QDebug>

QAtomicInteger<int> counter(0);  // 线程安全的计数器

void threadFunc() {
    for (int i = 0; i < 10; ++i) {
        // 原子递增,多个线程操作时不会出现数据竞争
        counter.fetchAndAddRelaxed(1);
        QThread::msleep(100);  // 模拟工作
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // 使用 QThread::create 创建线程
    QThread *t1 = QThread::create(threadFunc);
    QThread *t2 = QThread::create(threadFunc);

    t1->start();
    t2->start();

    t1->wait();
    t2->wait();

    qDebug() << "Final counter value:" << counter.load();

    delete t1;
    delete t2;

    return 0;
}
