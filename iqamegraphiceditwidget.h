#ifndef IQAMEGRAPHICEDITWIDGET_H
#define IQAMEGRAPHICEDITWIDGET_H

#include <QWidget>
#include "iqamelayer.h"

namespace Ui {
class IqAmeGraphicEditWidget;
}

class IqAmeGraphicEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IqAmeGraphicEditWidget(QWidget *parent = 0);
    ~IqAmeGraphicEditWidget();

    void setLayer(IqAmeLayer *layer);

private:
    Ui::IqAmeGraphicEditWidget *ui;
};

#endif // IQAMEGRAPHICEDITWIDGET_H
