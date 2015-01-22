#ifndef IQAMEGRAPHICEDITWIDGET_H
#define IQAMEGRAPHICEDITWIDGET_H

#include <QWidget>
#include "iqamelayer.h"
#include <QItemSelection>

namespace Ui {
class IqAmeGraphicEditWidget;
}

class IqAmeGraphicEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IqAmeGraphicEditWidget(QWidget *parent = Q_NULLPTR);
    ~IqAmeGraphicEditWidget();

    void setLayer(IqAmeLayer *layer);

private:
    Ui::IqAmeGraphicEditWidget *ui;

    void updateTableSelected();

    void updateGraphicsViewSelected();

private:
    bool m_updataTableSelectedInProcess;
    bool m_updateGraphicsViewSelectedInProcess;
};

#endif // IQAMEGRAPHICEDITWIDGET_H
