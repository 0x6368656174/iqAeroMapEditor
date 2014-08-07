#define SCALE_STEP 0.2

#include "iqlayerview.h"
#include <QDebug>
#include "iqamelayer.h"
#include "iqamegeohelper.h"

using namespace GeographicLib;

IqLayerView::IqLayerView(QWidget *parent) :
    QGLWidget(parent),
    _zoomFactor(1000),
    _center(QPoint(0, 0)),
    _translationEnabled(false)
{
    IqAmeGeoHelper::setLocalCartesianOrigin(48 + 31/60.0 + 41/3600.0, 135 + 11/60.0 + 70/3600.0); //Хабаровск
}

QPointF IqLayerView::mapToGeo(const QPoint &screenPoint) const
{
    qreal x = (_center.x() + screenPoint.x() - width()/2)*_zoomFactor;
    qreal y = -(-_center.y() + screenPoint.y() - height()/2)*_zoomFactor;
    return QPointF(x, y);
}

QPoint IqLayerView::mapFromGeo(const QPointF &geoPoint) const
{
    qint32 x = geoPoint.x()/_zoomFactor - _center.x() + width()/2;
    qint32 y = -geoPoint.y()/_zoomFactor + _center.y() + height()/2;
    return QPoint(x, y);
}

void IqLayerView::wheelEvent(QWheelEvent *event)
{
    qreal stepProcent = _zoomFactor*SCALE_STEP;

    QPointF geoPointOnMouse = mapToGeo(event->pos());

    if (event->delta() > 0)
    {
        _zoomFactor += stepProcent;
    }
    else
    {
        _zoomFactor -= stepProcent;
    }

    QPointF poinAfterZoom = mapToGeo(event->pos());
    qreal dx = (poinAfterZoom.x() - geoPointOnMouse.x())/_zoomFactor;
    qreal dy = (poinAfterZoom.y() - geoPointOnMouse.y())/_zoomFactor;
    _center.setX(_center.x() - dx);
    _center.setY(_center.y() - dy);

    repaint();
}

void IqLayerView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton)
    {
        _translationEnabled = true;
        _pressMousePos = event->pos();
        _pressCenter = _center;
    }
}

void IqLayerView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton)
    {
        _translationEnabled = false;
    }
}

void IqLayerView::mouseMoveEvent(QMouseEvent *event)
{
    if (_translationEnabled)
    {
        _center.setX(_pressCenter.x() + (_pressMousePos.x() - event->pos().x()));
        _center.setY(_pressCenter.y() + (event->pos().y() - _pressMousePos.y()));
        repaint();
    }
}

void IqLayerView::addLayerToView(IqAmeLayer *layer)
{
    _visibleLayers.append(layer);
    repaint();
}

void IqLayerView::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void IqLayerView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу

    glLoadIdentity(); // загружаем матрицу

    glOrtho((-width()/2+_center.x())*_zoomFactor,
            (width()/2+_center.x())*_zoomFactor,
            (-height()/2+_center.y())*_zoomFactor,
            (height()/2+_center.y())*_zoomFactor,
            0,
            1); // подготавливаем плоскости для матрицы

    qglClearColor(QColor(192,192,192));

    //Включаем возможность рисования пунктирных линий
    glEnable(GL_LINE_STIPPLE);

    //Рисовать будем только то, что видим
    QRectF area;
    area.setTopLeft(mapToGeo(QPoint(0, 0)));
    area.setBottomRight(mapToGeo(QPoint(width(), height())));

    //Продемся по всем видимым слоям
    foreach (IqAmeLayer *layer, _visibleLayers)
    {
        //Прорисуем каждый слой
        layer->paindGl(area, this);
    }
}
