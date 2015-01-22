#include "iqamestraightlinesegment.h"
#include "iqameapplication.h"
#include <QDebug>
#include <unistd.h>

IqAmeStraightLineSegment::IqAmeStraightLineSegment(QObject *parent) :
    IqAmeLineSegment(parent)
{
}

void IqAmeStraightLineSegment::drawSegment(QPainterPath *painterPath) const
{
    painterPath->moveTo(startPoint()->toGlPoint());
    painterPath->lineTo(endPoint()->toGlPoint());
}
