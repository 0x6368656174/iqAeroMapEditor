#include "iqamemainwindow.h"
#include "ui_iqamemainwindow.h"
#include "iqameapplication.h"
#include <QFileDialog>

IqAmeMainWindow::IqAmeMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IQAMEMainWindow)
{
    ui->setupUi(this);

    ui->layerTreeView->setModel(IqAmeApplication::aeroMapModel());
    connect(ui->layerTreeView, SIGNAL(pointsClicked()), this, SLOT(showPoints()));
    connect(ui->layerTreeView, SIGNAL(layerClicked(IqAmeLayer*)), this, SLOT(showLayer(IqAmeLayer*)));

    ui->pointTableWidget->setModel(IqAmeApplication::aeroMapModel()->pointsModel());

#if QT_VERSION >= 0x050000
        ui->layerTreeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        ui->layerTreeView->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
        ui->layerTreeView->header()->setSectionResizeMode(2, QHeaderView::Stretch);
#else
        ui->layerTreeView->header()->setResizeMode(0, QHeaderView::ResizeToContents);
        ui->layerTreeView->header()->setResizeMode(1, QHeaderView::ResizeToContents);
        ui->layerTreeView->header()->setResizeMode(2, QHeaderView::Stretch);
#endif

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFolder()));

    ui->editorWidget->hide();
    ui->pointTableWidget->show();
}

IqAmeMainWindow::~IqAmeMainWindow()
{
    delete ui;
}

void IqAmeMainWindow::openFolder()
{
    QString folder = QFileDialog::getExistingDirectory(this, tr("Open folder"));
    if (!folder.isEmpty())
    {
        IqAmeApplication::aeroMapModel()->startLoadData();
        IqAmeApplication::aeroMapModel()->loadFromFolder(folder);
        IqAmeApplication::aeroMapModel()->endLoadData();
    }
}

void IqAmeMainWindow::showPoints()
{
    ui->editorWidget->hide();
    ui->pointTableWidget->show();
}

void IqAmeMainWindow::showLayer(IqAmeLayer *layer)
{
    Q_UNUSED(layer);
    ui->editorWidget->setLayer(layer);
    ui->pointTableWidget->hide();
    ui->editorWidget->show();
}
