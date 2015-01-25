#include "iqamegraphiceditwidget.h"
#include "ui_iqamegraphiceditwidget.h"
#include <QSplitter>
#include <QHBoxLayout>
#include <QHeaderView>
#include "iqameapplication.h"
#include "iqameshapelink.h"

IqAmeGraphicEditWidget::IqAmeGraphicEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IqAmeGraphicEditWidget),
    m_updataTableSelectedInProcess(false),
    m_updateGraphicsViewSelectedInProcess(false)
{
    ui->setupUi(this);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(ui->shapesTableView);
    splitter->addWidget(ui->openGlWidget);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(splitter);

    setLayout(layout);

    connect(ui->openGlWidget, &IqLayerView::selectionFinished, this, &IqAmeGraphicEditWidget::updateTableSelected);
}

IqAmeGraphicEditWidget::~IqAmeGraphicEditWidget()
{
    delete ui;
}

void IqAmeGraphicEditWidget::setLayer(IqAmeLayer *layer)
{
    if (layer) {
        if (ui->shapesTableView->model()) {
            IqAmeShapesModel *oldModel = qobject_cast<IqAmeShapesModel *>(ui->shapesTableView->model());
            Q_CHECK_PTR(oldModel);
            oldModel->setInteractive(false);
        }
        ui->shapesTableView->setModel(layer->shapesModel());
        connect(ui->shapesTableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &IqAmeGraphicEditWidget::updateGraphicsViewSelected);
        layer->shapesModel()->setInteractive(true);
#if QT_VERSION >= 0x050000
        ui->shapesTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        ui->shapesTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
#else
        ui->shapesTableView->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
        ui->shapesTableView->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
#endif
    }
}

void IqAmeGraphicEditWidget::updateTableSelected()
{
    IqAmeShapesModel *shapeModel = qobject_cast<IqAmeShapesModel *>(ui->shapesTableView->model());
    if (!shapeModel)
        return;

    if (m_updateGraphicsViewSelectedInProcess)
        return;

    m_updataTableSelectedInProcess = true;

    ui->shapesTableView->clearSelection();

    QHash<QGraphicsItem *, int> itemsRows;
    int i = 0;
    foreach (IqAmeNamedShapeObject *shapeObject, shapeModel->toList()) {
        foreach (QGraphicsItem *item, shapeObject->graphicsItems()) {
            itemsRows[item] = i;
        }
        i++;
    }

    QItemSelection selection;
    QAbstractItemModel *model =ui->shapesTableView->model();
    int lastColumnt = model->columnCount() - 1;
    Q_ASSERT(lastColumnt > -1);
    int itemTableRow = -1;
    int lastFoundItem = -1;
    foreach (QGraphicsItem *item, IqAmeApplication::graphicsScene()->selectedItems()) {
        itemTableRow = itemsRows[item];
        if (itemTableRow != -1) {
            selection.select(model->index(itemTableRow, 0),
                             model->index(itemTableRow, lastColumnt));
            lastFoundItem = itemTableRow;
        }
    }

    ui->shapesTableView->selectionModel()->select(selection, QItemSelectionModel::Select);

    if (lastFoundItem != -1)
        ui->shapesTableView->scrollTo(ui->shapesTableView->model()->index(lastFoundItem, 0), QAbstractItemView::PositionAtCenter);

    m_updataTableSelectedInProcess = false;
}

void IqAmeGraphicEditWidget::updateGraphicsViewSelected()
{
    IqAmeShapesModel *shapeModel = qobject_cast<IqAmeShapesModel *>(ui->shapesTableView->model());
    if (!shapeModel)
        return;

    if (m_updataTableSelectedInProcess)
        return;

    m_updateGraphicsViewSelectedInProcess = true;

    IqAmeApplication::graphicsScene()->clearSelection();

    foreach (const QModelIndex &index, ui->shapesTableView->selectionModel()->selectedRows()) {
        IqAmeNamedShapeObject *shapeObject = shapeModel->toList().at(index.row());
        Q_CHECK_PTR(shapeObject);
        foreach (QGraphicsItem *item, shapeObject->graphicsItems()) {
            Q_CHECK_PTR(item);
            item->setSelected(true);
        }
    }

    m_updateGraphicsViewSelectedInProcess = false;
}

