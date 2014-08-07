#include "iqamegeopoint.h"
#include "iqamegeohelper.h"
#include <QRegExp>
#include <QDebug>

IqAmeGeoPoint::IqAmeGeoPoint(QObject *parent):
    QObject(parent),
    _name(""),
    _definitionType(Geo),
    _latitude(0.0),
    _longitude(0.0),
    _x(0.0),
    _y(0.0),
    _angle(0.0),
    _distance(0.0),
    _basePoint(NULL),
    _basePointName(""),
    _comment("")
{
}

IqAmeGeoPoint::~IqAmeGeoPoint()
{
    if (_basePoint)
        _basePoint->_relativePoints.removeOne(this);
}

bool IqAmeGeoPoint::fromCoordinate(const QString &coordinate)
{
    QRegExp coordinateRx("([NS])([^EW]+)([EW])([^\\W]+)");
//    coordinateRx.setCaseSensitivity(Qt::CaseInsensitive);
    if (coordinateRx.indexIn(coordinate) != -1)
    {
        QString pointString = QString("%0 %1=%2 %3=%4")
                .arg(coordinate.trimmed())
                .arg(coordinateRx.cap(1).toUpper())
                .arg(coordinateRx.cap(2))
                .arg(coordinateRx.cap(3).toUpper())
                .arg(coordinateRx.cap(4));

        return fromString(pointString.trimmed());
    }
    return false;
}

bool IqAmeGeoPoint::fromString(const QString &string)
{
    QRegExp geoRx ("^\\W*(\\S+)\\W+([NS])=(\\d+)\\W+([EW])=(\\d+)\\W*(;\\W*(.*)|\\*(.*)\\*|)$");
//    geoRx.setCaseSensitivity(Qt::CaseInsensitive);
    QRegExp cartesianRx ("^\\W*(\\S+)(\\W+T=(\\S+)|)\\W+X=(-{0,1}\\d+.{0,1}\\d*)\\W+Y=(-{0,1}\\d+.{0,1}\\d*)\\W*(;\\W*(.*)|\\*(.*)\\*|)$");
//    cartesianRx.setCaseSensitivity(Qt::CaseInsensitive);
    QRegExp polarRx ("^\\W*(\\S+)(\\W+T=(\\S+)|)\\W+A=(-{0,1}\\d+)\\W+D=(-{0,1}\\d+.{0,1}\\d*)\\W*(;\\W*(.*)|\\*(.*)\\*|)$");
//    polarRx.setCaseSensitivity(Qt::CaseInsensitive);

    if (geoRx.indexIn(string) != -1)
    {
        setDefinitionType(Geo);
        setName(geoRx.cap(1));

        setX(0);
        setY(0);
        setAngle(0);
        setDistance(0);
        setBasePoint(NULL);
        _basePointName = "";

        QString coordinateStr = geoRx.cap(2) + geoRx.cap(3) + geoRx.cap(4) + geoRx.cap(5);

        qreal lat, lon;

        if (!IqAmeGeoHelper::coordinateFromString(coordinateStr, lat, lon))
            return false;

        setLatitude(lat);
        setLongitude(lon);
        if (!geoRx.cap(6).isEmpty())
        {
            if (!geoRx.cap(7).isEmpty())
            {
                setComment(geoRx.cap(7));
            }
            else if (!geoRx.cap(8).isEmpty())
            {
                setComment(geoRx.cap(8));
            }
        }

        return true;
    }
    else if (cartesianRx.indexIn(string) != -1)
    {
        setDefinitionType(Cartesian);
        setName(cartesianRx.cap(1));

        setLatitude(0);
        setLongitude(0);
        setAngle(0);
        setDistance(0);
        setBasePoint(NULL);

        if (cartesianRx.cap(2) != "")
        {
            _basePointName = cartesianRx.cap(3);
        }
        else
        {
            _basePointName = "";
        }

        setX(cartesianRx.cap(4).toDouble());
        setY(cartesianRx.cap(5).toDouble());
        if (!cartesianRx.cap(7).isEmpty())
        {
            if (!cartesianRx.cap(8).isEmpty())
            {
                setComment(cartesianRx.cap(8));
            }
            else if (!cartesianRx.cap(9).isEmpty())
            {
                setComment(cartesianRx.cap(9));
            }
        }
        return true;
    }
    else if (polarRx.indexIn(string) != -1)
    {
        setDefinitionType(Polar);
        setName(polarRx.cap(1));

        setLatitude(0);
        setLongitude(0);
        setX(0);
        setY(0);
        setBasePoint(NULL);


        if (polarRx.cap(2) != "")
        {
            _basePointName = polarRx.cap(3);
        }
        else
        {
            _basePointName = "";
        }


        setAngle(polarRx.cap(4).toDouble());
        setDistance(polarRx.cap(5).toDouble());
        if (!polarRx.cap(7).isEmpty())
        {
            if (!polarRx.cap(8).isEmpty())
            {
                setComment(polarRx.cap(8));
            }
            else if (!polarRx.cap(9).isEmpty())
            {
                setComment(polarRx.cap(9));
            }
        }

        return true;
    }

    return false;
}

void IqAmeGeoPoint::setBasePoint(IqAmeGeoPoint *basePoint)
{
    if (_basePoint != basePoint)
    {
        if (_basePoint)
            _basePoint->_relativePoints.removeOne(this);

        _basePoint = basePoint;
        _basePointName.clear();

        _basePoint->_relativePoints << this;

        updateGlPointCache();
    }
}

QString IqAmeGeoPoint::basePointName() const
{
    if (_basePoint)
        return _basePoint->name();
    return _basePointName;
}

void IqAmeGeoPoint::updateGlPointCache()
{
    QPointF result;
    switch (definitionType())
    {
    case Cartesian:
    {
        result.setX(x()*1000);
        result.setY(y()*1000);
        break;
    }
    case Geo:
    {
        qreal x, y, z;
        IqAmeGeoHelper::toLocalCartesian(latitude(), longitude(), 0, x, y, z);

        result.setX(x);
        result.setY(y);
        break;
    }
    }

    _glPointCache = result;
}
