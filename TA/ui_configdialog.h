/********************************************************************************
** Form generated from reading UI file 'configdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGDIALOG_H
#define UI_CONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *themeBox;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(260, 84);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        themeBox = new QComboBox(Dialog);
        themeBox->setObjectName(QStringLiteral("themeBox"));

        horizontalLayout->addWidget(themeBox);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        okBtn = new QPushButton(Dialog);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setMaximumSize(QSize(75, 20));

        horizontalLayout_3->addWidget(okBtn);

        cancelBtn = new QPushButton(Dialog);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMaximumSize(QSize(75, 20));

        horizontalLayout_3->addWidget(cancelBtn);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "\350\256\276\347\275\256", 0));
        label->setText(QApplication::translate("Dialog", "\344\270\273\351\242\230\357\274\232", 0));
        themeBox->clear();
        themeBox->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\351\273\230\350\256\244", 0)
         << QApplication::translate("Dialog", "\351\273\221\350\211\262", 0)
        );
        label_2->setText(QApplication::translate("Dialog", "\357\274\210\351\207\215\345\220\257\347\224\237\346\225\210\357\274\211", 0));
        okBtn->setText(QApplication::translate("Dialog", "\347\241\256\350\256\244", 0));
        cancelBtn->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDIALOG_H
