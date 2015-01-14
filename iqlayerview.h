#ifndef IQLAYERVIEW_H
#define IQLAYERVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QPoint>

class IqAmeLayer;

class IqLayerView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit IqLayerView(QWidget *parent = Q_NULLPTR);

//    void setCurrentLayer(const IqAmeLayer *layer);

//    QPointF mapToGeo(const QPoint &screenPoint) const;

//    QPoint mapFromGeo(const QPointF &geoPoint) const;

//protected:
//    void resizeGL(int nWidth, int nHeight);
//    void paintGL();
    void wheelEvent(QWheelEvent * event);
//    void mousePressEvent(QMouseEvent * event);
//    void mouseReleaseEvent(QMouseEvent * event);
//    void mouseMoveEvent(QMouseEvent * event);

//private:
//    qreal _zoomFactor;
//    QPoint _center;
//    QPoint _pressCenter;
//    QPoint _pressMousePos;
//    bool _translationEnabled;
};

#endif // IQLAYERVIEW_H
