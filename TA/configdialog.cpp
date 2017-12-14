#include "configdialog.h"
#include "ui_configdialog.h"
#include "setting.h"
ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->themeBox->setCurrentText(CSetting::instance().getCurTheme());
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::on_okBtn_clicked()
{
    CSetting::instance().setTheme(ui->themeBox->currentText());
    accept();
}

void ConfigDialog::on_cancelBtn_clicked()
{
    reject();
}

//void ConfigDialog::on_themeBox_activated(const QString & text)
//{
//    CSetting::instance().setTheme(text);
//}
