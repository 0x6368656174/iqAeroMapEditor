#ifndef IQAMEGEOPOINTSSORTFILTERMODEL_H
#define IQAMEGEOPOINTSSORTFILTERMODEL_H

#include <QSortFilterProxyModel>
#include "iqamegeopointsmodel.h"

class IqAmeGeoPointsSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit IqAmeGeoPointsSortFilterModel(QObject *parent = 0);

    void setSourceModel(IqAmeGeoPointsModel *sourceModel);

protected:
    virtual bool lessThan(const QModelIndex &left,
                          const QModelIndex &right) const;

private:
    IqAmeGeoPointsModel *_geoPointsModel;
};

#endif // IQAMEGEOPOINTSSORTFILTERMODEL_H
