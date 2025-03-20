#ifndef MYWORKER_H
#define MYWORKER_H

#include <QObject>
#include <QMutex>
#include <QDebug>

class MyWorker : public QObject
{
    Q_OBJECT
signals:
    void finished();

public:
    explicit MyWorker(QObject *parent = nullptr);

    // 获取 counter 的值
    static int getCounter();

public slots:
    void doWork(int id);

private:
    static QMutex mutex;
    static int counter;
};

#endif // MYWORKER_H
