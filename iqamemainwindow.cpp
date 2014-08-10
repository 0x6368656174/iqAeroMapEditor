#include "iqamemainwindow.h"
#include "ui_iqamemainwindow.h"
#include "iqameapplication.h"
#include <QtConcurrentRun>
#include <QFileDialog>
#include <QFutureWatcher>

IqAmeMainWindow::IqAmeMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IQAMEMainWindow),
    _logDialog(new IqAmeLogDialog(this))
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
    connect(ui->actionLogs, SIGNAL(triggered()), this, SLOT(showLogs()));

    ui->editorWidget->hide();
    ui->pointTableWidget->show();
}

IqAmeMainWindow::~IqAmeMainWindow()
{
    delete ui;
}

void IqAmeMainWindow::showLogs()
{
    _logDialog->open();
}

void IqAmeMainWindow::openFolder()
{
    QString folder = QFileDialog::getExistingDirectory(this, tr("Open folder"));
    if (!folder.isEmpty())
    {
        qDebug() << tr("START LOAD MAP DATA...");
        _loadTimer.restart();
        QApplication::setOverrideCursor(Qt::WaitCursor);
        showLogs();
        IqAmeApplication::aeroMapModel()->startLoadData();

        QFutureWatcher <bool> *watcher = new QFutureWatcher<bool>(this);
        connect(watcher, SIGNAL(finished()), this, SLOT(onLoadFinished()));
        connect(watcher, SIGNAL(finished()), watcher, SLOT(deleteLater()));

        QString* nullResult = NULL;

        QFuture <bool> future = QtConcurrent::run(IqAmeApplication::aeroMapModel(), &IqAmeMapModel::loadFromFolder, folder, nullResult);
        watcher->setFuture(future);
    }
}

void IqAmeMainWindow::onLoadFinished()
{
    IqAmeApplication::aeroMapModel()->endLoadData();
    QApplication::restoreOverrideCursor();
    qDebug() << tr("LOAD MAP DATA FINISHED IN %0 sec")
                .arg(_loadTimer.elapsed()/1000);
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
