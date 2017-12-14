#ifndef CONFIGFORM_H
#define CONFIGFORM_H

#include <QDialog>
#include "ui_configdialog.h"
namespace Ui {
class Dialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();
protected slots:
    //void on_themeBox_activated(const QString & text);
    void on_okBtn_clicked();
    void on_cancelBtn_clicked();
private:
    Ui::Dialog *ui;
};

#endif // CONFIGFORM_H
