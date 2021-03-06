#define MAPLAB_FILE_NAME "maplab.txt"
#define HABAR_2_FILE_NAME "HABAR_2.LIS"
#define HABAR_W_FILE_NAME "HABAR_W.PNT"
#define ROUTES_W_FILE_NAME "ROUTES_W.SLD"
#define ROUT_S_W_FILE_NAME "ROUT_S_W.SLD"
#define POINTS_W_FILE_NAME "POINTS_W.SLD"

#define COLUMN_VISIBLE 0
#define COLUMN_ATD_NAME 1
#define COLUMN_FILE_NAME 2

#include "iqamemapmodel.h"
#include <QFile>
#include <QStringList>
#include <QFont>
#include <QDebug>
#include <QThread>
#include "iqameapplication.h"

IqAmeMapModel::IqAmeMapModel(QObject *parent) :
    QAbstractItemModel(parent),
    m_rootLayer(new IqAmeLayer(this)),
    m_pointsModel(new IqAmeGeoPointsModel(this))
{
}

void IqAmeMapModel::clear()
{
    //Удалим все дочерние слои
    if (rowCount() > 0) {
        emit beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
        QList<IqAmeLayer *> childs = m_rootLayer->childLayers();
        foreach (IqAmeLayer * layer, childs) {
            m_rootLayer->removeChildLayer(layer);
        }
        emit endRemoveRows();
    }
}

void IqAmeMapModel::startLoadData()
{
    m_pointsModel->startLoadData();
    beginResetModel();
}

void IqAmeMapModel::endLoadData()
{
    m_pointsModel->endLoadData();
    endResetModel();
}

