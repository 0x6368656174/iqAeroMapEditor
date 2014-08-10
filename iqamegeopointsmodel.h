#ifndef IQAMEGEOPOINTSMODEL_H
#define IQAMEGEOPOINTSMODEL_H

#include <QAbstractTableModel>
#include "iqamegeopoint.h"

class IqAmeGeoPointsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum ColumnsPosition
    {
        NAME_COLUMN,
        DEFINITION_TYPE_COLUMN,
        BASE_POINT_COLUMN,
        LATITUDE_COLUMN,
        LONGITUDE_COLUMN,
        X_COLUMN,
        Y_COLUMN,
        ANGLE_COLUMN,
        DISTANCE_COLUMN,
        COMMENT_COLUMN,
    };

    explicit IqAmeGeoPointsModel(QObject *parent = 0);

    void startLoadData();

    void endLoadData();

    ~IqAmeGeoPointsModel();

    bool loadFromFile(const QString &fileName, QString *lastError = 0);

    int row(const IqAmeGeoPoint *point) const;

    IqAmeGeoPoint *point (const QString &name, Qt::CaseSensitivity caseSensitivity = Qt::CaseSensitive) const;

    IqAmeGeoPoint *at (const int row) const;

public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const {Q_UNUSED(parent); return _points.count();}

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const {Q_UNUSED(parent); return 10;}

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex & index) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
    QList<IqAmeGeoPoint *> _points;
    QHash<QString, IqAmeGeoPoint *> _pointsIndex;
    QHash<QString, IqAmeGeoPoint *> _pointsIndexCaseInsensitive;
};

#endif // IQAMEGEOPOINTSMODEL_H
