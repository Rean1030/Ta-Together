#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PersonalTaskState.h"
#include "public.h"
#include <QFileDialog>
#include "theme/manhattanstyle.h"
#include "configdialog.h"
#include "theme/theme.h"
#include "theme/theme_p.h"
#include "setting.h"

#include <QIcon>
#include <QStyleFactory>
#include <QMenu>
#include <QCloseEvent>

using namespace Utils;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    c_newTag = 1;
    m_pFileServer = new FileServer(this);
    m_pNetServer = new UdpSocket(m_pFileServer, this);
    m_pTcpServer = new TcpServer(this);

    ui->setupUi(this);
    ui->treeWidget_MyTask->setCurrentItem(ui->treeWidget_MyTask->itemAt(0, 0));
    initNumEditValidator();

    m_pFileServer->readFile();
    ui->dateTimeEdit_EndTime->setReadOnly(true);

    // 获取局域网消息，初始化页面
    m_pFileServer->updateMemberFromJsonObj ();
    m_pFileServer->clearInvalid ();
    updatePages (ui->tabWidget->currentIndex ());
    updateProjectList (ui->comboBox_ProjectName->currentText ());
    if (ui->lineEdit_UserName->text () == "")
    {
        ui->lineEdit_UserName->setText (getOSUserName());
        m_pFileServer->setUserName (getOSUserName());
    }
    if (ui->comboBox_UserRole->currentText () == "")
    {
        ui->comboBox_UserRole->setCurrentIndex (0);
        m_pFileServer->setMemberRole (QStringLiteral("1研发"));
    }
    m_pFileServer->updateMemberToJsonObj ();

    m_pNetServer->getProjList ();
    m_pNetServer->getFileList(m_pFileServer->getCurProjName ());
    m_pNetServer->getFileLogs (m_pFileServer->getCurProjName ());
    m_pNetServer->getMemberInfo (m_pFileServer->getCurProjName ());

    ui->tableWidget_TeamBoard->verticalHeader()->hide();
    ui->tabWidget->setCurrentIndex(0);

    ui->tableWidget_TeamTask->setContextMenuPolicy(Qt::CustomContextMenu);
    m_pTeamTaskPopMenu = new QMenu(ui->tableWidget_TeamTask);
    m_pTeamTaskActExport = new QAction(QStringLiteral("导出Excel"), ui->tableWidget_TeamTask);
    connect(m_pTeamTaskActExport, SIGNAL(triggered()), this, SLOT(onTeamTaskExportExcel()));

    ui->dateEdit_LogDate->setDate(QDate::currentDate());

    ui->tableWidget_TeamBoard->setContextMenuPolicy(Qt::CustomContextMenu);
    m_pTeamBoardPopMenu = new QMenu(ui->tableWidget_TeamBoard);
    m_pTeamBoardActExport = new QAction(QStringLiteral("导出Excel"), ui->tableWidget_TeamBoard);
    connect(m_pTeamBoardActExport, SIGNAL(triggered()), this, SLOT(onTeamBoardExportExcel()));


    Theme::initialPalette();

    Theme *themeFromArg = ThemeEntry::createTheme(QString(":/themeqrc/%1").arg(CSetting::instance().getCurThemeEn()));
    if(NULL != themeFromArg && !CSetting::instance().getCurThemeEn().contains("default"))
    {
        setCreatorTheme(themeFromArg);
        QApplication::setPalette(themeFromArg->palette());
        QString baseName = "windows";
        const QStringList available = QStyleFactory::keys();
        foreach (const QString &s, Utils::creatorTheme()->preferredStyles()) {
            if (available.contains(s, Qt::CaseInsensitive)) {
                baseName = s;
                break;
            }
        }
        QApplication::setStyle(new ManhattanStyle(baseName));
    }

    connect (m_pNetServer, SIGNAL(updateProjs()), this, SLOT(updateProjectList()));
    connect (m_pNetServer, SIGNAL(updateFiles()), this, SLOT(updateFileTabWidget()));
    connect (m_pNetServer, SIGNAL(updateFileLogs()), this, SLOT(updateFileLogListWidget()));

    createActions();
    createTrayIcon();
}

MainWindow::~MainWindow()
{
    m_pFileServer->writeFile ();
    delete ui;
    delete m_pNetServer;
    delete m_pFileServer;
    delete m_pTcpServer;
}

QString MainWindow::getOSUserName()
{
    QString userName = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    userName = userName.section("/", -1, -1);
    return userName;
}

void MainWindow::initNumEditValidator()
{
    ui->lineEdit_PlannedTime->setValidator(new QDoubleValidator(0));
    ui->lineEdit_TimeFix->setValidator(new QDoubleValidator());
}

void MainWindow::updateEndTime()
{
    if (ui->horizontalSlider_TaskPercent->value() < 100)
    {
        QDateTime startDT = ui->dateTimeEdit_StartTime->dateTime();
        QDateTime endDT = startDT;
        qint64 plannedNum =  ui->lineEdit_PlannedTime->text().toLongLong();
        qint64 iD(0), iH(0);
        switch(ui->comboBox_TimeUnit->currentIndex())
        {
        case 0:
        {
            iD = plannedNum / 8;
            iH = plannedNum % 8;
        } break;
        case 1:
        {
            iD = plannedNum;
        } break;
        case 2:
        {
            iD = plannedNum * 5;
        } break;
        default:
        {
            qDebug() << "Ivalid unit type!";
        } break;
        }
        qint64 iN = iD;
        for (qint64 i = 1; i < iD + 1; i++)
        {
            if (startDT.addDays(i).date().dayOfWeek() > 5)
            {
                iN++;
            }
        }
        endDT = startDT.addDays(iN).addSecs(iH * 3600);
        ui->dateTimeEdit_EndTime->setDateTime(endDT);
    }
}

QDateTime MainWindow::getEndTime(QDateTime oStartDate, double dHours)
{
    QDateTime startDT = oStartDate;
    QDateTime endDT = oStartDate;
    qint64 iD(0), iH(0);
    iD = (int)dHours / 8;
    iH = (int)dHours % 8;
    qint64 iN = iD;
    for (qint64 i = 1; i < iD + 1; i++)
    {
        if (startDT.addDays(i).date().dayOfWeek() > 5)
        {
            iN++;
        }
    }
    endDT = startDT.addDays(iN).addSecs(iH * 3600);
    return endDT;
}

double MainWindow::getHours(double dPlanTime, QString sPlannedTimeUnit)
{
    double result = dPlanTime;
    if (QStringLiteral ("天") == sPlannedTimeUnit)
    {
        result = result * 8;
    }
    else if (QStringLiteral ("周") == sPlannedTimeUnit)
    {
        result = result * 8 * 5;
    }
    return result;
}

void MainWindow::updatePlannedTime()
{
    if (ui->horizontalSlider_TaskPercent->value() < 100)
    {
        QDateTime startDT = ui->dateTimeEdit_StartTime->dateTime();
        QDateTime endDT = ui->dateTimeEdit_EndTime->dateTime();
        qint64 iD = startDT.daysTo(endDT);
        qint64 iH = startDT.time().secsTo(endDT.time()) / 3600;
        qint64 iN = iD;
        for (qint64 i = 1; i < iD + 1; i++)
        {
            if (startDT.addDays(i).date().dayOfWeek() > 5)
            {
                iN--;
            }
        }
        qint64 iT = 0;
        switch(ui->comboBox_TimeUnit->currentIndex())
        {
        case 0:
        {
            iT = iN * 8 + iH;
        } break;
        case 1:
        {
            iT = iN + iH / 8;
        } break;
        case 2:
        {
            iT = (iN + iH / 8) / 5;
        } break;
        default:
        {
            qDebug() << "Ivalid unit type!";
        } break;
        }
        ui->lineEdit_PlannedTime->setText(QString::number(iT));
    }
}