bool IqAmeMapModel::loadFromFolder(const QString &folderName, QString *lastError)
{
    IqAmeLayer *newRootLayer = new IqAmeLayer();

    //Удалим старый слой
    m_rootLayer->deleteLater();
    m_rootLayer = new IqAmeLayer();
    m_rootLayer->moveToThread(this->thread());
    m_rootLayer->setParent(this);

    if (!QFile::exists(folderName)) {
        if (lastError)
            *lastError = tr("Folder \"%0\" not exist.").arg(folderName);
        qWarning() << tr("Folder \"%0\" not exist.").arg(folderName);

        newRootLayer->deleteLater();
        return false;
    }

    //Загрузим модель с точками
    if (!m_pointsModel->loadFromFile(folderName + "/" + HABAR_W_FILE_NAME)) {
        if (lastError)
            *lastError = tr("Error on load points file\"%0\".").arg(folderName + "/" + HABAR_W_FILE_NAME);
        qWarning() << tr("Error on load points file\"%0\".").arg(folderName + "/" + HABAR_W_FILE_NAME);

        newRootLayer->deleteLater();
        return false;
    }

    if (!QFile::exists(folderName + "/" + MAPLAB_FILE_NAME)) {
        if (lastError)
            *lastError = tr("File \"%0\" not exist.").arg(folderName + "/" + MAPLAB_FILE_NAME);
        qWarning() << tr("File \"%0\" not exist.").arg(folderName + "/" + MAPLAB_FILE_NAME);

        newRootLayer->deleteLater();
        return false;
    }

    if (!QFile::exists(folderName + "/" + HABAR_2_FILE_NAME)) {
        if (lastError)
            *lastError = tr("File \"%0\" not exist.").arg(folderName + "/" + HABAR_2_FILE_NAME);
        qWarning() << tr("File \"%0\" not exist.").arg(folderName + "/" + HABAR_2_FILE_NAME);

        newRootLayer->deleteLater();
        return false;
    }

    QFile maplabFile (folderName + "/" + MAPLAB_FILE_NAME);
    if (!maplabFile.open(QFile::ReadOnly)) {
        if (lastError)
            *lastError = tr("Can not open \"%0\" file.").arg(folderName + "/" + MAPLAB_FILE_NAME);
        qWarning() << tr("Can not open \"%0\" file.").arg(folderName + "/" + MAPLAB_FILE_NAME);

        newRootLayer->deleteLater();
        return false;
    }

    QFile habar2File (folderName + "/" + HABAR_2_FILE_NAME);
    if (!habar2File.open(QFile::ReadOnly)) {
        if (lastError)
            *lastError = tr("Can not open \"%0\" file.").arg(folderName + "/" + HABAR_2_FILE_NAME);
        qWarning() << tr("Can not open \"%0\" file.").arg(folderName + "/" + HABAR_2_FILE_NAME);

        newRootLayer->deleteLater();
        return false;
    }

    QByteArray maplabData = maplabFile.readAll();
    QByteArray habar2Data = habar2File.readAll();

    QString maplabStrin = IqAmeApplication::defaultTextCodec()->toUnicode(maplabData);
    QString habar2String = IqAmeApplication::defaultTextCodec()->toUnicode(habar2Data);

    QStringList maplabaStringList = maplabStrin.split("\n");
    QStringList habar2StringList = habar2String.split("\n");

    IqAmeLayer *parentLayer = newRootLayer;

    //Добавим пустой слой, в то место, где отображаются точки
    IqAmeLayer *nullLayer = new IqAmeLayer(newRootLayer);
    parentLayer->appendChildLayer(nullLayer);

    //    IqAmeLayer *routesSWLayer = new IqAmeLayer(this);
    //    routesSWLayer->setAtdMenuName(tr("TEST"));
    //    routesSWLayer->setFileName(folderName + "/HABSEC.SLD");
    //    routesSWLayer->loadFromFile(folderName + "/HABSEC.SLD");
    //    parentLayer->appendChildLayer(routesSWLayer);

    //Добавим слой с трассами
    IqAmeLayer *routesSWLayer = new IqAmeLayer(newRootLayer);
    routesSWLayer->setAtdMenuName(tr("ROUTES"));
    routesSWLayer->setFileName(folderName + "/" + ROUTES_W_FILE_NAME);
    routesSWLayer->loadFromFile(folderName + "/" + ROUTES_W_FILE_NAME);
    parentLayer->appendChildLayer(routesSWLayer);

    //Добавим слой с точками
    IqAmeLayer *pointsSWLayer = new IqAmeLayer(newRootLayer);
    pointsSWLayer->setAtdMenuName(tr("POINTS"));
    pointsSWLayer->setFileName(folderName + "/" + POINTS_W_FILE_NAME);
    pointsSWLayer->loadFromFile(folderName + "/" + POINTS_W_FILE_NAME);
    parentLayer->appendChildLayer(pointsSWLayer);

    int habar2Index = 0;
    foreach (QString maplabLine, maplabaStringList) {
        if (maplabLine.trimmed() == "**") {
            parentLayer = parentLayer->parentLayer();

            continue;
        }

        QRegExp menuContainerRx ("\\*(.+)\\*");
        if (menuContainerRx.indexIn(maplabLine) > -1) {
            IqAmeLayer *newParentLayer = new IqAmeLayer(parentLayer);
            newParentLayer->setAtdMenuName(menuContainerRx.cap(1));
            parentLayer->appendChildLayer(newParentLayer);
            parentLayer = newParentLayer;

            continue;
        }

        if (habar2Index >= habar2StringList.count()) {
            clear();

            if (lastError)
                *lastError = tr("The file \"%0\" is not enough lines.").arg(folderName + "/" + HABAR_2_FILE_NAME);
            qWarning() << tr("The file \"%0\" is not enough lines.").arg(folderName + "/" + HABAR_2_FILE_NAME);

            newRootLayer->deleteLater();
            return false;
        }

        IqAmeLayer *newSublineLayer = new IqAmeLayer(parentLayer);
        newSublineLayer->setAtdMenuName(maplabLine.trimmed());
        newSublineLayer->setFileName(habar2StringList[habar2Index].trimmed() + ".sld");
        if (newSublineLayer->loadFromFile(folderName + "/" + newSublineLayer->fileName().toUpper(), lastError)) {
            parentLayer->appendChildLayer(newSublineLayer);
        } else {
            qWarning() << tr("Error on load \"%0\". Skipped.").arg(newSublineLayer->fileName().toUpper() + ".SLD");
            newSublineLayer->deleteLater();
        }
        habar2Index++;
    }

    //Изменяем поток для нового слоя
    newRootLayer->moveToThread(this->thread());
    newRootLayer->setParent(this);
    //Заменим старый слой на новый
    m_rootLayer->deleteLater();
    m_rootLayer = newRootLayer;

    return true;
}

