/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_AddProject;
    QTabWidget *tabWidget;
    QWidget *tab_UserPage;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_UserPage;
    QTreeView *treeView_MyTask;
    QGroupBox *groupBox_MyTask;
    QGridLayout *gridLayout_2;
    QTextEdit *textEdit_TaskDetails;
    QLabel *label_TaskName;
    QLineEdit *lineEdit_TaskName;
    QLabel *label_PlannedTime;
    QLineEdit *lineEdit_PlannedTime;
    QLabel *label_StartTime;
    QLabel *label_EndTime;
    QDateTimeEdit *dateTimeEdit_EndTime;
    QComboBox *comboBox_TimeUnit;
    QDateTimeEdit *dateTimeEdit_StartTime;
    QLabel *label_UsedTime;
    QLCDNumber *lcdNumber_UsedTime;
    QLabel *label_TaskPercent;
    QSlider *horizontalSlider_TaskPercent;
    QLabel *label_PercentNum;
    QLabel *label_TimeFix;
    QLineEdit *lineEdit_TimeFix;
    QComboBox *comboBox_TaskStage;
    QLabel *label_Priority;
    QComboBox *comboBox_Priority;
    QComboBox *comboBox_Difficulty;
    QLabel *label_Difficulty;
    QLabel *label_TaskStage;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_AddMainTask;
    QPushButton *pushButton_DeleteTask;
    QPushButton *pushButton_AddSubTask;
    QFrame *line;
    QLineEdit *lineEdit_UserName;
    QPushButton *pushButton_SetUserName;
    QTextEdit *textEdit_UserTaskLog;
    QDateEdit *dateEdit_LogDate;
    QComboBox *comboBox_UserRole;
    QPushButton *pushButton_SetUserRole;
    QPushButton *pushButton_TaskLog;
    QWidget *tab_TeamPage;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_TeamPage;
    QListView *listView_TeamTask;
    QGroupBox *groupBox_TaskVeiw;
    QVBoxLayout *verticalLayout;
    QTableView *tableView_UserTask;
    QProgressBar *progressBar_UserPercent;
    QPushButton *pushButton_ExportCurrent;
    QPushButton *pushButton_ExportAll;
    QWidget *tab_TeamBoard;
    QGridLayout *gridLayout_7;
    QTableView *tableView_TeamBoard;
    QWidget *tab_TaskOverview;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_TaskOverview;
    QTableView *tableView_TeamTask;
    QLabel *label_TeamTaskLog;
    QTextEdit *textEdit_TeamTaskLog;
    QLabel *label_TeamPercent;
    QProgressBar *progressBar_TeamPercent;
    QWidget *tab_Files;
    QGridLayout *gridLayout_9;
    QGroupBox *groupBox_ProjectFile;
    QGridLayout *gridLayout_11;
    QListView *listView_ProjectFile;
    QGroupBox *groupBox_FileLog;
    QGridLayout *gridLayout_10;
    QListView *listView_FileLog;
    QLabel *label_Path;
    QLineEdit *lineEdit_Path;
    QPushButton *pushButton_SelectFile;
    QPushButton *pushButton_CommitFile;
    QPushButton *pushButton_GetFile;
    QPushButton *pushButton_UpdateFile;
    QLabel *label_CurrentProject;
    QComboBox *comboBox_ProjectName;
    QPushButton *pushButton_CreateProject;
    QPushButton *pushButton_DeleteProject;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 630);
        MainWindow->setMinimumSize(QSize(800, 630));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Logo/TA.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setIconSize(QSize(128, 128));
        MainWindow->setAnimated(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_AddProject = new QPushButton(centralwidget);
        pushButton_AddProject->setObjectName(QStringLiteral("pushButton_AddProject"));
        pushButton_AddProject->setMaximumSize(QSize(75, 25));

        gridLayout->addWidget(pushButton_AddProject, 1, 6, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setSizeIncrement(QSize(0, 0));
        tab_UserPage = new QWidget();
        tab_UserPage->setObjectName(QStringLiteral("tab_UserPage"));
        gridLayout_3 = new QGridLayout(tab_UserPage);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_UserPage = new QGridLayout();
        gridLayout_UserPage->setObjectName(QStringLiteral("gridLayout_UserPage"));
        treeView_MyTask = new QTreeView(tab_UserPage);
        treeView_MyTask->setObjectName(QStringLiteral("treeView_MyTask"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeView_MyTask->sizePolicy().hasHeightForWidth());
        treeView_MyTask->setSizePolicy(sizePolicy);
        treeView_MyTask->setMinimumSize(QSize(200, 0));
        treeView_MyTask->setSizeIncrement(QSize(0, 0));

        gridLayout_UserPage->addWidget(treeView_MyTask, 0, 0, 1, 3);

        groupBox_MyTask = new QGroupBox(tab_UserPage);
        groupBox_MyTask->setObjectName(QStringLiteral("groupBox_MyTask"));
        sizePolicy.setHeightForWidth(groupBox_MyTask->sizePolicy().hasHeightForWidth());
        groupBox_MyTask->setSizePolicy(sizePolicy);
        groupBox_MyTask->setSizeIncrement(QSize(0, 0));
        gridLayout_2 = new QGridLayout(groupBox_MyTask);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        textEdit_TaskDetails = new QTextEdit(groupBox_MyTask);
        textEdit_TaskDetails->setObjectName(QStringLiteral("textEdit_TaskDetails"));

        gridLayout_2->addWidget(textEdit_TaskDetails, 3, 0, 1, 9);

        label_TaskName = new QLabel(groupBox_MyTask);
        label_TaskName->setObjectName(QStringLiteral("label_TaskName"));
        label_TaskName->setMaximumSize(QSize(55, 16777215));
        label_TaskName->setAutoFillBackground(true);

        gridLayout_2->addWidget(label_TaskName, 0, 0, 1, 1);

        lineEdit_TaskName = new QLineEdit(groupBox_MyTask);
        lineEdit_TaskName->setObjectName(QStringLiteral("lineEdit_TaskName"));

        gridLayout_2->addWidget(lineEdit_TaskName, 0, 2, 1, 4);

        label_PlannedTime = new QLabel(groupBox_MyTask);
        label_PlannedTime->setObjectName(QStringLiteral("label_PlannedTime"));
        label_PlannedTime->setMaximumSize(QSize(80, 16777215));
        label_PlannedTime->setAutoFillBackground(true);

        gridLayout_2->addWidget(label_PlannedTime, 0, 6, 1, 1);

        lineEdit_PlannedTime = new QLineEdit(groupBox_MyTask);
        lineEdit_PlannedTime->setObjectName(QStringLiteral("lineEdit_PlannedTime"));
        lineEdit_PlannedTime->setMaximumSize(QSize(50, 16777215));

        gridLayout_2->addWidget(lineEdit_PlannedTime, 0, 7, 1, 1);

        label_StartTime = new QLabel(groupBox_MyTask);
        label_StartTime->setObjectName(QStringLiteral("label_StartTime"));
        label_StartTime->setMaximumSize(QSize(55, 16777215));
        label_StartTime->setAutoFillBackground(true);

        gridLayout_2->addWidget(label_StartTime, 1, 0, 1, 1);

        label_EndTime = new QLabel(groupBox_MyTask);
        label_EndTime->setObjectName(QStringLiteral("label_EndTime"));
        label_EndTime->setMaximumSize(QSize(55, 16777215));

        gridLayout_2->addWidget(label_EndTime, 1, 3, 1, 1);

        dateTimeEdit_EndTime = new QDateTimeEdit(groupBox_MyTask);
        dateTimeEdit_EndTime->setObjectName(QStringLiteral("dateTimeEdit_EndTime"));
        dateTimeEdit_EndTime->setAutoFillBackground(true);
        dateTimeEdit_EndTime->setCalendarPopup(true);

        gridLayout_2->addWidget(dateTimeEdit_EndTime, 1, 4, 1, 2);

        comboBox_TimeUnit = new QComboBox(groupBox_MyTask);
        comboBox_TimeUnit->setObjectName(QStringLiteral("comboBox_TimeUnit"));
        comboBox_TimeUnit->setMaximumSize(QSize(40, 16777215));

        gridLayout_2->addWidget(comboBox_TimeUnit, 0, 8, 1, 1);

        dateTimeEdit_StartTime = new QDateTimeEdit(groupBox_MyTask);
        dateTimeEdit_StartTime->setObjectName(QStringLiteral("dateTimeEdit_StartTime"));
        dateTimeEdit_StartTime->setAutoFillBackground(true);
        dateTimeEdit_StartTime->setCalendarPopup(true);

        gridLayout_2->addWidget(dateTimeEdit_StartTime, 1, 2, 1, 1);

        label_UsedTime = new QLabel(groupBox_MyTask);
        label_UsedTime->setObjectName(QStringLiteral("label_UsedTime"));
        label_UsedTime->setMaximumSize(QSize(80, 16777215));
        label_UsedTime->setAutoFillBackground(true);

        gridLayout_2->addWidget(label_UsedTime, 1, 6, 1, 1);

        lcdNumber_UsedTime = new QLCDNumber(groupBox_MyTask);
        lcdNumber_UsedTime->setObjectName(QStringLiteral("lcdNumber_UsedTime"));
        lcdNumber_UsedTime->setAutoFillBackground(true);
        lcdNumber_UsedTime->setSmallDecimalPoint(false);
        lcdNumber_UsedTime->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber_UsedTime->setProperty("value", QVariant(5.5));

        gridLayout_2->addWidget(lcdNumber_UsedTime, 1, 7, 1, 2);

        label_TaskPercent = new QLabel(groupBox_MyTask);
        label_TaskPercent->setObjectName(QStringLiteral("label_TaskPercent"));
        label_TaskPercent->setMaximumSize(QSize(55, 16777215));
        label_TaskPercent->setAutoFillBackground(true);

        gridLayout_2->addWidget(label_TaskPercent, 2, 0, 1, 1);

        horizontalSlider_TaskPercent = new QSlider(groupBox_MyTask);
        horizontalSlider_TaskPercent->setObjectName(QStringLiteral("horizontalSlider_TaskPercent"));
        horizontalSlider_TaskPercent->setCursor(QCursor(Qt::PointingHandCursor));
        horizontalSlider_TaskPercent->setAutoFillBackground(true);
        horizontalSlider_TaskPercent->setOrientation(Qt::Horizontal);
        horizontalSlider_TaskPercent->setTickPosition(QSlider::TicksAbove);
        horizontalSlider_TaskPercent->setTickInterval(5);

        gridLayout_2->addWidget(horizontalSlider_TaskPercent, 2, 2, 1, 3);

        label_PercentNum = new QLabel(groupBox_MyTask);
        label_PercentNum->setObjectName(QStringLiteral("label_PercentNum"));
        label_PercentNum->setMaximumSize(QSize(80, 16777215));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        label_PercentNum->setFont(font);
        label_PercentNum->setAutoFillBackground(true);
        label_PercentNum->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_PercentNum, 2, 5, 1, 1);

        label_TimeFix = new QLabel(groupBox_MyTask);
        label_TimeFix->setObjectName(QStringLiteral("label_TimeFix"));
        label_TimeFix->setMaximumSize(QSize(80, 16777215));
        label_TimeFix->setAutoFillBackground(true);

        gridLayout_2->addWidget(label_TimeFix, 2, 6, 1, 1);

        lineEdit_TimeFix = new QLineEdit(groupBox_MyTask);
        lineEdit_TimeFix->setObjectName(QStringLiteral("lineEdit_TimeFix"));
        lineEdit_TimeFix->setAutoFillBackground(true);

        gridLayout_2->addWidget(lineEdit_TimeFix, 2, 7, 1, 2);

        comboBox_TaskStage = new QComboBox(groupBox_MyTask);
        comboBox_TaskStage->setObjectName(QStringLiteral("comboBox_TaskStage"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_TaskStage->sizePolicy().hasHeightForWidth());
        comboBox_TaskStage->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(comboBox_TaskStage, 4, 2, 1, 1);

        label_Priority = new QLabel(groupBox_MyTask);
        label_Priority->setObjectName(QStringLiteral("label_Priority"));
        label_Priority->setMaximumSize(QSize(55, 16777215));
        label_Priority->setAutoFillBackground(true);

        gridLayout_2->addWidget(label_Priority, 4, 3, 1, 1);

        comboBox_Priority = new QComboBox(groupBox_MyTask);
        comboBox_Priority->setObjectName(QStringLiteral("comboBox_Priority"));
        sizePolicy1.setHeightForWidth(comboBox_Priority->sizePolicy().hasHeightForWidth());
        comboBox_Priority->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(comboBox_Priority, 4, 4, 1, 1);

        comboBox_Difficulty = new QComboBox(groupBox_MyTask);
        comboBox_Difficulty->setObjectName(QStringLiteral("comboBox_Difficulty"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox_Difficulty->sizePolicy().hasHeightForWidth());
        comboBox_Difficulty->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(comboBox_Difficulty, 4, 6, 1, 1);

        label_Difficulty = new QLabel(groupBox_MyTask);
        label_Difficulty->setObjectName(QStringLiteral("label_Difficulty"));
        label_Difficulty->setMaximumSize(QSize(55, 16777215));
        label_Difficulty->setAutoFillBackground(true);

        gridLayout_2->addWidget(label_Difficulty, 4, 5, 1, 1);

        label_TaskStage = new QLabel(groupBox_MyTask);
        label_TaskStage->setObjectName(QStringLiteral("label_TaskStage"));
        label_TaskStage->setMaximumSize(QSize(55, 16777215));
        label_TaskStage->setAutoFillBackground(true);

        gridLayout_2->addWidget(label_TaskStage, 4, 0, 1, 1);

        pushButton_Save = new QPushButton(groupBox_MyTask);
        pushButton_Save->setObjectName(QStringLiteral("pushButton_Save"));
        pushButton_Save->setMaximumSize(QSize(90, 16777215));

        gridLayout_2->addWidget(pushButton_Save, 4, 7, 1, 2);


        gridLayout_UserPage->addWidget(groupBox_MyTask, 0, 3, 2, 2);

        pushButton_AddMainTask = new QPushButton(tab_UserPage);
        pushButton_AddMainTask->setObjectName(QStringLiteral("pushButton_AddMainTask"));
        sizePolicy1.setHeightForWidth(pushButton_AddMainTask->sizePolicy().hasHeightForWidth());
        pushButton_AddMainTask->setSizePolicy(sizePolicy1);
        pushButton_AddMainTask->setMinimumSize(QSize(75, 0));
        pushButton_AddMainTask->setMaximumSize(QSize(75, 25));

        gridLayout_UserPage->addWidget(pushButton_AddMainTask, 1, 0, 1, 1);

        pushButton_DeleteTask = new QPushButton(tab_UserPage);
        pushButton_DeleteTask->setObjectName(QStringLiteral("pushButton_DeleteTask"));
        sizePolicy1.setHeightForWidth(pushButton_DeleteTask->sizePolicy().hasHeightForWidth());
        pushButton_DeleteTask->setSizePolicy(sizePolicy1);
        pushButton_DeleteTask->setMinimumSize(QSize(25, 0));
        pushButton_DeleteTask->setMaximumSize(QSize(500, 25));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        pushButton_DeleteTask->setFont(font1);

        gridLayout_UserPage->addWidget(pushButton_DeleteTask, 1, 1, 1, 1);

        pushButton_AddSubTask = new QPushButton(tab_UserPage);
        pushButton_AddSubTask->setObjectName(QStringLiteral("pushButton_AddSubTask"));
        sizePolicy1.setHeightForWidth(pushButton_AddSubTask->sizePolicy().hasHeightForWidth());
        pushButton_AddSubTask->setSizePolicy(sizePolicy1);
        pushButton_AddSubTask->setMinimumSize(QSize(75, 0));
        pushButton_AddSubTask->setMaximumSize(QSize(75, 25));

        gridLayout_UserPage->addWidget(pushButton_AddSubTask, 1, 2, 1, 1);

        line = new QFrame(tab_UserPage);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_UserPage->addWidget(line, 2, 0, 1, 5);

        lineEdit_UserName = new QLineEdit(tab_UserPage);
        lineEdit_UserName->setObjectName(QStringLiteral("lineEdit_UserName"));
        sizePolicy1.setHeightForWidth(lineEdit_UserName->sizePolicy().hasHeightForWidth());
        lineEdit_UserName->setSizePolicy(sizePolicy1);
        lineEdit_UserName->setMinimumSize(QSize(0, 0));
        lineEdit_UserName->setMaximumSize(QSize(16777215, 25));

        gridLayout_UserPage->addWidget(lineEdit_UserName, 3, 0, 1, 2);

        pushButton_SetUserName = new QPushButton(tab_UserPage);
        pushButton_SetUserName->setObjectName(QStringLiteral("pushButton_SetUserName"));
        sizePolicy1.setHeightForWidth(pushButton_SetUserName->sizePolicy().hasHeightForWidth());
        pushButton_SetUserName->setSizePolicy(sizePolicy1);
        pushButton_SetUserName->setMaximumSize(QSize(75, 25));

        gridLayout_UserPage->addWidget(pushButton_SetUserName, 3, 2, 1, 1);

        textEdit_UserTaskLog = new QTextEdit(tab_UserPage);
        textEdit_UserTaskLog->setObjectName(QStringLiteral("textEdit_UserTaskLog"));

        gridLayout_UserPage->addWidget(textEdit_UserTaskLog, 3, 3, 2, 1);

        dateEdit_LogDate = new QDateEdit(tab_UserPage);
        dateEdit_LogDate->setObjectName(QStringLiteral("dateEdit_LogDate"));
        dateEdit_LogDate->setMaximumSize(QSize(90, 16777215));
        dateEdit_LogDate->setAutoFillBackground(true);
        dateEdit_LogDate->setAlignment(Qt::AlignCenter);
        dateEdit_LogDate->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        dateEdit_LogDate->setProperty("showGroupSeparator", QVariant(false));
        dateEdit_LogDate->setCurrentSection(QDateTimeEdit::YearSection);
        dateEdit_LogDate->setCalendarPopup(true);

        gridLayout_UserPage->addWidget(dateEdit_LogDate, 3, 4, 1, 1);

        comboBox_UserRole = new QComboBox(tab_UserPage);
        comboBox_UserRole->setObjectName(QStringLiteral("comboBox_UserRole"));
        sizePolicy1.setHeightForWidth(comboBox_UserRole->sizePolicy().hasHeightForWidth());
        comboBox_UserRole->setSizePolicy(sizePolicy1);
        comboBox_UserRole->setMinimumSize(QSize(0, 0));
        comboBox_UserRole->setMaximumSize(QSize(16777215, 25));
        comboBox_UserRole->setEditable(true);

        gridLayout_UserPage->addWidget(comboBox_UserRole, 4, 0, 1, 2);

        pushButton_SetUserRole = new QPushButton(tab_UserPage);
        pushButton_SetUserRole->setObjectName(QStringLiteral("pushButton_SetUserRole"));
        sizePolicy1.setHeightForWidth(pushButton_SetUserRole->sizePolicy().hasHeightForWidth());
        pushButton_SetUserRole->setSizePolicy(sizePolicy1);
        pushButton_SetUserRole->setMaximumSize(QSize(75, 25));

        gridLayout_UserPage->addWidget(pushButton_SetUserRole, 4, 2, 1, 1);

        pushButton_TaskLog = new QPushButton(tab_UserPage);
        pushButton_TaskLog->setObjectName(QStringLiteral("pushButton_TaskLog"));
        pushButton_TaskLog->setMaximumSize(QSize(90, 25));

        gridLayout_UserPage->addWidget(pushButton_TaskLog, 4, 4, 1, 1);

        gridLayout_UserPage->setColumnStretch(0, 4);
        gridLayout_UserPage->setColumnStretch(1, 2);
        gridLayout_UserPage->setColumnStretch(2, 4);
        gridLayout_UserPage->setColumnStretch(3, 20);
        gridLayout_UserPage->setColumnStretch(4, 5);

        gridLayout_3->addLayout(gridLayout_UserPage, 0, 0, 1, 1);

        tabWidget->addTab(tab_UserPage, QString());
        tab_TeamPage = new QWidget();
        tab_TeamPage->setObjectName(QStringLiteral("tab_TeamPage"));
        sizePolicy.setHeightForWidth(tab_TeamPage->sizePolicy().hasHeightForWidth());
        tab_TeamPage->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(tab_TeamPage);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_TeamPage = new QGridLayout();
        gridLayout_TeamPage->setObjectName(QStringLiteral("gridLayout_TeamPage"));
        listView_TeamTask = new QListView(tab_TeamPage);
        listView_TeamTask->setObjectName(QStringLiteral("listView_TeamTask"));
        listView_TeamTask->setMaximumSize(QSize(150, 16777215));

        gridLayout_TeamPage->addWidget(listView_TeamTask, 0, 0, 1, 2);

        groupBox_TaskVeiw = new QGroupBox(tab_TeamPage);
        groupBox_TaskVeiw->setObjectName(QStringLiteral("groupBox_TaskVeiw"));
        verticalLayout = new QVBoxLayout(groupBox_TaskVeiw);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView_UserTask = new QTableView(groupBox_TaskVeiw);
        tableView_UserTask->setObjectName(QStringLiteral("tableView_UserTask"));

        verticalLayout->addWidget(tableView_UserTask);

        progressBar_UserPercent = new QProgressBar(groupBox_TaskVeiw);
        progressBar_UserPercent->setObjectName(QStringLiteral("progressBar_UserPercent"));
        progressBar_UserPercent->setAutoFillBackground(true);
        progressBar_UserPercent->setValue(24);

        verticalLayout->addWidget(progressBar_UserPercent);


        gridLayout_TeamPage->addWidget(groupBox_TaskVeiw, 0, 2, 2, 1);

        pushButton_ExportCurrent = new QPushButton(tab_TeamPage);
        pushButton_ExportCurrent->setObjectName(QStringLiteral("pushButton_ExportCurrent"));
        pushButton_ExportCurrent->setMinimumSize(QSize(75, 25));
        pushButton_ExportCurrent->setMaximumSize(QSize(75, 25));

        gridLayout_TeamPage->addWidget(pushButton_ExportCurrent, 1, 0, 1, 1);

        pushButton_ExportAll = new QPushButton(tab_TeamPage);
        pushButton_ExportAll->setObjectName(QStringLiteral("pushButton_ExportAll"));
        pushButton_ExportAll->setMinimumSize(QSize(75, 25));
        pushButton_ExportAll->setMaximumSize(QSize(75, 25));

        gridLayout_TeamPage->addWidget(pushButton_ExportAll, 1, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_TeamPage, 0, 0, 1, 1);

        tabWidget->addTab(tab_TeamPage, QString());
        tab_TeamBoard = new QWidget();
        tab_TeamBoard->setObjectName(QStringLiteral("tab_TeamBoard"));
        gridLayout_7 = new QGridLayout(tab_TeamBoard);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        tableView_TeamBoard = new QTableView(tab_TeamBoard);
        tableView_TeamBoard->setObjectName(QStringLiteral("tableView_TeamBoard"));

        gridLayout_7->addWidget(tableView_TeamBoard, 0, 0, 1, 1);

        tabWidget->addTab(tab_TeamBoard, QString());
        tab_TaskOverview = new QWidget();
        tab_TaskOverview->setObjectName(QStringLiteral("tab_TaskOverview"));
        gridLayout_8 = new QGridLayout(tab_TaskOverview);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_TaskOverview = new QGridLayout();
        gridLayout_TaskOverview->setObjectName(QStringLiteral("gridLayout_TaskOverview"));
        tableView_TeamTask = new QTableView(tab_TaskOverview);
        tableView_TeamTask->setObjectName(QStringLiteral("tableView_TeamTask"));

        gridLayout_TaskOverview->addWidget(tableView_TeamTask, 0, 0, 1, 2);

        label_TeamTaskLog = new QLabel(tab_TaskOverview);
        label_TeamTaskLog->setObjectName(QStringLiteral("label_TeamTaskLog"));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        label_TeamTaskLog->setFont(font2);
        label_TeamTaskLog->setAutoFillBackground(true);
        label_TeamTaskLog->setAlignment(Qt::AlignCenter);
        label_TeamTaskLog->setWordWrap(true);

        gridLayout_TaskOverview->addWidget(label_TeamTaskLog, 1, 0, 1, 1);

        textEdit_TeamTaskLog = new QTextEdit(tab_TaskOverview);
        textEdit_TeamTaskLog->setObjectName(QStringLiteral("textEdit_TeamTaskLog"));
        textEdit_TeamTaskLog->setEnabled(true);
        textEdit_TeamTaskLog->setMaximumSize(QSize(16777215, 75));
        textEdit_TeamTaskLog->setUndoRedoEnabled(false);
        textEdit_TeamTaskLog->setReadOnly(true);

        gridLayout_TaskOverview->addWidget(textEdit_TeamTaskLog, 1, 1, 1, 1);

        label_TeamPercent = new QLabel(tab_TaskOverview);
        label_TeamPercent->setObjectName(QStringLiteral("label_TeamPercent"));
        label_TeamPercent->setAutoFillBackground(true);
        label_TeamPercent->setAlignment(Qt::AlignCenter);

        gridLayout_TaskOverview->addWidget(label_TeamPercent, 2, 0, 1, 1);

        progressBar_TeamPercent = new QProgressBar(tab_TaskOverview);
        progressBar_TeamPercent->setObjectName(QStringLiteral("progressBar_TeamPercent"));
        progressBar_TeamPercent->setAutoFillBackground(true);
        progressBar_TeamPercent->setValue(24);

        gridLayout_TaskOverview->addWidget(progressBar_TeamPercent, 2, 1, 1, 1);

        gridLayout_TaskOverview->setColumnStretch(0, 1);
        gridLayout_TaskOverview->setColumnStretch(1, 50);

        gridLayout_8->addLayout(gridLayout_TaskOverview, 0, 0, 1, 1);

        tabWidget->addTab(tab_TaskOverview, QString());
        tab_Files = new QWidget();
        tab_Files->setObjectName(QStringLiteral("tab_Files"));
        gridLayout_9 = new QGridLayout(tab_Files);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        groupBox_ProjectFile = new QGroupBox(tab_Files);
        groupBox_ProjectFile->setObjectName(QStringLiteral("groupBox_ProjectFile"));
        gridLayout_11 = new QGridLayout(groupBox_ProjectFile);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        listView_ProjectFile = new QListView(groupBox_ProjectFile);
        listView_ProjectFile->setObjectName(QStringLiteral("listView_ProjectFile"));

        gridLayout_11->addWidget(listView_ProjectFile, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_ProjectFile, 0, 0, 1, 3);

        groupBox_FileLog = new QGroupBox(tab_Files);
        groupBox_FileLog->setObjectName(QStringLiteral("groupBox_FileLog"));
        gridLayout_10 = new QGridLayout(groupBox_FileLog);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        listView_FileLog = new QListView(groupBox_FileLog);
        listView_FileLog->setObjectName(QStringLiteral("listView_FileLog"));

        gridLayout_10->addWidget(listView_FileLog, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_FileLog, 0, 3, 1, 3);

        label_Path = new QLabel(tab_Files);
        label_Path->setObjectName(QStringLiteral("label_Path"));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(false);
        font3.setWeight(50);
        label_Path->setFont(font3);
        label_Path->setAutoFillBackground(true);

        gridLayout_9->addWidget(label_Path, 1, 0, 1, 1);

        lineEdit_Path = new QLineEdit(tab_Files);
        lineEdit_Path->setObjectName(QStringLiteral("lineEdit_Path"));

        gridLayout_9->addWidget(lineEdit_Path, 1, 1, 1, 1);

        pushButton_SelectFile = new QPushButton(tab_Files);
        pushButton_SelectFile->setObjectName(QStringLiteral("pushButton_SelectFile"));

        gridLayout_9->addWidget(pushButton_SelectFile, 1, 2, 1, 1);

        pushButton_CommitFile = new QPushButton(tab_Files);
        pushButton_CommitFile->setObjectName(QStringLiteral("pushButton_CommitFile"));

        gridLayout_9->addWidget(pushButton_CommitFile, 1, 3, 1, 1);

        pushButton_GetFile = new QPushButton(tab_Files);
        pushButton_GetFile->setObjectName(QStringLiteral("pushButton_GetFile"));

        gridLayout_9->addWidget(pushButton_GetFile, 1, 4, 1, 1);

        pushButton_UpdateFile = new QPushButton(tab_Files);
        pushButton_UpdateFile->setObjectName(QStringLiteral("pushButton_UpdateFile"));

        gridLayout_9->addWidget(pushButton_UpdateFile, 1, 5, 1, 1);

        tabWidget->addTab(tab_Files, QString());

        gridLayout->addWidget(tabWidget, 3, 1, 1, 9);

        label_CurrentProject = new QLabel(centralwidget);
        label_CurrentProject->setObjectName(QStringLiteral("label_CurrentProject"));
        label_CurrentProject->setMaximumSize(QSize(55, 25));

        gridLayout->addWidget(label_CurrentProject, 1, 3, 1, 1);

        comboBox_ProjectName = new QComboBox(centralwidget);
        comboBox_ProjectName->setObjectName(QStringLiteral("comboBox_ProjectName"));
        sizePolicy1.setHeightForWidth(comboBox_ProjectName->sizePolicy().hasHeightForWidth());
        comboBox_ProjectName->setSizePolicy(sizePolicy1);
        comboBox_ProjectName->setMinimumSize(QSize(450, 25));

        gridLayout->addWidget(comboBox_ProjectName, 1, 4, 1, 1);

        pushButton_CreateProject = new QPushButton(centralwidget);
        pushButton_CreateProject->setObjectName(QStringLiteral("pushButton_CreateProject"));
        pushButton_CreateProject->setMaximumSize(QSize(75, 25));

        gridLayout->addWidget(pushButton_CreateProject, 1, 7, 1, 1);

        pushButton_DeleteProject = new QPushButton(centralwidget);
        pushButton_DeleteProject->setObjectName(QStringLiteral("pushButton_DeleteProject"));
        pushButton_DeleteProject->setMaximumSize(QSize(75, 25));

        gridLayout->addWidget(pushButton_DeleteProject, 1, 8, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\233\242\351\230\237\345\212\251\346\211\213", "\345\233\242\351\230\237\345\212\251\346\211\213"));
        pushButton_AddProject->setText(QApplication::translate("MainWindow", "\345\212\240\345\205\245\351\241\271\347\233\256", Q_NULLPTR));
        groupBox_MyTask->setTitle(QApplication::translate("MainWindow", "\344\273\273\345\212\241\350\256\276\347\275\256", Q_NULLPTR));
        textEdit_TaskDetails->setDocumentTitle(QApplication::translate("MainWindow", "\344\273\273\345\212\241\350\257\246\346\203\205", Q_NULLPTR));
        textEdit_TaskDetails->setPlaceholderText(QApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\344\273\273\345\212\241\350\257\246\346\203\205...", Q_NULLPTR));
        label_TaskName->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\345\220\215\347\247\260:", Q_NULLPTR));
        label_PlannedTime->setText(QApplication::translate("MainWindow", "\351\242\204\344\274\260\344\273\273\345\212\241\347\224\250\346\227\266:", Q_NULLPTR));
        label_StartTime->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\227\266\351\227\264:", Q_NULLPTR));
        label_EndTime->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237\346\227\266\351\227\264:", Q_NULLPTR));
        comboBox_TimeUnit->clear();
        comboBox_TimeUnit->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\346\227\266", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\244\251", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\221\250", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\346\234\210", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\210\206", Q_NULLPTR)
        );
        label_UsedTime->setText(QApplication::translate("MainWindow", "\345\267\262\347\224\250\345\267\245\346\227\266\357\274\210H\357\274\211", Q_NULLPTR));
        label_TaskPercent->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\350\277\233\345\272\246:", Q_NULLPTR));
        label_PercentNum->setText(QApplication::translate("MainWindow", "55%", Q_NULLPTR));
        label_TimeFix->setText(QApplication::translate("MainWindow", "\345\267\245\346\227\266\350\260\203\345\267\256\357\274\210H\357\274\211", Q_NULLPTR));
        comboBox_TaskStage->clear();
        comboBox_TaskStage->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\207\206\345\244\207\351\230\266\346\256\265", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\274\200\345\217\221\351\230\266\346\256\265", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\274\200\345\217\221\350\207\252\346\265\213", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\351\234\200\346\261\202\351\252\214\350\257\201", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\346\265\213\350\257\225\351\230\266\346\256\265", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\256\214\346\210\220\345\217\221\345\270\203", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\205\266\344\273\226\347\212\266\346\200\201", Q_NULLPTR)
        );
        label_Priority->setText(QApplication::translate("MainWindow", "\344\274\230\345\205\210\347\272\247\345\210\253:", Q_NULLPTR));
        comboBox_Priority->clear();
        comboBox_Priority->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\346\232\202\347\274\223", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\275\216", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\270\200\350\210\254", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\351\253\230", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\347\264\247\346\200\245", Q_NULLPTR)
        );
        comboBox_Difficulty->clear();
        comboBox_Difficulty->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\344\270\200\347\272\247", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\272\214\347\272\247", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\270\211\347\272\247", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\233\233\347\272\247", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\272\224\347\272\247", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\205\266\344\273\226", Q_NULLPTR)
        );
        label_Difficulty->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\351\232\276\345\272\246:", Q_NULLPTR));
        label_TaskStage->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\347\212\266\346\200\201:", Q_NULLPTR));
        pushButton_Save->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\344\273\273\345\212\241\344\277\241\346\201\257", Q_NULLPTR));
        pushButton_AddMainTask->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\344\270\273\344\273\273\345\212\241", Q_NULLPTR));
        pushButton_DeleteTask->setText(QApplication::translate("MainWindow", "\345\210\240", Q_NULLPTR));
        pushButton_AddSubTask->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\345\255\220\344\273\273\345\212\241", Q_NULLPTR));
        pushButton_SetUserName->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\345\220\215\347\247\260", Q_NULLPTR));
        textEdit_UserTaskLog->setPlaceholderText(QApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\351\241\271\347\233\256\346\227\245\345\277\227...", Q_NULLPTR));
        dateEdit_LogDate->setDisplayFormat(QApplication::translate("MainWindow", "yyyy-M-d", Q_NULLPTR));
        comboBox_UserRole->clear();
        comboBox_UserRole->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\347\240\224\345\217\221", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\272\247\345\223\201", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\346\265\213\350\257\225", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\205\266\344\273\226", Q_NULLPTR)
        );
        pushButton_SetUserRole->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\350\247\222\350\211\262", Q_NULLPTR));
        pushButton_TaskLog->setText(QApplication::translate("MainWindow", "\350\256\260\345\275\225\344\273\273\345\212\241\346\227\245\345\277\227", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_UserPage), QApplication::translate("MainWindow", "\346\210\221\347\232\204\344\273\273\345\212\241", Q_NULLPTR));
        groupBox_TaskVeiw->setTitle(QApplication::translate("MainWindow", "\344\273\273\345\212\241\351\242\204\350\247\210", Q_NULLPTR));
        pushButton_ExportCurrent->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\345\275\223\345\211\215", Q_NULLPTR));
        pushButton_ExportAll->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\345\205\250\351\203\250", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_TeamPage), QApplication::translate("MainWindow", "\345\233\242\351\230\237\344\273\273\345\212\241", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_TeamBoard), QApplication::translate("MainWindow", "\345\233\242\351\230\237\347\234\213\346\235\277", Q_NULLPTR));
        label_TeamTaskLog->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\346\227\245\345\277\227", Q_NULLPTR));
        textEdit_TeamTaskLog->setPlaceholderText(QApplication::translate("MainWindow", "\347\202\271\351\200\211\344\273\273\345\212\241\350\212\202\347\202\271\344\273\245\346\230\276\347\244\272\345\257\271\345\272\224\346\227\245\345\277\227...", Q_NULLPTR));
        label_TeamPercent->setText(QApplication::translate("MainWindow", "\346\200\273\350\277\233\345\272\246:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_TaskOverview), QApplication::translate("MainWindow", "\344\273\273\345\212\241\346\200\273\350\247\210", Q_NULLPTR));
        groupBox_ProjectFile->setTitle(QApplication::translate("MainWindow", "\351\241\271\347\233\256\346\226\207\344\273\266", Q_NULLPTR));
        groupBox_FileLog->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266\346\227\245\345\277\227", Q_NULLPTR));
        label_Path->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\350\267\257\345\276\204:", Q_NULLPTR));
        pushButton_SelectFile->setText(QApplication::translate("MainWindow", "\346\265\217\350\247\210", Q_NULLPTR));
        pushButton_CommitFile->setText(QApplication::translate("MainWindow", "\346\217\220\344\272\244\346\226\207\344\273\266", Q_NULLPTR));
        pushButton_GetFile->setText(QApplication::translate("MainWindow", "\350\216\267\345\217\226\346\226\207\344\273\266", Q_NULLPTR));
        pushButton_UpdateFile->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260\345\210\227\350\241\250", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_Files), QApplication::translate("MainWindow", "\344\273\273\345\212\241\346\226\207\344\273\266", Q_NULLPTR));
        label_CurrentProject->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\351\241\271\347\233\256:", Q_NULLPTR));
        pushButton_CreateProject->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\351\241\271\347\233\256", Q_NULLPTR));
        pushButton_DeleteProject->setText(QApplication::translate("MainWindow", "\347\246\273\345\274\200\351\241\271\347\233\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
