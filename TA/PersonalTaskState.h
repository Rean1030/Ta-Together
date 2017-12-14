#ifndef PERSONALMISSIONSTATE_H
#define PERSONALMISSIONSTATE_H
#include <QTableWidget>
#include <QJsonObject>
class PersonalTaskState : public QTableWidget
{
public:
    PersonalTaskState(QWidget * parent = 0);
    PersonalTaskState(const QJsonObject&  member, QWidget * parent = 0);

    void setJsonMemberValue(const QJsonObject&  member);

    void updateUi();

    void initUi();
protected:
    QString getToolTip(QJsonObject& subTaskJson);
private:
    QJsonObject m_jMember;

};

#endif // PERSONALMISSIONSTATE_H
