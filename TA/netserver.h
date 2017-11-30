#ifndef NETSERVER_H
#define NETSERVER_H

#include <QtNetwork>

static quint16 c_port = 55555;
static QHostAddress c_HostAdress;

class NetServer : public QObject
{
    Q_OBJECT

public:
    explicit NetServer(QObject *parent = 0);



private:
    QHostAddress getIpAdress();

    QUdpSocket *m_pUdpSocket;
    QTcpSocket *m_pTcpSocket;
    QTcpServer *m_pTcpServer;

signals:

private slots:
    void processPendingDatagrams();
    qint64 broadcastDatagram(QByteArray datagram, QHostAddress dstAdress = QHostAddress::Broadcast, quint16 dstPort = c_port);

};

#endif // NETSERVER_H
