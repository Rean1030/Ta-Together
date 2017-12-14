#include "netserver.h"

UdpSocket::UdpSocket(FileServer *pFileServer, QObject *parent)
    : QObject(parent), m_pFileServer(pFileServer)
{
    c_HostAdress = getIpAdress();
    m_pTcpClient = new TcpClient(parent);
    m_pUdpSocket = new QUdpSocket(parent);
    while(!m_pUdpSocket->bind(c_UdpPort, QUdpSocket::DefaultForPlatform))
    {
        qDebug() << c_UdpPort << " Fail be bind, Tring to bind next...";
        c_UdpPort++;
    }
    connect(m_pUdpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

void UdpSocket::postChangeName(QJsonValue preName, QJsonValue curName, QHostAddress dstAdress, quint16 dstPort)
{
    QJsonObject msgObj;
    msgObj.insert (c_sNetCommand, c_sPostChangeName);
    msgObj.insert (c_sMsgPreName, preName);
    msgObj.insert (c_sMsgCurName, curName);

    QJsonDocument oMsg(msgObj);
    broadcastDatagram(oMsg.toJson (), dstAdress, dstPort);
}

void UdpSocket::postMemberInfo(QJsonValue projName, QHostAddress dstAdress, quint16 dstPort)
{
    QJsonObject oMemberInfo = m_pFileServer->getMember (projName);
    QJsonObject msgObj;
    msgObj.insert (c_sNetCommand, c_sPostMemberInfo);
    msgObj.insert (c_sMsgProjName, projName);
    msgObj.insert (c_sMsgMembInfo, oMemberInfo);

    QJsonDocument oMsg(msgObj);
    broadcastDatagram(oMsg.toJson (), dstAdress, dstPort);
}

void UdpSocket::getMemberInfo(QJsonValue projName)
{
    QJsonObject msgObj;
    msgObj.insert (c_sMsgProjName, projName);
    msgObj.insert (c_sNetCommand, c_sGetMemberInfo);

    QJsonDocument oMsg(msgObj);
    broadcastDatagram(oMsg.toJson ());
}

void UdpSocket::postCreateProj(QJsonValue projName, QHostAddress dstAdress, quint16 dstPort)
{
    QJsonObject msgObj;
    msgObj.insert (c_sNetCommand, c_sPostCreateProj);
    msgObj.insert (c_sMsgProjName, projName);
    msgObj.insert (c_sMsgCurName, m_pFileServer->getUserName ());

    QJsonDocument oMsg(msgObj);
    broadcastDatagram(oMsg.toJson (), dstAdress, dstPort);
}

void UdpSocket::postJionProj(QJsonValue projName, QHostAddress dstAdress, quint16 dstPort)
{
    QJsonObject msgObj;
    msgObj.insert (c_sNetCommand, c_sPostJionProj);
    msgObj.insert (c_sMsgProjName, projName);
    msgObj.insert (c_sMsgCurName, m_pFileServer->getUserName ());

    QJsonDocument oMsg(msgObj);
    broadcastDatagram(oMsg.toJson (), dstAdress, dstPort);
}

void UdpSocket::postLeaveProj(QJsonValue projName, QHostAddress dstAdress, quint16 dstPort)
{
    QJsonObject msgObj;
    msgObj.insert (c_sNetCommand, c_sPostLeaveProj);
    msgObj.insert (c_sMsgProjName, projName);
    msgObj.insert (c_sMsgCurName, m_pFileServer->getUserName ());

    QJsonDocument oMsg(msgObj);
    broadcastDatagram(oMsg.toJson (), dstAdress, dstPort);
}

void UdpSocket::getProjList()
{
    QJsonObject msgObj;
    msgObj.insert (c_sNetCommand, c_sGetProjList);

    QJsonDocument oMsg(msgObj);
    broadcastDatagram(oMsg.toJson ());
}

void UdpSocket::postProjList(QHostAddress dstAdress, quint16 dstPort)
{
    QJsonObject msgObj;
    QJsonArray projList = m_pFileServer->getProjList ();
    if (projList.count () > 0)
    {
        msgObj.insert (c_sNetCommand, c_sPostProjList);
        msgObj.insert (c_sMsgProjList, projList);
        msgObj.insert (c_sMsgCurName, m_pFileServer->getUserName ());

        QJsonDocument oMsg(msgObj);
        broadcastDatagram(oMsg.toJson (), dstAdress, dstPort);
    }
}

void UdpSocket::getFileList(QJsonValue projName)
{
    QJsonObject msgObj;
    msgObj.insert (c_sNetCommand, c_sGetFileList);
    msgObj.insert (c_sMsgProjName, projName);

    QJsonDocument oMsg(msgObj);
    broadcastDatagram(oMsg.toJson ());
}

void UdpSocket::postFileList(QJsonValue projName, QHostAddress dstAdress, quint16 dstPort)
{
    QJsonObject msgObj;
    QJsonArray oFiles = m_pFileServer->getFiles (projName);
    if (oFiles.count () > 0)
    {
        msgObj.insert (c_sNetCommand, c_sPostFileList);
        msgObj.insert (c_sMsgProjName, projName);
        msgObj.insert (c_sMsgFileList, oFiles);

        QJsonDocument oMsg(msgObj);
        broadcastDatagram(oMsg.toJson (), dstAdress, dstPort);
    }
}

void UdpSocket::getFileLogs(QJsonValue projName)
{
    QJsonObject msgObj;
    msgObj.insert (c_sNetCommand, c_sGetFileLogs);
    msgObj.insert (c_sMsgProjName, projName);

    QJsonDocument oMsg(msgObj);
    broadcastDatagram(oMsg.toJson ());
}

void UdpSocket::postFileLogs(QJsonValue projName, QHostAddress dstAdress, quint16 dstPort)
{
    QJsonObject msgObj;
    QJsonArray oFileLogs = m_pFileServer->getFileLogs (projName);
    if (oFileLogs.count () > 0)
    {
        msgObj.insert (c_sNetCommand, c_sPostFileLogs);
        msgObj.insert (c_sMsgProjName, projName);
        msgObj.insert (c_sMsgFileLogs, oFileLogs);

        QJsonDocument oMsg(msgObj);
        broadcastDatagram(oMsg.toJson (), dstAdress, dstPort);
    }
}

void UdpSocket::getFile(QJsonValue fileName, QJsonValue projName, QHostAddress dstAdress, quint16 dstPort)
{
    if (projName == "")
    {
        projName = m_pFileServer->getCurProjName ();
    }
    QJsonObject msgObj;
    msgObj.insert (c_sNetCommand, c_sGetFile);
    msgObj.insert (c_sMsgProjName, projName);
    msgObj.insert (c_sMsgFileName, fileName);
    msgObj.insert (c_sMsgIPAddress, dstAdress.toString ());
    msgObj.insert (c_sMsgPortNum, QString::number (dstPort));

    QJsonDocument oMsg(msgObj);
    broadcastDatagram(oMsg.toJson (), dstAdress, dstPort);
}

void UdpSocket::switchNetCommand(QByteArray datagram, QHostAddress dstAdress, quint16 dstPort)
{
    QJsonObject msgObj;
    QJsonParseError er;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(datagram, &er);
    if(er.error == QJsonParseError::NoError && !jsonDoc.isNull() && jsonDoc.isObject())
    {
        msgObj = jsonDoc.object();
        if (msgObj.contains (c_sNetCommand))
        {
            if (msgObj.value (c_sNetCommand).toString () == c_sPostChangeName)
            {
                QJsonValue preName = msgObj.value (c_sMsgPreName);
                QJsonValue curName = msgObj.value (c_sMsgCurName);
                m_pFileServer->changeMemberNames (preName, curName);
            }
            else if (msgObj.value (c_sNetCommand).toString () == c_sPostMemberInfo)
            {
                if (msgObj.contains (c_sMsgProjName) && msgObj.value (c_sMsgMembInfo).isObject ())
                {
                    QJsonValue projName = msgObj.value (c_sMsgProjName);
                    QJsonObject membInfo = msgObj.value (c_sMsgMembInfo).toObject ();
                    if (m_pFileServer->hasProject (projName) && !membInfo.isEmpty ())
                    {
                        m_pFileServer->setMember (membInfo, projName);
                        m_pFileServer->updateMemberToJsonObj ();
                    }
                }
            }
            else if (msgObj.value (c_sNetCommand).toString () == c_sGetMemberInfo)
            {
                if (msgObj.contains (c_sMsgProjName))
                {
                    QJsonValue projName = msgObj.value (c_sMsgProjName);
                    if (m_pFileServer->hasProject (projName))
                    {
                        postMemberInfo (projName, dstAdress, dstPort);
                    }
                }
            }
            else if (msgObj.value (c_sNetCommand).toString () == c_sPostCreateProj)
            {
                if (msgObj.contains (c_sMsgProjName) && msgObj.contains (c_sMsgCurName)
                        && (msgObj.value (c_sMsgCurName) != ""))
                {
                    QJsonValue projName = msgObj.value (c_sMsgProjName);
                    QJsonValue curName = msgObj.value (c_sMsgCurName);
                    if (m_pFileServer->createProject (projName, curName))
                    {
                        m_pFileServer->updateMemberFromJsonObj ();
                    }
                    else
                    {
                        qDebug() << projName << " project create failed!";
                    }
                }
            }
            else if (msgObj.value (c_sNetCommand).toString () == c_sPostJionProj)
            {
                if (msgObj.contains (c_sMsgProjName) && msgObj.contains (c_sMsgCurName)
                        && (msgObj.value (c_sMsgCurName) != ""))
                {
                    QJsonValue projName = msgObj.value (c_sMsgProjName);
                    QJsonValue curName = msgObj.value (c_sMsgCurName);
                    if (m_pFileServer->joinProject (projName, curName))
                    {
                        m_pFileServer->updateMemberFromJsonObj ();
                    }
                    else
                    {
                        qDebug() << projName << " project join failed!";
                    }
                }
            }
            else if (msgObj.value (c_sNetCommand).toString () == c_sPostLeaveProj)
            {
                if (msgObj.contains (c_sMsgProjName) && msgObj.contains (c_sMsgCurName)
                        && (msgObj.value (c_sMsgCurName) != ""))
                {
                    QJsonValue projName = msgObj.value (c_sMsgProjName);
                    QJsonValue curName = msgObj.value (c_sMsgCurName);
                    m_pFileServer->leaveProject (projName, curName);
                    m_pFileServer->updateMemberFromJsonObj ();
                }
            }
            else if (msgObj.value (c_sNetCommand).toString () == c_sGetProjList)
            {
                postProjList (dstAdress, dstPort);
            }
            else if (msgObj.value (c_sNetCommand).toString () == c_sPostProjList)
            {
                if (msgObj.contains (c_sMsgProjList) && msgObj.value (c_sMsgProjList).isArray ()
                        && msgObj.contains (c_sMsgCurName) && (msgObj.value (c_sMsgProjList).toArray ().count () > 0))
                {
                    QJsonArray projList = msgObj.value (c_sMsgProjList).toArray ();
                    QJsonValue curName = msgObj.value (c_sMsgCurName);
                    int iP = 0;
                    for (int i = 0; i < projList.count (); i++)
                    {
                        if (!m_pFileServer->hasProject (projList.at (i)))
                        {
                            m_pFileServer->createProject (projList.at (i), curName);
                            iP++;
                        }
                    }
                    if (iP > 0)
                    {
                        m_pFileServer->updateMemberFromJsonObj ();
                        emit(updateProjs ());
                    }
                }
            }
            else if (msgObj.value (c_sNetCommand).toString () == c_sGetFileList)
            {
                if (msgObj.contains (c_sMsgProjName) && msgObj.value (c_sMsgProjName) != "")
                {
                    postFileList (msgObj.value (c_sMsgProjName), dstAdress, dstPort);
                }
            }
            else if (msgObj.value (c_sNetCommand).toString () == c_sPostFileList)
            {
                if (msgObj.contains (c_sMsgProjName) && msgObj.contains (c_sMsgFileList)
                        && msgObj.value (c_sMsgFileList).isArray ())
                {
                    QJsonValue projName = msgObj.value (c_sMsgProjName);
                    QJsonArray fileList = msgObj.value (c_sMsgFileList).toArray ();
                    m_pFileServer->setFiles (fileList, projName);
                    m_pFileServer->updateMemberToJsonObj ();
                }
            }
            else if (msgObj.value (c_sNetCommand).toString () == c_sGetFileLogs)
            {
                if (msgObj.contains (c_sMsgProjName))
                {
                    postFileLogs (msgObj.value (c_sMsgProjName), dstAdress, dstPort);
                }
            }
            else if (msgObj.value (c_sNetCommand).toString () == c_sPostFileLogs)
            {
                if (msgObj.contains (c_sMsgProjName) && msgObj.contains (c_sMsgFileLogs)
                        && msgObj.value (c_sMsgFileLogs).isArray ())
                {
                    QJsonValue projName = msgObj.value (c_sMsgProjName);
                    QJsonArray fileLogs = msgObj.value (c_sMsgFileLogs).toArray ();
                    m_pFileServer->setFileLogs (fileLogs, projName);
                    m_pFileServer->updateMemberToJsonObj ();
                }
            }
            else if (msgObj.value (c_sNetCommand).toString () == c_sGetFile)
            {
                if (msgObj.contains (c_sMsgProjName) && msgObj.contains (c_sMsgFileName)
                        && msgObj.contains (c_sMsgIPAddress) && msgObj.contains (c_sMsgPortNum))
                {
                    QJsonValue projName = msgObj.value (c_sMsgProjName);
                    QJsonValue fileName = msgObj.value (c_sMsgFileName);
                    QHostAddress hostAddress;
                    hostAddress.setAddress (msgObj.value (c_sMsgIPAddress).toString ().toUInt ());
                    quint16 port = msgObj.value (c_sMsgPortNum).toString ().toUShort ();
                    QJsonObject fileObj = m_pFileServer->getFile (fileName, projName);

                    if (fileObj.contains (c_sFilePath) && (fileObj.value (c_sFilePath).toString () != "")
                            && !hostAddress.isNull ())
                    {
                        m_pTcpClient->setFileToSend (fileObj.value (c_sFilePath).toString ());
                        m_pTcpClient->sendFile (hostAddress);
                    }
                }
            }
            else
            {
                qDebug() << msgObj.value (c_sNetCommand) << " is invalid command!";
            }
        }
    }
    else
    {
        qDebug() << er.errorString();
    }
}

QHostAddress UdpSocket::getIpAdress()
{
//    return QNetworkInterface::allAddresses();
    QList <QHostAddress> listAddress = QNetworkInterface::allAddresses();
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

void UdpSocket::processPendingDatagrams()
{
    while (m_pUdpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        QHostAddress srcAddress;
        quint16 srcPort;
        datagram.resize(m_pUdpSocket->pendingDatagramSize());
        if (-1 != m_pUdpSocket->readDatagram(datagram.data(), datagram.size(), &srcAddress, &srcPort))
        {
//            bool bSelf = false;
//            for (int i = 0; i < c_HostAdress.count (); i++)
//            {
//                if (c_HostAdress.at (i).toIPv4Address () == srcAddress.toIPv4Address ())
//                {
//                    bSelf = true;
//                }
//            }
//            if (!bSelf)
            if (srcAddress != c_HostAdress)
            {
                // 解析并处理datagram中的数据
                switchNetCommand(datagram, srcAddress, srcPort);
            }
        }
    }
}

qint64 UdpSocket::broadcastDatagram(QByteArray datagram, QHostAddress dstAdress, quint16 dstPort)
{
    return m_pUdpSocket->writeDatagram(datagram, dstAdress, dstPort);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TcpClient::TcpClient(QObject *parent) : QObject (parent)
{
    tcpClient = new QTcpSocket(this);
    sendTimes = 0;

    connect(tcpClient, SIGNAL(connected()), this, SLOT(send()));  //当连接成功时，就开始传送文件
    connect(tcpClient, SIGNAL(bytesWritten(qint64)), this, SLOT(goOnSend(qint64)));
}

void TcpClient::send()
{
    byteToWrite = localFile->size();  //剩余数据的大小
    totalSize = localFile->size();

    loadSize = 4*1024;  //每次发送数据的大小

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);

    out<<qint64(0)<<qint64(0)<<currentFileName;

    totalSize += outBlock.size();  //总大小为文件大小加上文件名等信息大小
    byteToWrite += outBlock.size();

    out.device()->seek(0);  //回到字节流起点来写好前面连个qint64，分别为总大小和文件名等信息大小
    out<<totalSize<<qint64(outBlock.size());

    tcpClient->write(outBlock);  //将读到的文件发送到套接字
}

void TcpClient::goOnSend(qint64 numBytes)
{
    byteToWrite -= numBytes;  //剩余数据大小
    outBlock = localFile->read(qMin(byteToWrite, loadSize));
    tcpClient->write(outBlock);
}

void TcpClient::setFileToSend(QString sFileName)
{
    loadSize = 0;
    byteToWrite = 0;
    totalSize = 0;
    outBlock.clear();

    fileName = sFileName;
    localFile = new QFile(fileName);
    localFile->open(QFile::ReadOnly);
}

void TcpClient::sendFile(QHostAddress dstAddress)
{
    if(sendTimes == 0)  //只有第一次发送的时候，是发生在连接产生信号connect时
    {
        tcpClient->connectToHost(dstAddress, c_TcpPort);
        sendTimes = 1;
    }
    else
    {
        send();  //第一次发送的时候是由connectToHost出发connect信号才能调用send，第二次之后就需要调用send了
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TcpServer::TcpServer(QObject *parent) : QObject (parent)
{

}

void TcpServer::acceptConnection()
{
    receivedSocket = server->nextPendingConnection();
    connect(receivedSocket, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void TcpServer::readClient()
{
    if(byteReceived == 0)  //才刚开始接收数据，此数据为文件信息
    {
        QDataStream in(receivedSocket);
        in>>totalSize>>byteReceived>>fileName;
        fileName = c_sTAPath + "/Files/" + fileName;
        newFile = new QFile(fileName);
        newFile->open(QFile::WriteOnly);
    }
    else  //正式读取文件内容
    {
        inBlock = receivedSocket->readAll();

        byteReceived += inBlock.size();
        newFile->write(inBlock);
        newFile->flush();
    }

    if(byteReceived == totalSize)
    {
        inBlock.clear();
        byteReceived = 0;
        totalSize = 0;

        if (QMessageBox::question(NULL,QStringLiteral("完成"),QStringLiteral("文件已经获取完，是否现在打开？"),
                                  QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
        }
    }
}

void TcpServer::startListen(QHostAddress dstAddress)
{
    totalSize = 0;
    byteReceived = 0;

    server = new QTcpServer(this);
    server->listen(dstAddress, c_TcpPort);

    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}
