#include "setting.h"
#include "fileserver.h"
#include <QStandardPaths>
#include "public.h"
CSetting &CSetting::instance()
{
     static CSetting setting;
     return setting;
}

QString CSetting::getCurTheme() const
{
    QString ret = m_pSetting->value("Theme/theme","default").toString();

    if(ret.startsWith("flat-dark"))
    {
        ret = QStringLiteral("ǳ��");
    }
    else if(ret.startsWith("dark"))
    {
        ret = QStringLiteral("��ɫ");
    }
    else
    {
        ret = QStringLiteral("Ĭ��");
    }

    return ret;
}

QString CSetting::getCurThemeEn() const
{
    return m_pSetting->value("Theme/theme","default").toString();
}

void CSetting::setTheme(const QString& val)
{
    m_pSetting->setValue("Theme/theme",convertThemeChToEn(val));
}

QString CSetting::convertThemeEnToCh(QString en)//??? cant use?
{
    if(en.startsWith("flat-dark.theme"))
    {
        return QStringLiteral("ǳ��");
    }
    else if(en.startsWith("dark.theme"))
    {
        return QStringLiteral("��ɫ");
    }
    else
    {
        return QStringLiteral("Ĭ��");
    }
}

QString CSetting::convertThemeChToEn(QString ch)
{
    if(ch == QStringLiteral("ǳ��"))
    {
        return "flat-dark.theme";
    }
    else if(ch == QStringLiteral("��ɫ"))
    {
        return "dark.theme";
    }
    else
    {
        return "default.theme";
    }
}

CSetting::CSetting()
{
    m_pSetting = new QSettings(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +"/TaCnfig.ini",QSettings::IniFormat);

    if (m_pSetting->value("Theme/theme","default").toString().contains("dark"))
    {
        g_eCurTheme = eTheme_dark;
    }
}

CSetting::~CSetting()
{
    if(m_pSetting)
    {
        delete m_pSetting;
        m_pSetting;
    }
}
