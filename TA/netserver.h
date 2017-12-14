#ifndef NETSERVER_H
#define NETSERVER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QtNetwork>
#include "fileserver.h"

// 其他平台编码不一致时，需要切换常量的定义类型
static quint16 c_UdpPort = 55555;
static quint16 c_TcpPort = 50505;

static QHostAddress c_HostAdress;

static const QString c_sNetCommand      = QStringLiteral ("命令");

static const QString c_sMsgPreName      = QStringLiteral ("改前名称");
static const QString c_sMsgCurName      = QStringLiteral ("改后名称");
static const QString c_sMsgMembInfo     = QStringLiteral ("成员信息");
static const QString c_sMsgProjName     = QStringLiteral ("工程名称");
static const QString c_sMsgProjList     = QStringLiteral ("工程列表");
static const QString c_sMsgFileList     = QStringLiteral ("文件列表");
static const QString c_sMsgFileLogs     = QStringLiteral ("文件日志");

static const QString c_sMsgFileName     = QStringLiteral ("文件名称");
static const QString c_sMsgIPAddress    = QStringLiteral ("IP地址");
static const QString c_sMsgPortNum      = QStringLiteral ("端口地址");

static const QString c_sPostChangeName  = QStringLiteral ("发送改变名称");
static const QString c_sPostMemberInfo  = QStringLiteral ("发送成员信息");
static const QString c_sGetMemberInfo   = QStringLiteral ("获取成员信息");
static const QString c_sPostCreateProj  = QStringLiteral ("发送创建项目");
static const QString c_sPostJionProj    = QStringLiteral ("发送加入项目");
static const QString c_sPostLeaveProj   = QStringLiteral ("发送离开项目");
static const QString c_sGetProjList     = QStringLiteral ("获取项目列表");
static const QString c_sPostProjList    = QStringLiteral ("发送项目列表");
static const QString c_sGetFileList     = QStringLiteral ("获取文件列表");
static const QString c_sPostFileList    = QStringLiteral ("发送文件列表");
static const QString c_sGetFileLogs     = QStringLiteral ("获取文件日志");
static const QString c_sPostFileLogs    = QStringLiteral ("发送文件日志");

static const QString c_sGetFile         = QStringLiteral ("获取项目文件");


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
    QString fileName;       //文件名

    QByteArray outBlock;    //分次传
    qint64 loadSize;        //每次发送数据的大小
    qint64 byteToWrite;     //剩余数据大小
    qint64 totalSize;       //文件总大小

    int sendTimes;  //用来标记是否为第一次发送，第一次以后连接信号触发，后面的则手动调用

private slots:
    void send();  //传送文件头信息
    void goOnSend(qint64 numBytes);  //传送文件内容
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
    qint64 totalSize;  //总共需要发送的文件大小（文件内容&文件名信息）
    qint64 byteReceived;  //已经发送的大小

private slots:
    void acceptConnection();
    void readClient();
};

#endif // NETSERVER_H
