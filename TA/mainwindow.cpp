#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget_MyTask->expandAll();

    m_pUdpSocket = new QUdpSocket(this);
    m_port = 55554;
    while(!m_pUdpSocket->bind(m_port, QUdpSocket::DefaultForPlatform))
    {
        qDebug() << m_port << " 端口绑定失败，尝试下一个端口...";
        m_port++;
    }
    connect(m_pUdpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpServer = new QTcpServer(this);

    // TODO 初始化时获取网络信息和状态
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processPendingDatagrams()
{
    while (m_pUdpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_pUdpSocket->pendingDatagramSize());
        m_pUdpSocket->readDatagram(datagram.data(), datagram.size());

        // TODO 解析并处理datagram.data()中的数据

    }

}

void MainWindow::broadcastDatagram(QByteArray datagram)
{
    m_pUdpSocket->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, m_port);
}

void MainWindow::on_horizontalSlider_TaskPercent_valueChanged(int value)
{
    ui->label_PercentNum->setText(QString("%1%").arg(value));
}
