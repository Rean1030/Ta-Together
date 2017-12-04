#include "fileserver.h"

FileServer::FileServer(QObject *parent) : QObject(parent)
{
    c_sFile = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/TA.json";
}

bool FileServer::readFile()
{
    QFile file(c_sFile);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << c_sFile << "文件打开失败，文件不存在！";
        return false;
    }
    QByteArray fileByte = file.readAll();
    file.close();
    QJsonParseError er;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileByte, &er);
    if(er.error == QJsonParseError::NoError && !jsonDoc.isNull() && jsonDoc.isObject())
    {
        m_oJsonObj = jsonDoc.object();
        return true;
    }
    else
    {
        qDebug() << er.errorString();
        return false;
    }
}

bool FileServer::writeFile()
{
    QFile file(c_sFile);
    if(!file.open(QIODevice::Truncate))
    {
        qDebug() << c_sFile << "文件打开失败，文件不存在！";
        return false;
    }
    QJsonDocument jsonDoc(m_oJsonObj);
    QByteArray fileByte = jsonDoc.toJson();
    file.write(fileByte);
    file.close();
    return true;
}

QJsonValue FileServer::getUserName()
{
    return m_oUserName;
}

void FileServer::setUserName(QJsonValue userName)
{
    m_oMember[c_sMemberName] = userName;

    QJsonObject oMem;
    int iM(-1);
    for (int i =0; i < m_oMembers.count(); i++)
    {
        if (m_oMembers.at(i).toObject().value(c_sMemberName) == m_oUserName)
        {
            oMem = m_oMembers.at(i).toObject();
            oMem[c_sMemberName] = userName;
            iM = i;
        }
    }
    if (iM != -1)
    {
        m_oMembers.replace(iM, oMem);
    }

    QJsonArray oMembs;
    QJsonObject oProj, oMemb;
    int iP(-1);
    for (int i =0; i < m_oProjects.count(); i++)
    {
        oProj = m_oProjects.at(i).toObject();
        oMembs = m_oProjects.at(i).toObject().value(c_sMembers).toArray();
        for (int j = 0; j < m_oProjects.at(i).toObject().value(c_sMembers).toArray().count(); j++)
        {
            if (m_oProjects.at(i).toObject().value(c_sMembers).toArray().at(j).toObject().value(c_sMemberName)
                    == m_oUserName)
            {
                oMemb = m_oProjects.at(i).toObject().value(c_sMembers).toArray().at(j).toObject();
                oMemb[c_sMemberName] = userName;
                iP = j;
            }
        }
        if (iP != -1)
        {
            oMembs.replace(iP, oMemb);
        }
        oProj[c_sMembers] = oMembs;
        m_oProjects.replace(i, oProj);
    }

    m_oUserName = userName;
}

void FileServer::setTaskInf(QJsonObject mainTaskInf, QJsonObject subTaskInf)
{
    QJsonObject oMTaskInf = mainTaskInf;
    if (m_oMember.contains(c_sMainTaskList) && m_oMember.value(c_sMainTaskList).isArray())
    {
        QJsonArray mTaskList = m_oMember.take(c_sMainTaskList).toArray();
        int iM(-1), iS(-1);
        for (int i = 0; i < mTaskList.count(); i++)
        {
            if (mTaskList.at(i).toObject().contains(c_sTaskName)
                    && mTaskList.at(i).toObject().value(c_sTaskName)
                    == oMTaskInf.value(c_sTaskName))
            {
                iM = i;
                if (subTaskInf.isEmpty())
                {
                    oMTaskInf.insert(c_sSubTaskList,
                                    mTaskList.at(i).toObject().value(c_sSubTaskList));
                }
                else
                {
                    QJsonArray sTaskList = mTaskList.at(i).toObject().value(c_sSubTaskList).toArray();
                    for (int j = 0; j < sTaskList.count(); j++)
                    {
                        if (sTaskList.at(j).toObject().contains(c_sTaskName)
                                && sTaskList.at(j).toObject().value(c_sTaskName)
                                == subTaskInf.value(c_sTaskName))
                        {
                            iS = j;
                        }
                    }
                    if (iS != -1)
                    {
                        sTaskList.replace(iS, subTaskInf);
                        oMTaskInf.insert(c_sSubTaskList, sTaskList);
                    }
                }
            }
        }
        if (iM != -1)
        {
            mTaskList.replace(iM, oMTaskInf);
            m_oMember.insert(c_sMainTaskList, mTaskList);
        }
    }
    else
    {
        QJsonArray oMainTaskList, oSubTaskList;
        oSubTaskList.append(subTaskInf);
        oMTaskInf.insert(c_sSubTaskList, oSubTaskList);
        oMainTaskList.append(oMTaskInf);
        m_oMember.insert(c_sMainTaskList, oMainTaskList);
    }
}

