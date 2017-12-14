#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T23:17:36
#
#-------------------------------------------------

QT       += network core gui axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TA
TEMPLATE = app

RC_ICONS += TA.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    netserver.cpp \
    fileserver.cpp \
    PersonalTaskState.cpp \
    public.cpp \
    theme/theme.cpp \
    theme/qtcassert.cpp \
    theme/manhattanstyle.cpp \
    theme/stylehelper.cpp \
    configdialog.cpp \
    setting.cpp

HEADERS  += mainwindow.h \
    netserver.h \
    fileserver.h \
    PersonalTaskState.h \
    public.h \
    theme/theme.h \
    theme/theme_p.h \
    theme/qtcassert.h \
    theme/algorithm.h \
    theme/manhattanstyle.h \
    theme/stylehelper.h \
    configdialog.h \
    setting.h

FORMS    += mainwindow.ui \
    configdialog.ui

RESOURCES += \
    TA.qrc
