#include "iqamelinegraphicsitem.h"
#include "iqameline.h"

IqAmeLineGraphicsItem::IqAmeLineGraphicsItem(QGraphicsItem *parent) :
    QGraphicsItemGroup(parent),
    m_line(Q_NULLPTR)
{
}

void IqAmeLineGraphicsItem::updateBoundingRect()
{
    QRectF result;
    QRectF subLineBoundingRect;

    foreach (IqAmeSubLine *subLine, m_line->subLines())
    {
        subLineBoundingRect = subLine->graphicsItem()->boundingRect();
        result = result.united(subLineBoundingRect);
    }

    m_boundingRect = result;
}

QRectF IqAmeLineGraphicsItem::boundingRect() const
{
    return m_boundingRect;
}

void IqAmeLineGraphicsItem::setLine(IqAmeLine *line)
{
    if (m_line != line) {
        m_line = line;
    }
}
