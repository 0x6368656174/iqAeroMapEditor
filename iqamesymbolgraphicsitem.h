#ifndef IQAMESYMBOLGRAPHICSITEM_H
#define IQAMESYMBOLGRAPHICSITEM_H

#include <QGraphicsItem>
#include "iqameshapelink.h"

class IqAmeSymbol;
class IqAmeSymbolGraphicsItem : public QGraphicsItem, public IqAmeShapeLink
{
public:
    explicit IqAmeSymbolGraphicsItem(QGraphicsItem *parent = Q_NULLPTR);
    ~IqAmeSymbolGraphicsItem();

public:
    virtual QRectF boundingRect() const Q_DECL_OVERRIDE;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

public:
    void setSymbol(IqAmeSymbol *symbol);

private:
    IqAmeSymbol *m_symbol;
    mutable QRectF m_cacheBoundingRect;
    mutable QTransform m_cacheTransform;

    static QPixmap symbolPixmap(int number, bool selected = false);
    static QHash<int, QPixmap> m_symbolPixmaps;
    static QHash<int, QPixmap> m_selectedSymbolPixmaps;
};

#endif // IQAMESYMBOLGRAPHICSITEM_H
