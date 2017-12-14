#ifndef FILESERVER_H
#define FILESERVER_H

#include <QObject>
#include <QtCore>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QString>

// ����ƽ̨���벻һ��ʱ����Ҫ�л������Ķ�������
static QString c_sTAFile;
static QString c_sTAPath;

static int c_newTag = 1;

static const QString c_sGUID                =    QString ("GUID");
static const QString c_sDateTimeLongFormat  =    QString ("yyyy/M/d-H:m:s");
static const QString c_sDateTimeFormat      =    QString ("yyyy/M/d-H");
static const QString c_sDateFormat          =    QString ("yyyy/M/d");

static const QString c_sUserName            = QStringLiteral ("�û���");
static const QString c_sCurProject          = QStringLiteral ("��ǰ��Ŀ");

static const QString c_sProjects            = QStringLiteral ("��Ŀ");
static const QString c_sProjectName         = QStringLiteral ("��Ŀ����");

static const QString c_sFiles               = QStringLiteral ("�ļ�");
static const QString c_sFileName            = QStringLiteral ("�ļ���");
static const QString c_sFileDes             = QStringLiteral ("�ļ�����");
static const QString c_sFileUser            = QStringLiteral ("�ļ�������");
static const QString c_sFilePath            = QStringLiteral ("�ļ�·��");
static const QString c_sFileTime            = QStringLiteral ("�ļ��ϴ�ʱ��");
static const QString c_sFileLogs            = QStringLiteral ("�ļ���־");

static const QString c_sMembers             = QStringLiteral ("��Ա");
static const QString c_sMemberName          = QStringLiteral ("��Ա��");
static const QString c_sMemberRole          = QStringLiteral ("��ɫ");
static const QString c_sMemberTime          = QStringLiteral ("��Ա����ʱ��");

static const QString c_sUserLogs            = QStringLiteral ("������־");
static const QString c_sLogDate             = QStringLiteral ("��־����");
static const QString c_sLogInf              = QStringLiteral ("��־����");

static const QString c_sMainTaskList        = QStringLiteral ("�������б�");
static const QString c_sSubTaskList         = QStringLiteral ("�������б�");

static const QString c_sTaskName            = QStringLiteral ("��������");
static const QString c_sPlannedTime         = QStringLiteral ("�ƻ���ʱ");
static const QString c_sPlannedTimeUnit     = QStringLiteral ("�ƻ���ʱ��λ");
static const QString c_sUsedTime            = QStringLiteral ("���ù�ʱ");
static const QString c_sTimeFix             = QStringLiteral ("��ʱ����");
static const QString c_sStartTime           = QStringLiteral ("��ʼʱ��");
static const QString c_sTaskPercent         = QStringLiteral ("�������");
static const QString c_sTaskDetails         = QStringLiteral ("��������");
static const QString c_sTaskState           = QStringLiteral ("����״̬");
static const QString c_sPriority            = QStringLiteral ("���ȼ���");
static const QString c_sDifficulty          = QStringLiteral ("�����Ѷ�");


class FileServer : public QObject
{
    Q_OBJECT

public:
    explicit FileServer(QObject *parent = 0);

    bool readFile();
    bool writeFile();

    void clearInvalid();

    QJsonValue getUserName();
    void setUserName(QJsonValue userName);
    void changeMemberNames(QJsonValue oldName, QJsonValue newName);

    void setCurProjName(QJsonValue curProjName);
    QJsonValue getCurProjName();

    void changeTaskName(QJsonValue preName, QJsonValue curName, bool bMainTask);
    void setTaskInf(QJsonObject mainTaskInf);
    void setTaskInf(QJsonObject mainTaskInf, QJsonObject subTaskInf);
    QJsonObject getTaskInf(QJsonValue mainTaskName, QJsonValue subTaskName = "");
    void createNewTask(QJsonValue oNewTaskName, QJsonValue oParentTaskName = "");
    void deleteTask(QJsonValue oTaskName, QJsonValue oParentTaskName = "");

    void updateMainFromSub(QJsonValue mainTaskName);

    // ��������������
    void updateSubTaskName(QJsonValue mainTaskName, QJsonValue preSubTaskName, QJsonValue subTaskName);

    void setMemberLog(QJsonObject oLog);
    QJsonValue getMemberLog(QJsonValue oLogDate);

    void setMemberRole(QJsonValue oRole);
    QJsonValue getMemberRole();

    void updateMemberTime();

    bool createProject(QJsonValue oProjName, QJsonValue memberName = "");
    bool joinProject(QJsonValue oProjName, QJsonValue memberName = "");
    void leaveProject(QJsonValue oProjName, QJsonValue memberName = "");
    void deleteProject(QJsonValue oProjName);

    QJsonObject getFile(QJsonValue oFileName, QJsonValue projName = "");
    void putFile(QJsonObject oFile, bool bNameMatch = true);
    void removeFile(QJsonObject oFile);
    void removeFile(QJsonValue oFileName);
    QJsonArray getFiles(QJsonValue projName = "");
    void setFiles(QJsonArray oFiles, QJsonValue projName = "");

    void writeFileLog(QJsonValue logInfo);
    void clearFileLog(int iBegin, int iEnd = 0);
    QJsonArray getFileLogs(QJsonValue projName = "");
    void setFileLogs(QJsonArray oFileLogs, QJsonValue projName = "");

    bool hasMember(QJsonValue userName, QJsonValue projName = "");
    bool hasProject(QJsonValue projName);
    QJsonArray getProjList();

    inline QJsonArray getProjects() {return m_oProjects;}
    QJsonObject getProject(QJsonValue oProjName = "");
    void setProject(QJsonObject oProjectData, QJsonValue oProjName = "");
    QJsonObject getMember(QJsonValue oProjName = "");
    void setMember(QJsonObject oMemberData, QJsonValue oProjName = "");

    void updateMemberToJsonObj();
    void updateMemberFromJsonObj();

signals:

public slots:

private:
    QJsonObject     m_oJsonObj          ;
    QJsonValue      m_oUserName         ;
    QJsonValue      m_oCurProject       ;


    QJsonArray      m_oProjects         ;

    QJsonObject     m_oProject          ;

    QJsonArray      m_oMembers          ;

    QJsonObject     m_oMember           ;
};

#endif // FILESERVER_H
