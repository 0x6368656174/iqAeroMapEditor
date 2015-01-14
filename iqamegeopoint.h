#ifndef IQAMEGEOPOINT_H
#define IQAMEGEOPOINT_H

#include <QObject>
#include <QPointer>
#include <QPointF>

class IqAmeGeoPoint : public QObject
{
    Q_OBJECT
public:
    enum DefinitionType
    {
        Geo,
        Cartesian,
        Polar
    };

    explicit IqAmeGeoPoint(QObject *parent = Q_NULLPTR);

    ~IqAmeGeoPoint();

    bool fromString(const QString &string);

    bool fromCoordinate(const QString &coordinate);

public:
    QString name() const;
    void setName(const QString &name);

    DefinitionType definitionType() const;
    void setDefinitionType(DefinitionType definitionType);

    qreal latitude() const;
    void setLatitude(qreal latitude);

    qreal longitude() const;
    void setLongitude(qreal longitude);

    qreal x() const;
    void setX(qreal x);

    qreal y() const;
    void setY(qreal y);

    qreal angle() const;
    void setAngle(qreal angle);

    qreal distance() const;
    void setDistance(qreal distance);

    IqAmeGeoPoint *basePoint() const;
    void setBasePoint(IqAmeGeoPoint *basePoint);

    QString basePointName() const;

    QString comment() const;
    void setComment(const QString &comment);

    QList<IqAmeGeoPoint *> relativePoints() const;

    QPointF toGlPoint() const;

signals:
    void glPointChanged();

private:
    void updateGlPointCache();

private:
    QString m_name;
    DefinitionType m_definitionType;
    qreal m_latitude;
    qreal m_longitude;
    qreal m_x;
    qreal m_y;
    qreal m_angle;
    qreal m_distance;
    QPointer<IqAmeGeoPoint> m_basePoint;
    QString m_basePointName;
    QString m_comment;
    QList<IqAmeGeoPoint *> m_relativePoints;
    QPointF m_glPointCache;
};

#endif // IQAMEGEOPOINT_H
