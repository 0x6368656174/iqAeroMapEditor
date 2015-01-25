#define SCALE_STEP 0.2

#include "iqlayerview.h"
#include <QDebug>
#include "iqamelayer.h"
#include "iqamegeohelper.h"
#include "iqameapplication.h"
#include <QScrollBar>

using namespace GeographicLib;

IqLayerView::IqLayerView(QWidget *parent) :
    QGraphicsView(parent),
    m_pan(false)
{
    setBackgroundBrush(QBrush(QColor(192,192,192)));
    setOptimizationFlag(QGraphicsView::DontSavePainterState);

    IqAmeGeoHelper::setLocalCartesianOrigin(48 + 31/60.0 + 41/3600.0, 135 + 11/60.0 + 70/3600.0); //Хабаровск

    setScene(IqAmeApplication::graphicsScene());
    connect(IqAmeApplication::graphicsScene(), &QGraphicsScene::selectionChanged, this, &IqLayerView::updateItemsStack);
    setDragMode(RubberBandDrag);
    scale(0.001, 0.001);
}

void IqLayerView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    qreal scaleFactor = 1.15;
    if(event->delta() > 0) {
        scale(scaleFactor, scaleFactor);
    } else {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void IqLayerView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        m_pan = true;
        m_panStartPoint = QPoint(event->x(), event->y());
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
    QGraphicsView::mousePressEvent(event);
}

void IqLayerView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        m_pan = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    QGraphicsView::mouseReleaseEvent(event);

    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
        emit selectionFinished();
}

void IqLayerView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pan) {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - m_panStartPoint.x()));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - m_panStartPoint.y()));
        m_panStartPoint = QPoint(event->x(), event->y());
        event->accept();
        return;
    }
    QGraphicsView::mouseMoveEvent(event);
}

void IqLayerView::updateItemsStack()
{
    QSet<QGraphicsItem *> currentSelectedItem = IqAmeApplication::graphicsScene()->selectedItems().toSet();

    foreach (QGraphicsItem *item, m_oldSelectedItems) {
        if (!currentSelectedItem.contains(item))
            item->setZValue(0);
    }

    foreach (QGraphicsItem * item, currentSelectedItem) {
        item->setZValue(1);
    }

    m_oldSelectedItems = currentSelectedItem;
}
