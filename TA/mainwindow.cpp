#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget_MyTask->expandAll();

    m_pNetServer = new NetServer(this);

    // TODO 初始化时获取网络信息和状态
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_TaskPercent_valueChanged(int value)
{
    ui->label_PercentNum->setText(QString("%1%").arg(value));
}
