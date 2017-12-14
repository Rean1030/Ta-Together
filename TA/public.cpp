#include "public.h"
#include <QTableWidget>
#include <QAxObject>
#include <qdesktopservices.h>
#include <QFileDialog>
#include <QMessageBox>


ETheme g_eCurTheme = eTheme_default;

//extern const QColor g_readClr = QColor(29, 84, 92, 127);
//extern const QColor g_runClr = QColor(58, 51, 49, 127);
//extern const QColor g_afterClr = QColor(29, 28, 29, 127);
//extern const QColor g_finishClr = QColor(58, 51, 49, 127);

//extern const QColor g_memberBgc    = QColor(146, 208, 80);
//extern const QColor g_mainTaskBgc    = QColor(146, 208, 80);
//extern const QColor g_subTaskBgc     = QColor(146, 208, 80);
//extern const QColor g_plannedTimeBgc = QColor(0, 176, 240);
//extern const QColor g_usedTime       = QColor(155, 194, 230);

//extern const QColor g_memberBgc      = Qt::darkCyan;
//extern const QColor g_mainTaskBgc    = Qt::darkGreen;
//extern const QColor g_subTaskBgc     = Qt::darkGreen;
//extern const QColor g_plannedTimeBgc = Qt::darkMagenta;
//extern const QColor g_usedTime       = Qt::darkCyan;

extern const QColor g_memberBgc[eTheme_Max]      = {
    QColor(146, 208, 80),
    Qt::darkCyan};

extern const QColor g_mainTaskBgc[eTheme_Max]    = {
    QColor(146, 208, 80),
    Qt::darkGreen};

extern const QColor g_subTaskBgc[eTheme_Max]     = {
    QColor(146, 208, 80),
    Qt::darkGreen};

extern const QColor g_plannedTimeBgc[eTheme_Max] = {
    QColor(0, 176, 240),
    Qt::darkMagenta};

extern const QColor g_usedTime[eTheme_Max]       = {
    QColor(155, 194, 230),
    Qt::darkCyan};

QColor g_convertTaskStateToColor(const QString & sTaskState)
{
    QColor clr(Qt::transparent);


    if(QStringLiteral("׼��") == sTaskState)
    {
        clr =  g_eCurTheme == eTheme_default ? Qt::lightGray : Qt::gray;
    }
    else if(QStringLiteral("����") == sTaskState)
    {
        clr = g_eCurTheme == eTheme_default ? Qt::yellow : Qt::darkYellow;
    }
    else if(QStringLiteral("����") == sTaskState)
    {
        clr = g_eCurTheme == eTheme_default ? Qt::magenta : Qt::darkMagenta;
    }
    else if(QStringLiteral("���") == sTaskState)
    {
        clr = g_eCurTheme == eTheme_default ? Qt::green : Qt::darkGreen;
    }

    return clr;
}

