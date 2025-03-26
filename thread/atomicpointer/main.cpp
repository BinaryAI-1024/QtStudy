#include <QCoreApplication>
#include <QAtomicPointer>
#include <QThread>
#include <QDebug>

struct Node {
    int value;
};

QAtomicPointer<Node> atomicPtr(nullptr);

void threadFunc() {
    Node* newNode = new Node{42};
    atomicPtr.store(newNode);  // 线程安全地存储指针
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QThread *t = QThread::create(threadFunc);

    t->start();
    t->wait();

    qDebug() << "Atomic Pointer Value:" << atomicPtr.load()->value;

    delete atomicPtr.load();  // 释放内存
    return 0;
}
