#include "settings.h"

Settings* Settings::m_instance = NULL;

Settings::Settings()
{
    settings = new QSettings(CONFIG_FILE, QSettings::IniFormat);
}

Settings& Settings::instance()
{
    if (m_instance == NULL)
        m_instance = new Settings();
    return *m_instance;
}


QVariant Settings::value(const QString& key, const QVariant& defaultValue) const
{
    return settings->value(key, defaultValue);
}

void Settings::setValue(const QString& key, const QVariant& value)
{
    settings->setValue(key, value);
}
