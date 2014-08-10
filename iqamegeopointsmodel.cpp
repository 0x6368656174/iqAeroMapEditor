#include "iqamegeopointsmodel.h"
#include "iqameapplication.h"
#include "iqamegeohelper.h"
#include <QFile>
#include <QBrush>
#include <QDebug>
#include <QMessageBox>


IqAmeGeoPointsModel::IqAmeGeoPointsModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

IqAmeGeoPointsModel::~IqAmeGeoPointsModel()
{
    qDeleteAll(_points);
}

QVariant IqAmeGeoPointsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case NAME_COLUMN:
                return tr("Name");
                break;
            case DEFINITION_TYPE_COLUMN:
                return tr("Definition Type");
                break;
            case BASE_POINT_COLUMN:
                return tr("Base Point");
                break;
            case LATITUDE_COLUMN:
                return tr("Latitude");
                break;
            case LONGITUDE_COLUMN:
                return tr("Longitude");
                break;
            case X_COLUMN:
                return tr("X");
                break;
            case Y_COLUMN:
                return tr("Y");
                break;
            case ANGLE_COLUMN:
                return tr("Angle");
                break;
            case DISTANCE_COLUMN:
                return tr("Distance");
                break;
            case COMMENT_COLUMN:
                return tr("Comment");
                break;
            }
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant IqAmeGeoPointsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    if (index.column() < 0 || index.column() >= columnCount())
        return QVariant();

    IqAmeGeoPoint *point = _points.at(index.row());

    if (!point)
        return QVariant();

    switch (role)
    {
    case Qt::DisplayRole:
        switch (index.column())
        {
        case NAME_COLUMN:
            return point->name();
            break;
        case DEFINITION_TYPE_COLUMN:
            switch (point->definitionType())
            {
            case IqAmeGeoPoint::Geo:
                return tr("Geo");
                break;
            case IqAmeGeoPoint::Cartesian:
                return tr("Cartesian");
                break;
            case IqAmeGeoPoint::Polar:
                return tr("Polar");
                break;
            }
            break;
        case BASE_POINT_COLUMN:
            if (point->definitionType() != IqAmeGeoPoint::Geo)
            {
                if (point->basePoint())
                {
                    return point->basePoint()->name();
                } else if (!point->basePointName().isEmpty())
                {
                    return point->basePointName();
                }
            }
            break;
        case LATITUDE_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Geo)
            {
                return IqAmeGeoHelper::latitudeToString(point->latitude(), true);
            } else
            {
                return QVariant();
            }
            break;
        case LONGITUDE_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Geo)
            {
                return IqAmeGeoHelper::longitudeToString(point->longitude(), true);
            } else
            {
                return QVariant();
            }
            break;
        case X_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Cartesian)
            {
                return point->x();
            } else
            {
                return QVariant();
            }
            break;
        case Y_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Cartesian)
            {
                return point->y();
            } else
            {
                return QVariant();
            }
            break;
        case ANGLE_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Polar)
            {
                return point->angle();
            } else
            {
                return QVariant();
            }
            break;
        case DISTANCE_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Polar)
            {
                return point->distance();
            } else
            {
                return QVariant();
            }
            break;
        case COMMENT_COLUMN:
            return point->comment();
            break;
        }
        break;

    case Qt::EditRole:
        switch (index.column())
        {
        case NAME_COLUMN:
            return point->name();
            break;
        case DEFINITION_TYPE_COLUMN:
            switch (point->definitionType())
            {
            case IqAmeGeoPoint::Geo:
                return tr("Geo");
                break;
            case IqAmeGeoPoint::Cartesian:
                return tr("Cartesian");
                break;
            case IqAmeGeoPoint::Polar:
                return tr("Polar");
                break;
            }
            break;
        case BASE_POINT_COLUMN:
            if (point->definitionType() != IqAmeGeoPoint::Geo)
            {
                if (point->basePoint())
                {
                    return point->basePoint()->name();
                } else if (!point->basePointName().isEmpty())
                {
                    return point->basePointName();
                }
            }
            break;
        case LATITUDE_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Geo)
            {
                return IqAmeGeoHelper::latitudeToString(point->latitude(), false);
            } else
            {
                return QVariant();
            }
            break;
        case LONGITUDE_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Geo)
            {
                return IqAmeGeoHelper::longitudeToString(point->longitude(), false);
            } else
            {
                return QVariant();
            }
            break;
        case X_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Cartesian)
            {
                return point->x();
            } else
            {
                return QVariant();
            }
            break;
        case Y_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Cartesian)
            {
                return point->y();
            } else
            {
                return QVariant();
            }
            break;
        case ANGLE_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Polar)
            {
                return point->angle();
            } else
            {
                return QVariant();
            }
            break;
        case DISTANCE_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Polar)
            {
                return point->distance();
            } else
            {
                return QVariant();
            }
            break;
        case COMMENT_COLUMN:
            return point->comment();
            break;
        }
        break;

    case Qt::BackgroundRole:
        switch (index.column())
        {
        case NAME_COLUMN:
            return QBrush(QColor("#F5F5F5"));
            break;
        case DEFINITION_TYPE_COLUMN:
            return QBrush(QColor("#F5F5F5"));
            break;
        case BASE_POINT_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Geo)
            {
                return QBrush(QColor("#DEDEDE"));
            }
            else if (!point->basePoint() && !point->basePointName().isEmpty())
            {
                return QBrush(QColor("red"));
            }
            else
            {
                return QBrush(QColor("#F5F5F5"));
            }
            break;
        case LATITUDE_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Geo)
            {
                return QBrush(QColor("#F5F5F5"));
            } else
            {
                return QBrush(QColor("#DEDEDE"));
            }
            break;
        case LONGITUDE_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Geo)
            {
                return QBrush(QColor("#F5F5F5"));
            } else
            {
                return QBrush(QColor("#DEDEDE"));
            }
            break;
        case X_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Cartesian)
            {
                return QBrush(QColor("#F5F5F5"));
            } else
            {
                return QBrush(QColor("#DEDEDE"));
            }
            break;
        case Y_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Cartesian)
            {
                return QBrush(QColor("#F5F5F5"));
            } else
            {
                return QBrush(QColor("#DEDEDE"));
            }
            break;
        case ANGLE_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Polar)
            {
                return QBrush(QColor("#F5F5F5"));
            } else
            {
                return QBrush(QColor("#DEDEDE"));
            }
            break;
        case DISTANCE_COLUMN:
            if (point->definitionType() == IqAmeGeoPoint::Polar)
            {
                return QBrush(QColor("#F5F5F5"));
            } else
            {
                return QBrush(QColor("#DEDEDE"));
            }
            break;
        case COMMENT_COLUMN:
            return QBrush(QColor("#F5F5F5"));
            break;
        }
        break;

    case Qt::ToolTipRole:
        switch (index.column())
        {
        case BASE_POINT_COLUMN:
            if (!point->basePoint() && !point->basePointName().isEmpty())
                return tr("Point \"%0\" does not exist.").arg(point->basePointName());
            break;
        }
    }

    return QVariant();
}