void MainWindow::updateUsedTime()
{
    QDateTime startDT = ui->dateTimeEdit_StartTime->dateTime();
    double dF = ui->lineEdit_TimeFix->text().toDouble();
    if (ui->horizontalSlider_TaskPercent->value() == 100)
    {
        QDateTime endDT = ui->dateTimeEdit_EndTime->dateTime();
        qint64 iD = startDT.daysTo(endDT);
        qint64 iH = startDT.time().secsTo(endDT.time()) / 3600;
        qint64 iN = iD;
        for (qint64 i = 1; i < iD + 1; i++)
        {
            if (startDT.addDays(i).date().dayOfWeek() > 5)
            {
                iN--;
            }
        }
        qint64 unsdT = (iN * 8 + iH) < 0 ? 0: (iN * 8 + iH);
        ui->lcdNumber_UsedTime->display(QString::number(unsdT+ dF));
    }
    else
    {
        QDateTime endDT = QDateTime::currentDateTime();
        qint64 iD = startDT.daysTo(endDT);
        qint64 iH = startDT.time().secsTo(endDT.time()) / 3600;
        qint64 iN = iD;
        for (qint64 i = 1; i < iD + 1; i++)
        {
            if (startDT.addDays(i).date().dayOfWeek() > 5)
            {
                iN--;
            }
        }
        qint64 unsdT = (iN * 8 + iH) < 0 ? 0: (iN * 8 + iH);
        ui->lcdNumber_UsedTime->display(QString::number(unsdT+ dF));
    }
}

void MainWindow::updateCurTaskInfo(QTreeWidgetItem *current)
{
    if (!current)
    {
        ui->pushButton_AddSubTask->setEnabled (false);
        ui->pushButton_DeleteTask->setEnabled (false);
        ui->groupBox_MyTask->setEnabled (false);
        return;
    }
    else
    {
        ui->pushButton_AddSubTask->setEnabled (true);
        ui->pushButton_DeleteTask->setEnabled (true);
        ui->groupBox_MyTask->setEnabled (true);
    }
    QJsonObject oTask;
    if (!current->parent ())
    {
        oTask = m_pFileServer->getTaskInf (current->text (0));
        setTaskInfFromJs (oTask);

        ui->lineEdit_PlannedTime->setEnabled (false);
        ui->comboBox_TimeUnit->setEnabled (false);
        ui->dateTimeEdit_StartTime->setEnabled (false);
        ui->dateTimeEdit_EndTime->setEnabled (false);
        ui->horizontalSlider_TaskPercent->setEnabled (false);
        QDateTime dtStart, dtEnd;
        getMainTaskScope(oTask, dtStart, dtEnd);
        if(dtEnd.isValid())
        {
            ui->dateTimeEdit_EndTime->setDate(dtEnd.date());
        }
    }
    else
    {
        ui->lineEdit_PlannedTime->setEnabled (true);
        ui->comboBox_TimeUnit->setEnabled (true);
        ui->dateTimeEdit_StartTime->setEnabled (true);
        ui->dateTimeEdit_EndTime->setEnabled (true);
        ui->horizontalSlider_TaskPercent->setEnabled (true);

        oTask = m_pFileServer->getTaskInf (current->parent ()->text (0), current->text (0));
        setTaskInfFromJs (oTask);
        updateEndTime ();
    }    
}

void MainWindow::updateTreeWidget()
{
    QJsonObject oMemb = m_pFileServer->getMember ();
    ui->treeWidget_MyTask->clear ();
    if (oMemb.contains (c_sMainTaskList) && oMemb.value (c_sMainTaskList).isArray ())
    {
        QJsonArray oMainTasks = oMemb.value (c_sMainTaskList).toArray ();
        for (int i = 0; i < oMainTasks.count (); i++)
        {
            if (oMainTasks.at (i).isObject () && oMainTasks.at (i).toObject ().contains (c_sTaskName))
            {
                QTreeWidgetItem* pMItem = new QTreeWidgetItem();
                pMItem->setText (0, oMainTasks.at (i).toObject ().value (c_sTaskName).toString ());
                ui->treeWidget_MyTask->addTopLevelItem (pMItem);

                if (oMainTasks.at (i).toObject ().contains (c_sSubTaskList)
                        && oMainTasks.at (i).toObject ().value (c_sSubTaskList).isArray ())
                {
                    QJsonArray oSubTasks = oMainTasks.at (i).toObject ().value (c_sSubTaskList).toArray ();
                    for (int j = 0; j < oSubTasks.count (); j++)
                    {
                        if (oSubTasks.at (j).isObject () && oSubTasks.at (j).toObject ().contains (c_sTaskName))
                        {
                            QTreeWidgetItem* pSItem = new QTreeWidgetItem();
                            pSItem->setText (0, oSubTasks.at (j).toObject ().value (c_sTaskName).toString ());
                            pMItem->addChild (pSItem);
                        }
                    }
                }
            }
        }
    }
    if (ui->treeWidget_MyTask->topLevelItemCount () > 0)
    {
        ui->treeWidget_MyTask->setCurrentItem(ui->treeWidget_MyTask->itemAt(0, 0));
    }
    ui->treeWidget_MyTask->expandAll();
}

void MainWindow::updateFileTabWidget()
{
    ui->tableWidget_ProjectFile->clear ();

    QStringList slHeader;
    slHeader.append (QStringLiteral ("文件"));
    slHeader.append (QStringLiteral ("描述"));
    slHeader.append (QStringLiteral ("作者"));
    slHeader.append (QStringLiteral ("时间"));

    m_pNetServer->getFileList (m_pFileServer->getCurProjName ());
    QJsonArray oFileArr = m_pFileServer->getFiles();

    QTableWidget *pTab = ui->tableWidget_ProjectFile;
    pTab->setRowCount(oFileArr.count());
    for(int i = 0; i < oFileArr.count(); ++i)
    {
        QJsonObject obj = oFileArr[i].toObject();
        pTab->setItem(i, 0, new QTableWidgetItem(obj.value(c_sFileName).toString()));
        pTab->setItem(i, 1, new QTableWidgetItem(obj.value(c_sFileDes).toString()));
        pTab->setItem(i, 2, new QTableWidgetItem(obj.value(c_sFileUser).toString()));
        pTab->setItem(i, 3, new QTableWidgetItem(obj.value(c_sFileTime).toString()));
    }

    ui->tableWidget_ProjectFile->setColumnCount (4);
    ui->tableWidget_ProjectFile->setHorizontalHeaderLabels (slHeader);
    ui->tableWidget_ProjectFile->resizeColumnsToContents ();
    ui->tableWidget_ProjectFile->resizeRowsToContents ();
}

void MainWindow::updateFileLogListWidget()
{
    ui->listWidget_FileLog->clear ();

    m_pNetServer->getFileLogs (m_pFileServer->getCurProjName ());
    QJsonArray oFileLogs = m_pFileServer->getFileLogs ();

    for (int i = 0; i < oFileLogs.count (); i++)
    {
        ui->listWidget_FileLog->addItem (oFileLogs.at (i).toString ());
    }
}

void MainWindow::writeFileLog(QString sOperType, QString sName)
{
    QString sFileLog = m_pFileServer->getUserName ().toString () + sOperType + sName
            + QStringLiteral ("于") + QDateTime::currentDateTime ().toString (c_sDateTimeLongFormat);
    QJsonValue fileLog(sFileLog);

    m_pFileServer->writeFileLog (sFileLog);
    m_pFileServer->updateMemberToJsonObj ();

    updateFileLogListWidget ();

    m_pNetServer->postFileLogs (m_pFileServer->getCurProjName ());
}

void MainWindow::updateProjectList(QString sCurProj)
{
    if (sCurProj == "")
    {
        sCurProj = ui->comboBox_ProjectName->currentText ();
    }
    QJsonArray oProjects = m_pFileServer->getProjects ();
    ui->comboBox_ProjectName->clear ();
    QStringList slProjects;
    for (int i = 0; i < oProjects.count (); i++)
    {
        if (oProjects.at (i).isObject () && oProjects.at (i).toObject ().contains (c_sProjectName))
        {
            QString sName = oProjects.at (i).toObject ().value (c_sProjectName).toString ();
            if(ui->comboBox_ProjectName->findText (sName) == -1 && sName != "")
            {
                slProjects.append (sName);
            }
        }
    }
    ui->comboBox_ProjectName->addItems (slProjects);
    if (ui->comboBox_ProjectName->findText (sCurProj) == -1)
    {
        ui->comboBox_ProjectName->setCurrentIndex (0);
    }
    else
    {
        ui->comboBox_ProjectName->setCurrentText (sCurProj);
    }
}

void MainWindow::updatePages(int nPageIndex)
{
    switch (nPageIndex)
    {
    case 0:
        updateUserPage ();
        break;
    case 1:
        updateTeamPage ();
        break;
    case 2:
        updateTeamBoard ();
        break;
    case 3:
        updateTaskOverView ();
        break;
    case 4:
        updateFilesPage ();
        break;
    default:
        qDebug() << nPageIndex << "page don't have an update action!";
        break;
    }
}

