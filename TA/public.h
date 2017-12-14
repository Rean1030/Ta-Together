#ifndef _PUBLIC_H_
#define _PUBLIC_H_
#include <QString>
#include <QColor>

class QTableWidget;

enum ETheme
{
    eTheme_default = 0,
    eTheme_dark,
    eTheme_Max
};

extern ETheme g_eCurTheme;

extern const QColor g_memberBgc[]     ;
extern const QColor g_mainTaskBgc[]   ;
extern const QColor g_subTaskBgc[]    ;
extern const QColor g_plannedTimeBgc[];
extern const QColor g_usedTime[]      ;

QColor g_convertTaskStateToColor(const QString & sTaskState);

//保存单个QTableWidget到一个Excel中
void exportQTableWidgetToExcelFile(QTableWidget * table, QString title = "");
//保存多个QTableWidget到一个Excel中
void exportQTableWidgetsToExcelFile(QList<QTableWidget *> tables, QList<QString> sheetNames);

#endif // PUBLIC_H
