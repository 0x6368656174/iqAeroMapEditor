#ifndef IQAMESHAPESMODEL_H
#define IQAMESHAPESMODEL_H

#include <QAbstractTableModel>
#include "iqamenamedshapeobject.h"
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

    explicit IqAmeShapesModel(QObject *parent = Q_NULLPTR);

    QList<IqAmeNamedShapeObject *> toList() const;

    bool loadFromFile(const QString &fileName, QString *lastError = Q_NULLPTR);

public:
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    virtual QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

private:
    QList<IqAmeNamedShapeObject *> m_shapes;

    IqAmeShapesAttributes *m_baseAttributes;

    void clear();
};

#endif // IQAMESHAPESMODEL_H
