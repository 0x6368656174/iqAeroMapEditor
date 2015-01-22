#include "iqamelinesegment.h"

IqAmeLineSegment::IqAmeLineSegment(QObject *parent) :
    IqAmeShapeObject(parent),
    m_startPoint(Q_NULLPTR),
    m_endPoint(Q_NULLPTR)
{
}

IqAmeGeoPoint *IqAmeLineSegment::startPoint() const
{
    return m_startPoint;
}

void IqAmeLineSegment::setStartPoint(IqAmeGeoPoint *startPoint)
{
    if (m_startPoint != startPoint) {
        m_startPoint = startPoint;
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
        m_endPoint = endPoint;
        emit endPointChanged();
    }
}