void IqAmeGeoPointsModel::startLoadData()
{
    beginResetModel();
}

void IqAmeGeoPointsModel::endLoadData()
{
    endResetModel();
}

bool IqAmeGeoPointsModel::loadFromFile(const QString &fileName, QString *lastError)
{
    qDebug() << tr("Starting parsing \"%0\"...").arg(fileName);

    //Удалим старые данные
    qDeleteAll(_points);
    _points.clear();
    _pointsIndex.clear();
    _pointsIndexCaseInsensitive.clear();

    QFile pointsFile (fileName);
    if (!pointsFile.open(QFile::ReadOnly))
    {
        if (lastError)
            *lastError = tr("Can not open \"%0\" file.").arg(fileName);
        qWarning() << tr("Can not open \"%0\" file.").arg(fileName);

        return false;
    }

    QByteArray fileData = pointsFile.readAll();

    QString fileStrings = IqAmeApplication::defaultTextCodec()->toUnicode(fileData);

    QStringList fileStringList = fileStrings.split("\n");

    //Удаляем первые 2 строки
    fileStringList.removeFirst();
    fileStringList.removeFirst();

    //Распарсим точки
    foreach (QString pointString, fileStringList)
    {
        if (pointString.trimmed().isEmpty())
            continue;

        if (pointString.trimmed().left(1) == ";")
            continue;

        IqAmeGeoPoint *point = new IqAmeGeoPoint();
        if (point->fromString(pointString.trimmed()))
        {
            //Проверим, чтоб для данного имени точки уже не была точка
            if (!_pointsIndexCaseInsensitive.contains(point->name().toLower()))
            {
                _points.append(point);
                _pointsIndex[point->name()] = point;
                _pointsIndexCaseInsensitive[point->name().toLower()] = point;
            }
            else
            {
                qWarning() << tr("Found dublicat of poin from string \"%0\". Skipped.").arg(pointString.trimmed());
                delete point;
            }
        }
        else
        {
            qWarning() << tr("Error on create point from string \"%0\"").arg(pointString.trimmed());
            delete point;
        }
    }

    //Пройдемся по всем точкам и назначим им базовые точки
    foreach (IqAmeGeoPoint *childPoint, _points)
    {
        if (childPoint->basePointName().isEmpty())
            continue;

        IqAmeGeoPoint *basePoint = point(childPoint->basePointName());
        childPoint->setBasePoint(basePoint);
    }

    return true;
}

