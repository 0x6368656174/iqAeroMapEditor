#include "iqametextgraphicsitem.h"
#include "iqametext.h"
#include <QStyleOptionGraphicsItem>

IqAmeTextGraphicsItem::IqAmeTextGraphicsItem(QGraphicsItem *parent) :
    QGraphicsSimpleTextItem(parent),
    IqAmeShapeLink()
{
    setFlag(ItemIgnoresTransformations, true);
}

void IqAmeTextGraphicsItem::updateCache()
{
    Q_CHECK_PTR(m_text);
    QGraphicsSimpleTextItem::setText(m_text->text());

    Q_CHECK_PTR(m_text->outputAttributes());
    setFont(m_text->outputAttributes()->font());

    Q_CHECK_PTR(m_text->point());
    setPos(m_text->point()->toGlPoint());
}

void IqAmeTextGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (option->levelOfDetail < 0.1)
        return;

    if (isSelected())
        setBrush(QBrush("blue"));
    else
        setBrush(QBrush("white"));

    QStyleOptionGraphicsItem myOption (*option);
    if (option->state & QStyle::State_Selected)
        myOption.state = option->state ^ QStyle::State_Selected;
    QGraphicsSimpleTextItem::paint(painter, &myOption, widget);
}

void IqAmeTextGraphicsItem::setText(IqAmeText *text)
{
    if (m_text != text)
        m_text = text;
}
