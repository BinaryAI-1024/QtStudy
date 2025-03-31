#include "tcpserver.h"
#include <QDebug>

// 构造函数，初始化 QTcpServer 并连接 newConnection 信号
TcpServer::TcpServer(QObject *parent) : QObject(parent), server(new QTcpServer(this)) {
    // 每次有新连接可用时都会发出 newConnection() 信号
    connect(server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
}

// 析构函数，关闭服务器
TcpServer::~TcpServer() {
    server->close();
}

// 启动服务器，监听指定端口
void TcpServer::startServer(quint16 port) {
    if (server->listen(QHostAddress::Any, port)) {
        qDebug() << "Server started on port" << port;
    } else {
        qDebug() << "Server failed to start!";
    }
}

// 处理新客户端连接
void TcpServer::onNewConnection() {
    clientSocket = server->nextPendingConnection(); // 获取新连接的客户端套接字

    // 连接客户端的 readyRead 信号（有数据可读时触发）
    connect(clientSocket, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);

    // 连接客户端的 disconnected 信号（客户端断开连接时触发）
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);

    qDebug() << "New client connected!";
    clientSocket->write("Hello from server!\n"); // 发送欢迎消息给客户端
}

// 处理客户端发送的数据
void TcpServer::onReadyRead() {
    QByteArray data = clientSocket->readAll(); // 读取客户端数据
    qDebug() << "Received from client:" << data;
}
