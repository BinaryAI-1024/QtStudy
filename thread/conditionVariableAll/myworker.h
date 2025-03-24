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
    static QMutex mutex;  // 互斥锁（多个 MyWorker 共享）
    static QWaitCondition condition;  // 等待条件（多个 MyWorker 共享）
    static bool ready;  // 共享的标志变量
};

#endif // MYWORKER_H