void MainWindow::updateUserPage()
{
    if (m_pFileServer->hasMember (ui->lineEdit_UserName->text ()))
    {
        ui->tabWidget->setTabEnabled (0, true);

        ui->lineEdit_UserName->setText (m_pFileServer->getUserName ().toString ());
        ui->comboBox_UserRole->setCurrentText (m_pFileServer->getMemberRole ().toString ());
        updateTreeWidget ();
        updateCurTaskInfo(ui->treeWidget_MyTask->currentItem ());
    }
    else
    {
        ui->tabWidget->setTabEnabled (0, false);
    }
}

void MainWindow::updateTeamPage()
{
    //切换到团队任务页签
    QJsonObject oProject;
    if (m_pFileServer)
    {
        oProject = m_pFileServer->getProject();
        QJsonArray oMembs;
        oMembs = oProject.value(c_sMembers).toArray();
        ui->listWidget_TeamTask->clear();
        for (int i = 0; i < oMembs.count(); i++)
        {
            ui->listWidget_TeamTask->addItem(oMembs.at(i).toObject().value(c_sMemberName).toString());
        }
        if (ui->listWidget_TeamTask->count() > 0)
        {
            ui->listWidget_TeamTask->setCurrentItem(ui->listWidget_TeamTask->item(0));
        }
    }
}

void MainWindow::updateTeamBoard()
{
    QMap<QString, QVector<QJsonObject> > groupingByRole;

    QJsonObject proj = m_pFileServer->getProject();
    if (proj.contains(c_sMembers) && proj.value(c_sMembers).isArray())
    {
        QJsonArray members = proj.value(c_sMembers).toArray();

        for (int i = 0 ; i < members.count(); i++)
        {
            QJsonObject member = members[i].toObject();

            handleMemberBroadData(member,groupingByRole);
        }
    }

    // 添加表头

    ui->tableWidget_TeamBoard->setColumnCount(groupingByRole.count());
    QStringList colNames;

    ui->tableWidget_TeamBoard->setRowCount(0);
    // 更新数据
    int col = 0;
    int row = 0;
    int rowMax = 0;
    QMap<QString, QVector<QJsonObject> >::iterator it = groupingByRole.begin();
    for( ;it != groupingByRole.end() ; it++)
    {
        colNames.push_back(it.key());

        QVector<QJsonObject> & membersVec = it.value();

        for(int j = 0 ; j < membersVec.count() ; j++)
        {
            //解析member数据
            QJsonObject  member = membersVec[j];
            updateTABoardOneMemberData(member,col,row);
        }

        if(rowMax < row)
        {
            ui->tableWidget_TeamBoard->setRowCount(row);
            rowMax = row;
        }
        row = 0;
        col++;
    }



     ui->tableWidget_TeamBoard->setHorizontalHeaderLabels(colNames);

    ui->tableWidget_TeamBoard->resizeColumnsToContents();
    ui->tableWidget_TeamBoard->resizeRowsToContents();
}

void MainWindow::updateTABoardOneMemberData(QJsonObject& member, const int col, int& row)
{
    if(member.contains(c_sMemberName) && member.value(c_sMemberName).isString())
    {
        QFont font = qApp->font();
        font.setPointSize(12);
        ui->tableWidget_TeamBoard->setRowCount(ui->tableWidget_TeamBoard->rowCount()+1);

        QTableWidgetItem * item = new QTableWidgetItem(member.value(c_sMemberName).toString());
        //item->setBackgroundColor(QColor(146,208,80));
        item->setBackgroundColor(Qt::darkGreen);
        item->setFont(font);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_TeamBoard->setItem(row++,col,item);
    }
    else
     {
        return;
     }

    if(member.contains(c_sMainTaskList) && member.value(c_sMainTaskList).isArray())
    {

        QJsonArray mainTasks = member.value(c_sMainTaskList).toArray();
        for(int i = 0 ;i < mainTasks.count() ; i++)
        {
            QJsonObject mainTaskJson = mainTasks[i].toObject();

            QJsonArray subTasks  = mainTaskJson.value(c_sSubTaskList).toArray();
            for (int j = 0 ; j < subTasks.size(); j++)
            {
                QJsonObject subTaskJson = subTasks[j].toObject();
                QString taskState = subTaskJson.value(c_sTaskState).toString();
                if(taskState == QStringLiteral("进行") || taskState == QStringLiteral("后续"))
                {
                    ui->tableWidget_TeamBoard->setRowCount(ui->tableWidget_TeamBoard->rowCount()+5);
                    QString taskInfo = QStringLiteral("[%1] %2").arg(mainTaskJson.value(c_sTaskName).toString())
                            .arg(subTaskJson.value(c_sTaskName).toString());

                    // 任务名称加状态
                    QTableWidgetItem * item = new QTableWidgetItem(taskInfo);
                    item->setBackgroundColor(g_convertTaskStateToColor(taskState));
                    ui->tableWidget_TeamBoard->setItem(row++,col,item);
                    // 任务起止时间
                    QString strStart = subTaskJson.value(c_sStartTime).toString();
                    QDateTime startDt = QDateTime::fromString(strStart,c_sDateTimeFormat);
                    QDateTime tm = getEndTime(startDt, getHours(subTaskJson.value(c_sPlannedTime).toDouble(),
                                                                subTaskJson.value(c_sPlannedTimeUnit).toString()));
                    QString dtStr = QStringLiteral("起:") + strStart + "  " +
                            QStringLiteral("止:") + tm.toString(c_sDateTimeFormat);
                    item = new QTableWidgetItem(dtStr);
                    ui->tableWidget_TeamBoard->setItem(row++,col,item);
                    // 优先级别
                    item = new QTableWidgetItem(c_sPriority + ":" + subTaskJson.value(c_sPriority).toString());
                    ui->tableWidget_TeamBoard->setItem(row++,col,item);
                    // 任务进度

                    // 已用工时
                    double d = subTaskJson.value(c_sUsedTime).toDouble();
                    QString sTmp = QString::number(d);
                    item = new QTableWidgetItem(c_sUsedTime + ":" + sTmp);
                    ui->tableWidget_TeamBoard->setItem(row++,col,item);
                    // 任务难度
                    sTmp = subTaskJson.value(c_sDifficulty).toString();
                    item = new QTableWidgetItem(c_sDifficulty + ":" + sTmp);
                    ui->tableWidget_TeamBoard->setItem(row++,col,item);
                }

            }
        }
     }
}

