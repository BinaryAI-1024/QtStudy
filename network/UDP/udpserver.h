#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QUdpSocket>
#include <QObject>

class UdpServer : public QObject {
    Q_OBJECT
public:
    explicit UdpServer(QObject *parent = nullptr);
    ~UdpServer();

    void startServer(quint16 port); // 启动服务器

private slots:
    void onReadyRead(); // 处理接收的数据

private:
    QUdpSocket *udpSocket; // UDP 套接字
};

#endif // UDPSERVER_H
