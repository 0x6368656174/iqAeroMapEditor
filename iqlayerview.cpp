#define SCALE_STEP 0.2

#include "iqlayerview.h"
#include <QDebug>
#include <QGLWidget>
#include "iqamelayer.h"
#include "iqamegeohelper.h"
#include "iqameapplication.h"

using namespace GeographicLib;

IqLayerView::IqLayerView(QWidget *parent) :
    QGraphicsView(parent)
{
    setBackgroundBrush(QBrush(QColor(192,192,192)));
    setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    setOptimizationFlag(QGraphicsView::DontSavePainterState);

//    connect(IqAmeApplication::aeroMapModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(repaint()));
    IqAmeGeoHelper::setLocalCartesianOrigin(48 + 31/60.0 + 41/3600.0, 135 + 11/60.0 + 70/3600.0); //Хабаровск

    setScene(IqAmeApplication::graphicsScene());
    //Use ScrollHand Drag Mode to enable Panning
    setDragMode(ScrollHandDrag);
    scale(0.001, 0.001);
}

void IqLayerView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    // Don't call superclass handler here
    // as wheel is normally used for moving scrollbars
}