void MainWindow::createTrayIcon()
{
    m_pTrayIconMenu = new QMenu(this);
    m_pTrayIconMenu->addAction(m_pSetAction);
    m_pTrayIconMenu->addSeparator();
    m_pTrayIconMenu->addAction(m_pQuitAction);

    m_pTrayIcon = new QSystemTrayIcon(this);
    m_pTrayIcon->setContextMenu(m_pTrayIconMenu);
    m_pTrayIcon->setIcon(QIcon(":/Logo/TA.ico"));
    m_pTrayIcon->show();
    connect(m_pTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void MainWindow::createActions()
{
    m_pQuitAction = new QAction(QStringLiteral("退出"), this);
    connect(m_pQuitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    m_pSetAction = new QAction(QStringLiteral("设置"), this);
    connect(m_pSetAction, SIGNAL(triggered()), this, SLOT(setConfig()));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_pTrayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}

void MainWindow::updateTaskOverView()
{
    QTableWidget * oTable = ui->tableWidget_TeamTask;
    int nOriginalCol = oTable->columnCount();
    int nOriginalRow = oTable->rowCount();
    double nTotalPlannedHours = 0;
    double nTotalUsedHours = 0;
    //先清除非必须列
    for(int i = nOriginalCol-1; i >=0; i--)
    {
        oTable->removeColumn(i);
    }
    oTable->insertColumn(0);
    oTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QStringLiteral("成员")));
    //清除所有行
    for(int i = nOriginalRow-1; i >=0; i--)
    {
        oTable->removeRow(i);
    }
    if (m_pFileServer)
    {
        QJsonObject oProject = m_pFileServer->getProject();
        if (oProject.contains(c_sMembers) && oProject.value(c_sMembers).isArray())
        {
            QJsonArray oMembs = oProject.value(c_sMembers).toArray();
            // 遍历所有成员所有子任务获取所有需要的日期范围
            QMap <QDateTime, int> oAllDateTimes;
            for (int i = 0; i < oMembs.count(); i++)
            {
                QJsonObject oMember = oMembs.at(i).toObject();
                QDateTime dtStart, dtEnd;
                getMemberTaskScope(oMember, dtStart, dtEnd);
                if(dtStart.isValid() && dtEnd.isValid())
                {
                    oAllDateTimes.insert(dtStart, 1);
                    oAllDateTimes.insert(dtEnd, 1);
                }
            }

            if(oAllDateTimes.isEmpty())
            {
               return;
            }
            QDateTime dtStart = oAllDateTimes.firstKey();
            QDateTime dtEnd = oAllDateTimes.lastKey();
            int nColindex = 1;
            //按照不同的开始时间创建列
            insertTableColAccordingDateTime(oTable, dtStart, nColindex);
            ++nColindex;
            while (dtStart.date() < dtEnd.date())
            {
                dtStart = dtStart.addDays(1);
                insertTableColAccordingDateTime(oTable, dtStart, nColindex);
                ++nColindex;
            }
            int nRowindex = 0;
            //填写子任务信息
            for (int i = 0; i < oMembs.count(); i++)
            {
                QJsonObject oMember = oMembs.at(i).toObject();
                // 提取每个成员的任务信息
                QString sMemberName = oMember.value(c_sMemberName).toString();
                oTable->insertRow(nRowindex);
                oTable->setItem(nRowindex, 0, new QTableWidgetItem(sMemberName));
                oTable->item(nRowindex, 0)->setBackgroundColor(g_memberBgc[g_eCurTheme]);
                if (oMember.contains(c_sMainTaskList) && oMember.value(c_sMainTaskList).isArray())
                {
                    QJsonArray mainTaskList = oMember.value(c_sMainTaskList).toArray();
                    for (int i = 0; i < mainTaskList.count(); i++)
                    {
                        if (mainTaskList.at(i).toObject().contains(c_sSubTaskList) && mainTaskList.at(i).toObject().value(c_sSubTaskList).isArray())
                        {
                            QString sMainTaskName = mainTaskList.at(i).toObject().value(c_sTaskName).toString();
                            QJsonArray subTaskList = mainTaskList.at(i).toObject().value(c_sSubTaskList).toArray();
                            for (int i = 0; i < subTaskList.count(); i++)
                            {
                                QJsonObject subTask = subTaskList.at(i).toObject();
                                QString sSubTaskName = subTask.value(c_sTaskName).toString();
                                double dPlannedTime = subTask.value(c_sPlannedTime).toDouble();
                                dPlannedTime = getHours(dPlannedTime, subTask.value(c_sPlannedTimeUnit).toString());
                                nTotalPlannedHours += dPlannedTime;
                                QString sPlannedTime = QString::number(dPlannedTime);
                                nTotalUsedHours += subTask.value(c_sUsedTime).toDouble();
                                QString sUsedTime =  QString::number(subTask.value(c_sUsedTime).toDouble());
                                QString sTaskState = subTask.value(c_sTaskState).toString();
                                QString sPriority = subTask.value(c_sPriority).toString();
                                QString sDifficulty = subTask.value(c_sDifficulty).toString();
                                QColor oCellColor = g_convertTaskStateToColor(sTaskState);
                                QDateTime oDateTimeStart = QDateTime::fromString(subTask.value(c_sStartTime).toString(), c_sDateTimeFormat);
                                QDate odtStart = oDateTimeStart.date();
                                QDate odtEnd = getEndTime(oDateTimeStart, dPlannedTime).date();
                                //根据需要插入时间列
                                QDate tmpdate = odtStart;
                                while(tmpdate <= odtEnd && odtStart.isValid() && odtStart.isValid())
                                {
                                    for (int i = 1; i < nColindex; i++)
                                    {
                                        if (oTable->horizontalHeaderItem(i) != NULL && oTable->horizontalHeaderItem(i)->text() == tmpdate.toString(c_sDateFormat))
                                        {
                                            QString sContent = "[" + sMainTaskName + "]" +sSubTaskName + QStringLiteral(";计划用时:")+ sPlannedTime + QStringLiteral( ";已用时:")+ sUsedTime +
                                                    QStringLiteral(";任务状态：") + sTaskState+ QStringLiteral(";优先级别：") + sPriority + QStringLiteral(";任务难度：") +sDifficulty;
                                            if (oTable->item(nRowindex, i) == NULL)
                                            {
                                                //填充单元格颜色标识
                                                oTable->setItem(nRowindex, i, new QTableWidgetItem(sContent));
                                                oTable->item(nRowindex, i)->setBackgroundColor(oCellColor);
                                            }
                                            else
                                            {
                                                oTable->item(nRowindex, i)->setBackgroundColor(oCellColor);
                                                oTable->item(nRowindex, i)->setText(oTable->item(nRowindex, i)->text() + "\n" + sContent);
                                            }
                                            oTable->item(nRowindex, i)->setToolTip( oTable->item(nRowindex, i)->text());

                                            break;
                                        }
                                    }
                                    tmpdate = tmpdate.addDays(1);
                                }
                            }
                        }
                    }
                }
                nRowindex++;
            }
            //刷新进度条值
            if (nTotalPlannedHours == 0)
            {
                ui->progressBar_TeamPercent->setValue(0);
            }
            else
            {
                ui->progressBar_TeamPercent->setValue(nTotalUsedHours *100.0/nTotalPlannedHours > 100? 100: nTotalUsedHours *100.0/nTotalPlannedHours);
            }
        }
    }
}

void MainWindow::updateFilesPage()
{
    updateFileTabWidget ();
    updateFileLogListWidget ();
}

void MainWindow::saveTaskInfo(QTreeWidgetItem *previous)
{
    updateUsedTime();
    if (!previous) return;
    QJsonValue preName = previous->text (0);
    QJsonValue curName = ui->lineEdit_TaskName->text ();
    QJsonObject jsonTaskInf = getTaskInfToJs();
    if (jsonTaskInf.isEmpty () || preName == "" || curName == "")
    {
        return;
    }

    if (!previous->parent ())
    {
        m_pFileServer->changeTaskName (preName, curName, true);
        m_pFileServer->setTaskInf (jsonTaskInf);
    }
    else
    {
        m_pFileServer->changeTaskName (preName, curName, false);
        QJsonValue oMainTaskName = previous->parent ()->text (0);
        QJsonObject oMainTask = m_pFileServer->getTaskInf (oMainTaskName);
        m_pFileServer->setTaskInf (oMainTask, jsonTaskInf);
        m_pFileServer->updateMainFromSub(oMainTaskName);
    }
    previous->setText(0, ui->lineEdit_TaskName->text());

    m_pFileServer->updateMemberTime ();
    m_pFileServer->updateMemberToJsonObj ();
    m_pNetServer->postMemberInfo (m_pFileServer->getCurProjName ());
}

QJsonObject MainWindow::getTaskInfToJs()
{
    QJsonObject taskObj;
    if (ui->lineEdit_TaskName->text() != "")
    {
        taskObj.insert(c_sTaskName          , ui->lineEdit_TaskName->text()                                     );
        taskObj.insert(c_sPlannedTime       , ui->lineEdit_PlannedTime->text().toDouble()                       );
        taskObj.insert(c_sPlannedTimeUnit   , ui->comboBox_TimeUnit->currentText ()                             );
        taskObj.insert(c_sStartTime         , ui->dateTimeEdit_StartTime->dateTime().toString(c_sDateTimeFormat));
        taskObj.insert(c_sUsedTime          , ui->lcdNumber_UsedTime->value()                                   );
        taskObj.insert(c_sTimeFix           , ui->lineEdit_TimeFix->text().toDouble()                           );
        taskObj.insert(c_sTaskPercent       , ui->horizontalSlider_TaskPercent->value()                         );
        taskObj.insert(c_sTaskDetails       , ui->textEdit_TaskDetails->toHtml ()                               );
        taskObj.insert(c_sTaskState         , ui->comboBox_TaskState->currentText()                             );
        taskObj.insert(c_sPriority          , ui->comboBox_Priority->currentText()                              );
        taskObj.insert(c_sDifficulty        , ui->comboBox_Difficulty->currentText()                            );
    }
    return taskObj;
}

void MainWindow::setTaskInfFromJs(QJsonObject oTaskInf)
{
    ui->lineEdit_TaskName->setText (oTaskInf.value (c_sTaskName).toString ());
    ui->lineEdit_PlannedTime->setText (QString::number (oTaskInf.value (c_sPlannedTime).toDouble ()));
    ui->comboBox_TimeUnit->setCurrentText (oTaskInf.value (c_sPlannedTimeUnit).toString ());
    ui->dateTimeEdit_StartTime->setDateTime (QDateTime::fromString (oTaskInf.value (c_sStartTime).toString (), c_sDateTimeFormat));
    ui->lcdNumber_UsedTime->display (oTaskInf.value (c_sUsedTime).toDouble ());
    ui->lineEdit_TimeFix->setText (QString::number (oTaskInf.value (c_sTimeFix).toDouble ()));
    ui->horizontalSlider_TaskPercent->setValue (oTaskInf.value (c_sTaskPercent).toInt ());
    ui->textEdit_TaskDetails->setHtml (oTaskInf.value (c_sTaskDetails).toString ());
    ui->comboBox_TaskState->setCurrentText (oTaskInf.value (c_sTaskState).toString ());
    ui->comboBox_Priority->setCurrentText(oTaskInf.value (c_sPriority).toString ());
    ui->comboBox_Difficulty->setCurrentText(oTaskInf.value (c_sDifficulty).toString ());
}

void MainWindow::flushlistWidget_TeamTaskData(QTableWidget *oTable, const QString & currentText)
{
    if(oTable == NULL)
    {
        return;
    }
    int nOriginalCol = oTable->columnCount();
    int nOriginalRow = oTable->rowCount();
    //先清除非必须列
    for(int i = nOriginalCol-1; i >=0; i--)
    {
        oTable->removeColumn(i);
    }
    oTable->insertColumn(0);
    oTable->insertColumn(1);
    oTable->insertColumn(2);
    oTable->insertColumn(3);
    oTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QStringLiteral("主任务")));
    oTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QStringLiteral("子任务")));
    oTable->setHorizontalHeaderItem(2, new QTableWidgetItem(QStringLiteral("计划用时")));
    oTable->setHorizontalHeaderItem(3, new QTableWidgetItem(QStringLiteral("实际用时")));
    //设置一下时间列列宽
    oTable->setColumnWidth(0, 100);
    oTable->setColumnWidth(1, 100);
    oTable->setColumnWidth(2, 60);
    oTable->setColumnWidth(3, 60);

    //清除所有行
    for(int i = nOriginalRow-1; i >=0; i--)
    {
        oTable->removeRow(i);
    }

    if (m_pFileServer)
    {
        QJsonObject oProject = m_pFileServer->getProject();
        if (oProject.contains(c_sMembers) && oProject.value(c_sMembers).isArray())
        {
            QJsonArray oMembs = oProject.value(c_sMembers).toArray();
            for (int i = 0; i < oMembs.count(); i++)
            {
                QJsonObject oMember = oMembs.at(i).toObject();
                // 提取当前成员的任务信息
                if (oMember.value(c_sMemberName).toString() == currentText)
                {
                    int nRowindex = 0;
                    int nColindex = 4;

                    //获取当前成员的所有任务的时间跨度
                    QDateTime oDateTimeStart, oDateTimeEnd;
                    getMemberTaskScope(oMember, oDateTimeStart, oDateTimeEnd);
                    //为所有时间跨度的日期创建列
                    insertTableColAccordingDateTime(oTable, oDateTimeStart, nColindex);
                    ++nColindex;
                    while(oDateTimeStart.date() < oDateTimeEnd.date())
                    {
                        oDateTimeStart = oDateTimeStart.addDays(1);
                        insertTableColAccordingDateTime(oTable, oDateTimeStart, nColindex);
                        ++nColindex;
                    }
                    if (oMember.contains(c_sMainTaskList) && oMember.value(c_sMainTaskList).isArray())
                    {
                        QJsonArray mainTaskList = oMember.value(c_sMainTaskList).toArray();
                        //主要任务数目
                        int nMainTaskNum =  mainTaskList.count();
                        double nTotalPlannedHours = 0;
                        double nTotalUsedHours = 0;

                        QMultiMap <QDateTime , QJsonObject> oMapMainTasks;
                        QMultiMap <QDateTime , QJsonObject>::Iterator iter_mainTask;
                        for (int i = 0; i < mainTaskList.count(); i++)
                        {
                             //跳过无效的空信息
                            if (!mainTaskList.at(i).toObject().contains(c_sTaskName))
                            {
                                --nMainTaskNum;
                                continue;
                            }
                            //各个主任务按照时间排序
                            oMapMainTasks.insert(QDateTime::fromString(mainTaskList.at(i).toObject().value(c_sStartTime).toString(), c_sDateTimeFormat), mainTaskList.at(i).toObject());
                        }
                        for (iter_mainTask = oMapMainTasks.begin(); iter_mainTask != oMapMainTasks.end(); iter_mainTask ++)
                        {
                            QString sMainTaskName = iter_mainTask.value().value(c_sTaskName).toString();

                            if (iter_mainTask.value().contains(c_sSubTaskList) && iter_mainTask.value().value(c_sSubTaskList).isArray())
                            {
                                QJsonArray subTaskList = iter_mainTask.value().value(c_sSubTaskList).toArray();
                                //子任务数
                                int nSubTaskNum =  subTaskList.count();
                                QMultiMap <QDateTime , QJsonObject> oMapSubTasks;
                                QMultiMap <QDateTime , QJsonObject>::Iterator iter_subTask;
                                for (int i = 0; i < subTaskList.count(); i++)
                                {
                                    //跳过无效的空信息
                                    if (!subTaskList.at(i).toObject().contains(c_sTaskName))
                                    {
                                        --nSubTaskNum;
                                        continue;
                                    }
                                    //各个子任务按照时间排序
                                    oMapSubTasks.insert(QDateTime::fromString(subTaskList.at(i).toObject().value(c_sStartTime).toString(), c_sDateTimeFormat), subTaskList.at(i).toObject());
                                }

                                for (iter_subTask = oMapSubTasks.begin(); iter_subTask != oMapSubTasks.end(); iter_subTask ++)
                                {
                                    QJsonObject subTask = iter_subTask.value();
                                    QDateTime dtStart = iter_subTask.key();
                                    //转为纯日期格式
                                    QString sStartTime = dtStart.toString(c_sDateFormat);
                                    QString sSubTaskName = subTask.value(c_sTaskName).toString();                                    
                                    QString sPlannedTimeUnit = subTask.value(c_sPlannedTimeUnit).toString();
                                    double dPlannedTime = getHours(subTask.value(c_sPlannedTime).toDouble(), sPlannedTimeUnit);
                                    QDateTime dtEnd = getEndTime(dtStart, dPlannedTime);
                                     //记录所有时间跨度的日期
                                    QStringList oDaysList;
                                    oDaysList.append(sStartTime);
                                    while(dtStart.date() < dtEnd.date())
                                    {
                                        dtStart = dtStart.addDays(1);
                                        oDaysList.append(dtStart.toString(c_sDateFormat));
                                    }
//                                    oDaysList.append(dtEnd.toString(c_sDateFormat));

                                    nTotalPlannedHours += dPlannedTime;
                                    QString sPlannedTime = QString::number(dPlannedTime);
                                    nTotalUsedHours += subTask.value(c_sUsedTime).toDouble();
                                    QString sUsedTime =  QString::number(subTask.value(c_sUsedTime).toDouble());
                                    QString sTaskState = subTask.value(c_sTaskState).toString();
                                    QString sPriority = subTask.value(c_sPriority).toString();
                                    QString sDifficulty = subTask.value(c_sDifficulty).toString();
                                    QColor oCellColor = g_convertTaskStateToColor(sTaskState);

                                    oTable->insertRow(nRowindex);
                                    oTable->setItem(nRowindex, 0, new QTableWidgetItem(sMainTaskName));
                                    oTable->item(nRowindex, 0)->setBackgroundColor(g_mainTaskBgc[g_eCurTheme]);
                                    oTable->setItem(nRowindex, 1, new QTableWidgetItem(sSubTaskName));
                                    oTable->item(nRowindex, 1)->setBackgroundColor(g_subTaskBgc[g_eCurTheme]);
                                    oTable->setItem(nRowindex, 2, new QTableWidgetItem(sPlannedTime));
                                    oTable->item(nRowindex, 2)->setBackgroundColor(g_plannedTimeBgc[g_eCurTheme]);
                                    oTable->setItem(nRowindex, 3, new QTableWidgetItem(sUsedTime));
                                    oTable->item(nRowindex, 3)->setBackgroundColor(g_usedTime[g_eCurTheme]);

                                    //填充单元格颜色标识
                                    for(int j = 0; j < oDaysList.count(); j++)
                                    {
                                        for (int i = 4; i < nColindex; i++)
                                        {
                                            if (oTable->horizontalHeaderItem(i)->text() == oDaysList.at(j))
                                            {
                                                oTable->setItem(nRowindex, i, new QTableWidgetItem());
                                                oTable->item(nRowindex, i)->setBackgroundColor(oCellColor);
                                                oTable->item(nRowindex, i)->setToolTip(QStringLiteral("任务状态：") + sTaskState + "\n" +
                                                                                                 QStringLiteral("优先级别：") + sPriority + "\n" +
                                                                                                 QStringLiteral("任务难度：") +sDifficulty);
                                            }
                                        }
                                    }
                                    ++nRowindex ;
                                }
                                //合并相同主任务的子任务
                                oTable->setSpan(nRowindex-nSubTaskNum, 0, nSubTaskNum, 1);                                
                            }                            
                        }
                        //刷新进度条值
                        if(nTotalPlannedHours == 0)
                        {
                            ui->progressBar_UserPercent->setValue(0);
                        }
                        else
                        {
                            ui->progressBar_UserPercent->setValue(nTotalUsedHours *100.0/nTotalPlannedHours > 100? 100: nTotalUsedHours *100.0/nTotalPlannedHours);
                        }
                    }
                    return;
                }
            }
        }
    }
}

