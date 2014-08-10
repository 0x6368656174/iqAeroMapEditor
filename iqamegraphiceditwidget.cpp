#include "iqamegraphiceditwidget.h"
#include "ui_iqamegraphiceditwidget.h"
#include <QSplitter>
#include <QHBoxLayout>
#include <QHeaderView>

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
#if QT_VERSION >= 0x050000
        ui->shapesTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        ui->shapesTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
#else
        ui->shapesTableView->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
        ui->shapesTableView->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
#endif
    }
}
