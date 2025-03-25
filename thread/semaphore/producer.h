#ifndef PRODUCER_H
#define PRODUCER_H

#include <QObject>
#include <QSemaphore>

// 引用main.cpp中的全局变量，避免重复定义
extern QSemaphore emptySlots;
extern QSemaphore fullSlots;
extern int buffer[];
extern const int BufferSize;

class Producer : public QObject {
    Q_OBJECT
public:
    explicit Producer(QObject *parent = nullptr);

public slots:
    void produce();
};

#endif // PRODUCER_H
