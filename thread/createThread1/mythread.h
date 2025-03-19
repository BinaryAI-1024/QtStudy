#ifndef WORKDER_H
#define WORKDER_H
#include <QThread>
#include <QDebug>


class Mythread: public QThread{
    Q_OBJECT
public:
    explicit Mythread(QObject *parent = nullptr);
    void run();

};

#endif // WORKDER_H
