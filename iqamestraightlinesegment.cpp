#include "iqamestraightlinesegment.h"
#include "iqameapplication.h"
#include <QtOpenGL>
#include <QDebug>
#include <unistd.h>

IqAmeStraightLineSegment::IqAmeStraightLineSegment(QObject *parent) :
    IqAmeLineSegment(parent),
    m_graphicsItem(Q_NULLPTR)
{
}

IqAmeStraightLineSegment::~IqAmeStraightLineSegment()
{
    if (m_graphicsItem && !m_graphicsItem->parentItem())
        delete m_graphicsItem;
}

QGraphicsLineItem *IqAmeStraightLineSegment::graphicsItem()
{
    if (!m_graphicsItem) {
        if (startPoint() && endPoint() && outputAttributes()) {
            QLineF line (startPoint()->toGlPoint(), endPoint()->toGlPoint());
            m_graphicsItem = IqAmeApplication::graphicsScene()->addLine(line, outputAttributes()->pen());
        }
    }

    return m_graphicsItem;
}

void IqAmeStraightLineSegment::updateGraphicsItem()
{
    QGraphicsLineItem* lineItem = graphicsItem();
    if (lineItem) {
        QLineF line (startPoint()->toGlPoint(), endPoint()->toGlPoint());
        lineItem->setPen(outputAttributes()->pen());
        lineItem->setLine(line);
    }
}

bool IqAmeStraightLineSegment::loadFromString(const QString &string)
{

}

void IqAmeStraightLineSegment::drawSegment(QPainterPath *painterPath) const
{
    painterPath->moveTo(startPoint()->toGlPoint());
    painterPath->lineTo(endPoint()->toGlPoint());
}
