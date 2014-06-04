#define MAPLAB_FILE_NAME "maplab.txt"
#define HABAR_2_FILE_NAME "HABAR_2.LIS"
#define HABAR_W_FILE_NAME "HABAR_W.PNT"

#include "iqamemapmodel.h"
#include <QFile>
#include <QStringList>
#include <QFont>
#include <QDebug>
#include "iqameapplication.h"

IqAmeMapModel::IqAmeMapModel(QObject *parent) :
    QAbstractItemModel(parent),
    _pointsModel(new IqAmeGeoPointsModel(this))
{
}

void IqAmeMapModel::clear()
{

}

bool IqAmeMapModel::loadFromFolder(const QString &folderName, QString *lastError)
{
    clear();

    if (!QFile::exists(folderName))
    {
        if (lastError)
            *lastError = tr("Folder \"%0\" not exist.").arg(folderName);

        return false;
    }

    //Загрузим модель с точками
    if (!_pointsModel->loadFromFile(folderName + "/" + HABAR_W_FILE_NAME))
    {
        if (lastError)
            *lastError = tr("Error on load points file\"%0\".").arg(folderName + "/" + HABAR_W_FILE_NAME);
        return false;
    }

    if (!QFile::exists(folderName + "/" + MAPLAB_FILE_NAME))
    {
        if (lastError)
            *lastError = tr("File \"%0\" not exist.").arg(folderName + "/" + MAPLAB_FILE_NAME);

        return false;
    }

    if (!QFile::exists(folderName + "/" + HABAR_2_FILE_NAME))
    {
        if (lastError)
            *lastError = tr("File \"%0\" not exist.").arg(folderName + "/" + HABAR_2_FILE_NAME);

        return false;
    }

    QFile maplabFile (folderName + "/" + MAPLAB_FILE_NAME);
    if (!maplabFile.open(QFile::ReadOnly))
    {
        if (lastError)
            *lastError = tr("Can not open \"%0\" file.").arg(folderName + "/" + MAPLAB_FILE_NAME);

        return false;
    }

    QFile habar2File (folderName + "/" + HABAR_2_FILE_NAME);
    if (!habar2File.open(QFile::ReadOnly))
    {
        if (lastError)
            *lastError = tr("Can not open \"%0\" file.").arg(folderName + "/" + HABAR_2_FILE_NAME);

        return false;
    }

    _rootLayer = new IqAmeLayer(this);

    QByteArray maplabData = maplabFile.readAll();
    QByteArray habar2Data = habar2File.readAll();

    QString maplabStrin = IqAmeApplication::defaultTextCodec()->toUnicode(maplabData);
    QString habar2String = IqAmeApplication::defaultTextCodec()->toUnicode(habar2Data);

    QStringList maplabaStringList = maplabStrin.split("\n");
    QStringList habar2StringList = habar2String.split("\n");

    IqAmeLayer *parentLayer = _rootLayer;
    int habar2Index = 0;
    foreach (QString maplabLine, maplabaStringList)
    {
        if (maplabLine.trimmed() == "**")
        {
            parentLayer = parentLayer->parentLayer();

            continue;
        }

        QRegExp menuContainerRx ("\\*(.+)\\*");
        if (menuContainerRx.indexIn(maplabLine) > -1)
        {
            IqAmeLayer *newParentLayer = new IqAmeLayer(this);
            newParentLayer->setAtdMenuName(menuContainerRx.cap(1));
            parentLayer->appendChildLayer(newParentLayer);
            parentLayer = newParentLayer;

            continue;
        }

        if (habar2Index >= habar2StringList.count())
        {
            clear();

            if (lastError)
                *lastError = tr("The file \"%0\" is not enough lines.").arg(folderName + "/" + HABAR_2_FILE_NAME);

            return false;
        }

        IqAmeLayer *newSublineLayer = new IqAmeLayer(this);
        newSublineLayer->setAtdMenuName(maplabLine.trimmed());
        newSublineLayer->setFileName(habar2StringList[habar2Index].trimmed() + ".sld");
        if (newSublineLayer->loadFromFile(folderName + "/" + newSublineLayer->fileName().toUpper(), lastError))
        {
            parentLayer->appendChildLayer(newSublineLayer);
        }
        else
        {
            qWarning() << tr("Error on load \"%0\". Skipped.").arg(newSublineLayer->fileName().toUpper() + ".SLD");
            newSublineLayer->deleteLater();
        }
        habar2Index++;
    }

    return true;
}

QModelIndex IqAmeMapModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    IqAmeLayer *parentLayer;

    if (!parent.isValid())
        parentLayer = _rootLayer;
    else
        parentLayer = static_cast<IqAmeLayer*>(parent.internalPointer());

    IqAmeLayer *childLayer = parentLayer->childLayer(row);
    if (childLayer)
        return createIndex(row, column, childLayer);
    else
        return QModelIndex();
}

QModelIndex IqAmeMapModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    IqAmeLayer *childLayer = static_cast<IqAmeLayer*>(index.internalPointer());
    IqAmeLayer *parentLayer = childLayer->parentLayer();

    if (parentLayer == _rootLayer)
        return QModelIndex();

    return createIndex(parentLayer->index(), 0, parentLayer);
}

int IqAmeMapModel::rowCount(const QModelIndex &parent) const
{
    IqAmeLayer *parentLayer;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
    {
        parentLayer = _rootLayer;
        return parentLayer->childLayersCount() + 1;
    }
    else
        parentLayer = static_cast<IqAmeLayer*>(parent.internalPointer());

    return parentLayer->childLayersCount();
}

QVariant IqAmeMapModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (!index.parent().isValid())
    {
        if (index.row() == 0)
        {
            if (index.column() == 0)
            {
                if (role == Qt::DisplayRole)
                {
                    return tr("POINTS");
                }
                else if (role == Qt::FontRole)
                {
                    QFont font;
                    font.setBold(true);
                    return font;
                }
                else
                {
                    return QVariant();
                }
            }
            else
            {
                return QVariant();
            }
        }
    }

    if (role != Qt::DisplayRole)
        return QVariant();

    IqAmeLayer *layer = static_cast<IqAmeLayer*>(index.internalPointer());

    if (index.column() == 0)
    {
        return layer->atdMenuName();
    }
    else if (index.column() == 1)
    {
        return layer->fileName();
    }

    return QVariant();
}

Qt::ItemFlags IqAmeMapModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant IqAmeMapModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == 0)
        {
            return tr("ATD Menu Name");
        }
        else if (section == 1)
        {
            return tr("File Name");
        }
    }

    return QVariant();
}
