#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "netserver.h"


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
    void on_horizontalSlider_TaskPercent_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    NetServer *m_pNetServer;
    QString fileName;

};

#endif // MAINWINDOW_H
