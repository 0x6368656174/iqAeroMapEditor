#include "iqameapplication.h"

IqAmeMapModel * IqAmeApplication::m_aeroMapModel = Q_NULLPTR;
QGraphicsScene *IqAmeApplication::m_graphicsScene = Q_NULLPTR;
QGraphicsView *IqAmeApplication::m_mapView = Q_NULLPTR;

IqAmeApplication::IqAmeApplication(QObject *parent) :
    QObject(parent)
{
}

IqAmeMapModel * IqAmeApplication::aeroMapModel()
{
    if (!m_aeroMapModel)
        m_aeroMapModel = new IqAmeMapModel();
    return m_aeroMapModel;
}

QGraphicsScene *IqAmeApplication::graphicsScene()
{
    if (!m_graphicsScene)
        m_graphicsScene = new QGraphicsScene();
    return m_graphicsScene;
}
QGraphicsView *IqAmeApplication::mapView()
{
    return m_mapView;
}

void IqAmeApplication::setMapView(QGraphicsView *mapView)
{
    if (m_mapView != mapView)
        m_mapView = mapView;
}

