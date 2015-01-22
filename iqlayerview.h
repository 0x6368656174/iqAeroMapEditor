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

signals:
    void selectionFinished();

protected:
    void wheelEvent(QWheelEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

private:
    void updateItemsStack();

private:
    bool m_pan;
    QPoint m_panStartPoint;
    QSet<QGraphicsItem *> m_oldSelectedItems;
};

#endif // IQLAYERVIEW_H
