#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget_MyTask->expandAll();
    ui->treeWidget_MyTask->setCurrentItem(ui->treeWidget_MyTask->itemAt(0, 0));
    initNumEditValidator();

    m_pNetServer = new NetServer(this);
    m_pFileServer = new FileServer(this);

    m_pFileServer->readFile();

    // TODO 初始化时获取网络信息和状态
}

MainWindow::~MainWindow()
{
    delete ui;
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
        int iM(0);
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
        case 3:
        {
            iM = ui->lineEdit_PlannedTime->text().toInt();
        } break;
        }
        qint64 iN = iD;
        for (qint64 i = 1; i < iD + 1; i++)
        {
            if (startDT.addMonths(iM).addDays(i).date().dayOfWeek() > 5)
            {
                iN++;
            }
        }
        endDT = startDT.addMonths(iM).addDays(iN).addSecs(iH * 3600);
        ui->dateTimeEdit_EndTime->setDateTime(endDT);
    }
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
        case 3:
        {
            iT = endDT.date().month() - startDT.date().month();
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
        ui->lcdNumber_UsedTime->display(QString::number(iN * 8 + iH + dF));
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
        ui->lcdNumber_UsedTime->display(QString::number(iN * 8 + iH + dF));
    }
}

QJsonObject MainWindow::getTaskInfToJs()
{
    QJsonObject taskObj;
    taskObj.insert(c_sTaskName, ui->lineEdit_TaskName->text());
    taskObj.insert(c_sPlannedTime, ui->lineEdit_PlannedTime->text().toDouble());
    taskObj.insert(c_sStartTime, ui->dateTimeEdit_StartTime->dateTime().toString(c_sDateTimeFormat));
    taskObj.insert(c_sUsedTime, ui->lcdNumber_UsedTime->value());
    taskObj.insert(c_sTimeFix, ui->lineEdit_TimeFix->text().toDouble());
    taskObj.insert(c_sTaskPercent, ui->horizontalSlider_TaskPercent->value());
    taskObj.insert(c_sTaskState, ui->comboBox_TaskState->currentText());
    taskObj.insert(c_sPriority, ui->comboBox_Priority->currentText());
    taskObj.insert(c_sDifficulty, ui->comboBox_Difficulty->currentText());
    return taskObj;
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

void MainWindow::on_pushButton_Save_clicked()
{
    // TODO
    updateUsedTime();
    ui->treeWidget_MyTask->currentItem()->setText(0, ui->lineEdit_TaskName->text());
    QJsonObject jsonTaskInf = getTaskInfToJs();

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
    updateUsedTime();
}

void MainWindow::on_dateTimeEdit_StartTime_dateTimeChanged(const QDateTime &dateTime)
{
    updateEndTime();
}

void MainWindow::on_pushButton_SetUserName_clicked()
{

}

void MainWindow::on_pushButton_SetUserRole_clicked()
{

}

void MainWindow::on_pushButton_TaskLog_clicked()
{

}

void MainWindow::on_pushButton_AddMainTask_clicked()
{

}

void MainWindow::on_pushButton_AddSubTask_clicked()
{

}

void MainWindow::on_pushButton_DeleteTask_clicked()
{

}

void MainWindow::on_tabWidget_currentChanged(int index)
{

}

void MainWindow::on_pushButton_ExportCurrent_clicked()
{

}

void MainWindow::on_pushButton_ExportAll_clicked()
{

}
