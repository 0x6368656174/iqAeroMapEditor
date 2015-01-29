#ifndef IQAMESYMBOLGRAPHICSITEM_H
#define IQAMESYMBOLGRAPHICSITEM_H

#include <QGraphicsSimpleTextItem>
#include "iqameshapelink.h"

class IqAmeSymbol;
class IqAmeSymbolGraphicsItem : public QGraphicsSimpleTextItem, public IqAmeShapeLink
{
public:
    explicit IqAmeSymbolGraphicsItem(QGraphicsItem *parent = Q_NULLPTR);
    ~IqAmeSymbolGraphicsItem();

    void updateCache();

public:
    virtual QRectF boundingRect() const Q_DECL_OVERRIDE;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    virtual QPainterPath shape() const Q_DECL_OVERRIDE;

public:
    void setSymbol(IqAmeSymbol *symbol);

private:
    QPainterPath createPainterPath() const;

private:
    IqAmeSymbol *m_symbol;
    QPainterPath m_painterPath;
    QRectF m_boundingRect;
};

#endif // IQAMESYMBOLGRAPHICSITEM_H
