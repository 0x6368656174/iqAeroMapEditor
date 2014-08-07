#ifndef IQLAYERVIEW_H
#define IQLAYERVIEW_H

#include <QGLWidget>
#include <QWheelEvent>
#include <QPoint>
#include <QGLFunctions>

class IqAmeLayer;

class IqLayerView : public QGLWidget
{
    Q_OBJECT
public:
    explicit IqLayerView(QWidget *parent = 0);

//    void setCurrentLayer(const IqAmeLayer *layer);
    void addLayerToView( IqAmeLayer *layer);

    QPointF mapToGeo(const QPoint &screenPoint) const;

    QPoint mapFromGeo(const QPointF &geoPoint) const;

protected:
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void wheelEvent(QWheelEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

private:
    QList<IqAmeLayer *> _visibleLayers;
    qreal _zoomFactor;
    QPoint _center;
    QPoint _pressCenter;
    QPoint _pressMousePos;
    bool _translationEnabled;
};

#endif // IQLAYERVIEW_H
