#include <QCoreApplication>
#include "udpserver.h"
#include "udpclient.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // 启动服务器
    UdpServer server;
    server.startServer(12345);

    // 启动客户端并发送消息
    UdpClient client;
    client.sendMessage("Hello from client!", "127.0.0.1", 12345);

    return a.exec();
}
