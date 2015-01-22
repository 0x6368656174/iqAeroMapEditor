#ifndef IQAMESUBLINEGRAPHICSITEM_H
#define IQAMESUBLINEGRAPHICSITEM_H

#include <QGraphicsItem>
#include "iqameshapelink.h"

class IqAmeSubLine;
class IqAmeSublineGraphicsItem : public QGraphicsItem, public IqAmeShapeLink
{
public:
    explicit IqAmeSublineGraphicsItem(QGraphicsItem * parent = Q_NULLPTR);

    void updateCache();

public:
    virtual QRectF boundingRect() const Q_DECL_OVERRIDE;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    virtual QPainterPath shape() const Q_DECL_OVERRIDE;

public:
    void setSubLine(IqAmeSubLine *subLine);

private:
    IqAmeSubLine *m_subLine;
    QRectF m_boundingRect;
    QPainterPath m_painterPath;
};

#endif // IQAMESUBLINEGRAPHICSITEM_H
