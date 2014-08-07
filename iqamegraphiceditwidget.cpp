#include "iqamegraphiceditwidget.h"
#include "ui_iqamegraphiceditwidget.h"
#include <QSplitter>
#include <QHBoxLayout>

IqAmeGraphicEditWidget::IqAmeGraphicEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IqAmeGraphicEditWidget)
{
    ui->setupUi(this);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(ui->shapesTableView);
    splitter->addWidget(ui->openGlWidget);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(splitter);

    setLayout(layout);
}

IqAmeGraphicEditWidget::~IqAmeGraphicEditWidget()
{
    delete ui;
}

void IqAmeGraphicEditWidget::setLayer(IqAmeLayer *layer)
{
    if (layer)
    {
        ui->shapesTableView->setModel(layer->shapesModel());
        ui->openGlWidget->addLayerToView(layer);
    }
}
