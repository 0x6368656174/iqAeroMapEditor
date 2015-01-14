#ifndef IQAMEPOINTSTABLEWIDGET_H
#define IQAMEPOINTSTABLEWIDGET_H

#include <QWidget>
#include "iqamegeopointsmodel.h"

namespace Ui {
class IqAmePointsTableWidget;
}

class IqAmePointsTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IqAmePointsTableWidget(QWidget *parent = Q_NULLPTR);
    ~IqAmePointsTableWidget();

    void setModel(IqAmeGeoPointsModel *model);

private:
    Ui::IqAmePointsTableWidget *ui;
};

#endif // IQAMEPOINTSTABLEWIDGET_H
