#ifndef IQAMEMAPMODELTREEVIEW_H
#define IQAMEMAPMODELTREEVIEW_H

#include <QTreeView>
#include "iqamemapmodel.h"

class IqAmeMapModelTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit IqAmeMapModelTreeView(QWidget *parent = Q_NULLPTR);

    void setModel(IqAmeMapModel * model);

signals:
    void pointsClicked();
    void layerClicked(IqAmeLayer *layer);

private slots:
    void onActivated(const QModelIndex & index);

private:
    IqAmeMapModel *m_mapModel;
};

#endif // IQAMEMAPMODELTREEVIEW_H