void exportQTableWidgetToExcelFile(QTableWidget * table, QString title /*= ""*/)
{
    QString fileName = QFileDialog::getSaveFileName(table, QStringLiteral("����"),
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                    QStringLiteral("Excel �ļ�(*.xls *.xlsx)"));
    if (fileName!="")
    {
        QAxObject *excel = new QAxObject;
        if (excel->setControl("Excel.Application")) //����Excel�ؼ�
        {
            excel->dynamicCall("SetVisible (bool Visible)","false");//����ʾ����
            excel->setProperty("DisplayAlerts", false);//����ʾ�κξ�����Ϣ�����Ϊtrue��ô�ڹر��ǻ�������ơ��ļ����޸ģ��Ƿ񱣴桱����ʾ
            QAxObject *workbooks = excel->querySubObject("WorkBooks");//��ȡ����������
            workbooks->dynamicCall("Add");//�½�һ��������
            QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//��ȡ��ǰ������
            QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
            worksheet->setProperty("Name",title);
            int i,j,colcount=table->columnCount();
            QAxObject *cell,*col;
            //������
            cell=worksheet->querySubObject("Cells(int,int)", 1, 1);
            cell->dynamicCall("SetValue(const QString&)", title);
            cell->querySubObject("Font")->setProperty("Size", 18);
            //�����и�
            worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
            //�ϲ�������
            QString cellTitle;
            cellTitle.append("A1:");
            cellTitle.append(QChar(colcount - 1 + 'A'));
            cellTitle.append(QString::number(1));
            QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);
            range->setProperty("WrapText", true);
            range->setProperty("MergeCells", true);
            range->setProperty("HorizontalAlignment", -4108);//xlCenter
            range->setProperty("VerticalAlignment", -4108);//xlCenter
            //�б���
            for(i=0;i<colcount;i++)
            {
                QString columnName;
                columnName.append(QChar(i  + 'A'));
                columnName.append(":");
                columnName.append(QChar(i + 'A'));
                col = worksheet->querySubObject("Columns(const QString&)", columnName);
                col->setProperty("ColumnWidth", table->columnWidth(i)/6);
                cell=worksheet->querySubObject("Cells(int,int)", 2, i+1);
                columnName=table->horizontalHeaderItem(i)->text();
                cell->dynamicCall("SetValue(const QString&)", columnName);
                cell->querySubObject("Font")->setProperty("Bold", true);
                cell->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
                cell->setProperty("HorizontalAlignment", -4108);//xlCenter
                cell->setProperty("VerticalAlignment", -4108);//xlCenter
            }
            //������
            for(i=0;i<table->rowCount();i++){
                for (j=0;j<colcount;j++)
                {
                    worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", table->item(i,j)?table->item(i,j)->text():"");
                }
            }
            //������
            QString lrange;
            lrange.append("A2:");
            lrange.append(colcount - 1 + 'A');
            lrange.append(QString::number(table->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", lrange);
            range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
            range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
            //�����������и�
            QString rowsName;
            rowsName.append("2:");
            rowsName.append(QString::number(table->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", rowsName);
            range->setProperty("RowHeight", 20);
            workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName));//������fileName
            workbook->dynamicCall("Close()");//�رչ�����
            excel->dynamicCall("Quit()");//�ر�excel
            delete excel;
            excel=NULL;
            if (QMessageBox::question(NULL,QStringLiteral("���"),QStringLiteral("�ļ��Ѿ��������Ƿ����ڴ򿪣�"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
            {
                QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
            }
        }
        else
        {
            QMessageBox::warning(NULL,QStringLiteral("����"), QStringLiteral("δ�ܴ��� Excel �����밲װ Microsoft Excel��"),QMessageBox::Apply);
        }
    }
}



void exportQTableWidgetsToExcelFile(QList<QTableWidget *> tables, QList<QString> sheetNames)
{
    if(tables.count() != sheetNames.count())
    {
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(NULL, QStringLiteral("����"),
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                    QStringLiteral("Excel �ļ�(*.xls *.xlsx)"));
    if (fileName!="")
    {
        QAxObject *excel = new QAxObject;
        if (excel->setControl("Excel.Application")) //����Excel�ؼ�
        {
            excel->dynamicCall("SetVisible (bool Visible)","false");//����ʾ����
            excel->setProperty("DisplayAlerts", false);//����ʾ�κξ�����Ϣ�����Ϊtrue��ô�ڹر��ǻ�������ơ��ļ����޸ģ��Ƿ񱣴桱����ʾ
            QAxObject *workbooks = excel->querySubObject("WorkBooks");//��ȡ����������
            workbooks->dynamicCall("Add");//�½�һ��������
            QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//��ȡ��ǰ������
            QAxObject *worksheets = workbook->querySubObject("Sheets");//��ȡ��������
            for(int sheetIndex = 0; sheetIndex < tables.count(); sheetIndex++)
            {
                QTableWidget *table = tables.at(sheetIndex);
                QAxObject *worksheet = worksheets->querySubObject("Item(int)", sheetIndex+1);
                //��Ҫʱ�����µ�Sheet
                if(worksheet == NULL)
                {
                    worksheet = worksheets->querySubObject("Add()");
                }
                worksheet->setProperty("Name",sheetNames.at(sheetIndex));

                int i,j,colcount=table->columnCount();
                QAxObject *cell,*col;
                //������
                cell=worksheet->querySubObject("Cells(int,int)", 1, 1);
                cell->dynamicCall("SetValue(const QString&)", sheetNames.at(sheetIndex));
                cell->querySubObject("Font")->setProperty("Size", 18);
                //�����и�
                worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
                //�ϲ�������
                QString cellTitle;
                cellTitle.append("A1:");
                cellTitle.append(QChar(colcount - 1 + 'A'));
                cellTitle.append(QString::number(1));
                QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);
                range->setProperty("WrapText", true);
                range->setProperty("MergeCells", true);
                range->setProperty("HorizontalAlignment", -4108);//xlCenter
                range->setProperty("VerticalAlignment", -4108);//xlCenter
                //�б���
                for(i=0;i<colcount;i++)
                {
                    QString columnName;
                    columnName.append(QChar(i  + 'A'));
                    columnName.append(":");
                    columnName.append(QChar(i + 'A'));
                    col = worksheet->querySubObject("Columns(const QString&)", columnName);
                    col->setProperty("ColumnWidth", table->columnWidth(i)/6);
                    cell=worksheet->querySubObject("Cells(int,int)", 2, i+1);
                    columnName=table->horizontalHeaderItem(i)->text();
                    cell->dynamicCall("SetValue(const QString&)", columnName);
                    cell->querySubObject("Font")->setProperty("Bold", true);
                    cell->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
                    cell->setProperty("HorizontalAlignment", -4108);//xlCenter
                    cell->setProperty("VerticalAlignment", -4108);//xlCenter
                }
                //������
                for(i=0;i<table->rowCount();i++){
                    for (j=0;j<colcount;j++)
                    {
                        worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", table->item(i,j)?table->item(i,j)->text():"");
                    }
                }
                //������
                QString lrange;
                lrange.append("A2:");
                lrange.append(colcount - 1 + 'A');
                lrange.append(QString::number(table->rowCount() + 2));
                range = worksheet->querySubObject("Range(const QString&)", lrange);
                range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
                range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
                //�����������и�
                QString rowsName;
                rowsName.append("2:");
                rowsName.append(QString::number(table->rowCount() + 2));
                range = worksheet->querySubObject("Range(const QString&)", rowsName);
                range->setProperty("RowHeight", 20);
            }
            workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName));//������fileName
            workbook->dynamicCall("Close()");//�رչ�����
            excel->dynamicCall("Quit()");//�ر�excel
            delete excel;
            excel=NULL;
            if (QMessageBox::question(NULL,QStringLiteral("���"),QStringLiteral("�ļ��Ѿ��������Ƿ����ڴ򿪣�"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
            {
                QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
            }
        }
        else
        {
            QMessageBox::warning(NULL,QStringLiteral("����"),QStringLiteral("δ�ܴ��� Excel �����밲װ Microsoft Excel��"),QMessageBox::Apply);
        }
    }
}
