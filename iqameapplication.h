#ifndef IQAMEAPPLICATION_H
#define IQAMEAPPLICATION_H

#include <QObject>
#include <QTextCodec>
#include "iqamemapmodel.h"

class IqAmeApplication : public QObject
{
    Q_OBJECT
public:
    explicit IqAmeApplication(QObject *parent = 0);

    static QTextCodec* defaultTextCodec() {return QTextCodec::codecForName("koi8-r");}

    static IqAmeMapModel *aeroMapModel();

private:
    static IqAmeMapModel *_aeroMapModel;
};

#endif // IQAMEAPPLICATION_H
