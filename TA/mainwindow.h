#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void processPendingDatagrams();
    void broadcastDatagram(QByteArray datagram);

    void on_horizontalSlider_TaskPercent_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    quint16 m_port;
    QUdpSocket *m_pUdpSocket;
    QTcpSocket *m_pTcpSocket;
    QTcpServer *m_pTcpServer;
    QString fileName;
    QString getIP();


};

#endif // MAINWINDOW_H
