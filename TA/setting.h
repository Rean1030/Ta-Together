#ifndef SETTING_H
#define SETTING_H

#include <QSettings>
class CSetting
{
public:
    static CSetting& instance();

    QString getCurTheme() const;

    QString getCurThemeEn() const;

    void setTheme(const QString& val);
protected:
    QString convertThemeEnToCh(QString en);
    QString convertThemeChToEn(QString ch);
private:
    CSetting();
    ~CSetting();

    QSettings * m_pSetting;

};

#endif // SETTING_H
