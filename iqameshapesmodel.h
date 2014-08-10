#ifndef IQAMESHAPESMODEL_H
#define IQAMESHAPESMODEL_H

#include <QAbstractTableModel>
#include "iqameshapeobject.h"
#include "iqameshapesattributes.h"


class IqAmeShapesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum ColumnsPosition
    {
        COLUMN_TYPE,
        COLUMN_NAME
    };

    enum Roles
    {
        ShapeObject = Qt::UserRole
    };

    explicit IqAmeShapesModel(QObject *parent = 0);

    bool loadFromFile(const QString &fileName, QString *lastError = 0);

public:
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const {Q_UNUSED(parent); return 2;}

    int rowCount(const QModelIndex &parent = QModelIndex()) const {Q_UNUSED(parent); return _shapes.count();}

private:
    QList<IqAmeShapeObject *> _shapes;

    IqAmeShapesAttributes *_baseAttributes;

    void clear();
};

#endif // IQAMESHAPESMODEL_H
