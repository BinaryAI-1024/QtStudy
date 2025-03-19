#ifndef MYWORKER_H
#define MYWORKER_H

#include <QObject>
class MyWorker : public QObject
{
public:
    explicit MyWorker(QObject *parent = nullptr);
    void working();

};

#endif // MYWORKER_H
