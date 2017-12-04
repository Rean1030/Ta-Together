#ifndef FILESERVER_H
#define FILESERVER_H

#include <QObject>
#include <QtCore>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

const static QString c_sDateTimeFormat("yyyy/M/d-H");

static const QString c_sUserName("用户名");
static const QString c_sCurProject("当前项目");

static const QString c_sProjects("项目");
static const QString c_sProjectName("项目名称");

static const QString c_sFiles("文件");
static const QString c_sFileName("文件名");
static const QString c_sFileDes("文件描述");
static const QString c_sFileUser("文件所有者");
static const QString c_sFilePath("文件路径");
static const QString c_sFileTime("文件上传时间");

static const QString c_sMembers("队员");
static const QString c_sMemberName("队员名");
static const QString c_sMemberRole("角色");
static const QString c_sMemberTime("队员保存时间");

static const QString c_sUserLogs("任务日志");
static const QString c_sLogDate("日志日期");
static const QString c_sLogInf("日志内容");

static const QString c_sMainTaskList("主任务列表");
static const QString c_sSubTaskList("子任务列表");

static const QString c_sTaskName("任务名称");
static const QString c_sPlannedTime("计划用时");
static const QString c_sUsedTime("已用工时");
static const QString c_sTimeFix("工时调差");
static const QString c_sStartTime("开始时间");
static const QString c_sTaskPercent("任务进度");
static const QString c_sTaskState("任务状态");
static const QString c_sPriority("优先级别");
static const QString c_sDifficulty("任务难度");

static QString c_sFile;

class FileServer : public QObject
{
    Q_OBJECT

public:
    explicit FileServer(QObject *parent = 0);

    bool readFile();
    bool writeFile();

    QJsonValue getUserName();
    void setUserName(QJsonValue userName);

    void setTaskInf(QJsonObject mainTaskInf, QJsonObject subTaskInf);
    QJsonObject getTaskInf(QJsonValue mainTaskName, QJsonValue subTaskName = "");

    void setMemberLog(QJsonObject oLog);
    QJsonValue getMemberLog(QJsonValue oLogDate);

    void setMemberRole(QJsonValue oRole);
    QJsonValue getMemberRole();

    void updateMemberTime();

    bool createProject(QJsonValue oProjName);
    bool joinProject(QJsonValue oProjName);
    void leaveProject(QJsonValue oProjName);

    inline QJsonObject getProject() {return m_oProject;}
    inline QJsonObject getMember() {return m_oMember;}
    inline void setMember(QJsonObject oMemberData) {m_oMember = oMemberData;}

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