QJsonObject FileServer::getTaskInf(QJsonValue mainTaskName, QJsonValue subTaskName)
{
    QJsonObject oJsObj;
    if (m_oMember.contains(c_sMainTaskList) && m_oMember.value(c_sMainTaskList).isArray())
    {
        QJsonArray mTaskList = m_oMember.value(c_sMainTaskList).toArray();
        for (int i = 0; i < mTaskList.count(); i++)
        {
            if (mTaskList.at(i).toObject().contains(c_sTaskName)
                    && mTaskList.at(i).toObject().value(c_sTaskName) == mainTaskName)
            {
                if (subTaskName == "")
                {
                    oJsObj = mTaskList.at(i).toObject();
                }
                else if (mTaskList.at(i).toObject().contains(c_sSubTaskList)
                         && mTaskList.at(i).toObject().value(c_sSubTaskList).isArray())
                {
                    QJsonArray sTaskList = mTaskList.at(i).toObject().value(c_sSubTaskList).toArray();
                    for (int i = 0; i < sTaskList.count(); i++)
                    {
                        if (sTaskList.at(i).toObject().contains(c_sTaskName)
                                && sTaskList.at(i).toObject().value(c_sTaskName) == subTaskName)
                        {
                            oJsObj = sTaskList.at(i).toObject();
                        }
                    }
                }
            }
        }
    }
    return oJsObj;
}

void FileServer::setMemberLog(QJsonObject oLog)
{
    if(m_oMember.contains(c_sUserLogs))
    {
        QJsonArray oLogs = m_oMember.value(c_sUserLogs).toArray();
        int iL(-1);
        for (int i = 0; i < oLogs.count(); i++)
        {
            if(oLogs.at(i).toObject().value(c_sLogDate) == oLog.value(c_sLogDate))
            {
                iL = i;
            }
        }
        if (iL != -1 )
        {
            if (oLog.value(c_sLogInf).toString().isEmpty() || oLog.value(c_sLogInf).toString().isEmpty())
            {
                oLogs.removeAt(iL);
                m_oMember[c_sUserLogs] = oLogs;
            }
            else
            {
                oLogs.replace(iL, oLog);
                m_oMember[c_sUserLogs] = oLogs;
            }
        }
        else
        {
            oLogs.append(oLog);
            m_oMember[c_sUserLogs] = oLogs;
        }
    }
    else
    {
        QJsonArray oLogs;
        oLogs.append(oLog);
        m_oMember.insert(c_sUserLogs, oLogs);
    }
}

QJsonValue FileServer::getMemberLog(QJsonValue oLogDate)
{
    QJsonValue oLdate;
    if(m_oMember.contains(c_sUserLogs))
    {
        for (int i = 0; i < m_oMember.value(c_sUserLogs).toArray().count(); i++)
        {
            QJsonArray oLogs = m_oMember.value(c_sUserLogs).toArray();
            for (int i = 0; i < oLogs.count(); i++)
            {
                if(oLogs.at(i).toObject().value(c_sLogDate) == oLogDate)
                {
                    oLdate = oLogs.at(i).toObject().value(c_sLogInf);
                }
            }
        }
    }
    return oLdate;
}

void FileServer::setMemberRole(QJsonValue oRole)
{
    if (m_oMember.contains(c_sMemberRole))
    {
        m_oMember[c_sMemberRole] = oRole;
    }
    else
    {
        m_oMember.insert(c_sMemberRole, oRole);
    }
}

QJsonValue FileServer::getMemberRole()
{
    QJsonValue oRole;
    if (m_oMember.contains(c_sMemberRole))
    {
        oRole = m_oMember.value(c_sMemberRole);
    }
    return oRole;
}

void FileServer::updateMemberTime()
{
    if(m_oMember.contains(c_sMemberTime))
    {
        m_oMember[c_sMemberTime] = QDateTime::currentDateTime().toString(c_sDateTimeFormat);
    }
    else
    {
        m_oMember.insert(c_sMemberTime, QDateTime::currentDateTime().toString(c_sDateTimeFormat));
    }
}

bool FileServer::createProject(QJsonValue oProjName)
{
    bool bIn = false;
    for (int i = 0; i < m_oProjects.count(); i++)
    {
        if (m_oProjects.at(i).toObject().value(c_sProjectName) == oProjName)
        {
            bIn = true;
        }
    }

    if (bIn)
    {
        return false;
    }
    else
    {
        QJsonObject oNewProj;
        oNewProj.insert(c_sProjectName, oProjName);
        QJsonArray oMembs;
        QJsonObject oMemb;
        oMemb.insert(c_sMemberName, m_oUserName);
        oMembs.append(oMemb);
        oNewProj.insert(c_sMembers, oMembs);

        m_oProjects.append(oNewProj);
        m_oCurProject = oProjName;
        return true;
    }
}

