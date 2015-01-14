#ifndef IQAMEAPPLICATION_H
#define IQAMEAPPLICATION_H

#include <QObject>
#include <QTextCodec>
#include <QGraphicsScene>
#include "iqamemapmodel.h"

class IqAmeApplication : public QObject
{
    Q_OBJECT
public:
    explicit IqAmeApplication(QObject *parent = Q_NULLPTR);

    static QTextCodec* defaultTextCodec() {return QTextCodec::codecForName("koi8-r");}

    static IqAmeMapModel *aeroMapModel();

    static QGraphicsScene *graphicsScene();

private:
    static IqAmeMapModel *m_aeroMapModel;
    static QGraphicsScene *m_graphicsScene;
};

#endif // IQAMEAPPLICATION_H
