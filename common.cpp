#include "common.h"
#include <QLocale>

QString Common::getTimeStampString(QDateTime datetime)
{
    static QLocale english_locale(QLocale::English);
    return english_locale.toString(datetime, "ddd, d MMM yyyy hh:mm:SS") + " GMT";
}
