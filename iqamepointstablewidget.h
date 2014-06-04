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
    explicit IqAmePointsTableWidget(QWidget *parent = 0);
    ~IqAmePointsTableWidget();

    void setModel(IqAmeGeoPointsModel *model);

private:
    Ui::IqAmePointsTableWidget *ui;
};

#endif // IQAMEPOINTSTABLEWIDGET_H