void MainWindow::getMemberTaskScope(QJsonObject oMember, QDateTime &Start, QDateTime &End)
{
    QMap <QDateTime , int> oMapDateTimes;
    if (oMember.contains(c_sMainTaskList) && oMember.value(c_sMainTaskList).isArray())
    {
        QJsonArray mainTaskList = oMember.value(c_sMainTaskList).toArray();
        for (int i = 0; i < mainTaskList.count(); i++)
        {
            QJsonObject mainTask = mainTaskList.at(i).toObject();
            if (mainTask.contains(c_sSubTaskList) && mainTask.value(c_sSubTaskList).isArray())
            {
                QJsonArray subTaskList = mainTask.value(c_sSubTaskList).toArray();
                for (int i = 0; i < subTaskList.count(); i++)
                {
                    QJsonObject subTask = subTaskList.at(i).toObject();
                    QDateTime dtStart = QDateTime::fromString(subTask.value(c_sStartTime).toString(), c_sDateTimeFormat);
                    QString sPlannedTimeUnit = subTask.value(c_sPlannedTimeUnit).toString();
                    double dPlannedTime = getHours(subTask.value(c_sPlannedTime).toDouble(), sPlannedTimeUnit);
                    QDateTime dtEnd = getEndTime(dtStart, dPlannedTime);
                    oMapDateTimes.insert(dtStart, 1);
                    oMapDateTimes.insert(dtEnd, 1);
                }
            }
        }
        if(!oMapDateTimes.isEmpty())
        {
            Start = oMapDateTimes.firstKey();
            End = oMapDateTimes.lastKey();
        }
    }
}

