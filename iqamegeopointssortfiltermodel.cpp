#include "iqamegeopointssortfiltermodel.h"

IqAmeGeoPointsSortFilterModel::IqAmeGeoPointsSortFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    _geoPointsModel(NULL)
{
}

void IqAmeGeoPointsSortFilterModel::setSourceModel(IqAmeGeoPointsModel *sourceModel)
{
    if (_geoPointsModel != sourceModel)
    {
        _geoPointsModel = sourceModel;

        QSortFilterProxyModel::setSourceModel(sourceModel);
    }
}

bool IqAmeGeoPointsSortFilterModel::lessThan(const QModelIndex &left,
                                             const QModelIndex &right) const
{
    IqAmeGeoPoint *leftPoint = _geoPointsModel->at (left.row());
    IqAmeGeoPoint *rightPoint = _geoPointsModel->at (right.row());

    if (!leftPoint)
        return false;
    if (!rightPoint)
        return true;

    switch (left.column())
    {
    case IqAmeGeoPointsModel::NAME_COLUMN:
        return leftPoint->name() < rightPoint->name();
    case IqAmeGeoPointsModel::DEFINITION_TYPE_COLUMN:
        return leftPoint->definitionType() < rightPoint->definitionType();
    case IqAmeGeoPointsModel::BASE_POINT_COLUMN:
    {
        IqAmeGeoPoint *leftBasePoint = leftPoint->basePoint();
        IqAmeGeoPoint *rightBasePoint = rightPoint->basePoint();
        if (!leftBasePoint)
            return false;
        if (!rightBasePoint)
            return true;
        return leftBasePoint->name() < rightBasePoint->name();
    }
    case IqAmeGeoPointsModel::LATITUDE_COLUMN:
        return leftPoint->latitude() < rightPoint->latitude();
    case IqAmeGeoPointsModel::LONGITUDE_COLUMN:
        return leftPoint->longitude() < rightPoint->longitude();
    case IqAmeGeoPointsModel::X_COLUMN:
        return leftPoint->x() < rightPoint->x();
    case IqAmeGeoPointsModel::Y_COLUMN:
        return leftPoint->y() < rightPoint->y();
    case IqAmeGeoPointsModel::ANGLE_COLUMN:
        return leftPoint->angle() < rightPoint->angle();
    case IqAmeGeoPointsModel::DISTANCE_COLUMN:
        return leftPoint->distance() < rightPoint->distance();
    case IqAmeGeoPointsModel::COMMENT_COLUMN:
        return leftPoint->comment() < rightPoint->comment();
    }

    return true;
}
