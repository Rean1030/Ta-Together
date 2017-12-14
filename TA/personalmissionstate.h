#ifndef PERSONALMISSIONSTATE_H
#define PERSONALMISSIONSTATE_H
#include <QTableWidget>

class PersonalMissionState : public QTableWidget
{
public:
    PersonalMissionState(QWidget * parent = 0);

    void setMissionName(const QString & val);

    QString getMissionName() const;

    void setMissionState();

    void getMissionState() const;

    void setMissionTime(QString start, QString end);
};

#endif // PERSONALMISSIONSTATE_H
