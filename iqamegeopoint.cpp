#include "iqamegeopoint.h"
#include "iqamegeohelper.h"
#include <QRegExp>

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

bool IqAmeGeoPoint::fromString(const QString &string)
{
    QRegExp geoRx ("^(\\S+)\\s+([NS])=(\\d+)\\s+([EW])=(\\d+)\\s*(;\\s*(.*)|\\*(.*)\\*|)$");
    QRegExp cartesianRx ("^(\\S+)(\\s+T=(\\S+)|)\\s+X=(-{0,1}\\d+.{0,1}\\d*)\\s+Y=(-{0,1}\\d+.{0,1}\\d*)\\s*(;\\s*(.*)|\\*(.*)\\*|)$");
    QRegExp polarRx ("^(\\S+)(\\s+T=(\\S+)|)\\s+A=(-{0,1}\\d+)\\s+D=(-{0,1}\\d+.{0,1}\\d*)\\s*(;\\s*(.*)|\\*(.*)\\*|)$");

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
    }
}

QString IqAmeGeoPoint::basePointName() const
{
    if (_basePoint)
        return _basePoint->name();
    return _basePointName;
}
