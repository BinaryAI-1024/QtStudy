#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>


class TcpServer : public QObject {
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    ~TcpServer();

    void startServer(quint16 port); // 启动服务器并监听指定端口

private slots:
    void onNewConnection(); // 处理新的客户端连接
    void onReadyRead(); // 处理客户端发送的数据

private:
    QTcpServer *server; // 监听 TCP 连接的服务器对象
    QTcpSocket *clientSocket; // 当前连接的客户端套接字
};

#endif // TCPSERVER_H
