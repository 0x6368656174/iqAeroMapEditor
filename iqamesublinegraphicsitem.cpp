#include "iqamesublinegraphicsitem.h"
#include "iqamesubline.h"
#include <QDebug>

IqAmeSublineGraphicsItem::IqAmeSublineGraphicsItem(QGraphicsItem *parent) :
    QGraphicsItem(parent),
    IqAmeShapeLink(),
    m_subLine(Q_NULLPTR)
{
}

void IqAmeSublineGraphicsItem::updateCache()
{
    m_painterPath = QPainterPath();

    foreach (IqAmeLineSegment* segment, m_subLine->segments()) {
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

    QPen pen = m_subLine->outputAttributes()->pen();
    if (isSelected())
        pen.setColor("blue");

    painter->setPen(pen);
    painter->drawPath(m_painterPath);
}

QPainterPath IqAmeSublineGraphicsItem::shape() const
{
    return m_painterPath;
}