bool FileServer::joinProject(QJsonValue oProjName)
{
    bool bOk = false;
    for (int i = 0; i < m_oProjects.count(); i++)
    {
        QJsonObject oProj = m_oProjects.at(i).toObject();
        if (oProj.value(c_sProjectName) == oProjName)
        {
            if (oProj.contains(c_sMembers))
            {
                QJsonArray oMembs = oProj.value(c_sMembers).toArray();

                bool bHas = false;
                for (int j = 0; j < oMembs.count(); j++)
                {
                    if (oMembs.at(i).toObject().value(c_sMemberName) == m_oUserName)
                    {
                        bHas = true;
                    }
                }

                if (!bHas)
                {
                    QJsonObject oMemb;
                    oMemb.insert(c_sMemberName, m_oUserName);
                    oMembs.append(oMemb);
                    oProj.insert(c_sMembers, oMembs);
                    bOk = true;
                }
            }
            else
            {
                QJsonArray oMembs;
                QJsonObject oMemb;
                oMemb.insert(c_sMemberName, m_oUserName);
                oMembs.append(oMemb);
                oProj.insert(c_sMembers, oMembs);
                bOk = true;
            }
            m_oProjects.replace(i, oProj);
        }
    }

    return bOk;
}

void FileServer::leaveProject(QJsonValue oProjName)
{
    int iP(-1);
    QJsonObject oProj;
    for (int i = 0; i < m_oProjects.count(); i++)
    {
        if (m_oProjects.at(i).toObject().value(c_sProjectName) == oProjName)
        {
            oProj = m_oProjects.at(i).toObject();
            if (oProj.contains(c_sMembers))
            {
                QJsonArray oMembs = oProj.value(c_sMembers).toArray();
                int iM = -1;
                for (int j = 0; j < oMembs.count(); j++)
                {
                    if (oMembs.at(i).toObject().value(c_sMemberName) == m_oUserName)
                    {
                        iM = j;
                    }
                }

                if (iM != -1)
                {
                    oMembs.removeAt(iM);
                    oProj[c_sMembers] = oMembs;
                    iP = i;
                }
            }            
        }
    }
    if (iP != -1)
    {
        m_oProjects.replace(iP, oProj);
    }
}

void FileServer::updateMemberToJsonObj()
{
    int iM(-1);
    for (int i = 0; i < m_oMembers.count(); i++)
    {
        if (m_oMembers.at(i).toObject().value(c_sMemberName) == m_oMember.value(c_sMemberName))
        {
            iM = i;
        }
    }
    m_oMembers.replace(iM, m_oMember);

    m_oProject[c_sMembers] = m_oMembers;

    int iP(-1);
    for (int i = 0; i < m_oProjects.count(); i++)
    {
        if (m_oProjects.at(i).toObject().value(c_sProjectName) == m_oProject.value(c_sProjectName))
        {
            iP = i;
        }
    }
    m_oProjects.replace(iP, m_oProject);

    m_oJsonObj.insert(c_sUserName, m_oUserName);
    m_oJsonObj.insert(c_sCurProject, m_oCurProject);
    m_oJsonObj.insert(c_sProjects, m_oProjects);
}

void FileServer::updateMemberFromJsonObj()
{
    m_oUserName = m_oJsonObj.value(c_sUserName);
    m_oCurProject = m_oJsonObj.value(c_sCurProject);

    if (m_oJsonObj.contains(c_sProjects) && m_oJsonObj.value(c_sProjects).isArray())
    {
        m_oProjects = m_oJsonObj.value(c_sProjects).toArray();
    }

    for (int i = 0; i < m_oProjects.count(); i++)
    {
        if (m_oProjects.at(i).isObject() && m_oProjects.at(i).toObject().contains(c_sProjectName)
                && (m_oProjects.at(i).toObject().value(c_sProjectName) == m_oCurProject))
        {
            m_oProject = m_oProjects.at(i).toObject();
        }
    }

    if (m_oProject.contains(c_sMembers) && m_oProject.value(c_sMembers).isArray())
    {
        m_oMembers = m_oProject.value(c_sMembers).toArray();
    }

    for (int i = 0; i < m_oMembers.count(); i++)
    {
        if (m_oMembers.at(i).isObject() && m_oMembers.at(i).toObject().contains(c_sMemberName)
                && (m_oMembers.at(i).toObject().value(c_sMemberName) == m_oUserName))
        {
            m_oMember = m_oMembers.at(i).toObject();
        }
    }
}