IqAmeGeoPoint* IqAmeGeoPointsModel::point(const QString &name, Qt::CaseSensitivity caseSensitivity) const
{
    if (caseSensitivity)
    {
        return _pointsIndex[name.trimmed()];
    }
    else
    {
        return _pointsIndexCaseInsensitive[name.trimmed().toLower()];
    }
}

Qt::ItemFlags IqAmeGeoPointsModel::flags(const QModelIndex &index) const
{
    if (index.row() < 0 || index.row() >= rowCount())
        return QAbstractTableModel::flags(index);

    if (index.column() < 0 || index.column() >= columnCount())
        return QAbstractTableModel::flags(index);

    IqAmeGeoPoint *point = _points.at(index.row());

    if (!point)
        return QAbstractTableModel::flags(index);


    switch (index.column())
    {
    case NAME_COLUMN:
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        break;
    case DEFINITION_TYPE_COLUMN:
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        break;
    case BASE_POINT_COLUMN:
        if (point->definitionType() != IqAmeGeoPoint::Geo)
        {
            return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        } else
        {
            return Qt::NoItemFlags;
        }
        break;
    case LATITUDE_COLUMN:
        if (point->definitionType() == IqAmeGeoPoint::Geo)
        {
            return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        } else
        {
            return Qt::NoItemFlags;
        }
        break;
    case LONGITUDE_COLUMN:
        if (point->definitionType() == IqAmeGeoPoint::Geo)
        {
            return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        } else
        {
            return Qt::NoItemFlags;
        }
        break;
    case X_COLUMN:
        if (point->definitionType() == IqAmeGeoPoint::Cartesian)
        {
            return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        } else
        {
            return Qt::NoItemFlags;
        }
        break;
    case Y_COLUMN:
        if (point->definitionType() == IqAmeGeoPoint::Cartesian)
        {
            return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        } else
        {
            return Qt::NoItemFlags;
        }
        break;
    case ANGLE_COLUMN:
        if (point->definitionType() == IqAmeGeoPoint::Polar)
        {
            return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        } else
        {
            return Qt::NoItemFlags;
        }
        break;
    case DISTANCE_COLUMN:
        if (point->definitionType() == IqAmeGeoPoint::Polar)
        {
            return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        } else
        {
            return Qt::NoItemFlags;
        }
        break;
    case COMMENT_COLUMN:
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        break;
    }

    return QAbstractTableModel::flags(index);
}

IqAmeGeoPoint * IqAmeGeoPointsModel::at(const int row) const
{
    if (row < 0 || row >= _points.count())
        return NULL;

    return _points.at(row);
}

