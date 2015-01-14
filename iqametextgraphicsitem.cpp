#include "iqametextgraphicsitem.h"
#include "iqametext.h"
#include <QStyleOptionGraphicsItem>

IqAmeTextGraphicsItem::IqAmeTextGraphicsItem(QGraphicsItem *parent) :
    QGraphicsSimpleTextItem(parent)
{
    setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
}

void IqAmeTextGraphicsItem::updateCache()
{
    QGraphicsSimpleTextItem::setText(m_text->text());
    setFont(m_text->outputAttributes()->font());
    setPos(m_text->point()->toGlPoint());
}

void IqAmeTextGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (option->levelOfDetail < 0.1)
        return;

    QGraphicsSimpleTextItem::paint(painter, option, widget);
}

void IqAmeTextGraphicsItem::setText(IqAmeText *text)
{
    if (m_text != text)
        m_text = text;
}
