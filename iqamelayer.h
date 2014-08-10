#ifndef IQAMELAYER_H
#define IQAMELAYER_H

#include <QObject>
#include <QRectF>
#include "iqlayerview.h"
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
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
public:
    explicit IqAmeLayer(QObject *parent = 0);

    void insertChildLayer(const qint32 index, IqAmeLayer *layer);

    void appendChildLayer(IqAmeLayer *layer);

    void removeChildLayer(IqAmeLayer *layer);

    IqAmeLayer * childLayer(const qint32 index) const;

    inline QList<IqAmeLayer *> childLayers() const {return _childLayers;}

    QList<IqAmeLayer *> allChildLayers() const;

    inline IqAmeShapesModel * shapesModel() const {return _shapesModel;}

    qint32 index() const;

    bool loadFromFile(const QString &fileName, QString *lastError = NULL);

    bool loadFromFile(QString *lastError = NULL);

    void paindGl(const QRectF &area, IqLayerView *layerView);

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

    inline bool visible() const {return _visible;}
    void setVisible(const bool visible);

signals:
    void atdMenuNameChanged();
    void fileNameChanged();
    void descriptionChanged();
    void parentLayerChanged();
    void childLayersCountChanged();
    void videomapNameChanged();
    void visibleChanged();

private:
    QString _atdMenuName;
    QString _fileName;
    QString _description;
    QString _videomapName;
    bool _visible;
    IqAmeShapesModel *_shapesModel;

    QList<IqAmeLayer *> _childLayers;
    IqAmeLayer * _parentLayer;

    void setParentLayer(IqAmeLayer *layer);
};

#endif // IQAMELAYER_H
