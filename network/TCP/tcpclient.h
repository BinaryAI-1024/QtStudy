#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include <QObject>


class TcpClient : public QObject {
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    ~TcpClient();

    void connectToServer(const QString &host, quint16 port); // 连接到指定服务器

private slots:
    void onConnected(); // 处理成功连接到服务器的事件
    void onReadyRead(); // 处理从服务器接收的数据

private:
    QTcpSocket *socket; // 客户端 TCP 套接字对象
};

#endif // TCPCLIENT_H