void MainWindow::getMainTaskScope(QJsonObject oMainTask, QDateTime &Start, QDateTime &End)
{
    QMap <QDateTime , int> oMapDateTimes;
    QJsonObject mainTask = oMainTask;
    if (mainTask.contains(c_sSubTaskList) && mainTask.value(c_sSubTaskList).isArray())
    {
        QJsonArray subTaskList = mainTask.value(c_sSubTaskList).toArray();
        for (int i = 0; i < subTaskList.count(); i++)
        {
            QJsonObject subTask = subTaskList.at(i).toObject();
            QDateTime dtStart = QDateTime::fromString(subTask.value(c_sStartTime).toString(), c_sDateTimeFormat);
            QString sPlannedTimeUnit = subTask.value(c_sPlannedTimeUnit).toString();
            double dPlannedTime = getHours(subTask.value(c_sPlannedTime).toDouble(), sPlannedTimeUnit);
            QDateTime dtEnd = getEndTime(dtStart, dPlannedTime);
            oMapDateTimes.insert(dtStart, 1);
            oMapDateTimes.insert(dtEnd, 1);
        }

    }
    if(!oMapDateTimes.isEmpty())
    {
        Start = oMapDateTimes.firstKey();
        End = oMapDateTimes.lastKey();
    }
}

void MainWindow::insertTableColAccordingDateTime(QTableWidget *oTable, QDateTime &oDateTime, int index)
{
    oTable->insertColumn(index);
    oTable->setColumnWidth(index, 90);
    //周末的日期标示一下
    if(oDateTime.date().dayOfWeek() > 5)
    {
        oTable->setHorizontalHeaderItem(index, new QTableWidgetItem(QIcon(":/Logo/Weekend.ico"), oDateTime.toString(c_sDateFormat)));
    }
    else
    {
        oTable->setHorizontalHeaderItem(index, new QTableWidgetItem(oDateTime.toString(c_sDateFormat)));
    }
}

void MainWindow::onTeamTaskExportExcel()
{
    exportQTableWidgetToExcelFile(ui->tableWidget_TeamTask);
}

void MainWindow::onTeamBoardExportExcel()
{
    exportQTableWidgetToExcelFile(ui->tableWidget_TeamBoard);
}

void MainWindow::handleMemberBroadData(QJsonObject& member, QMap<QString, QVector<QJsonObject> >& groupingHash)
{
    if( member.contains(c_sMemberRole) && member.value(c_sMemberRole).isString()
        && member.contains(c_sMemberName) )
    {
        QString sRole = member.value(c_sMemberRole).toString();

        QMap<QString, QVector<QJsonObject> >::iterator it = groupingHash.find(sRole);
        if( it == groupingHash.end())
        {
            QVector<QJsonObject> tmpObjVec;
            tmpObjVec.append(member);
            groupingHash.insert(sRole,tmpObjVec);
        }
        else
        {
            it.value().append(member);
        }
    }
}

void MainWindow::clearFileLog()
{
    m_pFileServer->clearFileLog (0);
    m_pNetServer->postFileList (m_pFileServer->getCurProjName ());
    ui->listWidget_FileLog->clear ();
    writeFileLog (QStringLiteral ("清空"), QStringLiteral ("日志"));
    updateFileLogListWidget ();
}

void MainWindow::on_horizontalSlider_TaskPercent_valueChanged(int value)
{
    ui->label_PercentNum->setText(QString("%1%").arg(value));
    if (value == 100)
    {
        ui->dateTimeEdit_EndTime->setDateTime(QDateTime::currentDateTime());
    }
    updateUsedTime();
}

void MainWindow::on_pushButton_ResetTaskInfo_clicked()
{
    updateCurTaskInfo(ui->treeWidget_MyTask->currentItem ());
}

void MainWindow::on_comboBox_TimeUnit_currentIndexChanged(int index)
{
    updateEndTime();
}

void MainWindow::on_lineEdit_PlannedTime_textChanged(const QString &arg1)
{
    updateEndTime();
}

void MainWindow::on_lineEdit_TimeFix_textChanged(const QString &arg1)
{
    updateUsedTime();
}

void MainWindow::on_dateTimeEdit_EndTime_dateTimeChanged(const QDateTime &dateTime)
{
    if (dateTime < ui->dateTimeEdit_StartTime->dateTime ())
    {
//        QMessageBox::warning (this, QStringLiteral ("警告"), QStringLiteral ("结束时间不能早于开始时间！"), QMessageBox::Ok);
        ui->dateTimeEdit_EndTime->setDateTime (ui->dateTimeEdit_StartTime->dateTime ());
    }
    updateUsedTime();
//    updatePlannedTime();
}

void MainWindow::on_dateTimeEdit_StartTime_dateTimeChanged(const QDateTime &dateTime)
{
    updateEndTime();
}

void MainWindow::on_pushButton_SetUserName_clicked()
{
    QJsonValue preName = m_pFileServer->getUserName ();
    QJsonValue curName = ui->lineEdit_UserName->text ();
    if (preName != curName)
    {
        m_pFileServer->setUserName (curName);

        m_pFileServer->updateMemberTime ();
        m_pFileServer->updateMemberToJsonObj ();
        m_pNetServer->postChangeName (preName, curName);
    }
}

