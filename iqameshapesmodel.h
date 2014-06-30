#ifndef IQAMESHAPESMODEL_H
#define IQAMESHAPESMODEL_H

#include <QAbstractTableModel>
#include "iqamegraphicobject.h"

class IqAmeShapesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum ColumnsPosition
    {
        TYPE_COLUMN,
        NAME_COLUMN
    };

    explicit IqAmeShapesModel(QObject *parent = 0);

    bool loadFromFile(const QString &fileName, QString *lastError = 0);

public:
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const {Q_UNUSED(parent); return 2;}

    int rowCount(const QModelIndex &parent = QModelIndex()) const {Q_UNUSED(parent); return _shapes.count();}

private:
    QList<IqAmeGraphicObject *> _shapes;

    void clear();
};

#endif // IQAMESHAPESMODEL_H
