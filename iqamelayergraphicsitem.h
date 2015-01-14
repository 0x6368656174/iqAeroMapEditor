#ifndef IQAMELAYERGRAPHICSITEM_H
#define IQAMELAYERGRAPHICSITEM_H

#include <QGraphicsItemGroup>

class IqAmeLayer;
class IqAmeLayerGraphicsItem : public QGraphicsItemGroup
{
public:
    explicit IqAmeLayerGraphicsItem(QGraphicsItem *parent = Q_NULLPTR);

    void updateBoundingRect();

public:
    virtual QRectF boundingRect() const Q_DECL_OVERRIDE;

public:
    void setLayer(IqAmeLayer *layer);

private:
    IqAmeLayer *m_layer;
    QRectF m_boundingRect;


};

#endif // IQAMELAYERGRAPHICSITEM_H
