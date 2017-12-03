#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "netserver.h"
#include "fileserver.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initNumEditValidator();
    void updateEndTime();
    void updatePlannedTime();
    void updateUsedTime();

    QJsonObject getTaskInfToJs();

private slots:
    void on_horizontalSlider_TaskPercent_valueChanged(int value);

    void on_pushButton_Save_clicked();

    void on_comboBox_TimeUnit_currentIndexChanged(int index);

    void on_lineEdit_PlannedTime_textChanged(const QString &arg1);

    void on_lineEdit_TimeFix_textChanged(const QString &arg1);

    void on_dateTimeEdit_EndTime_dateTimeChanged(const QDateTime &dateTime);

    void on_dateTimeEdit_StartTime_dateTimeChanged(const QDateTime &dateTime);

    void on_pushButton_SetUserName_clicked();

    void on_pushButton_SetUserRole_clicked();

    void on_pushButton_TaskLog_clicked();

    void on_pushButton_AddMainTask_clicked();

    void on_pushButton_AddSubTask_clicked();

    void on_pushButton_DeleteTask_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_ExportCurrent_clicked();

    void on_pushButton_ExportAll_clicked();

private:
    Ui::MainWindow *ui;

    double m_timeFac;
    NetServer *m_pNetServer;
    FileServer *m_pFileServer;

};

#endif // MAINWINDOW_H
