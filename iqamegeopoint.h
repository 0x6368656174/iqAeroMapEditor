#ifndef IQAMEGEOPOINT_H
#define IQAMEGEOPOINT_H

#include <QObject>
#include <QPointer>

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

public:
    inline QString name() const {return _name;}
    inline void setName(const QString &name) {_name = name;}

    inline DefinitionType definitionType() const {return _definitionType;}
    inline void setDefinitionType(const DefinitionType definitionType) {_definitionType = definitionType;}

    inline qreal latitude() const {return _latitude;}
    inline void setLatitude(const qreal latitude) {_latitude = latitude;}

    inline qreal longitude() const {return _longitude;}
    inline void setLongitude(const qreal longitude) {_longitude = longitude;}

    inline qreal x() const {return _x;}
    inline void setX(const qreal x) {_x = x;}

    inline qreal y() const {return _y;}
    inline void setY(const qreal y) {_y = y;}

    inline qreal angle() const {return _angle;}
    inline void setAngle(const qreal angle) {_angle = angle;}

    inline qreal distance() const {return _distance;}
    inline void setDistance(const qreal distance) {_distance = distance;}

    inline IqAmeGeoPoint * basePoint() const {return _basePoint;}
    void setBasePoint(IqAmeGeoPoint *basePoint);

    QString basePointName() const;

    inline QString comment() const {return _comment;}
    inline void setComment(const QString &comment) {_comment = comment;}

    inline QList<IqAmeGeoPoint *> relativePoints() const {return _relativePoints;}

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
};

#endif // IQAMEGEOPOINT_H
