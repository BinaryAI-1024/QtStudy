#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QUdpSocket>
#include <QObject>

class UdpClient : public QObject {
    Q_OBJECT
public:
    explicit UdpClient(QObject *parent = nullptr);
    ~UdpClient();

    void sendMessage(const QString &message, const QString &host, quint16 port);

private slots:
    void onReadyRead(); // 处理服务器返回的数据

private:
    QUdpSocket *udpSocket;
};

#endif // UDPCLIENT_H
