#ifndef IQAMEGEOPOINT_H
#define IQAMEGEOPOINT_H

#include <QObject>
#include <QPointer>
#include <QPointF>

class IqAmeGeoPoint : public QObject
{
public:
    explicit IqAmeGeoPoint(QObject *parent = 0);

    ~IqAmeGeoPoint();

    enum DefinitionType
    {
        Geo,
        Cartesian,
        Polar
    };

    bool fromString(const QString &string);

    bool fromCoordinate(const QString &coordinate);

public:
    inline QString name() const {return _name;}
    inline void setName(const QString &name) {_name = name;}

    inline DefinitionType definitionType() const {return _definitionType;}
    inline void setDefinitionType(const DefinitionType definitionType) {_definitionType = definitionType; updateGlPointCache();}

    inline qreal latitude() const {return _latitude;}
    inline void setLatitude(const qreal latitude) {_latitude = latitude; updateGlPointCache();}

    inline qreal longitude() const {return _longitude;}
    inline void setLongitude(const qreal longitude) {_longitude = longitude; updateGlPointCache();}

    inline qreal x() const {return _x;}
    inline void setX(const qreal x) {_x = x; updateGlPointCache();}

    inline qreal y() const {return _y;}
    inline void setY(const qreal y) {_y = y; updateGlPointCache();}

    inline qreal angle() const {return _angle;}
    inline void setAngle(const qreal angle) {_angle = angle; updateGlPointCache();}

    inline qreal distance() const {return _distance;}
    inline void setDistance(const qreal distance) {_distance = distance; updateGlPointCache();}

    inline IqAmeGeoPoint * basePoint() const {return _basePoint;}
    void setBasePoint(IqAmeGeoPoint *basePoint);

    QString basePointName() const;

    inline QString comment() const {return _comment;}
    inline void setComment(const QString &comment) {_comment = comment;}

    inline QList<IqAmeGeoPoint *> relativePoints() const {return _relativePoints;}

    inline QPointF toGlPoint() const {return _glPointCache;}

private:
    QString _name;
    DefinitionType _definitionType;
    qreal _latitude;
    qreal _longitude;
    qreal _x;
    qreal _y;
    qreal _angle;
    qreal _distance;
    QPointer<IqAmeGeoPoint> _basePoint;
    QString _basePointName;
    QString _comment;
    QList<IqAmeGeoPoint *> _relativePoints;
    QPointF _glPointCache;

    void updateGlPointCache();
};

#endif // IQAMEGEOPOINT_H
