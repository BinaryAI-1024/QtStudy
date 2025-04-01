#include "udpclient.h"
#include <QDebug>

// 构造函数，初始化 QUdpSocket 并连接 readyRead 信号
UdpClient::UdpClient(QObject *parent) : QObject(parent), udpSocket(new QUdpSocket(this)) {
    // 当有数据可读时，触发 onReadyRead 处理数据
    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpClient::onReadyRead);
}

// 析构函数，关闭 UDP 套接字
UdpClient::~UdpClient() {
    udpSocket->close();
}

// 发送 UDP 数据到指定的 IP 和端口
void UdpClient::sendMessage(const QString &message, const QString &host, quint16 port) {
    udpSocket->writeDatagram(message.toUtf8(), QHostAddress(host), port);
}

// 处理接收到的数据
void UdpClient::onReadyRead() {
    while (udpSocket->hasPendingDatagrams()) { // 检查是否有未处理的数据包
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize()); // 调整数组大小以容纳数据
        udpSocket->readDatagram(datagram.data(), datagram.size()); // 读取数据包
        qDebug() << "Received from server:" << datagram; // 输出接收到的数据
    }
}
