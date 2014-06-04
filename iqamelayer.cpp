#include "iqamelayer.h"
#include "iqameapplication.h"
#include <QFile>
#include <QRegExp>
#include <QStringList>
#include <QDebug>
#include "iqameline.h"

IqAmeLayer::IqAmeLayer(QObject *parent) :
    QObject(parent),
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

bool IqAmeLayer::loadFromFile(QString *lastError)
{
    return loadFromFile(fileName(), lastError);
}

bool IqAmeLayer::loadFromFile(const QString &fileName, QString *lastError)
{
    setFileName(fileName);

    qDeleteAll(_shapes);
    _shapes.clear();

    if (_fileName.isEmpty())
        return false;

    if (!QFile::exists(_fileName))
    {
        QString error = tr("File \"%0\" not exist.").arg(_fileName);
        qWarning() << error;
        if (lastError)
            *lastError = error;

        return false;
    }

    qDebug() << tr("Starting parsing \"%0\"...").arg(fileName);

    QFile file (_fileName);
    if (!file.open(QFile::ReadOnly))
    {
        QString error = tr("Can not open \"%0\" file.").arg(_fileName);
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
        QString error = tr("Not found layer name in file \"%0\".").arg(_fileName);
        qWarning() << error;
        if (lastError)
            *lastError = error;

        return false;
    }

    QStringList fileStringList = fileString.split("\n");

    //Удалим имя
    fileStringList.removeFirst();

    QRegExp shapeRx ("^\\s*(LINE|L|TEXT|T|SYMB|S|FILL|F|SETA|SA|SETD|SD)\\s*:");
    shapeRx.setCaseSensitivity(Qt::CaseInsensitive);
    QString shape;
    QString shapeType;

    foreach (QString str, fileStringList)
    {
        if (shapeRx.indexIn(str) != -1)
        {
            //Обработаем приметив
            if (!shape.isEmpty() && (shapeType.compare("LINE", Qt::CaseInsensitive) == 0 || shapeType.compare("L", Qt::CaseInsensitive) == 0))
            {
                IqAmeLine *line = new IqAmeLine(this);
                if (line->loadFromString(shape))
                {
                    _shapes << line;
                }
                else
                {
                    qWarning() << tr("Can not parse line string \"%0\". Skipped.").arg(shape);
                    line->deleteLater();
                }
            }

            //Начат новый приметив
            shapeType = shapeRx.cap(1);
            shape = str.trimmed();
        }
        else
        {
            shape += " " + str.trimmed();
        }
    }

    return true;
}
