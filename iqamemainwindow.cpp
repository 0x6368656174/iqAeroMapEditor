#include "iqamemainwindow.h"
#include "ui_iqamemainwindow.h"
#include "iqameapplication.h"
#if QT_VERSION >= 0x050000
#include <QtConcurrent/QtConcurrentRun>
#else
#include <QtConcurrentRun>
#endif
#include <QFileDialog>
#include <QFutureWatcher>
#include <QApplication>
#include <QSettings>

IqAmeMainWindow::IqAmeMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IQAMEMainWindow),
    m_logDialog(new IqAmeLogDialog(this))
{
    ui->setupUi(this);

    ui->layerTreeView->setModel(IqAmeApplication::aeroMapModel());
    connect(ui->layerTreeView, &IqAmeMapModelTreeView::pointsClicked, this, &IqAmeMainWindow::showPoints);
    connect(ui->layerTreeView, &IqAmeMapModelTreeView::layerClicked, this, &IqAmeMainWindow::showLayer);

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

    connect(ui->actionAntialiasing, &QAction::triggered, this, &IqAmeMainWindow::updateRenderhints);
    connect(ui->actionTextAntialiasing, &QAction::triggered, this, &IqAmeMainWindow::updateRenderhints);
    connect(ui->actionSmoothPixmapTransform, &QAction::triggered, this, &IqAmeMainWindow::updateRenderhints);
    connect(ui->actionHighQualityAntialiasing, &QAction::triggered, this, &IqAmeMainWindow::updateRenderhints);

    ui->editorWidget->hide();
    ui->pointTableWidget->show();
}

IqAmeMainWindow::~IqAmeMainWindow()
{
    delete ui;
}

void IqAmeMainWindow::showLogs()
{
    m_logDialog->open();
}

void IqAmeMainWindow::openFolder()
{
    QString folder = QFileDialog::getExistingDirectory(this, tr("Open folder"));
    if (!folder.isEmpty()) {
        qDebug() << tr("START LOAD MAP DATA...");
        m_loadTimer.restart();
        QApplication::setOverrideCursor(Qt::WaitCursor);
        showLogs();
        IqAmeApplication::aeroMapModel()->startLoadData();

        QFutureWatcher <bool> *watcher = new QFutureWatcher<bool>(this);
        connect(watcher, SIGNAL(finished()), this, SLOT(onLoadFinished()));
        connect(watcher, SIGNAL(finished()), watcher, SLOT(deleteLater()));

        QString* nullResult = Q_NULLPTR;
        QFuture <bool> future = QtConcurrent::run(IqAmeApplication::aeroMapModel(), &IqAmeMapModel::loadFromFolder, folder, nullResult);
        watcher->setFuture(future);
    }
}

void IqAmeMainWindow::onLoadFinished()
{
    IqAmeApplication::aeroMapModel()->endLoadData();
    QApplication::restoreOverrideCursor();
    qDebug() << tr("LOAD MAP DATA FINISHED IN %0 sec")
                .arg(m_loadTimer.elapsed()/1000);
}

void IqAmeMainWindow::updateRenderhints()
{
    ui->editorWidget->setMapViewRenderHint(QPainter::Antialiasing, ui->actionAntialiasing->isChecked());
    ui->editorWidget->setMapViewRenderHint(QPainter::TextAntialiasing, ui->actionTextAntialiasing->isChecked());
    ui->editorWidget->setMapViewRenderHint(QPainter::SmoothPixmapTransform, ui->actionSmoothPixmapTransform->isChecked());
    ui->editorWidget->setMapViewRenderHint(QPainter::HighQualityAntialiasing, ui->actionHighQualityAntialiasing->isChecked());
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
