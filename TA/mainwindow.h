#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QListWidget>
#include <QTabWidget>
#include <QMenu>
#include <QHash>
#include <QMap>
#include <QVector>
#include <QTableWidget>
#include <QSystemTrayIcon>

#include "netserver.h"
#include "fileserver.h"
#include "theme/manhattanstyle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString getOSUserName();

    void initNumEditValidator();
    void updateEndTime();
    QDateTime getEndTime(QDateTime oStartDate, double dHours);
    double getHours(double dPlanTime, QString sPlannedTimeUnit);
    void updatePlannedTime();
    void updateUsedTime();

    void updateCurTaskInfo(QTreeWidgetItem *current);
    void updateTreeWidget();

    void writeFileLog(QString sOperType, QString sName);

    void updatePages(int nPageIndex);
    void updateUserPage();
    void updateTeamPage();
    void updateTeamBoard();
    void updateTaskOverView();
    void updateFilesPage();

    void saveTaskInfo(QTreeWidgetItem *previous);

    QJsonObject getTaskInfToJs();
    void setTaskInfFromJs(QJsonObject oTaskInf);

    //刷新团队任务左侧每个成员对应的表格信息到QTableWidget中
    void flushlistWidget_TeamTaskData(QTableWidget * oTable, const QString &currentText);
    //获取每个成员的所有任务时间跨度
    void getMemberTaskScope(QJsonObject oMember, QDateTime &Start, QDateTime &End);
    //获取每个主任务的时间跨度
    void getMainTaskScope(QJsonObject oMainTask, QDateTime &Start, QDateTime &End);
    void insertTableColAccordingDateTime(QTableWidget * oTable, QDateTime & oDateTime, int index);

public slots:
    void updateProjectList(QString sCurProj = "");
    void updateFileTabWidget();
    void updateFileLogListWidget();

    void onTeamTaskExportExcel();
    void onTeamBoardExportExcel();
protected:
    //@ breif: 处理团队看板数据
    //@ out param: groupingHash按角色分组数据
    void handleMemberBroadData(QJsonObject& member, QMap<QString, QVector<QJsonObject> >& groupingHash);

    void updateTABoardOneMemberData(QJsonObject& member, const int col, int& row);

    void createTrayIcon();

    void createActions();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void clearFileLog();

    void on_horizontalSlider_TaskPercent_valueChanged(int value);

    void on_pushButton_ResetTaskInfo_clicked();

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

    void on_treeWidget_MyTask_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_dateEdit_LogDate_dateChanged(const QDate &date);

    void on_comboBox_ProjectName_currentTextChanged(const QString &arg1);

    void on_pushButton_AddProject_clicked();

    void on_pushButton_CreateProject_clicked();

    void on_pushButton_DeleteProject_clicked();

    void on_listWidget_FileLog_customContextMenuRequested(const QPoint &pos);

    void on_listWidget_TeamTask_currentTextChanged(const QString &currentText);

    void on_pushButton_SelectFile_clicked();

    void on_pushButton_CommitFile_clicked();

    void on_pushButton_UpdateFile_clicked();

    void on_pushButton_DeleteFile_clicked();

    void on_tableWidget_TeamTask_customContextMenuRequested(const QPoint &pos);

    void on_tableWidget_TeamBoard_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_OpenFile_clicked();

    void on_tableWidget_TeamTask_itemClicked(QTableWidgetItem *item);

	void iconActivated(QSystemTrayIcon::ActivationReason reason);
	
	void setConfig();
private:
    Ui::MainWindow *ui;

    UdpSocket   *m_pNetServer;
    FileServer  *m_pFileServer;
    TcpServer   *m_pTcpServer;

    QMenu *m_pTeamTaskPopMenu;
    QAction *m_pTeamTaskActExport;

    QMenu *m_pTeamBoardPopMenu;
    QAction *m_pTeamBoardActExport;

    QAction *m_pSetAction;
    QAction *m_pQuitAction;

    QSystemTrayIcon *m_pTrayIcon;
    QMenu *m_pTrayIconMenu;

};

#endif // MAINWINDOW_H
