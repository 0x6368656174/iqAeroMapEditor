#include "iqamegeopoint.h"
#include "iqamegeohelper.h"
#include <QRegExp>
#include <QDebug>

IqAmeGeoPoint::IqAmeGeoPoint(QObject *parent):
    QObject(parent),
    m_name(""),
    m_definitionType(Geo),
    m_latitude(0.0),
    m_longitude(0.0),
    m_x(0.0),
    m_y(0.0),
    m_angle(0.0),
    m_distance(0.0),
    m_basePoint(Q_NULLPTR),
    m_basePointName(""),
    m_comment("")
{
}

IqAmeGeoPoint::~IqAmeGeoPoint()
{
    if (m_basePoint)
        m_basePoint->m_relativePoints.removeOne(this);
}

bool IqAmeGeoPoint::fromCoordinate(const QString &coordinate)
{
    QRegExp coordinateRx("([NS])([^EW]+)([EW])([^\\W]+)");
//    coordinateRx.setCaseSensitivity(Qt::CaseInsensitive);
    if (coordinateRx.indexIn(coordinate) != -1) {
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

QString IqAmeGeoPoint::name() const
{
    return m_name;
}

void IqAmeGeoPoint::setName(const QString &name)
{
    if (m_name != name)
        m_name = name;
}

IqAmeGeoPoint::DefinitionType IqAmeGeoPoint::definitionType() const
{
    return m_definitionType;
}

void IqAmeGeoPoint::setDefinitionType(IqAmeGeoPoint::DefinitionType definitionType)
{
    if (m_definitionType != definitionType) {
        m_definitionType = definitionType;
        updateGlPointCache();
    }
}

qreal IqAmeGeoPoint::latitude() const
{
    return m_latitude;
}

void IqAmeGeoPoint::setLatitude(qreal latitude)
{
    if (m_latitude != latitude) {
        m_latitude = latitude;
        updateGlPointCache();
    }
}

qreal IqAmeGeoPoint::longitude() const
{
    return m_longitude;
}

void IqAmeGeoPoint::setLongitude(qreal longitude)
{
    if (m_longitude != longitude) {
        m_longitude = longitude;
        updateGlPointCache();
    }
}

qreal IqAmeGeoPoint::x() const
{
    return m_x;
}

void IqAmeGeoPoint::setX(qreal x)
{
    if (m_x != x) {
        m_x = x;
        updateGlPointCache();
    }
}

qreal IqAmeGeoPoint::y() const
{
    return m_y;
}

void IqAmeGeoPoint::setY(qreal y)
{
    if (m_y != y) {
        m_y = y;
        updateGlPointCache();
    }
}

qreal IqAmeGeoPoint::angle() const
{
    return m_angle;
}

void IqAmeGeoPoint::setAngle(qreal angle)
{
    if (m_angle != angle) {
        m_angle = angle;
        updateGlPointCache();
    }
}

qreal IqAmeGeoPoint::distance() const
{
    return m_distance;
}

void IqAmeGeoPoint::setDistance(qreal distance)
{
    if (m_distance != distance) {
        m_distance = distance;
        updateGlPointCache();
    }
}

IqAmeGeoPoint *IqAmeGeoPoint::basePoint() const
{
    return m_basePoint;
}

bool IqAmeGeoPoint::fromString(const QString &string)
{
    QRegExp geoRx ("^\\W*(\\S+)\\W+([NS])=(\\d+)\\W+([EW])=(\\d+)\\W*(;\\W*(.*)|\\*(.*)\\*|)$");
//    geoRx.setCaseSensitivity(Qt::CaseInsensitive);
    QRegExp cartesianRx ("^\\W*(\\S+)(\\W+T=(\\S+)|)\\W+X=(-{0,1}\\d+.{0,1}\\d*)\\W+Y=(-{0,1}\\d+.{0,1}\\d*)\\W*(;\\W*(.*)|\\*(.*)\\*|)$");
//    cartesianRx.setCaseSensitivity(Qt::CaseInsensitive);
    QRegExp polarRx ("^\\W*(\\S+)(\\W+T=(\\S+)|)\\W+A=(-{0,1}\\d+)\\W+D=(-{0,1}\\d+.{0,1}\\d*)\\W*(;\\W*(.*)|\\*(.*)\\*|)$");
//    polarRx.setCaseSensitivity(Qt::CaseInsensitive);

    if (geoRx.indexIn(string) != -1) {
        setDefinitionType(Geo);
        setName(geoRx.cap(1));

        setX(0);
        setY(0);
        setAngle(0);
        setDistance(0);
        setBasePoint(NULL);
        m_basePointName = "";

        QString coordinateStr = geoRx.cap(2) + geoRx.cap(3) + geoRx.cap(4) + geoRx.cap(5);

        qreal lat, lon;

        if (!IqAmeGeoHelper::coordinateFromString(coordinateStr, lat, lon))
            return false;

        setLatitude(lat);
        setLongitude(lon);
        if (!geoRx.cap(6).isEmpty()) {
            if (!geoRx.cap(7).isEmpty()) {
                setComment(geoRx.cap(7));
            } else if (!geoRx.cap(8).isEmpty()) {
                setComment(geoRx.cap(8));
            }
        }

        return true;
    } else if (cartesianRx.indexIn(string) != -1) {
        setDefinitionType(Cartesian);
        setName(cartesianRx.cap(1));

        setLatitude(0);
        setLongitude(0);
        setAngle(0);
        setDistance(0);
        setBasePoint(NULL);

        if (cartesianRx.cap(2) != "") {
            m_basePointName = cartesianRx.cap(3);
        } else {
            m_basePointName = "";
        }

        setX(cartesianRx.cap(4).toDouble());
        setY(cartesianRx.cap(5).toDouble());
        if (!cartesianRx.cap(7).isEmpty()) {
            if (!cartesianRx.cap(8).isEmpty()) {
                setComment(cartesianRx.cap(8));
            } else if (!cartesianRx.cap(9).isEmpty()) {
                setComment(cartesianRx.cap(9));
            }
        }
        return true;
    } else if (polarRx.indexIn(string) != -1) {
        setDefinitionType(Polar);
        setName(polarRx.cap(1));

        setLatitude(0);
        setLongitude(0);
        setX(0);
        setY(0);
        setBasePoint(NULL);


        if (polarRx.cap(2) != "") {
            m_basePointName = polarRx.cap(3);
        } else {
            m_basePointName = "";
        }


        setAngle(polarRx.cap(4).toDouble());
        setDistance(polarRx.cap(5).toDouble());
        if (!polarRx.cap(7).isEmpty()) {
            if (!polarRx.cap(8).isEmpty()) {
                setComment(polarRx.cap(8));
            } else if (!polarRx.cap(9).isEmpty()) {
                setComment(polarRx.cap(9));
            }
        }

        return true;
    }

    return false;
}

void IqAmeGeoPoint::setBasePoint(IqAmeGeoPoint *basePoint)
{
    if (m_basePoint != basePoint) {
        if (m_basePoint)
            m_basePoint->m_relativePoints.removeOne(this);

        m_basePoint = basePoint;
        m_basePointName.clear();

        m_basePoint->m_relativePoints << this;

        updateGlPointCache();
    }
}

QString IqAmeGeoPoint::basePointName() const
{
    if (m_basePoint)
        return m_basePoint->name();
    return m_basePointName;
}

QString IqAmeGeoPoint::comment() const
{
    return m_comment;
}

void IqAmeGeoPoint::setComment(const QString &comment)
{
    if (m_comment != comment)
        m_comment = comment;
}

QList<IqAmeGeoPoint *> IqAmeGeoPoint::relativePoints() const
{
    return m_relativePoints;
}

QPointF IqAmeGeoPoint::toGlPoint() const
{
    return m_glPointCache;
}

void IqAmeGeoPoint::updateGlPointCache()
{
    QPointF result;
    switch (definitionType()) {
    case Cartesian: {
        result.setX(x()*1000);
        result.setY(-y()*1000);
        break;
    }
    case Geo: {
        qreal x, y, z;
        IqAmeGeoHelper::toLocalCartesian(latitude(), longitude(), 0, x, y, z);

        result.setX(x);
        result.setY(-y);
        break;
    }
    }

    if (m_glPointCache != result) {
        m_glPointCache = result;
        emit glPointChanged();
    }
}
