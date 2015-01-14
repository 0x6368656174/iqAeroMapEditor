#include "iqamelayergraphicsitem.h"
#include "iqamelayer.h"

IqAmeLayerGraphicsItem::IqAmeLayerGraphicsItem(QGraphicsItem *parent) :
    QGraphicsItemGroup(parent),
    m_layer(Q_NULLPTR)
{
}

void IqAmeLayerGraphicsItem::updateBoundingRect()
{
    QRectF result;
    QRectF subLineBoundingRect;

    foreach (IqAmeShapeObject *shapeObject, m_layer->shapesModel()->toList())
    {
        subLineBoundingRect = shapeObject->graphicsItem()->boundingRect();
        result = result.united(subLineBoundingRect);
    }

    m_boundingRect = result;
}

QRectF IqAmeLayerGraphicsItem::boundingRect() const
{
    return m_boundingRect;
}

void IqAmeLayerGraphicsItem::setLayer(IqAmeLayer *layer)
{
    if (m_layer != layer) {
        m_layer = layer;
    }
}
