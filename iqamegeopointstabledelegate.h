#ifndef IQAMEGEOPOINTSTABLEDELEGATE_H
#define IQAMEGEOPOINTSTABLEDELEGATE_H

#include <QStyledItemDelegate>
#include "iqamegeopointsmodel.h"

class IqAmeGeoPointsTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit IqAmeGeoPointsTableDelegate(QObject *parent = Q_NULLPTR);

    void setSourceGeoPointsModel(IqAmeGeoPointsModel *model);

public:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void setEditorData (QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private:
    IqAmeGeoPointsModel *m_sourceGeoPointsModel;
};

#endif // IQAMEGEOPOINTSTABLEDELEGATE_H
