#include "iqamegeohelper.h"
#include <math.h>
#include <QRegExp>

IqAmeGeoHelper::IqAmeGeoHelper()
{
}

void IqAmeGeoHelper::setLocalCartesianOrigin(const qreal latitude, const qreal longitude)
{
    _localCartesian = LocalCartesian(latitude, longitude, 0);
}

void IqAmeGeoHelper::toLocalCartesian(const qreal latitude, const qreal longitude, const qreal altitude,  qreal &x, qreal &y, qreal &z)
{
    _localCartesian.Forward(latitude, longitude, altitude, x, y, z);
}

bool IqAmeGeoHelper::coordinateFromString(const QString &string, qreal &latitude, qreal &longitude)
{
    QRegExp coordRX ("([NS])(-{0,1})(\\d{2})(\\d{2})(\\d{2})(\\d*)\\s*([WE])(-{0,1})(\\d{3})(\\d{2})(\\d{2})(\\d*)");
    if (coordRX.indexIn(string) != -1)
    {
        latitude = coordRX.cap(3).toDouble() + coordRX.cap(4).toDouble()/60 + coordRX.cap(5).toDouble()/3600 + coordRX.cap(6).toDouble()/360000;
        if (coordRX.cap(1) == "S")
            latitude = -latitude;
        if (coordRX.cap(2) == "-")
            latitude = -latitude;
        longitude = coordRX.cap(9).toDouble() + coordRX.cap(10).toDouble()/60 + coordRX.cap(11).toDouble()/3600 + coordRX.cap(12).toDouble()/360000;
        if (coordRX.cap(7) == "W")
            longitude = -longitude;
        if (coordRX.cap(8) == "-")
            longitude = -longitude;

        return true;
    }

    return false;
}

bool IqAmeGeoHelper::latitudeFromString(const QString &string, qreal &latitude)
{
    QRegExp coordRX ("([NS])(-{0,1})(\\d{2})(\\d{2})(\\d{2})(\\d*)");
    if (coordRX.indexIn(string) != -1)
    {
        latitude = coordRX.cap(3).toDouble() + coordRX.cap(4).toDouble()/60 + coordRX.cap(5).toDouble()/3600 + coordRX.cap(6).toDouble()/360000;
        if (coordRX.cap(1) == "S")
            latitude = -latitude;
        if (coordRX.cap(2) == "-")
            latitude = -latitude;

        return true;
    }

    return false;
}

bool IqAmeGeoHelper::longitudeFromString(const QString &string, qreal &longitude)
{
    QRegExp coordRX ("([WE])(-{0,1})(\\d{3})(\\d{2})(\\d{2})(\\d*)");
    if (coordRX.indexIn(string) != -1)
    {
        longitude = coordRX.cap(3).toDouble() + coordRX.cap(4).toDouble()/60 + coordRX.cap(5).toDouble()/3600 + coordRX.cap(6).toDouble()/360000;
        if (coordRX.cap(1) == "W")
            longitude = -longitude;
        if (coordRX.cap(2) == "-")
            longitude = -longitude;

        return true;
    }

    return false;
}

QString IqAmeGeoHelper::coordinateToString(const qreal latitude, const qreal longitude)
{
    return latitudeToString(latitude) + longitudeToString(longitude);
}

QString IqAmeGeoHelper::latitudeToString(const qreal latitude, bool pretty)
{
    qreal absLat = fabs(latitude);

    int latGr = absLat;
    int latMin = (absLat - latGr)*60;
    int latSec = ((absLat - latGr)*60 - latMin)*60;
    int latMSec = floor((((absLat - latGr)*60 - latMin)*60 - latSec)*100 + 0.5);

    if (latMSec == 100)
    {
        latSec++;
        latMSec = 0;
    }

    QString result;
    if (latitude > 0)
    {
        result += "N";
    }
    else
    {
        result += "S";
    }

    if (!pretty)
    {
        result += QString("%0%1%2%3")
                .arg(latGr, 2, 'f', 0, '0')
                .arg(latMin, 2, 'f', 0, '0')
                .arg(latSec, 2, 'f', 0, '0')
                .arg(latMSec, 2, 'f', 0, '0');
    }
    else
    {
        result += QString("%0%1%2'%3.%4\"")
                .arg(latGr, 2, 'f', 0, '0')
                .arg(QChar(0xB0))
                .arg(latMin, 2, 'f', 0, '0')
                .arg(latSec, 2, 'f', 0, '0')
                .arg(latMSec, 2, 'f', 0, '0');
    }

    return result;
}

QString IqAmeGeoHelper::longitudeToString(const qreal longitude, bool pretty)
{
    qreal absLon = fabs(longitude);

    int lonGr = absLon;
    int lonMin = (absLon - lonGr)*60;
    int lonSec = ((absLon - lonGr)*60 - lonMin)*60;
    int lonMSec = floor((((absLon - lonGr)*60 - lonMin)*60 - lonSec)*100 + 0.5);

    if (lonMSec == 100)
    {
        lonSec++;
        lonMSec = 0;
    }

    QString result;
    if (longitude > 0)
    {
        result += "E";
    }
    else
    {
        result += "W";
    }

    if (!pretty)
    {
    result += QString("%0%1%2%3")
            .arg(lonGr, 3, 'f', 0, '0')
            .arg(lonMin, 2, 'f', 0, '0')
            .arg(lonSec, 2, 'f', 0, '0')
            .arg(lonMSec, 2, 'f', 0, '0');
    }
    else
    {
        result += QString("%0%1%2'%3.%4\"")
                .arg(lonGr, 3, 'f', 0, '0')
                .arg(QChar(0xB0))
                .arg(lonMin, 2, 'f', 0, '0')
                .arg(lonSec, 2, 'f', 0, '0')
                .arg(lonMSec, 2, 'f', 0, '0');
    }

    return result;

}
