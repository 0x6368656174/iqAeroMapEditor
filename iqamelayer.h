#ifndef IQAMELAYER_H
#define IQAMELAYER_H

#include <QObject>
#include <QRectF>
#include "iqlayerview.h"
#include "iqameshapesmodel.h"
#include <QGraphicsItemGroup>

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
    explicit IqAmeLayer(QObject *parent = Q_NULLPTR);

    void insertChildLayer(const qint32 index, IqAmeLayer *layer);

    void appendChildLayer(IqAmeLayer *layer);

    void removeChildLayer(IqAmeLayer *layer);

    IqAmeLayer * childLayer(const qint32 index) const;

    QList<IqAmeLayer *> childLayers() const;

    QList<IqAmeLayer *> allChildLayers() const;

    IqAmeShapesModel *shapesModel() const;

    qint32 index() const;

    bool loadFromFile(const QString &fileName, QString *lastError = Q_NULLPTR);

    bool loadFromFile(QString *lastError = Q_NULLPTR);

    void updateGraphicsItem();

public:
    QString atdMenuName() const;
    void setAtdMenuName(const QString &atdMenuName);

    QString fileName() const;
    void setFileName(const QString &fileName);

    QString description() const;
    void setDescription(const QString &description);

    qint32 childLayersCount() const;

    IqAmeLayer *parentLayer() const;

    QString videomapName() const;
    void setVideomapName(const QString &videomapName);

    bool visible();
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
    QString m_atdMenuName;
    QString m_fileName;
    QString m_description;
    QString m_videomapName;
    IqAmeShapesModel *m_shapesModel;

    QList<IqAmeLayer *> m_childLayers;
    IqAmeLayer * m_parentLayer;

    bool m_visible;

    void setParentLayer(IqAmeLayer *layer);
};

#endif // IQAMELAYER_H
