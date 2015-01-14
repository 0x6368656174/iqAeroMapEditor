#ifndef IQAMEMAPMODEL_H
#define IQAMEMAPMODEL_H

#include <QAbstractItemModel>
#include "iqamelayer.h"
#include "iqamegeopointsmodel.h"

class IqAmeMapModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit IqAmeMapModel(QObject *parent = Q_NULLPTR);

    void startLoadData();

    void endLoadData();

    bool loadFromFolder(const QString& folderName, QString *lastError = Q_NULLPTR);

    IqAmeGeoPointsModel *pointsModel() const;

    IqAmeLayer *rootLayer() const;

public:
    virtual QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    virtual QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    virtual QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    virtual QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

private:
    void clear();

    IqAmeLayer *m_rootLayer;

    IqAmeGeoPointsModel *m_pointsModel;
};

#endif // IQAMEMAPMODEL_H
