#include "iqamelinesegment.h"

IqAmeLineSegment::IqAmeLineSegment(QObject *parent) :
    QObject(parent),
    _startPoint(NULL),
    _endPoint(NULL)
{
}


void IqAmeLineSegment::setStartPoint(IqAmeGeoPoint *startPoint)
{
    if (_startPoint != startPoint)
    {
        _startPoint = startPoint;

        emit startPointChanged();
    }
}

void IqAmeLineSegment::setEndPoint(IqAmeGeoPoint *endPoint)
{
    if (_endPoint != endPoint)
    {
        _endPoint = endPoint;

        emit endPointChanged();
    }
}
