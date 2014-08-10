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
    explicit IqAmeGeoPointsTableView(QWidget *parent = 0);

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
    QMenu *_contextMenu;
    QAction *_findBasePointAction;
    QAction *_addPointAction;
    QAction *_removePointAction;
    QAction *_pointDependingAction;
    QModelIndex _currentIndex;
    IqAmeGeoPointsModel *_geoPointModel;
    IqAmeGeoPointsSortFilterModel *_sortFilterModel;
    IqAmeGeoPointsTableDelegate *_delegate;

    bool rowAvailableToBeRemoved(const int row);
};

#endif // IQAMEGEOPOINTSTABLEVIEW_H
