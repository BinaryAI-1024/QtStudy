#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include <QSemaphore>

// 引用main.cpp中的全局变量，避免重复定义
extern QSemaphore emptySlots;
extern QSemaphore fullSlots;
extern int buffer[];
extern const int BufferSize;  // 添加 BufferSize 声明

class Consumer : public QObject {
    Q_OBJECT
public:
    explicit Consumer(QObject *parent = nullptr);

public slots:
    void consume();
};

#endif // CONSUMER_H
