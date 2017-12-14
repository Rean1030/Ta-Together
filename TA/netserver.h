#ifndef NETSERVER_H
#define NETSERVER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QtNetwork>
#include "fileserver.h"

// ����ƽ̨���벻һ��ʱ����Ҫ�л������Ķ�������
static quint16 c_UdpPort = 55555;
static quint16 c_TcpPort = 50505;

static QHostAddress c_HostAdress;

static const QString c_sNetCommand      = QStringLiteral ("����");

static const QString c_sMsgPreName      = QStringLiteral ("��ǰ����");
static const QString c_sMsgCurName      = QStringLiteral ("�ĺ�����");
static const QString c_sMsgMembInfo     = QStringLiteral ("��Ա��Ϣ");
static const QString c_sMsgProjName     = QStringLiteral ("��������");
static const QString c_sMsgProjList     = QStringLiteral ("�����б�");
static const QString c_sMsgFileList     = QStringLiteral ("�ļ��б�");
static const QString c_sMsgFileLogs     = QStringLiteral ("�ļ���־");

static const QString c_sMsgFileName     = QStringLiteral ("�ļ�����");
static const QString c_sMsgIPAddress    = QStringLiteral ("IP��ַ");
static const QString c_sMsgPortNum      = QStringLiteral ("�˿ڵ�ַ");

static const QString c_sPostChangeName  = QStringLiteral ("���͸ı�����");
static const QString c_sPostMemberInfo  = QStringLiteral ("���ͳ�Ա��Ϣ");
static const QString c_sGetMemberInfo   = QStringLiteral ("��ȡ��Ա��Ϣ");
static const QString c_sPostCreateProj  = QStringLiteral ("���ʹ�����Ŀ");
static const QString c_sPostJionProj    = QStringLiteral ("���ͼ�����Ŀ");
static const QString c_sPostLeaveProj   = QStringLiteral ("�����뿪��Ŀ");
static const QString c_sGetProjList     = QStringLiteral ("��ȡ��Ŀ�б�");
static const QString c_sPostProjList    = QStringLiteral ("������Ŀ�б�");
static const QString c_sGetFileList     = QStringLiteral ("��ȡ�ļ��б�");
static const QString c_sPostFileList    = QStringLiteral ("�����ļ��б�");
static const QString c_sGetFileLogs     = QStringLiteral ("��ȡ�ļ���־");
static const QString c_sPostFileLogs    = QStringLiteral ("�����ļ���־");

static const QString c_sGetFile         = QStringLiteral ("��ȡ��Ŀ�ļ�");


class TcpClient;
class TcpServer;

class UdpSocket : public QObject
{
    Q_OBJECT

public:
    explicit UdpSocket(FileServer *pFileServer,QObject *parent = 0);

    void getProjList();
    void postProjList(QHostAddress dstAdress = QHostAddress::Broadcast, quint16 dstPort = c_UdpPort);
    void postChangeName(QJsonValue preName, QJsonValue curName, QHostAddress dstAdress = QHostAddress::Broadcast, quint16 dstPort = c_UdpPort);
    void postMemberInfo(QJsonValue projName, QHostAddress dstAdress = QHostAddress::Broadcast, quint16 dstPort = c_UdpPort);
    void getMemberInfo(QJsonValue projName);
    void postCreateProj(QJsonValue projName, QHostAddress dstAdress = QHostAddress::Broadcast, quint16 dstPort = c_UdpPort);
    void postJionProj(QJsonValue projName, QHostAddress dstAdress = QHostAddress::Broadcast, quint16 dstPort = c_UdpPort);
    void postLeaveProj(QJsonValue projName, QHostAddress dstAdress = QHostAddress::Broadcast, quint16 dstPort = c_UdpPort);
    void getFileList(QJsonValue projName);
    void postFileList(QJsonValue projName, QHostAddress dstAdress = QHostAddress::Broadcast, quint16 dstPort = c_UdpPort);
    void getFileLogs(QJsonValue projName);
    void postFileLogs(QJsonValue projName, QHostAddress dstAdress = QHostAddress::Broadcast, quint16 dstPort = c_UdpPort);

    void getFile(QJsonValue fileName, QJsonValue projName = "",
                 QHostAddress dstAdress = QHostAddress::Broadcast, quint16 dstPort = c_UdpPort);
    void sendFile(QJsonValue fileName, QJsonValue projName = "",
                  QHostAddress dstAdress = QHostAddress::Broadcast, quint16 dstPort = c_UdpPort);

    void switchNetCommand(QByteArray datagram,
                          QHostAddress dstAdress = QHostAddress::Broadcast,
                          quint16 dstPort = c_UdpPort);

private:
    FileServer *m_pFileServer;

    QHostAddress getIpAdress();
    QUdpSocket *m_pUdpSocket;
    TcpClient *m_pTcpClient;

signals:
    void updateProjs();
    void updateFiles();
    void updateFileLogs();

private slots:
    void processPendingDatagrams();
    qint64 broadcastDatagram(QByteArray datagram,
                             QHostAddress dstAdress = QHostAddress::Broadcast,
                             quint16 dstPort = c_UdpPort);
};

class TcpClient : public QObject
{
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent = 0);

    void setFileToSend(QString sFileName);
    void sendFile(QHostAddress dstAddress);

private:
    QTcpSocket *tcpClient;
    QFile *localFile;
    QString fileName;       //�ļ���

    QByteArray outBlock;    //�ִδ�
    qint64 loadSize;        //ÿ�η������ݵĴ�С
    qint64 byteToWrite;     //ʣ�����ݴ�С
    qint64 totalSize;       //�ļ��ܴ�С

    int sendTimes;  //��������Ƿ�Ϊ��һ�η��ͣ���һ���Ժ������źŴ�������������ֶ�����

private slots:
    void send();  //�����ļ�ͷ��Ϣ
    void goOnSend(qint64 numBytes);  //�����ļ�����
};

class TcpServer : public QObject
{
    Q_OBJECT

public:
    explicit TcpServer(QObject *parent = 0);

    void startListen(QHostAddress dstAddress = QHostAddress::Any);

private:
    QTcpServer *server;
    QTcpSocket *receivedSocket;
    QFile *newFile;

    QByteArray inBlock;
    QString fileName;
    qint64 totalSize;  //�ܹ���Ҫ���͵��ļ���С���ļ�����&�ļ�����Ϣ��
    qint64 byteReceived;  //�Ѿ����͵Ĵ�С

private slots:
    void acceptConnection();
    void readClient();
};

#endif // NETSERVER_H
