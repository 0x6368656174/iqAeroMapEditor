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

    int lastFoundItem = -1;
    foreach (QGraphicsItem *item, IqAmeApplication::graphicsScene()->selectedItems()) {
        Q_CHECK_PTR(item);
        IqAmeShapeLink *shapeLink = dynamic_cast<IqAmeShapeLink *>(item);
        Q_CHECK_PTR(shapeLink);
        Q_CHECK_PTR(shapeLink->namedShapeObject());

        int i = 0;
        foreach (IqAmeNamedShapeObject *shapeObject, shapeModel->toList()) {
            if (shapeObject == shapeLink->namedShapeObject()) {
                //Выделим объект
                ui->shapesTableView->selectionModel()->select(ui->shapesTableView->model()->index(i, 0), QItemSelectionModel::Select | QItemSelectionModel::Rows);
                lastFoundItem = i;
            }
            ++i;
        }
    }

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

    QSet<QGraphicsItem *> currentSelectedItem = IqAmeApplication::graphicsScene()->selectedItems().toSet();
    QSet<QGraphicsItem *> itemToSelect;

    foreach (const QModelIndex &index, ui->shapesTableView->selectionModel()->selectedRows()) {
        IqAmeNamedShapeObject *shapeObject = shapeModel->toList().at(index.row());
        Q_CHECK_PTR(shapeObject);
        foreach (QGraphicsItem *item, shapeObject->graphicsItems()) {
            Q_CHECK_PTR(item);
            if (currentSelectedItem.contains(item)) {
                currentSelectedItem.remove(item);
                continue;
            }
            itemToSelect << item;
        }
    }

    foreach (QGraphicsItem *item, currentSelectedItem) {
        Q_CHECK_PTR(item);
        item->setSelected(false);
    }

    foreach (QGraphicsItem *item, itemToSelect) {
        Q_CHECK_PTR(item);
        item->setSelected(true);
    }

    m_updateGraphicsViewSelectedInProcess = false;
}

