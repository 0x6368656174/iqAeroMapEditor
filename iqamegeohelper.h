#ifndef IQAMEGEOHELPER_H
#define IQAMEGEOHELPER_H

#include <QObject>
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/LocalCartesian.hpp>

using namespace GeographicLib;

class IqAmeGeoHelper
{
public:
    IqAmeGeoHelper();

    void setLocalCartesianOrigin(const qreal latitude, const qreal longitude);

    void toLocalCartesian(const qreal latitude, const qreal longitude, const qreal altitude, qreal &x, qreal &y, qreal &z);

    static bool coordinateFromString(const QString &string, qreal &latitude, qreal &longitude);

    static bool latitudeFromString(const QString &string, qreal &latitude);

    static bool longitudeFromString(const QString &string, qreal &longitude);

    static QString coordinateToString(const qreal latitude, const qreal longitude);

    static QString latitudeToString(const qreal latitude, bool pretty = false);

    static QString longitudeToString(const qreal longitude, bool pretty = false);

private:
    LocalCartesian _localCartesian;
};

#endif // IQAMEGEOHELPER_H
