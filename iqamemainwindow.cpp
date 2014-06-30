#include "iqamemainwindow.h"
#include "ui_iqamemainwindow.h"
#include "iqameapplication.h"


IQAMEMainWindow::IQAMEMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IQAMEMainWindow)
{
    ui->setupUi(this);

    IqAmeApplication::aeroMapModel()->loadFromFolder("/mnt/windows/mapsData/");

    ui->layerTreeView->setModel(IqAmeApplication::aeroMapModel());
    connect(ui->layerTreeView, SIGNAL(pointsClicked()), this, SLOT(showPoints()));
    connect(ui->layerTreeView, SIGNAL(layerClicked(IqAmeLayer*)), this, SLOT(showLayer(IqAmeLayer*)));

    ui->pointTableWidget->setModel(IqAmeApplication::aeroMapModel()->pointsModel());

    QItemSelection pointSelection (ui->layerTreeView->model()->index(0, 0),
                                   ui->layerTreeView->model()->index(0, 1));
    ui->layerTreeView->selectionModel()->select(pointSelection, QItemSelectionModel::Select | QItemSelectionModel::Current);
}

IQAMEMainWindow::~IQAMEMainWindow()
{
    delete ui;
}

void IQAMEMainWindow::showPoints()
{
    ui->editorWidget->hide();
    ui->pointTableWidget->show();
}

void IQAMEMainWindow::showLayer(IqAmeLayer *layer)
{
    Q_UNUSED(layer);
    ui->editorWidget->setLayer(layer);
    ui->pointTableWidget->hide();
    ui->editorWidget->show();
}