IqAmeGeoPointsModel *IqAmeMapModel::pointsModel() const
{
    return m_pointsModel;
}

IqAmeLayer *IqAmeMapModel::rootLayer() const
{
    return m_rootLayer;
}

QModelIndex IqAmeMapModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    IqAmeLayer *parentLayer;

    if (!parent.isValid())
        parentLayer = m_rootLayer;
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

    if (parentLayer == m_rootLayer)
        return QModelIndex();

    return createIndex(parentLayer->index(), 0, parentLayer);
}

int IqAmeMapModel::rowCount(const QModelIndex &parent) const
{
    IqAmeLayer *parentLayer;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid()) {
        parentLayer = m_rootLayer;
        return parentLayer->childLayersCount() + 1;
    } else
        parentLayer = static_cast<IqAmeLayer*>(parent.internalPointer());

    return parentLayer->childLayersCount();
}

int IqAmeMapModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant IqAmeMapModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int column = index.column();
    int row = index.row();
    IqAmeLayer *layer = static_cast<IqAmeLayer*>(index.internalPointer());

    if (!index.parent().isValid()) {
        if (row < 4) {
            if (column == COLUMN_VISIBLE) {
                switch (role) {
                case Qt::CheckStateRole: {
                    if (index.row() == 0) {
                        return Qt::Unchecked;
                    } else {
                        if (layer->visible()) {
                            return Qt::Checked;
                        } else {
                            return Qt::Unchecked;
                        }
                    }
                }
                default:
                    return QVariant();
                }
            }


            else if (column == COLUMN_ATD_NAME) {
                switch (role) {
                case Qt::DisplayRole: {
                    if (index.row() == 0) {
                        return tr("GEO POINTS");
                    } else {
                        return layer->atdMenuName();
                    }
                }
                case Qt::FontRole: {
                    QFont font;
                    font.setBold(true);
                    return font;
                }
                default:
                    return QVariant();
                }
            }


            else if (column == COLUMN_FILE_NAME) {
                switch (role) {
                case Qt::DisplayRole: {
                    if (row == 0) {
                        return QVariant();
                    } else {
                        IqAmeLayer *layer = static_cast<IqAmeLayer*>(index.internalPointer());
                        return layer->fileName();
                    }
                }
                default:
                    return QVariant();
                }
            }
        }
    }

    if (column == COLUMN_VISIBLE) {
        switch (role) {
        case Qt::CheckStateRole: {
            if (layer->visible()) {
                return Qt::Checked;
            } else {
                return Qt::Unchecked;
            }
        }
        }
    } else  if (column == COLUMN_ATD_NAME) {
        switch (role) {
        case Qt::DisplayRole:
            return layer->atdMenuName();
        }
    } else if (column == COLUMN_FILE_NAME) {
        switch (role) {
        case Qt::DisplayRole:
            return layer->fileName();
        }
    }

    return QVariant();
}

Qt::ItemFlags IqAmeMapModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    Qt::ItemFlags result = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if (index.column() == COLUMN_VISIBLE && (index.row() > 0 || index.parent().isValid()))
        result |= Qt::ItemIsUserCheckable | Qt::ItemIsEditable;

    return result;
}

QVariant IqAmeMapModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (orientation) {
    case Qt::Horizontal: {
        switch (role) {
        case Qt::DisplayRole: {
            switch (section) {
            case COLUMN_VISIBLE:
                return tr("V");
            case COLUMN_ATD_NAME:
                return tr("ATD Menu Name");
            case COLUMN_FILE_NAME:
                return tr("File Name");
            }
        }
        case Qt::TextAlignmentRole:
            return Qt::AlignHCenter;
        }
    }
    case Qt::Vertical:
        break;
    }

    return QAbstractItemModel::headerData(section, orientation, role);
}

bool IqAmeMapModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    if (!index.isValid())
        return false;

    int column = index.column();
    IqAmeLayer *layer = static_cast<IqAmeLayer*>(index.internalPointer());
    if (!layer)
        return false;

    if (column == COLUMN_VISIBLE) {
        layer->setVisible(value == Qt::Checked);
        emit dataChanged(index, index);

        return true;
    }

    return false;
}
