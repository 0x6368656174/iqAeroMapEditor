#include "iqamelinesegment.h"

IqAmeLineSegment::IqAmeLineSegment(QObject *parent) :
    IqAmeShapeObject(parent),
    m_startPoint(Q_NULLPTR),
    m_endPoint(Q_NULLPTR)
{
    connect(this, &IqAmeLineSegment::startPointChanged, this, &IqAmeLineSegment::updateGraphicsItem);
    connect(this, &IqAmeLineSegment::endPointChanged, this, &IqAmeLineSegment::updateGraphicsItem);
}

IqAmeGeoPoint *IqAmeLineSegment::startPoint() const
{
    return m_startPoint;
}

void IqAmeLineSegment::setStartPoint(IqAmeGeoPoint *startPoint)
{
    if (m_startPoint != startPoint) {
        if (m_startPoint)
            disconnect(m_startPoint, 0, this, 0);

        m_startPoint = startPoint;
        connect(m_startPoint, &IqAmeGeoPoint::glPointChanged, this, &IqAmeLineSegment::updateGraphicsItem);

        emit startPointChanged();
    }
}

IqAmeGeoPoint *IqAmeLineSegment::endPoint() const
{
    return m_endPoint;
}

void IqAmeLineSegment::setEndPoint(IqAmeGeoPoint *endPoint)
{
    if (m_endPoint != endPoint) {
        if (m_endPoint)
            disconnect(m_endPoint, 0, this, 0);

        m_endPoint = endPoint;
        connect(m_endPoint, &IqAmeGeoPoint::glPointChanged, this, &IqAmeLineSegment::updateGraphicsItem);

        emit endPointChanged();
    }
}
