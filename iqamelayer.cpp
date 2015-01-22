#include "iqamelayer.h"
#include "iqameapplication.h"
#include <QFile>
#include <QRegExp>
#include <QStringList>
#include <QDebug>
#include <QRectF>
#include "iqameline.h"

IqAmeLayer::IqAmeLayer(QObject *parent) :
    QObject(parent),
    m_shapesModel(new IqAmeShapesModel(this)),
    m_childLayers(QList<IqAmeLayer *>()),
    m_parentLayer(Q_NULLPTR),
    m_visible(false)
{
}

void IqAmeLayer::insertChildLayer(const qint32 index, IqAmeLayer *layer)
{
    if (layer) {
        m_childLayers.insert(index, layer);
        layer->setParent(this);
        layer->setParentLayer(this);

        emit childLayersCountChanged();
    }
}

void IqAmeLayer::appendChildLayer(IqAmeLayer *layer)
{
    if (layer) {
        m_childLayers.append(layer);
        layer->setParent(this);
        layer->setParentLayer(this);

        emit childLayersCountChanged();
    }
}

void IqAmeLayer::removeChildLayer(IqAmeLayer *layer)
{
    if (layer) {
        if (m_childLayers.removeAll(layer) > 0)
            emit childLayersCountChanged();
        layer->deleteLater();
    }
}

IqAmeLayer * IqAmeLayer::childLayer(const qint32 index) const
{
    if (index > -1 && index < childLayersCount()) {
        return m_childLayers[index];
    }

    return NULL;
}

QList<IqAmeLayer *> IqAmeLayer::childLayers() const
{
    return m_childLayers;
}

qint32 IqAmeLayer::index() const
{
    if (m_parentLayer)
        return m_parentLayer->m_childLayers.indexOf(const_cast<IqAmeLayer*>(this));

    return 0;
}


void IqAmeLayer::setParentLayer(IqAmeLayer *layer)
{
    if (m_parentLayer != layer) {
        m_parentLayer = layer;

        emit parentLayerChanged();
    }
}

void IqAmeLayer::setAtdMenuName(const QString &atdMenuName)
{
    if (m_atdMenuName != atdMenuName) {
        m_atdMenuName = atdMenuName;

        emit atdMenuNameChanged();
    }
}

QString IqAmeLayer::fileName() const
{
    return m_fileName;
}

void IqAmeLayer::setFileName(const QString &fileName)
{
    if (m_fileName != fileName) {
        m_fileName = fileName;

        emit fileNameChanged();
    }
}

QString IqAmeLayer::description() const
{
    return m_description;
}

void IqAmeLayer::setDescription(const QString &description)
{
    if (m_description != description) {
        m_description = description;

        emit descriptionChanged();
    }
}

qint32 IqAmeLayer::childLayersCount() const
{
    return m_childLayers.count();
}

IqAmeLayer *IqAmeLayer::parentLayer() const
{
    return m_parentLayer;
}

QString IqAmeLayer::videomapName() const
{
    return m_videomapName;
}

void IqAmeLayer::setVideomapName(const QString &videomapName)
{
    if (m_videomapName != videomapName) {
        m_videomapName = videomapName;

        emit videomapNameChanged();
    }
}

bool IqAmeLayer::visible()
{
    return m_visible;
}

void IqAmeLayer::setVisible(const bool visible)
{
    if (m_visible != visible) {
        m_visible = visible;
        updateGraphicsItem();
        emit visibleChanged();
    }
}

bool IqAmeLayer::loadFromFile(QString *lastError)
{
    return loadFromFile(fileName(), lastError);
}

bool IqAmeLayer::loadFromFile(const QString &fileName, QString *lastError)
{
    setFileName(fileName);

    if (fileName.isEmpty())
        return false;

    if (!QFile::exists(fileName)) {
        QString error = tr("File \"%0\" not exist.").arg(fileName);
        qWarning() << error;
        if (lastError)
            *lastError = error;

        return false;
    }

    qDebug() << tr("Starting parsing \"%0\"...").arg(fileName);

    QFile file (fileName);
    if (!file.open(QFile::ReadOnly)) {
        QString error = tr("Can not open \"%0\" file.").arg(fileName);
        qWarning() << error;
        if (lastError)
            *lastError = error;

        return false;
    }

    QByteArray fileData = file.readAll();

    QString fileString = IqAmeApplication::defaultTextCodec()->toUnicode(fileData);

    QRegExp nameRx ("^\\s*(N|NAME):\\s*\\\"(.*)\\\"\\s*\\*\\s*(.*)");

    if (nameRx.indexIn(fileString) != -1) {
        setVideomapName(nameRx.cap(2));
        setDescription(nameRx.cap(3));
    } else {
        QString error = tr("Not found layer name in file \"%0\".").arg(fileName);
        qWarning() << error;
        if (lastError)
            *lastError = error;

        return false;
    }

    return m_shapesModel->loadFromFile(fileName, lastError);
}

void IqAmeLayer::updateGraphicsItem()
{
    foreach (IqAmeNamedShapeObject *shape, shapesModel()->toList()) {
        Q_CHECK_PTR(shape);
        shape->setVisible(visible());
        shape->updateGraphicsItems();
        foreach (QGraphicsItem *item, shape->graphicsItems()) {
            Q_CHECK_PTR(item);
            IqAmeApplication::graphicsScene()->addItem(item);
        }
    }
}

QString IqAmeLayer::atdMenuName() const
{
    return m_atdMenuName;
}

QList<IqAmeLayer *> IqAmeLayer::allChildLayers() const
{
    QList<IqAmeLayer *> result;
    foreach (IqAmeLayer* layer, m_childLayers) {
        if (layer) {
            result << layer;
            result << layer->allChildLayers();
        }
    }

    return result;
}

IqAmeShapesModel *IqAmeLayer::shapesModel() const
{
    return m_shapesModel;
}