void MainWindow::on_pushButton_SetUserRole_clicked()
{
    m_pFileServer->setMemberRole (ui->comboBox_UserRole->currentText ());

    m_pFileServer->updateMemberTime ();
    m_pFileServer->updateMemberToJsonObj ();
    m_pNetServer->postMemberInfo (m_pFileServer->getCurProjName ());
}

void MainWindow::on_pushButton_TaskLog_clicked()
{
    QDateTime dtStart, dtEnd;
    getMemberTaskScope(m_pFileServer->getMember(), dtStart, dtEnd);
    if(ui->dateEdit_LogDate->dateTime ().date() < dtStart.date() || ui->dateEdit_LogDate->dateTime ().date() > dtEnd.date())
    {
        QMessageBox::about(NULL, QStringLiteral("提示"), QStringLiteral("您当前设置的日志时间不在项目计划时间范围") +
                           QString("(%1~%2)").arg(dtStart.toString(c_sDateFormat)).arg(dtEnd.toString(c_sDateFormat)) + QStringLiteral("内，请重新设置."));
        return;
    }
    QJsonObject oLog;
    oLog.insert (c_sLogDate, ui->dateEdit_LogDate->dateTime ().toString (c_sDateFormat));
    oLog.insert (c_sLogInf, ui->textEdit_UserTaskLog->toHtml ());
    m_pFileServer->setMemberLog (oLog);

    m_pFileServer->updateMemberTime ();
    m_pFileServer->updateMemberToJsonObj ();
    m_pNetServer->postMemberInfo (m_pFileServer->getCurProjName ());
}

void MainWindow::on_pushButton_AddMainTask_clicked()
{
    QStringList slMainTaskNames;
    QString oName;
    for (int i = 0; i < ui->treeWidget_MyTask->topLevelItemCount (); i++)
    {
        slMainTaskNames.append (ui->treeWidget_MyTask->topLevelItem (i)->text (0));
    }
    do
    {
        oName = QStringLiteral ("主任务") + QString::number (c_newTag++);
    } while (slMainTaskNames.contains (oName));

    m_pFileServer->createNewTask (oName);
    QTreeWidgetItem *oNewTask = new QTreeWidgetItem();
    oNewTask->setText (0, oName);
    ui->treeWidget_MyTask->addTopLevelItem (oNewTask);
    ui->treeWidget_MyTask->setCurrentItem (oNewTask);
    QJsonObject newTaskInf = m_pFileServer->getTaskInf (oName);
    setTaskInfFromJs (newTaskInf);

    m_pFileServer->updateMemberTime ();
    m_pFileServer->updateMemberToJsonObj ();
    m_pNetServer->postMemberInfo (m_pFileServer->getCurProjName ());
}

void MainWindow::on_pushButton_AddSubTask_clicked()
{
    QString oParentName;
    QTreeWidgetItem *oTreeWidget;
    if (ui->treeWidget_MyTask->currentItem ())
    {
        if (!ui->treeWidget_MyTask->currentItem ()->parent ())
        {
            oTreeWidget = ui->treeWidget_MyTask->currentItem ();
        }
        else
        {
            oTreeWidget = ui->treeWidget_MyTask->currentItem ()->parent ();
        }
        oParentName = oTreeWidget->text (0);
    }
    QStringList slSubTaskNames;
    QString oName;
    for (int i = 0; i < oTreeWidget->childCount (); i++)
    {
        slSubTaskNames.append (oTreeWidget->child (i)->text (0));
    }
    do
    {
        oName = QStringLiteral ("子任务") + QString::number (c_newTag++);
    } while (slSubTaskNames.contains (oName));

    m_pFileServer->createNewTask (oName, oParentName);
    m_pFileServer->updateMemberToJsonObj ();
    QTreeWidgetItem *oNewTask = new QTreeWidgetItem();
    oNewTask->setText (0, oName);
    oTreeWidget->addChild (oNewTask);
    ui->treeWidget_MyTask->setCurrentItem (oNewTask);
    QJsonObject newTaskInf = m_pFileServer->getTaskInf (oParentName, oName);
    setTaskInfFromJs (newTaskInf);

    m_pFileServer->updateMemberTime ();
    m_pFileServer->updateMemberToJsonObj ();
    m_pNetServer->postMemberInfo (m_pFileServer->getCurProjName ());
}

void MainWindow::on_pushButton_DeleteTask_clicked()
{
    QTreeWidgetItem *pTreeWidget = ui->treeWidget_MyTask->currentItem ();
    if (!pTreeWidget) return;

    QJsonObject oTaskInf;
    if (!pTreeWidget->parent ())
    {
        m_pFileServer->deleteTask (pTreeWidget->text (0));
        oTaskInf = m_pFileServer->getTaskInf (ui->treeWidget_MyTask->currentItem ()->text (0));
    }
    else
    {
        m_pFileServer->deleteTask (pTreeWidget->text (0), pTreeWidget->parent ()->text (0));
        oTaskInf = m_pFileServer->getTaskInf (ui->treeWidget_MyTask->currentItem ()->parent ()->text (0),
                                                            ui->treeWidget_MyTask->currentItem ()->text (0));
    }
    if(ui->treeWidget_MyTask->itemAbove (pTreeWidget))
    {
        ui->treeWidget_MyTask->setCurrentItem (ui->treeWidget_MyTask->itemAbove (pTreeWidget));
    }
    else if (ui->treeWidget_MyTask->itemBelow (pTreeWidget))
    {
        ui->treeWidget_MyTask->setCurrentItem (ui->treeWidget_MyTask->itemBelow (pTreeWidget));
    }
    delete pTreeWidget;
    setTaskInfFromJs (oTaskInf);

    m_pFileServer->setCurProjName (ui->comboBox_ProjectName->currentText ());
    m_pFileServer->updateMemberTime ();
    m_pFileServer->updateMemberToJsonObj ();
    m_pNetServer->postMemberInfo (m_pFileServer->getCurProjName ());
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    m_pNetServer->getMemberInfo (m_pFileServer->getCurProjName ());
    m_pFileServer->updateMemberToJsonObj ();
    m_pFileServer->writeFile ();
    updatePages (index);
}

void MainWindow::on_pushButton_ExportCurrent_clicked()
{    
    exportQTableWidgetToExcelFile(ui->tableWidget_UserTask, ui->listWidget_TeamTask->currentItem()->text());
}

void MainWindow::on_pushButton_ExportAll_clicked()
{
    QList<QTableWidget *> tables;
    QList<QString> texts;
    for (int i = 0; i < ui->listWidget_TeamTask->count(); ++i)
    {
        QTableWidget * oTable = new QTableWidget();
        tables.append(oTable);
        texts.append( ui->listWidget_TeamTask->item(i)->text());
        flushlistWidget_TeamTaskData(oTable,  ui->listWidget_TeamTask->item(i)->text());
    }
    exportQTableWidgetsToExcelFile(tables, texts);

    for (int i = tables.count() -1; i >= 0; --i)
    {
        delete(tables.at(i));
    }
}

void MainWindow::on_treeWidget_MyTask_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    saveTaskInfo(previous);
    updateCurTaskInfo (current);
}

void MainWindow::on_dateEdit_LogDate_dateChanged(const QDate &date)
{
    QJsonValue oTaskLog = m_pFileServer->getMemberLog (date.toString (c_sDateFormat));
    ui->textEdit_UserTaskLog->setHtml (oTaskLog.toString ());
}

void MainWindow::on_comboBox_ProjectName_currentTextChanged(const QString &arg1)
{
    if (m_pFileServer->hasProject (arg1))
    {
        m_pFileServer->setCurProjName (arg1);
        m_pFileServer->updateMemberFromJsonObj ();
        updatePages (ui->tabWidget->currentIndex ());
        m_pNetServer->getProjList ();
        m_pNetServer->getFileList(m_pFileServer->getCurProjName ());
        m_pNetServer->getFileLogs (m_pFileServer->getCurProjName ());
        m_pNetServer->getMemberInfo (m_pFileServer->getCurProjName ());
    }
}

