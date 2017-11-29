#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget_MyTask->expandAll();

    m_pUdpSocket = new QUdpSocket(this);
    m_port = 55555;
    m_pUdpSocket->bind(m_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(m_pUdpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

//    m_pTcpSocket = new QTcpSocket(this);
//    m_pTcpServer = new QTcpServer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processPendingDatagrams()
{

}

void MainWindow::on_horizontalSlider_TaskPercent_valueChanged(int value)
{
    ui->label_PercentNum->setText(QString("%1%").arg(value));
}
