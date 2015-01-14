#ifndef IQAMELINESEGMENT_H
#define IQAMELINESEGMENT_H

#include "iqameshapeobject.h"
#include "iqamegeopoint.h"
#include <QRectF>
#include <QGraphicsItem>
#include "iqlayerview.h"

class IqAmeLineSegment : public IqAmeShapeObject
{
    Q_OBJECT
    Q_PROPERTY(IqAmeGeoPoint * startPoint READ startPoint WRITE setStartPoint NOTIFY startPointChanged)
    Q_PROPERTY(IqAmeGeoPoint * endPoint READ endPoint WRITE setEndPoint NOTIFY endPointChanged)

public:
    explicit IqAmeLineSegment(QObject *parent = 0);

    virtual void drawSegment(QPainterPath *painterPath) const = 0;

public:
    IqAmeGeoPoint *startPoint() const;
    void setStartPoint(IqAmeGeoPoint *startPoint);

    IqAmeGeoPoint *endPoint() const;
    void setEndPoint(IqAmeGeoPoint *endPoint);

signals:
    void startPointChanged();
    void endPointChanged();

private:
    IqAmeGeoPoint *m_startPoint;
    IqAmeGeoPoint *m_endPoint;
};

#endif // IQAMELINESEGMENT_H
