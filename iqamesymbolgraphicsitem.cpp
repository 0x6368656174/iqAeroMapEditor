#include "iqamesymbolgraphicsitem.h"
#include "iqamesymbol.h"
#include "iqameapplication.h"

IqAmeSymbolGraphicsItem::IqAmeSymbolGraphicsItem(QGraphicsItem *parent) :
    QGraphicsSimpleTextItem(parent),
    IqAmeShapeLink(),
    m_symbol(Q_NULLPTR)
{
}

IqAmeSymbolGraphicsItem::~IqAmeSymbolGraphicsItem()
{
}

QRectF IqAmeSymbolGraphicsItem::boundingRect() const
{
    return createPainterPath().boundingRect();
}

void IqAmeSymbolGraphicsItem::updateCache()
{
    QPainterPath newPath;

    Q_CHECK_PTR(m_symbol);
    switch (m_symbol->type()) {
    case IqAmeSymbol::PointRequedReport:
        QPointF top = m_symbol->point()->toGlPoint();
        top.setY(top.y() - 4300);
        QPointF right = m_symbol->point()->toGlPoint();
        right.setX(right.x() + 5000);
        right.setY(right.y() + 4300);
        QPointF left = m_symbol->point()->toGlPoint();
        left.setX(left.x() - 5000);
        left.setY(left.y() + 4300);

        newPath.moveTo(top);
        newPath.lineTo(right);
        newPath.lineTo(left);
        newPath.closeSubpath();

        break;
    }

    m_painterPath = newPath;
    m_boundingRect = m_painterPath.boundingRect();
}

void IqAmeSymbolGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QPen pen = m_symbol->outputAttributes()->pen();
    if (isSelected())
        pen.setColor("blue");

    QBrush brush = QBrush(pen.color());

    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPath(createPainterPath());
}

QPainterPath IqAmeSymbolGraphicsItem::shape() const
{
    return m_painterPath;
}

void IqAmeSymbolGraphicsItem::setSymbol(IqAmeSymbol *symbol)
{
    if (m_symbol != symbol)
        m_symbol = symbol;
}

QPainterPath IqAmeSymbolGraphicsItem::createPainterPath() const
{

    QPainterPath newPath;

    Q_CHECK_PTR(m_symbol);

    QPointF center = deviceTransform(IqAmeApplication::mapView()->transform()).map(m_symbol->point()->toGlPoint());
    QTransform inverdedTransform = deviceTransform(IqAmeApplication::mapView()->transform()).inverted();

    switch (m_symbol->type()) {
    case IqAmeSymbol::PointRequedReport:
        QPointF top = center;
        top.setY(top.y() - 4.3);
        QPointF right = center;
        right.setX(right.x() + 5);
        right.setY(right.y() + 4.3);
        QPointF left = center;
        left.setX(left.x() - 5);
        left.setY(left.y() + 4.3);

        newPath.moveTo(inverdedTransform.map(top));
        newPath.lineTo(inverdedTransform.map(right));
        newPath.lineTo(inverdedTransform.map(left));
        newPath.closeSubpath();

        break;
    }

    return newPath;
}

