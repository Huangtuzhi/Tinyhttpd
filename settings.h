#ifndef SETTINGS
#define SETTINGS
#include "common.h"
#include <QVariant>
#include <QSettings>

class Settings
{
public:
    static Settings & instance();
    QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const;
    void setValue(const QString& key, const QVariant& value);

private:
    Settings();
    static Settings* m_instance;

    QSettings* settings;
};

#endif // SETTINGS

