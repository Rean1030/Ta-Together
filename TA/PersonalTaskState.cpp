#include "PersonalTaskState.h"
#include <QHeaderView>
#include <QToolTip>

#include "fileserver.h"
#include "public.h"

PersonalTaskState::PersonalTaskState(QWidget * parent/* = 0*/)
 : QTableWidget(parent)
{
    initUi();

}

PersonalTaskState::PersonalTaskState(const QJsonObject&  member, QWidget * parent/* = 0*/)
 : QTableWidget(parent)
{
    m_jMember = member;
    initUi();
    updateUi();
}

void PersonalTaskState::setJsonMemberValue(const QJsonObject&  member)
{
    m_jMember = member;
}

void PersonalTaskState::initUi()
{
    setRowCount(4);
    setColumnCount(1);
    setColumnWidth(0,200);

    horizontalHeader()->hide();
    verticalHeader()->hide();
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

QString PersonalTaskState::getToolTip(QJsonObject& subTaskJson)
{
    QString tip;
    tip += QStringLiteral("%1:%2\n").arg(c_sPlannedTime).arg(subTaskJson.value(c_sPlannedTime).toString());
    tip += QStringLiteral("%1:%2\n").arg(c_sUsedTime).arg(subTaskJson.value(c_sUsedTime).toString());
    tip += QStringLiteral("%1:%2\n").arg(c_sStartTime).arg(subTaskJson.value(c_sStartTime).toString());
    tip += QStringLiteral("%1:%2\n").arg(c_sTaskPercent).arg(subTaskJson.value(c_sTaskPercent).toString());
    tip += QStringLiteral("%1:%2\n").arg(c_sTaskState).arg(subTaskJson.value(c_sTaskState).toString());
    tip += QStringLiteral("%1:%2\n").arg(c_sPriority).arg(subTaskJson.value(c_sPriority).toString());
    tip += QStringLiteral("%1:%2").arg(c_sDifficulty).arg(subTaskJson.value(c_sDifficulty).toString());
    return tip;
}


void PersonalTaskState::updateUi()
{
    clearContents();

    int curRow = 0;
    if(m_jMember.contains(c_sMemberName) && m_jMember.value(c_sMemberName).isString())
    {
        QTableWidgetItem * item = new QTableWidgetItem(m_jMember.value(c_sMemberName).toString());
        item->setTextAlignment(Qt::AlignCenter);
        setItem(0,curRow++,item);
    }

    if(m_jMember.contains(c_sMainTaskList) && m_jMember.value(c_sMainTaskList).isArray())
    {
        QStringList taskInfos;
        QStringList taskToolTips;
        QVector<QColor> taskStateClrs;
        QJsonArray mainTasks = m_jMember.value(c_sMainTaskList).toArray();
        for(int i = 0 ;i < mainTasks.count() ; i++)
        {
            QJsonObject mainTaskJson = mainTasks[i].toObject();

            QJsonArray subTasks  = mainTasks[i].toObject().value(c_sSubTaskList).toArray();
            for (int j = 0 ; j < subTasks.size(); j++)
            {
                QJsonObject subTaskJson = subTasks[j].toObject();
                QString taskState = subTaskJson.value(c_sTaskState).toString();
                if(taskState != QStringLiteral("完成") && taskState != QStringLiteral("准备"))
                {
                    QString taskInfo = QStringLiteral("[%1] %2").arg(mainTaskJson.value(c_sTaskName).toString())
                            .arg(subTaskJson.value(c_sTaskName).toString());
                    taskInfos.append(taskInfo);

                    taskStateClrs.append(g_convertTaskStateToColor(taskState));

                    taskToolTips.append(getToolTip(subTaskJson));
                    continue;
                }

            }
        }

        if(taskInfos.empty())
        {
            QTableWidgetItem * item = new QTableWidgetItem(QStringLiteral("当前无任务进行"));
            setItem(0,curRow++,item);
        }
        else
        {
            for(int i = 0 ;i < taskInfos.count() ; i++)
            {
                if(taskInfos[i].isEmpty())
                {
                    continue;
                }

                QTableWidgetItem * item = new QTableWidgetItem(taskInfos[i]);

                if(!taskToolTips[i].isEmpty())
                {
                    item->setToolTip(taskToolTips[i]);
                }


                setItem(0,curRow++,item);
                item->setBackground(taskStateClrs[i]);
            }
        }
    }

    setRowCount(curRow);

}


