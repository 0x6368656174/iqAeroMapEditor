#include "iqamesublinegraphicsitem.h"
#include "iqamesubline.h"

IqAmeSublineGraphicsItem::IqAmeSublineGraphicsItem(QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_subLine(Q_NULLPTR)
{
}

void IqAmeSublineGraphicsItem::updateCache()
{
    m_painterPath = QPainterPath();

    foreach (IqAmeLineSegment* segment, m_subLine->segments())
    {
        segment->drawSegment(&m_painterPath);
    }

    m_boundingRect = m_painterPath.boundingRect();
}

void IqAmeSublineGraphicsItem::setSubLine(IqAmeSubLine *subLine)
{
    if (m_subLine != subLine) {
        m_subLine = subLine;
    }
}

QRectF IqAmeSublineGraphicsItem::boundingRect() const
{
    return m_boundingRect;
}

void IqAmeSublineGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(m_subLine->outputAttributes()->pen());
    painter->drawPath(m_painterPath);
}
