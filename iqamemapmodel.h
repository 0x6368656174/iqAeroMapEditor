#ifndef IQAMEMAPMODEL_H
#define IQAMEMAPMODEL_H

#include <QAbstractItemModel>
#include "iqamelayer.h"
#include "iqamegeopointsmodel.h"

class IqAmeMapModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit IqAmeMapModel(QObject *parent = 0);

    bool loadFromFolder(const QString& folderName, QString *lastError = NULL);

    inline IqAmeGeoPointsModel* pointsModel() const {return _pointsModel;}

public:
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const{ Q_UNUSED(parent); return 3;}
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

private:
    void clear();

    IqAmeLayer *_rootLayer;

    IqAmeGeoPointsModel *_pointsModel;
};

#endif // IQAMEMAPMODEL_H
