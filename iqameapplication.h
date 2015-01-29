#ifndef IQAMEAPPLICATION_H
#define IQAMEAPPLICATION_H

#include <QObject>
#include <QTextCodec>
#include <QGraphicsScene>
#include "iqamemapmodel.h"
#include <QGraphicsView>

class IqAmeApplication : public QObject
{
    Q_OBJECT
public:
    explicit IqAmeApplication(QObject *parent = Q_NULLPTR);

    static QTextCodec* defaultTextCodec() {return QTextCodec::codecForName("koi8-r");}

    static IqAmeMapModel *aeroMapModel();

    static QGraphicsScene *graphicsScene();

    static QGraphicsView *mapView();
    static void setMapView(QGraphicsView *mapView);

private:
    static IqAmeMapModel *m_aeroMapModel;
    static QGraphicsScene *m_graphicsScene;
    static QGraphicsView *m_mapView;
};

#endif // IQAMEAPPLICATION_H