bool IqAmeGeoPointsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    if (index.row() < 0 || index.row() >= rowCount())
        return false;

    if (index.column() < 0 || index.column() >= columnCount())
        return false;

    IqAmeGeoPoint *point = _points.at(index.row());

    if (!point)
        return false;

    bool result = false;

    switch (index.column())
    {
    case NAME_COLUMN:
    {
        if (point->name() != value.toString())
        {
            //Найдем точку данным названием
            if (this->point(value.toString(), Qt::CaseInsensitive))
            {
                QMessageBox::warning(NULL, tr("Name setting failed."), tr("Point with name \"%0\" already exist.")
                                     .arg(value.toString()));
                result = false;
            }
            else
            {
                //Удалим из индекса старую точку
                _pointsIndex.remove(value.toString());
                _pointsIndexCaseInsensitive.remove(value.toString().toLower());
                //Добавим в индекс новую точку
                _pointsIndex[value.toString()] = point;
                _pointsIndexCaseInsensitive[value.toString().toLower()] = point;

                point->setName(value.toString());
                result = true;
            }
        }
        else
        {
            result = true;
        }
        break;
    }
    case DEFINITION_TYPE_COLUMN:
        result = true;
        break;
    case BASE_POINT_COLUMN:
        result = true;
        break;
    case LATITUDE_COLUMN:
        qreal latitude;
        result = IqAmeGeoHelper::latitudeFromString(value.toString(), latitude);
        if (result)
        {
            point->setLatitude(latitude);
        }
        else
        {
            QMessageBox::warning(NULL, tr("Latitude setting failed."), tr("Latitude must be in format [NS]ddmmssnn, where: \n"
                                                                          "\tdd - degrees, \n"
                                                                          "\tmm-minute, \n"
                                                                          "\tss - seconds \n"
                                                                          "\tnn - millisecond."));
        }
        break;
    case LONGITUDE_COLUMN:
        qreal longitude;
        result = IqAmeGeoHelper::longitudeFromString(value.toString(), longitude);
        if (result)
        {
            point->setLongitude(longitude);
        }
        else
        {
            QMessageBox::warning(NULL, tr("Longitude setting failed."), tr("Longitude must be in format [NS]dddmmssnn, where: \n"
                                                                           "\tddd - degrees, \n"
                                                                           "\tmm-minute, \n"
                                                                           "\tss - seconds \n"
                                                                           "\tnn - millisecond."));
        }
        break;
    case X_COLUMN:
        point->setX(value.toDouble());
        result = true;
        break;
    case Y_COLUMN:
        point->setY(value.toDouble());
        result = true;
        break;
    case ANGLE_COLUMN:
        point->setAngle(value.toDouble());
        result = true;
        break;
    case DISTANCE_COLUMN:
        point->setDistance(value.toDouble());
        result = true;
        break;
    case COMMENT_COLUMN:
        point->setComment(value.toString());
        result = true;
        break;
    }

    if (result)
        emit dataChanged(this->index(index.row(), 0), this->index(index.row(), columnCount() - 1));

    return true;
}

int IqAmeGeoPointsModel::row(const IqAmeGeoPoint *point) const
{
    if (point)
    {
        return _points.indexOf(const_cast<IqAmeGeoPoint *>(point));
    }

    return -1;
}

bool IqAmeGeoPointsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    int correctRow = row;
    if (row < 0)
        correctRow = 0;

    if (row > rowCount())
        correctRow = rowCount();

    emit beginInsertRows(parent, correctRow, correctRow + count - 1);
    for(int i = 0; i < count; i++)
    {
        IqAmeGeoPoint *newPoint = new IqAmeGeoPoint();

        _points.insert(row, newPoint);
    }
    emit endInsertRows();

    return true;
}

bool IqAmeGeoPointsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0)
        return false;

    if (row + count > rowCount())
        return false;

    for (int i = row + count - 1; i >= row; i--)
    {
        if (_points.at(i)->relativePoints().count() != 0)
            return false;
    }

    emit beginRemoveRows(parent, row, row + count - 1);
    for (int i = row + count - 1; i >= row; i--)
    {
        delete _points.at(i);
        _points.removeAt(i);
    }
    emit endRemoveRows();

    return true;
}
