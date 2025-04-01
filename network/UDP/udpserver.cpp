#include "udpserver.h"
#include <QDebug>

// 构造函数，初始化 QUdpSocket 并连接 readyRead 信号
UdpServer::UdpServer(QObject *parent) : QObject(parent), udpSocket(new QUdpSocket(this)) {
    // 当有数据可读时，触发 onReadyRead 处理数据
    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpServer::onReadyRead);
}

// 析构函数，关闭 UDP 套接字
UdpServer::~UdpServer() {
    udpSocket->close();
}

// 绑定端口
void UdpServer::startServer(quint16 port) {
    if (udpSocket->bind(QHostAddress::Any, port)) { // 绑定到所有可用的网络接口
        qDebug() << "UDP Server started on port" << port;
    } else {
        qDebug() << "UDP Server failed to start!";
    }
}

// 处理接收到的数据
void UdpServer::onReadyRead() {
    while (udpSocket->hasPendingDatagrams()) { // 检查是否有未处理的数据包
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize()); // 调整数组大小以容纳数据
        QHostAddress sender; // 发送方 IP 地址
        quint16 senderPort;  // 发送方端口号

        // 读取数据包，并获取发送方地址和端口
        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        qDebug() << "Received from" << sender.toString() << ":" << senderPort << "->" << datagram;

        // 发送响应数据回给客户端
        udpSocket->writeDatagram("Hello from server!", sender, senderPort);
    }
}
