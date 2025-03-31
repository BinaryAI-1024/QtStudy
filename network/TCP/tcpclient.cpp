#include "tcpclient.h"
#include <QDebug>

// TcpClient 构造函数，初始化 QTcpSocket 并连接信号槽
TcpClient::TcpClient(QObject *parent) : QObject(parent), socket(new QTcpSocket(this)) {
    connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected); // 连接成功信号
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead); // 读取数据信号
}

// TcpClient 析构函数，关闭套接字
TcpClient::~TcpClient() {
    socket->close();
}

// 连接到服务器的指定主机和端口
void TcpClient::connectToServer(const QString &host, quint16 port) {
    socket->connectToHost(host, port);
}

// 处理成功连接到服务器的事件
void TcpClient::onConnected() {
    qDebug() << "Connected to server!";
    socket->write("Hello from client!\n"); // 发送消息给服务器
}

// 处理从服务器接收的数据
void TcpClient::onReadyRead() {
    QByteArray data = socket->readAll();
    qDebug() << "Received from server:" << data;
}
