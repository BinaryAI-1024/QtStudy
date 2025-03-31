#include <QCoreApplication>
#include "tcpserver.h"
#include "tcpclient.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // 启动服务器
    TcpServer server;
    server.startServer(12345);

    // 启动客户端，连接到服务器
    TcpClient client;
    client.connectToServer("127.0.0.1", 12345);

    return a.exec();
}
