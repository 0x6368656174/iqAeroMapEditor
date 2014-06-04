#include "iqamepointstablewidget.h"
#include "ui_iqamepointstablewidget.h"

IqAmePointsTableWidget::IqAmePointsTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IqAmePointsTableWidget)
{
    ui->setupUi(this);

    connect(ui->poindDependingPushButton, SIGNAL(clicked()), ui->pointsTableView, SLOT(showPointDepending()));
    connect(ui->addPointPushButton, SIGNAL(clicked()), ui->pointsTableView, SLOT(addRow()));
    connect(ui->removePointPushButton, SIGNAL(clicked()), ui->pointsTableView, SLOT(removeSelectedRows()));
    connect(ui->pointsTableView, SIGNAL(selectionChanged(bool)), ui->poindDependingPushButton, SLOT(setEnabled(bool)));
    connect(ui->pointsTableView, SIGNAL(selectionChanged(bool)), ui->removePointPushButton, SLOT(setEnabled(bool)));
}

IqAmePointsTableWidget::~IqAmePointsTableWidget()
{
    delete ui;
}

void IqAmePointsTableWidget::setModel(IqAmeGeoPointsModel *model)
{
    ui->pointsTableView->setModel(model);
}
