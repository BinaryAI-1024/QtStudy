#ifndef MYWORKER_H
#define MYWORKER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>

class MyWorker : public QObject {
    Q_OBJECT
public:
    explicit MyWorker(QObject *parent = nullptr);
    ~MyWorker();
signals:
    void finished();
public slots:
    void doWork();
    void startWork();

private:
    QMutex mutex;              // 每个实例都有一个互斥锁
    QWaitCondition condition;  // 每个实例都有一个条件变量
    bool ready = false;        // 每个实例都有一个标志变量
};

#endif // MYWORKER_H
