#ifndef IQAMELINESEGMENT_H
#define IQAMELINESEGMENT_H

#include <QObject>
#include "iqamegeopoint.h"
#include <QRectF>
#include "iqlayerview.h"

class IqAmeLineSegment : public QObject
{
    Q_OBJECT
    Q_PROPERTY(IqAmeGeoPoint* startPoint READ startPoint WRITE setStartPoint NOTIFY startPointChanged)
    Q_PROPERTY(IqAmeGeoPoint* endPoint READ endPoint WRITE setEndPoint NOTIFY endPointChanged)

public:
    explicit IqAmeLineSegment(QObject *parent = 0);

    virtual void paintGl(const QRectF &area, IqLayerView *layerView) = 0;

public:
    inline IqAmeGeoPoint *startPoint() const {return _startPoint;}
    void setStartPoint(IqAmeGeoPoint *startPoint);

    inline IqAmeGeoPoint *endPoint() const {return _endPoint;}
    void setEndPoint(IqAmeGeoPoint *endPoint);

signals:
    void startPointChanged();
    void endPointChanged();

private:
    IqAmeGeoPoint *_startPoint;
    IqAmeGeoPoint *_endPoint;
};

#endif // IQAMELINESEGMENT_H
