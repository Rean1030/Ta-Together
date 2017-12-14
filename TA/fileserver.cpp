#include "fileserver.h"

FileServer::FileServer(QObject *parent) : QObject(parent)
{
    c_sTAPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    c_sTAFile = c_sTAPath + "/TA.json";
    QDir fileDir(c_sTAPath);
    if (!fileDir.exists ())
    {
        fileDir.mkdir (c_sTAPath);
    }
}

bool FileServer::readFile()
{
    QFile file(c_sTAFile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << c_sTAFile << "read open failed!";
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
    QFile file(c_sTAFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << c_sTAFile << "write open failed!";
        return false;
    }
    QJsonDocument jsonDoc(m_oJsonObj);
    QByteArray fileByte = jsonDoc.toJson();
    file.write(fileByte);
    file.close();
    return true;
}

void FileServer::clearInvalid()
{
    QList<int> nToDel;
    for (int i = 0; i < m_oProjects.count (); i++)
    {
        if (!m_oProjects.at (i).toObject ().contains (c_sProjectName)
                || (m_oProjects.at (i).toObject ().value (c_sProjectName) == ""))
        {
            nToDel.append (i);
        }
    }
    for(int i = 0; i < nToDel.count (); i++)
    {
        m_oProjects.removeAt (nToDel.at (i));
    }

    nToDel.clear ();
    for (int i = 0; i < m_oMembers.count (); i++)
    {
        if (!m_oMembers.at (i).toObject ().contains (c_sMemberName)
                || (m_oMembers.at (i).toObject ().value (c_sMemberName) == ""))
        {
            nToDel.append (i);
        }
    }
    for(int i = 0; i < nToDel.count (); i++)
    {
        m_oMembers.removeAt (nToDel.at (i));
    }

    nToDel.clear ();
    if (m_oMember.contains (c_sMainTaskList) && m_oMember.value (c_sMainTaskList).isArray ())
    {
        QJsonArray mTaskList = m_oMember.value (c_sMainTaskList).toArray ();
        for (int i = 0; i < mTaskList.count (); i++)
        {
            if (!mTaskList.at (i).toObject ().contains (c_sMainTaskList)
                    || (mTaskList.at (i).toObject ().value (c_sMainTaskList) == ""))
            {
                nToDel.append (i);
            }
        }
        for(int i = 0; i < nToDel.count (); i++)
        {
            mTaskList.removeAt (nToDel.at (i));
        }
        m_oMember[c_sMainTaskList] = mTaskList;
    }

    if (m_oMember.contains (c_sMainTaskList) && m_oMember.value (c_sMainTaskList).isArray ())
    {
        QJsonArray mTaskList = m_oMember.value (c_sMainTaskList).toArray ();
        QList<int> nMl, nSl;
        QList<QJsonObject> mMainTasks;
        for (int i = 0; i < mTaskList.count (); i++)
        {
            if (mTaskList.at (i).toObject ().contains (c_sSubTaskList)
                    && (mTaskList.at (i).toObject ().value (c_sSubTaskList).isArray ()))
            {
                QJsonObject mMainTask = mTaskList.at (i).toObject ();
                nSl.clear ();
                QJsonArray oSubTasks = mTaskList.at (i).toObject ().value (c_sSubTaskList).toArray ();
                for (int j = 0; j < oSubTasks.count (); j++)
                {
                    if (!oSubTasks.at (j).toObject ().contains (c_sTaskName)
                            || (oSubTasks.at (j).toObject ().value (c_sTaskName) == ""))
                    {
                        nSl.append (j);
                    }
                }
                if (nSl.count () > 0)
                {
                    for(int k = 0; k < nSl.count (); k++)
                    {
                        oSubTasks.removeAt (nSl.at (k));
                    }
                    mMainTask[c_sSubTaskList] = oSubTasks;
                    mMainTasks.append (mMainTask);
                    nMl.append (i);
                }
            }
        }
        for(int i = 0; i < nMl.count (); i++)
        {
            mTaskList.replace (nMl.at (i),  mMainTasks.at (i));
        }
        m_oMember[c_sMainTaskList] = mTaskList;
    }
}

QJsonValue FileServer::getUserName()
{
    return m_oUserName;
}

void FileServer::setUserName(QJsonValue userName)
{
    if (m_oMember.contains (c_sMemberName))
    {
        m_oMember[c_sMemberName] = userName;
    }
    changeMemberNames(m_oUserName, userName);

    m_oUserName = userName;
    if (m_oJsonObj.contains (c_sUserName))
    {
        m_oJsonObj[c_sUserName] = m_oUserName;
    }
    else
    {
        m_oJsonObj.insert (c_sUserName, m_oUserName);
    }
}

void FileServer::changeMemberNames(QJsonValue oldName, QJsonValue newName)
{
    QJsonObject oMem;
    int iM(-1);
    for (int i =0; i < m_oMembers.count(); i++)
    {
        if (m_oMembers.at(i).isObject () && m_oMembers.at(i).toObject().contains (c_sMemberName)
               && m_oMembers.at(i).toObject().value(c_sMemberName) == oldName)
        {
            oMem = m_oMembers.at(i).toObject();
            oMem[c_sMemberName] = newName;
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
        if (m_oProjects.at(i).isObject () && m_oProjects.at(i).toObject().contains (c_sMembers)
                && m_oProjects.at(i).toObject().value(c_sMembers).isArray ())
        {
            oProj = m_oProjects.at(i).toObject();
            oMembs = m_oProjects.at(i).toObject().value(c_sMembers).toArray();
            for (int j = 0; j < m_oProjects.at(i).toObject().value(c_sMembers).toArray().count(); j++)
            {
                if (m_oProjects.at(i).toObject().value(c_sMembers).toArray().at(j).toObject().value(c_sMemberName)
                        == oldName)
                {
                    oMemb = m_oProjects.at(i).toObject().value(c_sMembers).toArray().at(j).toObject();
                    oMemb[c_sMemberName] = newName;
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
    }
}

void FileServer::setCurProjName(QJsonValue curProjName)
{
    m_oCurProject = curProjName;
    if (m_oJsonObj.contains (c_sCurProject))
    {
        m_oJsonObj[c_sCurProject] = m_oCurProject;
    }
    else
    {
        m_oJsonObj.insert (c_sCurProject, m_oCurProject);
    }
}

QJsonValue FileServer::getCurProjName()
{
    return m_oCurProject;
}

void FileServer::changeTaskName(QJsonValue preName, QJsonValue curName, bool bMainTask)
{
    if (preName != "" && curName != "" && preName != curName)
    {
            if (m_oMember.contains(c_sMainTaskList) && m_oMember.value(c_sMainTaskList).isArray())
            {
                QJsonArray & mTaskList = m_oMember.value(c_sMainTaskList).toArray();
                QJsonObject oMTaskInf;
                int iM(-1), iS(-1);
                for (int i = 0; i < mTaskList.count(); i++)
                {
                    oMTaskInf = mTaskList.at(i).toObject();
                    if (bMainTask && mTaskList.at(i).toObject().contains(c_sTaskName)
                            && (mTaskList.at(i).toObject().value(c_sTaskName) == preName))
                    {
                        oMTaskInf[c_sTaskName] = curName;
                        iM = i;
                    }
                    if (!bMainTask && mTaskList.at(i).toObject().contains (c_sSubTaskList)
                            && mTaskList.at(i).toObject().value (c_sSubTaskList).isArray ())
                    {
                        QJsonArray & sTaskList = mTaskList.at(i).toObject().value(c_sSubTaskList).toArray();
                        QJsonObject sTask;
                        for (int j = 0; j < sTaskList.count(); j++)
                        {
                            if (sTaskList.at(j).toObject().contains(c_sTaskName)
                                    && (sTaskList.at(j).toObject().value(c_sTaskName) == preName))
                            {
                                sTask = sTaskList.at(j).toObject();
                                sTask[c_sTaskName] = curName;
                                iS = j;
                            }
                        }
                        if (iS != -1)
                        {
                            sTaskList.replace(iS, sTask);
                            oMTaskInf[c_sSubTaskList] = sTaskList;
                            iM = i;
                        }
                    }
                }
                if (iM != -1)
                {
                    mTaskList.replace(iM, oMTaskInf);
                    m_oMember[c_sMainTaskList] = mTaskList;
                }
            }
        }
}

void FileServer::setTaskInf(QJsonObject mainTaskInf)
{
    QJsonObject oSubTask;
    setTaskInf(mainTaskInf, oSubTask);
}

void FileServer::setTaskInf(QJsonObject mainTaskInf, QJsonObject subTaskInf)
{
    QJsonObject oMTaskInf = mainTaskInf;
    if (m_oMember.contains(c_sMainTaskList) && m_oMember.value(c_sMainTaskList).isArray())
    {
        QJsonArray mTaskList = m_oMember.value(c_sMainTaskList).toArray();
        int iM(-1), iS(-1);
        for (int i = 0; i < mTaskList.count(); i++)
        {
            if (mTaskList.at(i).toObject().contains(c_sTaskName)
                    && (mTaskList.at(i).toObject().value(c_sTaskName)
                    == oMTaskInf.value(c_sTaskName)))
            {
                iM = i;
                if (subTaskInf.isEmpty())
                {
                    oMTaskInf.insert(c_sSubTaskList,
                                    mTaskList.at(i).toObject().value(c_sSubTaskList));
                }
                else if (mTaskList.at(i).toObject().contains (c_sSubTaskList)
                         && mTaskList.at(i).toObject().value (c_sSubTaskList).isArray ())
                {
                    QJsonArray sTaskList = mTaskList.at(i).toObject().value(c_sSubTaskList).toArray();
                    for (int j = 0; j < sTaskList.count(); j++)
                    {
                        if (sTaskList.at(j).toObject().contains(c_sTaskName)
                                && (sTaskList.at(j).toObject().value(c_sTaskName)
                                == subTaskInf.value(c_sTaskName)))
                        {
                            iS = j;
                        }
                    }
                    if (iS != -1)
                    {
                        sTaskList.replace(iS, subTaskInf);
                        oMTaskInf.insert(c_sSubTaskList, sTaskList);
                    }
                    else
                    {
                        sTaskList.append (subTaskInf);
                        oMTaskInf.insert(c_sSubTaskList, sTaskList);
                    }
                }
            }
        }
        if (iM != -1)
        {
            mTaskList.replace(iM, oMTaskInf);
            m_oMember[c_sMainTaskList] = mTaskList;
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

void FileServer::createNewTask(QJsonValue oNewTaskName, QJsonValue oParentTaskName)
{
    QJsonObject oNewTask;
    oNewTask.insert(c_sTaskName         , oNewTaskName);
    oNewTask.insert(c_sPlannedTime      , 0.);
    oNewTask.insert(c_sPlannedTimeUnit  , QStringLiteral ("时"));
    oNewTask.insert(c_sStartTime        , QDateTime::currentDateTime ().toString (c_sDateTimeFormat));
    oNewTask.insert(c_sUsedTime         , 0.);
    oNewTask.insert(c_sTimeFix          , 0.);
    oNewTask.insert(c_sTaskPercent      , 0);
    oNewTask.insert(c_sTaskDetails      , QStringLiteral (""));
    oNewTask.insert(c_sTaskState        , QStringLiteral ("准备"));
    oNewTask.insert(c_sPriority         , QStringLiteral ("暂缓"));
    oNewTask.insert(c_sDifficulty       , QStringLiteral ("一级"));

    QJsonArray mTaskList;
    if (m_oMember.contains (c_sMainTaskList) && m_oMember.value (c_sMainTaskList).isArray ())
    {
        mTaskList = m_oMember.value (c_sMainTaskList).toArray ();
        if (oParentTaskName == "")
        {
            mTaskList.append (oNewTask);
        }
        else
        {
            QJsonObject oMainTask;
            QJsonArray oSubTasks;
            int iM(-1);
            for (int i = 0; i < mTaskList.count (); i++)
            {
                if (mTaskList.at (i).isObject () && mTaskList.at (i).toObject ().contains (c_sTaskName)
                        && (mTaskList.at (i).toObject ().value (c_sTaskName) == oParentTaskName))
                {
                    oMainTask = mTaskList.at (i).toObject ();
                    if (mTaskList.at (i).toObject ().contains (c_sSubTaskList)
                            && mTaskList.at (i).toObject ().value (c_sSubTaskList).isArray ())
                    {
                        oSubTasks = mTaskList.at (i).toObject ().value (c_sSubTaskList).toArray ();
                    }
                    oSubTasks.append (oNewTask);
                    iM = i;
                }
                if (mTaskList.at (i).toObject ().contains (c_sSubTaskList))
                {
                    oMainTask[c_sSubTaskList] = oSubTasks;
                }
                else
                {
                    oMainTask.insert (c_sSubTaskList, oSubTasks);
                }
            }
            if (iM != -1)
            {
                mTaskList.replace (iM, oMainTask);
            }
        }
        m_oMember[c_sMainTaskList] = mTaskList;
    }
    else
    {
        mTaskList.append (oNewTask);
        m_oMember.insert (c_sMainTaskList, mTaskList);
        m_oMember.insert (c_sMemberRole, QStringLiteral("1研发"));
        m_oMember.insert (c_sMemberName, m_oUserName);
    }
}

void FileServer::deleteTask(QJsonValue oTaskName, QJsonValue oParentTaskName)
{
    if (m_oMember.contains (c_sMainTaskList) && m_oMember.value (c_sMainTaskList).isArray ())
    {
        QJsonArray mTaskList = m_oMember.value (c_sMainTaskList).toArray ();
        int iM(-1), iS(-1);
        if (oParentTaskName == "")
        {
            for (int i = 0; i < mTaskList.count (); i++)
            {
                if (mTaskList.at (i).isObject () && mTaskList.at (i).toObject ().contains (c_sTaskName)
                        && (mTaskList.at (i).toObject ().value (c_sTaskName) == oTaskName))
                {
                    iM = i;
                }
            }
            if (iM != -1)
            {
                mTaskList.removeAt (iM);
            }
        }
        else
        {
            QJsonObject oMainTask;
            QJsonArray oSubTasks;
            for (int i = 0; i < mTaskList.count (); i++)
            {
                if (mTaskList.at (i).isObject () && mTaskList.at (i).toObject ().contains (c_sTaskName)
                        && (mTaskList.at (i).toObject ().value (c_sTaskName) == oParentTaskName))
                {
                    oMainTask = mTaskList.at (i).toObject ();
                    if (mTaskList.at (i).toObject ().contains (c_sSubTaskList)
                            && mTaskList.at (i).toObject ().value (c_sSubTaskList).isArray ())
                    {
                        oSubTasks = mTaskList.at (i).toObject ().value (c_sSubTaskList).toArray ();
                        for (int j = 0; j < oSubTasks.count (); j++)
                        {
                            if (oSubTasks.at (j).isObject () && oSubTasks.at (j).toObject ().contains (c_sTaskName)
                                    && (oSubTasks.at (j).toObject ().value (c_sTaskName) == oTaskName))
                            {
                                iM = i;
                                iS = j;
                            }
                        }
                    }
                }
            }
            if (iS != -1 && iM != -1)
            {
                oSubTasks.removeAt (iS);
                oMainTask[c_sSubTaskList] = oSubTasks;
                mTaskList.replace (iM, oMainTask);
            }
        }
        m_oMember[c_sMainTaskList] = mTaskList;
    }
}

void FileServer::updateMainFromSub(QJsonValue mainTaskName)
{
    if (m_oMember.contains (c_sMainTaskList) && m_oMember.value (c_sMainTaskList).isArray ())
    {
        QJsonArray mTaskList = m_oMember.value (c_sMainTaskList).toArray ();
        QJsonObject mianTask;
        int iM = -1;
        for (int i = 0; i < m_oMember.value (c_sMainTaskList).toArray ().count (); i++)
        {
            if (m_oMember.value (c_sMainTaskList).toArray ().at (i).isObject ()
                    && m_oMember.value (c_sMainTaskList).toArray ().at (i).toObject ().contains (c_sTaskName)
                    && (m_oMember.value (c_sMainTaskList).toArray ().at (i).toObject ().value (c_sTaskName) == mainTaskName)
                    && m_oMember.value (c_sMainTaskList).toArray ().at (i).toObject ().contains (c_sSubTaskList)
                    && m_oMember.value (c_sMainTaskList).toArray ().at (i).toObject ().value (c_sSubTaskList).isArray ())
            {
                mianTask = m_oMember.value (c_sMainTaskList).toArray ().at (i).toObject ();
                QJsonArray subTaskList = mianTask.value (c_sSubTaskList).toArray ();
                QDateTime tStartTime, tmpTime;
                double dPlannedTime(0), dUsedTime(0), dTimeFix(0);
                int nTaskPercent(0);
                for (int j = 0; j < subTaskList.count (); j++)
                {
                    if (subTaskList.at (j).isObject () && subTaskList.at (j).toObject ().contains (c_sStartTime))
                    {
                        tmpTime = QDateTime::fromString (subTaskList.at (j).toObject ().value (c_sStartTime).toString (), c_sDateTimeFormat);
                        if (j == 0 || tStartTime > tmpTime)
                        {
                            tStartTime = tmpTime;
                        }
                    }

                    if (subTaskList.at (j).isObject () && subTaskList.at (j).toObject ().contains (c_sPlannedTime))
                    {
                        QString oUnit = subTaskList.at (j).toObject ().value (c_sPlannedTimeUnit).toString ();
                        if (QStringLiteral ("时") == oUnit)
                        {
                            dPlannedTime += subTaskList.at (j).toObject ().value (c_sPlannedTime).toDouble ();
                        }
                        else if (QStringLiteral ("天") == oUnit)
                        {
                            dPlannedTime += subTaskList.at (j).toObject ().value (c_sPlannedTime).toDouble () * 8;
                        }
                        else if (QStringLiteral ("周") == oUnit)
                        {
                            dPlannedTime += subTaskList.at (j).toObject ().value (c_sPlannedTime).toDouble () * 8 * 5;
                        }
                        else
                        {
                            qDebug() << oUnit << "is invalid unit!";
                        }
                    }

                    if (subTaskList.at (j).isObject () && subTaskList.at (j).toObject ().contains (c_sUsedTime))
                    {
                        dUsedTime += subTaskList.at (j).toObject ().value (c_sUsedTime).toDouble ();
                    }

                    if (subTaskList.at (j).isObject () && subTaskList.at (j).toObject ().contains (c_sTimeFix))
                    {
                        dTimeFix += subTaskList.at (j).toObject ().value (c_sTimeFix).toDouble ();
                    }

                    if (subTaskList.at (j).isObject () && subTaskList.at (j).toObject ().contains (c_sTaskPercent))
                    {
                        nTaskPercent += subTaskList.at (j).toObject ().value (c_sTaskPercent).toInt ();
                    }
                }
                nTaskPercent /= subTaskList.count ();

                mianTask[c_sStartTime] = tStartTime.toString (c_sDateTimeFormat);
                mianTask[c_sPlannedTime] = dPlannedTime;
                mianTask[c_sPlannedTimeUnit] = QStringLiteral ("时");
                mianTask[c_sUsedTime] = dUsedTime;
                mianTask[c_sTimeFix] = dTimeFix;
                mianTask[c_sTaskPercent] = nTaskPercent;

                iM = i;
            }
        }
        if (iM != -1)
        {
            mTaskList.replace (iM, mianTask);
            m_oMember[c_sMainTaskList] = mTaskList;
        }
    }
}

void FileServer::updateSubTaskName(QJsonValue mainTaskName, QJsonValue preSubTaskName, QJsonValue subTaskName)
{
    if (m_oMember.contains (c_sMainTaskList) && m_oMember.value (c_sMainTaskList).isArray ())
    {
         QJsonArray & mainTasks = m_oMember.value (c_sMainTaskList).toArray();
         for (int i = 0 ; i < mainTasks.count() ; i ++)
         {
            QJsonObject & mainTaskObj = mainTasks[i].toObject();
            if(mainTaskObj.contains(c_sSubTaskList) && mainTaskObj.value(c_sSubTaskList).isArray())
            {
                QJsonArray & subTasks = m_oMember.value (c_sSubTaskList).toArray();

                for (int j = 0 ; j < subTasks.count() ; j ++)
                {
                    QJsonObject & subTaskObj = subTasks[i].toObject();
                    if( subTaskObj.contains(c_sTaskName) && preSubTaskName == subTaskObj.value(c_sTaskName))
                    {
                        subTaskObj.find(c_sTaskName).value() = subTaskName;
                        break;
                    }
                }
                break;
            }
         }
    }
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
    QJsonValue oLdata;
    if(m_oMember.contains(c_sUserLogs))
    {
        for (int i = 0; i < m_oMember.value(c_sUserLogs).toArray().count(); i++)
        {
            QJsonArray oLogs = m_oMember.value(c_sUserLogs).toArray();
            for (int i = 0; i < oLogs.count(); i++)
            {
                if(oLogs.at(i).toObject().value(c_sLogDate) == oLogDate)
                {
                    oLdata = oLogs.at(i).toObject().value(c_sLogInf);
                }
            }
        }
    }
    return oLdata;
}

void FileServer::setMemberRole(QJsonValue oRole)
{
    if (m_oProject.contains (c_sProjectName) && m_oMember.contains (c_sMemberName))
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
        m_oMember[c_sMemberTime] = QDateTime::currentDateTime().toString(c_sDateTimeLongFormat);
    }
    else
    {
        m_oMember.insert(c_sMemberTime, QDateTime::currentDateTime().toString(c_sDateTimeLongFormat));
    }
}

bool FileServer::createProject(QJsonValue oProjName, QJsonValue memberName)
{
    if (oProjName == "" || hasProject(oProjName))
    {
        return false;
    }
    else
    {
        if (memberName == "")
        {
            QJsonObject oNewProj;
            oNewProj.insert(c_sProjectName, oProjName);
            QJsonArray oMembs;
            QJsonObject oMemb;
            oMemb.insert(c_sMemberName, m_oUserName);
            oMembs.append(oMemb);
            oNewProj.insert(c_sMembers, oMembs);
            m_oProject = oNewProj;
            m_oProjects.append(oNewProj);
            m_oCurProject = oProjName;

            if (m_oJsonObj.contains (c_sProjects))
            {
                m_oJsonObj[c_sProjects]  = m_oProjects;
            }
            else
            {
                m_oJsonObj.insert(c_sProjects, m_oProjects);
            }
            return true;
        }
        else
        {
            QJsonObject oNewProj;
            oNewProj.insert(c_sProjectName, oProjName);
            QJsonArray oMembs;
            QJsonObject oMemb;
            oMemb.insert(c_sMemberName, memberName);
            oMembs.append(oMemb);
            oNewProj.insert(c_sMembers, oMembs);
            m_oProject = oNewProj;
            m_oProjects.append(oNewProj);
            m_oCurProject = oProjName;

            if (m_oJsonObj.contains (c_sProjects))
            {
                m_oJsonObj[c_sProjects]  = m_oProjects;
            }
            else
            {
                m_oJsonObj.insert(c_sProjects, m_oProjects);
            }
            return true;
        }
    }
}

bool FileServer::joinProject(QJsonValue oProjName, QJsonValue memberName)
{
    if (memberName == "")
    {
        memberName = m_oUserName;
    }

    if (oProjName == "") return false;
    bool bOk = false;
    QJsonObject oProj;
    int iP = -1;
    for (int i = 0; i < m_oProjects.count(); i++)
    {
        oProj = m_oProjects.at(i).toObject();
        if (oProj.value(c_sProjectName) == oProjName)
        {
            if (oProj.contains(c_sMembers))
            {
                QJsonArray oMembs = oProj.value(c_sMembers).toArray();

                bool bHas = false;
                for (int j = 0; j < oMembs.count(); j++)
                {
                    if (oMembs.at(j).toObject().value(c_sMemberName) == memberName)
                    {
                        bHas = true;
                    }
                }
                if (!bHas)
                {
                    QJsonObject oMemb;
                    oMemb.insert(c_sMemberName, memberName);
                    oMembs.append(oMemb);
                    oProj[c_sMembers] = oMembs;
                    bOk = true;
                }
            }
            else
            {
                QJsonArray oMembs;
                QJsonObject oMemb;
                oMemb.insert(c_sMemberName, memberName);
                oMembs.append(oMemb);
                oProj.insert(c_sMembers, oMembs);
                bOk = true;
            }
            iP = i;
        }
    }
    if (iP != -1)
    {
        m_oProjects.replace(iP, oProj);
        if (m_oJsonObj.contains (c_sProjects))
        {
            m_oJsonObj[c_sProjects]  = m_oProjects;
        }
        else
        {
            m_oJsonObj.insert(c_sProjects, m_oProjects);
        }
    }
    return bOk;
}

void FileServer::leaveProject(QJsonValue oProjName, QJsonValue memberName)
{
    if (memberName == "")
    {
        memberName = m_oUserName;
    }

    if (oProjName == "") return;
    int iP(-1);
    QJsonObject oProj;
    for (int i = 0; i < m_oProjects.count(); i++)
    {
        if (m_oProjects.at(i).isObject () && m_oProjects.at(i).toObject().contains (c_sProjectName)
                && m_oProjects.at(i).toObject().value(c_sProjectName) == oProjName)
        {
            oProj = m_oProjects.at(i).toObject();
            if (oProj.contains(c_sMembers) && oProj.value(c_sMembers).isArray ())
            {
                QJsonArray oMembs;
                for (int j = 0; j < oProj.value(c_sMembers).toArray().count(); j++)
                {
                    if (oProj.value(c_sMembers).toArray().at(j).isObject ()
                            && oProj.value(c_sMembers).toArray().at(j).toObject().contains (c_sMemberName)
                            && (oProj.value(c_sMembers).toArray().at(j).toObject().value(c_sMemberName) != memberName))
                    {
                        oMembs.append (oProj.value(c_sMembers).toArray().at(j).toObject());
                    }
                }
                oProj[c_sMembers] = oMembs;
                iP = i;
            }
        }
    }
    if (iP != -1)
    {
        m_oProjects.replace(iP, oProj);
        if (m_oJsonObj.contains (c_sProjects))
        {
            m_oJsonObj[c_sProjects]  = m_oProjects;
        }
        else
        {
            m_oJsonObj.insert(c_sProjects, m_oProjects);
        }
    }
}

void FileServer::deleteProject(QJsonValue oProjName)
{
    int iP(-1);
    for (int i = 0; i < m_oProjects.count(); i++)
    {
        if (m_oProjects.at (i).isObject () && m_oProjects.at (i).toObject ().contains (c_sProjectName)
                && (m_oProjects.at (i).toObject ().value (c_sProjectName) == oProjName))
        {
            iP = i;
        }
    }
    if (iP != -1)
    {
        m_oProjects.removeAt (iP);
    }
    if (m_oProjects.count () > 0)
    {
        m_oJsonObj[c_sProjects] = m_oProjects;
    }
    else
    {
        m_oJsonObj.remove (c_sProjects);
    }
}

void FileServer::putFile(QJsonObject oFile, bool bNameMatch)
{
    QJsonArray oFiles;
    if (m_oProject.contains(c_sFiles) && m_oProject.value(c_sFiles).isArray())
    {
        for (int i = 0; i < m_oProject.value(c_sFiles).toArray().count(); i++)
        {
            if (bNameMatch)
            {
                if (m_oProject.value(c_sFiles).toArray().at(i).isObject()
                        && m_oProject.value(c_sFiles).toArray().at(i).toObject().contains(c_sFileName)
                        && (m_oProject.value(c_sFiles).toArray().at(i).toObject().value(c_sFileName)
                            == oFile.value(c_sFileName)))
                {
                    continue;
                }
            }
            else
            {
                if (m_oProject.value(c_sFiles).toArray().at(i).isObject()
                        && (m_oProject.value(c_sFiles).toArray().at(i).toObject() == oFile))
                {
                    continue;
                }
            }
            oFiles.append(m_oProject.value(c_sFiles).toArray().at(i));
        }
    }
    oFiles.append(oFile);
    if (m_oProject.contains(c_sFiles))
    {
        m_oProject[c_sFiles] = oFiles;
    }
    else
    {
        m_oProject.insert(c_sFiles, oFiles);
    }
}

QJsonObject FileServer::getFile(QJsonValue oFileName, QJsonValue projName)
{
    QJsonObject projObj;
    if (projName == "")
    {
       projObj = m_oProject;
    }
    else
    {
        projObj = getProject (projName);
    }
    QJsonObject oFile;
    if (projObj.contains(c_sFiles) && projObj.value(c_sFiles).isArray())
    {
        for (int i = 0; i < projObj.value(c_sFiles).toArray().count(); i++)
        {
            if (projObj.value(c_sFiles).toArray().at(i).isObject()
                    && projObj.value(c_sFiles).toArray().at(i).toObject().contains(c_sFileName)
                    && (projObj.value(c_sFiles).toArray().at(i).toObject().value(c_sFileName) == oFileName))
            {
                oFile = projObj.value(c_sFiles).toArray().at(i).toObject();
            }
        }
    }
    return oFile;
}

void FileServer::removeFile(QJsonObject oFile)
{
    QJsonArray oFiles;
    if (m_oProject.contains(c_sFiles) && m_oProject.value(c_sFiles).isArray())
    {
        for (int i = 0; i < m_oProject.value(c_sFiles).toArray().count(); i++)
        {
            if (m_oProject.value(c_sFiles).toArray().at(i).isObject()
                    && (m_oProject.value(c_sFiles).toArray().at(i).toObject() == oFile))
            {
                continue;
            }
            oFiles.append(m_oProject.value(c_sFiles).toArray().at(i));
        }
    }
    if (m_oProject.contains(c_sFiles))
    {
        m_oProject[c_sFiles] = oFiles;
    }
    else
    {
        m_oProject.insert(c_sFiles, oFiles);
    }
}

void FileServer::removeFile(QJsonValue oFileName)
{
    QJsonArray oFiles;
    if (m_oProject.contains(c_sFiles) && m_oProject.value(c_sFiles).isArray())
    {
        for (int i = 0; i < m_oProject.value(c_sFiles).toArray().count(); i++)
        {
            if (m_oProject.value(c_sFiles).toArray().at(i).isObject()
                    && m_oProject.value(c_sFiles).toArray().at(i).toObject().contains(c_sFileName)
                    && (m_oProject.value(c_sFiles).toArray().at(i).toObject().value(c_sFileName)
                        == oFileName))
            {
                continue;
            }
            oFiles.append(m_oProject.value(c_sFiles).toArray().at(i));
        }
    }
    if (m_oProject.contains(c_sFiles))
    {
        m_oProject[c_sFiles] = oFiles;
    }
    else
    {
        m_oProject.insert(c_sFiles, oFiles);
    }
}

QJsonArray FileServer::getFiles(QJsonValue projName)
{
    QJsonArray oFiles;
    if (projName == "")
    {
        if (m_oProject.contains(c_sFiles) && m_oProject.value(c_sFiles).isArray())
        {
            oFiles = m_oProject.value(c_sFiles).toArray();
        }
    }
    else
    {
        for (int i = 0; i < m_oProjects.count (); i++)
        {
            if (m_oProjects.at (i).isObject () && m_oProjects.at (i).toObject ().contains (c_sProjectName)
                    && (m_oProjects.at (i).toObject ().value (c_sProjectName) == projName)
                    && m_oProjects.at (i).toObject ().contains (c_sFiles)
                    && m_oProjects.at (i).toObject ().value (c_sFiles).isArray ())
            {
                oFiles = m_oProjects.at (i).toObject ().value (c_sFiles).toArray ();
            }
        }
    }
    return oFiles;
}

void FileServer::setFiles(QJsonArray oFiles, QJsonValue projName)
{
    if (projName == "")
    {
        if (m_oProject.contains(c_sFiles))
        {
            m_oProject[c_sFiles] = oFiles;
        }
        else
        {
            m_oProject.insert (c_sFiles, oFiles);
        }
    }
    else
    {
        QJsonObject oProj;
        int iP = -1;
        for (int i = 0; i < m_oProjects.count (); i++)
        {
            if (m_oProjects.at (i).isObject () && m_oProjects.at (i).toObject ().contains (c_sProjectName)
                    && (m_oProjects.at (i).toObject ().value (c_sProjectName) == projName))
            {
                oProj = m_oProjects.at (i).toObject ();
                if (oProj.contains(c_sFiles))
                {
                    oProj[c_sFiles] = oFiles;
                }
                else
                {
                    oProj.insert (c_sFiles, oFiles);
                }
                iP = i;
            }
        }
        if (iP != -1)
        {
            m_oProjects.replace (iP, oProj);
            if (m_oProject.value (c_sProjectName) == oProj.value (c_sProjectName))
            {
                m_oProject = oProj;
            }
        }
    }
}

void FileServer::writeFileLog(QJsonValue logInfo)
{
    if (m_oProject.contains (c_sFileLogs) && m_oProject.value (c_sFileLogs).isArray ())
    {
        QJsonArray oFileLogs = m_oProject.value (c_sFileLogs).toArray ();
        oFileLogs.append (logInfo);
        m_oProject[c_sFileLogs] = oFileLogs;
    }
    else
    {
        QJsonArray oFileLogs;
        oFileLogs.append (logInfo);
        m_oProject.insert (c_sFileLogs, oFileLogs);
    }
}

void FileServer::clearFileLog(int iBegin, int iEnd)
{
    if (m_oProject.contains (c_sFileLogs) && m_oProject.value (c_sFileLogs).isArray ())
    {
        QJsonArray oFileLogs = m_oProject.value (c_sFileLogs).toArray ();
        if (iEnd == 0) iEnd = oFileLogs.count ();
        QList<int> nToDel;
        for (int i = iBegin; i < qMin(iEnd, oFileLogs.count ()); i++)
        {
            nToDel.append (i);
        }
        if (nToDel.count () == oFileLogs.count ())
        {
            m_oProject.remove (c_sFileLogs);
        }
        else
        {
            for (int i = 0; i < nToDel.count (); i++)
            {
                oFileLogs.removeAt (i);
            }
            m_oProject[c_sFileLogs] = oFileLogs;
        }
    }
}

QJsonArray FileServer::getFileLogs(QJsonValue projName)
{
    QJsonArray oFileLogs;
    if (projName == "")
    {
        if (m_oProject.contains(c_sFileLogs) && m_oProject.value(c_sFileLogs).isArray())
        {
            oFileLogs = m_oProject.value(c_sFileLogs).toArray();
        }
    }
    else
    {
        for (int i = 0; i < m_oProjects.count (); i++)
        {
            if (m_oProjects.at (i).isObject () && m_oProjects.at (i).toObject ().contains (c_sProjectName)
                    && (m_oProjects.at (i).toObject ().value (c_sProjectName) == projName)
                    && m_oProjects.at (i).toObject ().contains (c_sFileLogs)
                    && m_oProjects.at (i).toObject ().value (c_sFileLogs).isArray ())
            {
                oFileLogs = m_oProjects.at (i).toObject ().value (c_sFileLogs).toArray ();
            }
        }
    }
    return oFileLogs;
}

void FileServer::setFileLogs(QJsonArray oFileLogs, QJsonValue projName)
{
    if (projName == "")
    {
        if (m_oProject.contains(c_sFileLogs))
        {
            m_oProject[c_sFileLogs] = oFileLogs;
        }
        else
        {
            m_oProject.insert (c_sFileLogs, oFileLogs);
        }
    }
    else
    {
        QJsonObject oProj;
        int iP = -1;
        for (int i = 0; i < m_oProjects.count (); i++)
        {
            if (m_oProjects.at (i).isObject () && m_oProjects.at (i).toObject ().contains (c_sProjectName)
                    && (m_oProjects.at (i).toObject ().value (c_sProjectName) == projName))
            {
                oProj = m_oProjects.at (i).toObject ();
                if (oProj.contains(c_sFileLogs))
                {
                    oProj[c_sFileLogs] = oFileLogs;
                }
                else
                {
                    oProj.insert (c_sFileLogs, oFileLogs);
                }
                iP = i;
            }
        }
        if (iP != -1)
        {
            m_oProjects.replace (iP, oProj);
            if (m_oProject.value (c_sProjectName) == oProj.value (c_sProjectName))
            {
                m_oProject = oProj;
            }
        }
    }
}

bool FileServer::hasMember(QJsonValue userName, QJsonValue projName)
{
    bool bIN = false;
    QJsonObject proj;
    if (projName == "")
    {
        proj = m_oProject;
    }
    else
    {
        proj = getProject (projName);
    }
    if (proj.contains (c_sMembers) && proj.value (c_sMembers).isArray ())
    {
        for (int i = 0; i < proj.value (c_sMembers).toArray ().count (); i++)
        {
            if (proj.value (c_sMembers).toArray ().at (i).toObject ().contains (c_sMemberName)
                    && proj.value (c_sMembers).toArray ().at (i).toObject ().value (c_sMemberName) == userName)
            {
                bIN = true;
            }
        }
    }
    return bIN;
}

bool FileServer::hasProject(QJsonValue projName)
{
    bool bHave = false;
    for (int i = 0; i < m_oProjects.count (); i++)
    {
        if (m_oProjects.at (i).isObject () && m_oProjects.at (i).toObject ().contains (c_sProjectName)
                && (m_oProjects.at (i).toObject ().value (c_sProjectName) == projName))
        {
            bHave = true;
        }
    }
    return bHave;
}

QJsonArray FileServer::getProjList()
{
    QJsonArray oProjList;
    for (int i =0; i < m_oProjects.count (); i++)
    {
        if (m_oProjects.at (i).isObject () && m_oProjects.at (i).toObject ().contains (c_sProjectName)
                && !oProjList.contains (m_oProjects.at (i).toObject ().value (c_sProjectName)))
        {
            oProjList.append (m_oProjects.at (i).toObject ().value (c_sProjectName));
        }
    }
    return oProjList;
}

QJsonObject FileServer::getProject(QJsonValue oProjName)
{
    QJsonObject oProj;
    if (oProjName == "")
    {
        oProj = m_oProject;
    }
    else
    {
        for (int i = 0; i < m_oProjects.count (); i++)
        {
            if (m_oProjects.at (i).isObject () && m_oProjects.at (i).toObject ().contains (c_sProjectName)
                    && (m_oProjects.at (i).toObject ().value (c_sProjectName) == oProjName))
            {
                oProj = m_oProjects.at (i).toObject ();
            }
        }
    }
    return oProj;
}

void FileServer::setProject(QJsonObject oProjectData, QJsonValue oProjName)
{
    if (oProjName == "")
    {
        m_oProject = oProjectData;
    }
    else
    {
        int iP = -1;
        for (int i = 0; i < m_oProjects.count (); i++)
        {
            if (m_oProjects.at (i).isObject () && m_oProjects.at (i).toObject ().contains (c_sProjectName)
                    && (m_oProjects.at (i).toObject ().value (c_sProjectName) == oProjName))
            {
                iP = i;
            }
        }
        if (iP != -1)
        {
            m_oProjects.replace (iP, oProjectData);
        }
    }
}

QJsonObject FileServer::getMember(QJsonValue oProjName)
{
    QJsonObject oMemb;
    if (oProjName == "")
    {
        oMemb = m_oMember;
    }
    else
    {
        for (int i = 0; i < m_oProjects.count (); i++)
        {
            if (m_oProjects.at (i).isObject () && m_oProjects.at (i).toObject ().contains (c_sProjectName)
                    && (m_oProjects.at (i).toObject ().value (c_sProjectName) == oProjName)
                    && m_oProjects.at (i).toObject ().contains (c_sMembers)
                    && m_oProjects.at (i).toObject ().value (c_sMembers).isArray ())
            {
                for (int j = 0; j < m_oProjects.at (i).toObject ().value (c_sMembers).toArray ().count (); j++)
                {
                    if (m_oProjects.at (i).toObject ().value (c_sMembers).toArray ().at (j).toObject ().contains (c_sMemberName)
                            && (m_oProjects.at (i).toObject ().value (c_sMembers).toArray ().at (j).toObject ().value (c_sMemberName)
                            == m_oUserName))
                    {
                        oMemb = m_oProjects.at (i).toObject ().value (c_sMembers).toArray ().at (j).toObject ();
                    }
                }
            }
        }
    }
    return oMemb;
}

void FileServer::setMember(QJsonObject oMemberData, QJsonValue oProjName)
{
    if (oProjName == "")
    {
        m_oMember = oMemberData;
    }
    else
    {
        QJsonObject oProject;
        QJsonArray oMembs;
        int iP(-1), iM(-1);
        for (int i = 0; i < m_oProjects.count (); i++)
        {
            if (m_oProjects.at (i).isObject () && m_oProjects.at (i).toObject ().contains (c_sProjectName)
                    && (m_oProjects.at (i).toObject ().value (c_sProjectName) == oProjName))
            {
                oProject = m_oProjects.at (i).toObject ();
                if (oProject.contains (c_sMembers) && oProject.value (c_sMembers).isArray ())
                {
                    oMembs = oProject.value (c_sMembers).toArray ();
                    for (int j = 0; j < oMembs.count (); j++)
                    {
                        if (oMembs.at (j).isObject () && oMembs.at (j).toObject ().contains (c_sMemberName)
                                && (oMembs.at (j).toObject ().value (c_sMemberName) == oMemberData.value (c_sMemberName)))
                        {
                            iM = j;
                        }
                    }
                    if (iM != -1)
                    {
                        oMembs.replace (iM, oMemberData);
                        oProject[c_sMembers] = oMembs;
                    }
                    else
                    {
                        oMembs.append (oMemberData);
                        oProject[c_sMembers] = oMembs;
                    }
                }
                else
                {
                    oMembs.append (oMemberData);
                    oProject.insert (c_sMembers, oMembs);
                }
                iP = i;
            }
        }
        if (iP != -1)
        {
            m_oProjects.replace (iP, oProject);
            if (oProject.value (c_sProjectName) == m_oCurProject)
            {
                m_oProject = oProject;
                m_oMembers = m_oProject.value (c_sMembers).toArray ();
            }
        }
    }
}

void FileServer::updateMemberToJsonObj()
{
    if (m_oMembers.count () > 0)
    {
        int iM(-1);
        for (int i = 0; i < m_oMembers.count(); i++)
        {
            if (m_oMembers.at(i).toObject().value(c_sMemberName) == m_oMember.value(c_sMemberName))
            {
                iM = i;
            }
        }
        if (iM != -1)
        {
            m_oMembers.replace(iM, m_oMember);
        }
    }
    else if (m_oMember.contains (c_sMemberName))
    {
        m_oMembers.append (m_oMember);
    }

    if (m_oProject.contains (c_sMembers))
    {
        m_oProject[c_sMembers] = m_oMembers;
    }
    else if (m_oMembers.count () > 0)
    {
        m_oProject.insert (c_sMembers, m_oMembers);
    }

    if (m_oProjects.count () > 0)
    {
        int iP(-1);
        for (int i = 0; i < m_oProjects.count(); i++)
        {
            if (m_oProjects.at(i).toObject().value(c_sProjectName) == m_oProject.value(c_sProjectName))
            {
                iP = i;
            }
        }
        if (iP != -1)
        {
            m_oProjects.replace(iP, m_oProject);
        }
    }
    else if (m_oProject.contains (c_sProjectName))
    {
        m_oProjects.append (m_oProject);
    }

    if (m_oJsonObj.contains (c_sUserName))
    {
        m_oJsonObj[c_sUserName] = m_oUserName;
    }
    else
    {
        m_oJsonObj.insert(c_sUserName, m_oUserName);
    }
    if (m_oJsonObj.contains (c_sCurProject))
    {
        m_oJsonObj[c_sCurProject] = m_oCurProject;
    }
    else
    {
        m_oJsonObj.insert(c_sCurProject, m_oCurProject);
    }
    if (m_oJsonObj.contains (c_sProjects) && m_oProjects.count () > 0)
    {
        m_oJsonObj[c_sProjects] = m_oProjects;
    }
    else if (m_oProjects.count () > 0)
    {
        m_oJsonObj.insert(c_sProjects, m_oProjects);
    }
}

void FileServer::updateMemberFromJsonObj()
{
    m_oUserName = m_oJsonObj.value(c_sUserName);
    m_oCurProject = m_oJsonObj.value(c_sCurProject);

    QJsonArray emptProjs, emptMembs;
    QJsonObject emptProj, emptMemb;
    if (m_oJsonObj.contains(c_sProjects) && m_oJsonObj.value(c_sProjects).isArray())
    {
        m_oProjects = m_oJsonObj.value(c_sProjects).toArray();
    }
    else
    {
        m_oProjects = emptProjs;
    }

    if (m_oProjects.count() > 0)
    {
        for (int i = 0; i < m_oProjects.count(); i++)
        {
            if (m_oProjects.at(i).isObject() && m_oProjects.at(i).toObject().contains(c_sProjectName)
                    && (m_oProjects.at(i).toObject().value(c_sProjectName) == m_oCurProject))
            {
                m_oProject = m_oProjects.at(i).toObject();
            }
        }
    }
    else
    {
        m_oProject = emptProj;
    }

    if (m_oProject.contains(c_sMembers) && m_oProject.value(c_sMembers).isArray())
    {
        m_oMembers = m_oProject.value(c_sMembers).toArray();
    }
    else
    {
        m_oMembers = emptMembs;
    }

    if (m_oMembers.count() > 0)
    {
        for (int i = 0; i < m_oMembers.count(); i++)
        {
            if (m_oMembers.at(i).isObject() && m_oMembers.at(i).toObject().contains(c_sMemberName)
                    && (m_oMembers.at(i).toObject().value(c_sMemberName) == m_oUserName))
            {
                m_oMember = m_oMembers.at(i).toObject();
            }
        }
    }
    else
    {
        m_oMember = emptMemb;
    }
}
