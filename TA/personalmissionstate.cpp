#include "personalmissionstate.h"
#include <QHeaderView>

PersonalMissionState::PersonalMissionState(QWidget * parent/* = 0*/)
 : QTableWidget(parent)
{
    setRowCount(4);
    setColumnCount(1);
    setColumnWidth(0,200);

    QTableWidgetItem * item = new QTableWidgetItem(QStringLiteral("沈宝成"));
    setItem(0,0,item);

    item = new QTableWidgetItem(QStringLiteral("进行中"));
    item->setBackgroundColor(Qt::yellow);
    setItem(0,1,item);

    item = new QTableWidgetItem(QStringLiteral("Start:2017-12-01 08:00:00"));
    setItem(0,2,item);

    item = new QTableWidgetItem(QStringLiteral("End:2017-12-02 18:00:00"));
    setItem(0,3,item);

    horizontalHeader()->hide();
    verticalHeader()->hide();
}

void PersonalMissionState::setMissionName(const QString &val)
{

}

QString PersonalMissionState::getMissionName() const
{
    return "";
}

void PersonalMissionState::setMissionState()
{

}

void PersonalMissionState::getMissionState() const
{

}

void PersonalMissionState::setMissionTime(QString start, QString end)
{

}

