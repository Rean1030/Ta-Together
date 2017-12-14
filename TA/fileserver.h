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

// 其他平台编码不一致时，需要切换常量的定义类型
static QString c_sTAFile;
static QString c_sTAPath;

static int c_newTag = 1;

static const QString c_sGUID                =    QString ("GUID");
static const QString c_sDateTimeLongFormat  =    QString ("yyyy/M/d-H:m:s");
static const QString c_sDateTimeFormat      =    QString ("yyyy/M/d-H");
static const QString c_sDateFormat          =    QString ("yyyy/M/d");

static const QString c_sUserName            = QStringLiteral ("用户名");
static const QString c_sCurProject          = QStringLiteral ("当前项目");

static const QString c_sProjects            = QStringLiteral ("项目");
static const QString c_sProjectName         = QStringLiteral ("项目名称");

static const QString c_sFiles               = QStringLiteral ("文件");
static const QString c_sFileName            = QStringLiteral ("文件名");
static const QString c_sFileDes             = QStringLiteral ("文件描述");
static const QString c_sFileUser            = QStringLiteral ("文件所有者");
static const QString c_sFilePath            = QStringLiteral ("文件路径");
static const QString c_sFileTime            = QStringLiteral ("文件上传时间");
static const QString c_sFileLogs            = QStringLiteral ("文件日志");

static const QString c_sMembers             = QStringLiteral ("队员");
static const QString c_sMemberName          = QStringLiteral ("队员名");
static const QString c_sMemberRole          = QStringLiteral ("角色");
static const QString c_sMemberTime          = QStringLiteral ("队员保存时间");

static const QString c_sUserLogs            = QStringLiteral ("任务日志");
static const QString c_sLogDate             = QStringLiteral ("日志日期");
static const QString c_sLogInf              = QStringLiteral ("日志内容");

static const QString c_sMainTaskList        = QStringLiteral ("主任务列表");
static const QString c_sSubTaskList         = QStringLiteral ("子任务列表");

static const QString c_sTaskName            = QStringLiteral ("任务名称");
static const QString c_sPlannedTime         = QStringLiteral ("计划用时");
static const QString c_sPlannedTimeUnit     = QStringLiteral ("计划用时单位");
static const QString c_sUsedTime            = QStringLiteral ("已用工时");
static const QString c_sTimeFix             = QStringLiteral ("工时调差");
static const QString c_sStartTime           = QStringLiteral ("开始时间");
static const QString c_sTaskPercent         = QStringLiteral ("任务进度");
static const QString c_sTaskDetails         = QStringLiteral ("任务内容");
static const QString c_sTaskState           = QStringLiteral ("任务状态");
static const QString c_sPriority            = QStringLiteral ("优先级别");
static const QString c_sDifficulty          = QStringLiteral ("任务难度");


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

    // 更新子任务名称
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
