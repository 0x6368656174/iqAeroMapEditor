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
    _visible(false),
    _shapesModel(new IqAmeShapesModel(this)),
    _parentLayer(NULL)
{
}

void IqAmeLayer::insertChildLayer(const qint32 index, IqAmeLayer *layer)
{
    if (layer)
    {
        _childLayers.insert(index, layer);
        layer->setParent(this);
        layer->setParentLayer(this);

        emit childLayersCountChanged();
    }
}

void IqAmeLayer::appendChildLayer(IqAmeLayer *layer)
{
    if (layer)
    {
        _childLayers.append(layer);
        layer->setParent(this);
        layer->setParentLayer(this);

        emit childLayersCountChanged();
    }
}

void IqAmeLayer::removeChildLayer(IqAmeLayer *layer)
{
    if (layer)
    {
        if (_childLayers.removeAll(layer) > 0)
            emit childLayersCountChanged();
        layer->deleteLater();
    }
}

IqAmeLayer * IqAmeLayer::childLayer(const qint32 index) const
{
    if (index > -1 && index < childLayersCount())
    {
        return _childLayers[index];
    }

    return NULL;
}

qint32 IqAmeLayer::index() const
{
    if (_parentLayer)
        return _parentLayer->_childLayers.indexOf(const_cast<IqAmeLayer*>(this));

    return 0;
}


void IqAmeLayer::setParentLayer(IqAmeLayer *layer)
{
    if (_parentLayer != layer)
    {
        _parentLayer = layer;

        emit parentLayerChanged();
    }
}

void IqAmeLayer::setAtdMenuName(const QString &atdMenuName)
{
    if (_atdMenuName != atdMenuName)
    {
        _atdMenuName = atdMenuName;

        emit atdMenuNameChanged();
    }
}

void IqAmeLayer::setFileName(const QString &fileName)
{
    if (_fileName != fileName)
    {
        _fileName = fileName;

        emit fileNameChanged();
    }
}

void IqAmeLayer::setDescription(const QString &description)
{
    if (_description != description)
    {
        _description = description;

        emit descriptionChanged();
    }
}

void IqAmeLayer::setVideomapName(const QString &videomapName)
{
    if (_videomapName != videomapName)
    {
        _videomapName = videomapName;

        emit videomapNameChanged();
    }
}

void IqAmeLayer::setVisible(const bool visible)
{
    if (_visible != visible)
    {
        _visible = visible;

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

    if (!QFile::exists(fileName))
    {
        QString error = tr("File \"%0\" not exist.").arg(fileName);
        qWarning() << error;
        if (lastError)
            *lastError = error;

        return false;
    }

    qDebug() << tr("Starting parsing \"%0\"...").arg(fileName);

    QFile file (fileName);
    if (!file.open(QFile::ReadOnly))
    {
        QString error = tr("Can not open \"%0\" file.").arg(fileName);
        qWarning() << error;
        if (lastError)
            *lastError = error;

        return false;
    }

    QByteArray fileData = file.readAll();

    QString fileString = IqAmeApplication::defaultTextCodec()->toUnicode(fileData);

    QRegExp nameRx ("^\\s*(N|NAME):\\s*\\\"(.*)\\\"\\s*\\*\\s*(.*)");

    if (nameRx.indexIn(fileString) != -1)
    {
        setVideomapName(nameRx.cap(2));
        setDescription(nameRx.cap(3));
    }
    else
    {
        QString error = tr("Not found layer name in file \"%0\".").arg(fileName);
        qWarning() << error;
        if (lastError)
            *lastError = error;

        return false;
    }

    return _shapesModel->loadFromFile(fileName, lastError);
}

void IqAmeLayer::paindGl(const QRectF &area, IqLayerView *layerView)
{
    //В каждом слое, для каждого приметива вызовем функцию рисования
    if (!shapesModel())
        return;
    for (int i = 0; i < shapesModel()->rowCount(); i++)
    {
        QModelIndex shapeIndex = shapesModel()->index(i, 0);
        IqAmeShapeObject * shape = qvariant_cast<IqAmeShapeObject *>(shapesModel()->data(shapeIndex, IqAmeShapesModel::ShapeObject));

        if (shape)
        {
            //Если приметив входит в область
            QRectF boundingBox = shape->boundingBox();
            if (area.intersects(boundingBox))
                shape->paindGl(area, layerView);
        }
    }
}