void MainWindow::on_pushButton_AddProject_clicked()
{
    if (m_pFileServer->joinProject (ui->comboBox_ProjectName->currentText ()))
    {
        m_pFileServer->updateMemberFromJsonObj ();
        updatePages (ui->tabWidget->currentIndex ());
        m_pNetServer->postJionProj (m_pFileServer->getCurProjName ());
        m_pNetServer->getMemberInfo (m_pFileServer->getCurProjName ());
        QMessageBox::information (this, QStringLiteral ("提示"), QStringLiteral ("加入项目成功！"), QMessageBox::Ok);
    }
    else
    {
        ui->comboBox_ProjectName->clearEditText ();
        QMessageBox::warning(this, QStringLiteral ("警告"), QStringLiteral ("加入项目失败！"), QMessageBox::Ok);
    }
    updateProjectList (ui->comboBox_ProjectName->currentText ());
    updateUserPage();
}

void MainWindow::on_pushButton_CreateProject_clicked()
{
    if ((ui->comboBox_ProjectName->currentText () != "")
            && m_pFileServer->createProject (ui->comboBox_ProjectName->currentText ()))
    {
        m_pFileServer->updateMemberFromJsonObj ();
        m_pNetServer->postCreateProj (m_pFileServer->getCurProjName ());
        m_pNetServer->getMemberInfo (m_pFileServer->getCurProjName ());
        QMessageBox::information (this, QStringLiteral ("提示"), QStringLiteral ("创建项目成功！"), QMessageBox::Ok);
    }
    else
    {
        ui->comboBox_ProjectName->clearEditText ();
        QMessageBox::warning(this, QStringLiteral ("警告"), QStringLiteral ("创建项目失败！"), QMessageBox::Ok);
    }
    m_pFileServer->setCurProjName (ui->comboBox_ProjectName->currentText ());
    updateProjectList (ui->comboBox_ProjectName->currentText ());
    updatePages (ui->tabWidget->currentIndex ());
    updateUserPage();
}

void MainWindow::on_pushButton_DeleteProject_clicked()
{
    m_pFileServer->leaveProject (ui->comboBox_ProjectName->currentText ());
    m_pNetServer->postLeaveProj (m_pFileServer->getCurProjName ());
    m_pNetServer->getMemberInfo (m_pFileServer->getCurProjName ());
    m_pFileServer->deleteProject (ui->comboBox_ProjectName->currentText ());
    m_pFileServer->updateMemberFromJsonObj ();
    ui->comboBox_ProjectName->setCurrentIndex (qMax((ui->comboBox_ProjectName->currentIndex () - 1), 0));
    m_pFileServer->setCurProjName (ui->comboBox_ProjectName->currentText ());
    updateProjectList (ui->comboBox_ProjectName->currentText ());
    updatePages (ui->tabWidget->currentIndex ());
    updateUserPage();
}

void MainWindow::on_listWidget_FileLog_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem* curItem = ui->listWidget_FileLog->itemAt(pos);
    if(!curItem)
    {
        return;
    }
    QMenu *popMenu = new QMenu(this);
    QAction *clearLog = new QAction(QStringLiteral ("清空"), this);
    popMenu->addAction(clearLog);
    connect(clearLog, SIGNAL(triggered()), this, SLOT(clearFileLog()));
    popMenu->exec(QCursor::pos());
    delete popMenu;
    delete clearLog;
}

void MainWindow::on_listWidget_TeamTask_currentTextChanged(const QString &currentText)
{
    flushlistWidget_TeamTaskData(ui->tableWidget_UserTask, currentText);
}

void MainWindow::on_pushButton_SelectFile_clicked()
{
    QFileDialog fileDlg(this, QStringLiteral ("选取上传文件"), c_sTAPath);
    QString sFile;
    if(fileDlg.exec() == QDialog::Accepted)
    {
        sFile = fileDlg.selectedFiles ().first ();
        ui->lineEdit_Path->setText (sFile);
    }
}

void MainWindow::on_pushButton_CommitFile_clicked()
{
    QString sFileName = QFileInfo(ui->lineEdit_Path->text()).fileName();
    if(sFileName.isEmpty())
    {
        return;
    }

    QString sFileDes = ui->lineEdit_FileDes->text();
    QString sUser = m_pFileServer->getUserName().toString();
    QString sTime = QDateTime::currentDateTime().toString(c_sDateTimeLongFormat);

    QJsonObject oFile;
    oFile.insert(c_sFileName, QJsonValue(sFileName));
    oFile.insert(c_sFileDes, QJsonValue(sFileDes));
    oFile.insert(c_sFileUser, QJsonValue(sUser));
    oFile.insert(c_sFileTime, QJsonValue(sTime));
    oFile.insert(c_sFilePath, ui->lineEdit_Path->text());

    m_pFileServer->putFile(oFile);
    m_pFileServer->updateMemberToJsonObj ();

    m_pNetServer->postFileList(m_pFileServer->getCurProjName ());

    writeFileLog (QStringLiteral ("提交"), sFileName);
    updateFileTabWidget ();
}

void MainWindow::on_pushButton_DeleteFile_clicked()
{
    if (ui->tableWidget_ProjectFile->currentRow () < 0) return;
    QString sFileName = ui->tableWidget_ProjectFile->item (ui->tableWidget_ProjectFile->currentRow (), 0)->text ();
    if(sFileName.isEmpty())
    {
        return;
    }

    m_pFileServer->removeFile (sFileName);
    m_pFileServer->updateMemberToJsonObj ();

    m_pNetServer->postFileList(m_pFileServer->getCurProjName ());

    writeFileLog (QStringLiteral ("删除"), sFileName);
    updateFileTabWidget ();
}

void MainWindow::on_pushButton_UpdateFile_clicked()
{
    updateFileTabWidget ();
    updateFileLogListWidget ();
}

void MainWindow::on_tableWidget_TeamTask_customContextMenuRequested(const QPoint &pos)
{
    m_pTeamTaskPopMenu->addAction(m_pTeamTaskActExport);
    m_pTeamTaskPopMenu->exec(QCursor::pos());
}

void MainWindow::on_tableWidget_TeamBoard_customContextMenuRequested(const QPoint &pos)
{
    m_pTeamBoardPopMenu->addAction(m_pTeamBoardActExport);
    m_pTeamBoardPopMenu->exec(QCursor::pos());
}

void MainWindow::on_pushButton_OpenFile_clicked()
{
    if (ui->tableWidget_ProjectFile->currentRow () < 0) return;
    QString sFileName = ui->tableWidget_ProjectFile->item (ui->tableWidget_ProjectFile->currentRow (), 0)->text ();
    if(sFileName.isEmpty())
    {
        return;
    }

    m_pNetServer->getFile (sFileName, m_pFileServer->getCurProjName (), c_HostAdress);

    // TODO TCP开启监听准备传输文件
    m_pTcpServer->startListen ();

    m_pFileServer->updateMemberToJsonObj ();

    writeFileLog (QStringLiteral ("获取"), sFileName);
    updateFileTabWidget ();
}

void MainWindow::on_tableWidget_TeamTask_itemClicked(QTableWidgetItem *item)
{
    QString sLog = "";
    QTableWidget * oTable = ui->tableWidget_TeamTask;
    QString sMember = oTable->item(item->row(), 0)->text();
    QString sDate = oTable->horizontalHeaderItem(item->column())->text();
    if (m_pFileServer)
    {
        QJsonObject oProject = m_pFileServer->getProject();
        if (oProject.contains(c_sMembers) && oProject.value(c_sMembers).isArray())
        {
            QJsonArray oMembs = oProject.value(c_sMembers).toArray();
            for (int i = 0; i < oMembs.count(); i++)
            {
                QJsonObject oMember = oMembs.at(i).toObject();
                // 提取当前成员的任务信息
                if (oMember.value(c_sMemberName).toString() == sMember)
                {
                    QJsonArray oLogs = oMember.value(c_sUserLogs).toArray();
                    for(int j = 0; j < oLogs.count(); j++)
                    {
                       QJsonObject oLog =  oLogs.at(j).toObject();
                       if(oLog.value(c_sLogDate).toString() == sDate)
                       {
                           sLog = oLog.value(c_sLogInf).toString();
                           ui->textEdit_TeamTaskLog->setText(sLog);
                           return;
                       }
                    }
                }
            }
        }
    }
    ui->textEdit_TeamTaskLog->setText(sLog);
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        showNormal();
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}

void MainWindow::setConfig()
{
    ConfigDialog dlg;
    dlg.exec();
}
