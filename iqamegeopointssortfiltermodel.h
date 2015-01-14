#ifndef IQAMEGEOPOINTSSORTFILTERMODEL_H
#define IQAMEGEOPOINTSSORTFILTERMODEL_H

#include <QSortFilterProxyModel>
#include "iqamegeopointsmodel.h"

class IqAmeGeoPointsSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit IqAmeGeoPointsSortFilterModel(QObject *parent = Q_NULLPTR);

    void setSourceModel(IqAmeGeoPointsModel *sourceModel);

protected:
    virtual bool lessThan(const QModelIndex &left,
                          const QModelIndex &right) const Q_DECL_OVERRIDE;

private:
    IqAmeGeoPointsModel *m_geoPointsModel;
};

#endif // IQAMEGEOPOINTSSORTFILTERMODEL_H
