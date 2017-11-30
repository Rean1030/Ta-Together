#include "netserver.h"

NetServer::NetServer(QObject *parent) : QObject(parent)
{
    c_HostAdress = getIpAdress();
    m_pUdpSocket = new QUdpSocket(parent);
    while(!m_pUdpSocket->bind(c_port, QUdpSocket::DefaultForPlatform))
    {
        qDebug() << c_port << " 端口绑定失败，尝试下一个端口...";
        c_port++;
    }
    connect(m_pUdpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

    m_pTcpSocket = new QTcpSocket(parent);
    m_pTcpServer = new QTcpServer(parent);

}

QHostAddress NetServer::getIpAdress()
{
    QList <QHostAddress>listAddress = QNetworkInterface::allAddresses();
    for(int j = 0; j < listAddress.size(); j++)
    {
        if(!listAddress.at(j).isNull()
                && listAddress.at(j).protocol() == QAbstractSocket::IPv4Protocol
                && listAddress.at(j) != QHostAddress::LocalHost)
        {
            return listAddress.at(j);
        }
    }
    return QHostAddress::Null;
}

void NetServer::processPendingDatagrams()
{
    while (m_pUdpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        QHostAddress *srcAddress = NULL;
        quint16 *srcPort = NULL;
        datagram.resize(m_pUdpSocket->pendingDatagramSize());
        if (-1 != m_pUdpSocket->readDatagram(datagram.data(), datagram.size(), srcAddress, srcPort))
        {
            // TODO 解析并处理datagram.data()中的数据

        }
    }
}

qint64 NetServer::broadcastDatagram(QByteArray datagram, QHostAddress dstAdress, quint16 dstPort)
{
    return m_pUdpSocket->writeDatagram(datagram, dstAdress, dstPort);
}
