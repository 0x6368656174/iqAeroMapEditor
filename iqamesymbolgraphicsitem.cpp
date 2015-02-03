#include "iqamesymbolgraphicsitem.h"
#include "iqamesymbol.h"
#include "iqameapplication.h"
#include <QBitmap>

QHash<int, QPixmap> IqAmeSymbolGraphicsItem::m_symbolPixmaps;
QHash<int, QPixmap> IqAmeSymbolGraphicsItem::m_selectedSymbolPixmaps;

IqAmeSymbolGraphicsItem::IqAmeSymbolGraphicsItem(QGraphicsItem *parent) :
    QGraphicsItem(parent),
    IqAmeShapeLink(),
    m_symbol(Q_NULLPTR)
{
}

IqAmeSymbolGraphicsItem::~IqAmeSymbolGraphicsItem()
{
}

QRectF IqAmeSymbolGraphicsItem::boundingRect() const
{
    if (IqAmeApplication::mapView()->transform() == m_cacheTransform)
        return m_cacheBoundingRect;

    m_cacheTransform = IqAmeApplication::mapView()->transform();

    Q_CHECK_PTR(m_symbol);

    QPointF center = deviceTransform(m_cacheTransform).map(m_symbol->point()->toGlPoint());
    QTransform inverdedTransform = deviceTransform(m_cacheTransform).inverted();
    qreal a = m_symbol->outputAttributes()->font().pixelSize();

    QPointF topLeft (center.x() - a/2, center.y() - a/2);
    QPointF bottomRight (center.x() + a/2, center.y() + a/2);

    m_cacheBoundingRect = QRectF(inverdedTransform.map(topLeft),
                                 inverdedTransform.map(bottomRight));
    return m_cacheBoundingRect;
}

void IqAmeSymbolGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->drawPixmap(boundingRect().toRect(), symbolPixmap(m_symbol->type(), isSelected()));
}

void IqAmeSymbolGraphicsItem::setSymbol(IqAmeSymbol *symbol)
{
    if (m_symbol != symbol)
        m_symbol = symbol;
}

QPixmap IqAmeSymbolGraphicsItem::symbolPixmap(int number, bool selected)
{
    if (!selected) {
        if (m_symbolPixmaps.contains(number))
            return m_symbolPixmaps[number];
        m_symbolPixmaps[number] = QPixmap(QString("://symbols/%0.png").arg(number));
        return m_symbolPixmaps[number];
    }

    if (m_selectedSymbolPixmaps.contains(number))
        return m_selectedSymbolPixmaps[number];
    QPixmap oldPixmap = symbolPixmap(number);
    QPixmap newPixmap (oldPixmap.size());
    newPixmap.fill(Qt::blue);
    newPixmap.setMask(oldPixmap.createMaskFromColor(Qt::transparent));
    m_selectedSymbolPixmaps[number] = newPixmap;
    return m_selectedSymbolPixmaps[number];
}
