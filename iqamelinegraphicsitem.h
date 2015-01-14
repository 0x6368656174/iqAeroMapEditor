#ifndef IQAMELINEGRAPHICSITEM_H
#define IQAMELINEGRAPHICSITEM_H

#include <QGraphicsItemGroup>

class IqAmeLine;
class IqAmeLineGraphicsItem : public QGraphicsItemGroup
{
public:
    explicit IqAmeLineGraphicsItem(QGraphicsItem *parent = Q_NULLPTR);

    void updateBoundingRect();

public:
    virtual QRectF boundingRect() const Q_DECL_OVERRIDE;

public:
    void setLine(IqAmeLine *line);

private:
    IqAmeLine *m_line;
    QRectF m_boundingRect;
};

#endif // IQAMELINEGRAPHICSITEM_H
