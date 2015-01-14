#ifndef IQAMEGEOPOINTSTABLEVIEW_H
#define IQAMEGEOPOINTSTABLEVIEW_H

#include <QTableView>
#include "iqamegeopointssortfiltermodel.h"
#include "iqamegeopointsmodel.h"
#include "iqamegeopointstabledelegate.h"

class IqAmeGeoPointsTableView : public QTableView
{
    Q_OBJECT
public:
    explicit IqAmeGeoPointsTableView(QWidget *parent = Q_NULLPTR);

    void setModel(IqAmeGeoPointsModel *model);

signals:
    void selectionChanged(bool hasSelected);

public slots:
    void addRow();
    void removeSelectedRows();
    void showPointDepending();

private slots:
    void checkActions(const QModelIndex & current, const QModelIndex & previous);

    void showContextMenu(const QPoint &pos);

    void findBasePoint();

    void checkSelection();

    void disableSortModel();

    void enableSortModel();

private:
    QMenu *m_contextMenu;
    QAction *m_findBasePointAction;
    QAction *m_addPointAction;
    QAction *m_removePointAction;
    QAction *m_pointDependingAction;
    QModelIndex m_currentIndex;
    IqAmeGeoPointsModel *m_geoPointModel;
    IqAmeGeoPointsSortFilterModel *m_sortFilterModel;
    IqAmeGeoPointsTableDelegate *m_delegate;

    bool rowAvailableToBeRemoved(const int row);
};

#endif // IQAMEGEOPOINTSTABLEVIEW_H
