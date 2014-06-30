#ifndef IQAMELAYER_H
#define IQAMELAYER_H

#include <QObject>
#include "iqameshapesmodel.h"

class IqAmeLayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString atdMenuName READ atdMenuName WRITE setAtdMenuName NOTIFY atdMenuNameChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(IqAmeLayer * parentLayer READ parentLayer NOTIFY parentLayerChanged)
    Q_PROPERTY(qint32 childLayersCount READ childLayersCount NOTIFY childLayersCountChanged)
    Q_PROPERTY(QString videomapName READ videomapName WRITE setVideomapName NOTIFY videomapNameChanged)

public:
    explicit IqAmeLayer(QObject *parent = 0);

    void insertChildLayer(const qint32 index, IqAmeLayer *layer);

    void appendChildLayer(IqAmeLayer *layer);

    void removeChildLayer(IqAmeLayer *layer);

    IqAmeLayer * childLayer(const qint32 index) const;

    inline IqAmeShapesModel * shapesModel() const {return _shapesModel;}

    qint32 index() const;

    bool loadFromFile(const QString &fileName, QString *lastError = NULL);

    bool loadFromFile(QString *lastError = NULL);

public:
    inline QString atdMenuName() const {return _atdMenuName;}
    void setAtdMenuName(const QString &atdMenuName);

    inline QString fileName() const {return _fileName;}
    void setFileName(const QString &fileName);

    inline QString description() const {return _description;}
    void setDescription(const QString &description);

    inline qint32 childLayersCount() const {return _childLayers.count();}

    inline IqAmeLayer * parentLayer() const {return _parentLayer;}

    inline QString videomapName() const {return _videomapName;}
    void setVideomapName(const QString &videomapName);

signals:
    void atdMenuNameChanged();
    void fileNameChanged();
    void descriptionChanged();
    void parentLayerChanged();
    void childLayersCountChanged();
    void videomapNameChanged();

private:
    QString _atdMenuName;
    QString _fileName;
    QString _description;
    QString _videomapName;
    IqAmeShapesModel *_shapesModel;

    QList<IqAmeLayer *> _childLayers;
    IqAmeLayer * _parentLayer;

    void setParentLayer(IqAmeLayer *layer);
};

#endif // IQAMELAYER_H
