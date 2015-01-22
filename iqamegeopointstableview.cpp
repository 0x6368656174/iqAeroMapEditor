#include "iqamegeopointstableview.h"
#include <QInputDialog>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QModelIndexList>
#include <QMessageBox>

IqAmeGeoPointsTableView::IqAmeGeoPointsTableView(QWidget *parent) :
    QTableView(parent),
    m_contextMenu(new QMenu(this)),
    m_findBasePointAction(new QAction(this)),
    m_addPointAction(new QAction(this)),
    m_removePointAction(new QAction(this)),
    m_pointDependingAction(new QAction(this)),
    m_geoPointModel(Q_NULLPTR),
    m_sortFilterModel(new IqAmeGeoPointsSortFilterModel(this)),
    m_delegate(new IqAmeGeoPointsTableDelegate(this))
{
    setItemDelegate(m_delegate);

    QTableView::setModel(m_sortFilterModel);

    m_addPointAction->setText(tr("Add point"));
    m_addPointAction->setIcon(QIcon("://icons/appbar.list.add.png"));
    connect(m_addPointAction, SIGNAL(triggered()), this, SLOT(addRow()));
    m_contextMenu->addAction(m_addPointAction);

    m_removePointAction->setText(tr("Remove point"));
    m_removePointAction->setIcon(QIcon("://icons/appbar.list.delete.inline.png"));
    connect(m_removePointAction, SIGNAL(triggered()), this, SLOT(removeSelectedRows()));
    m_contextMenu->addAction(m_removePointAction);

    m_pointDependingAction->setText(tr("Point depending"));
    m_pointDependingAction->setIcon(QIcon("://icons/appbar.link.png"));
    connect(m_pointDependingAction, SIGNAL(triggered()), this, SLOT(showPointDepending()));
    m_contextMenu->addAction(m_pointDependingAction);

    m_findBasePointAction->setText(tr("Move to &base point"));
    m_findBasePointAction->setShortcut(QKeySequence(tr("Ctrl+B", "Move to base point")));
    connect(m_findBasePointAction, SIGNAL(triggered()), this, SLOT(findBasePoint()));
    m_contextMenu->addAction(m_findBasePointAction);

    connect(selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(checkActions(QModelIndex,QModelIndex)));
    connect(selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(checkSelection()));
    connect(model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(checkActions(QModelIndex,QModelIndex)));
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    setContextMenuPolicy(Qt::CustomContextMenu);
}

void IqAmeGeoPointsTableView::showContextMenu(const QPoint &pos)
{
    m_currentIndex = indexAt(pos);

    if (m_currentIndex.isValid())
        m_contextMenu->exec(QCursor::pos());

    m_currentIndex = QModelIndex();
}

void IqAmeGeoPointsTableView::checkActions(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    if (m_geoPointModel) {
        m_addPointAction->setEnabled(true);

        IqAmeGeoPoint *point = m_geoPointModel->point(model()->data(model()->index(current.row(), IqAmeGeoPointsModel::NAME_COLUMN)).toString());

        if (point) {
            m_removePointAction->setEnabled(true);

            if (point->definitionType() != IqAmeGeoPoint::Geo && point->basePoint()) {
                m_findBasePointAction->setEnabled(true);
            } else {
                m_findBasePointAction->setEnabled(false);
            }
        }
    } else {
        m_addPointAction->setEnabled(false);
        m_removePointAction->setEnabled(false);
        m_findBasePointAction->setEnabled(false);
    }
}

void IqAmeGeoPointsTableView::setModel(IqAmeGeoPointsModel *model)
{
    if (m_geoPointModel != model) {
        m_geoPointModel = model;

        connect(m_geoPointModel, SIGNAL(modelAboutToBeReset()), this, SLOT(disableSortModel()));
        connect(m_geoPointModel, SIGNAL(modelReset()), this, SLOT(enableSortModel()));
    }
}

void IqAmeGeoPointsTableView::disableSortModel()
{
    m_delegate->setSourceGeoPointsModel(Q_NULLPTR);
    m_sortFilterModel->setSourceModel(Q_NULLPTR);
}

void IqAmeGeoPointsTableView::enableSortModel()
{

    m_delegate->setSourceGeoPointsModel(m_geoPointModel);
    m_sortFilterModel->setSourceModel(m_geoPointModel);
    m_sortFilterModel->invalidate();
}

void IqAmeGeoPointsTableView::findBasePoint()
{
    if (m_geoPointModel) {
        QModelIndex current = m_currentIndex;
        if (!current.isValid())
            current = currentIndex();

        QString basePointName = model()->data(model()->index(current.row(), IqAmeGeoPointsModel::BASE_POINT_COLUMN)).toString();

        if (!basePointName.isEmpty() && m_geoPointModel) {
            int pointRow = m_geoPointModel->row(m_geoPointModel->point(basePointName));

            QModelIndex pointIndex = m_sortFilterModel->mapFromSource(m_geoPointModel->index(pointRow, 0));

            clearSelection();
            selectRow(pointIndex.row());
            showRow(pointIndex.row());
        }
    }
}

void IqAmeGeoPointsTableView::addRow()
{
    if (m_geoPointModel) {
        bool ok = true;
        QString pointName = QInputDialog::getText(this, tr("Point name"), tr("Enter point name"), QLineEdit::Normal, "",&ok);
        IqAmeGeoPoint *existPoint = m_geoPointModel->point(pointName, Qt::CaseInsensitive);
        while ((pointName.isEmpty() || existPoint) && ok) {
            if (pointName.isEmpty()) {
                pointName =  QInputDialog::getText(this, tr("Point name"), tr("Point name must not empy! Enter point name"), QLineEdit::Normal, pointName, &ok);
                existPoint = m_geoPointModel->point(pointName, Qt::CaseInsensitive);
                continue;
            }
            if (existPoint) {
                pointName =  QInputDialog::getText(this, tr("Point name"), tr("Point with this name already exist! Enter new point name"), QLineEdit::Normal, pointName, &ok);
                existPoint = m_geoPointModel->point(pointName, Qt::CaseInsensitive);
                continue;
            }
        }

        if (!ok)
            return;

        QModelIndex current = m_currentIndex;
        if (!current.isValid())
            current = currentIndex();

        int row = m_sortFilterModel->mapToSource(current).row() + 1;

        m_geoPointModel->insertRow(row);
        m_geoPointModel->setData(m_geoPointModel->index(row, IqAmeGeoPointsModel::NAME_COLUMN), pointName);

        QModelIndex pointIndex = m_sortFilterModel->mapFromSource(m_geoPointModel->index(row, 0));

        clearSelection();
        selectRow(pointIndex.row());
        showRow(pointIndex.row());
    }
}

void IqAmeGeoPointsTableView::removeSelectedRows()
{
    if (m_geoPointModel) {
        QModelIndex current = m_currentIndex;
        if (!current.isValid())
            current = currentIndex();

        QSet<int> rowToRemove;

        foreach (QModelIndex selection, selectionModel()->selectedIndexes()) {
            rowToRemove << selection.row();
        }

        //Если мы тыкнули внутрь выделения, то удалим все выделение
        if (rowToRemove.contains(current.row())) {

            if (rowToRemove.isEmpty())
                return;

            QList<int> sortRowToRemove = rowToRemove.toList();
            qSort(sortRowToRemove);

            foreach (int row, sortRowToRemove) {
                if (!rowAvailableToBeRemoved(row))
                    return;
            }

            int fistRow = sortRowToRemove.first();

            for (int i = sortRowToRemove.count() - 1; i > -1; i--) {
                m_geoPointModel->removeRow(m_sortFilterModel->mapToSource(model()->index(sortRowToRemove[i], 0)).row());
            }

            clearSelection();
            selectRow(fistRow);
            showRow(fistRow);
        } else {
            //Иначе удалим только строку в которую тыкнули
            if (!rowAvailableToBeRemoved(current.row()))
                return;

            int row = current.row();

            m_geoPointModel->removeRow(m_sortFilterModel->mapToSource(current).row());

            clearSelection();
            selectRow(row);
            showRow(row);
        }
    }
}

void IqAmeGeoPointsTableView::checkSelection()
{
    emit selectionChanged(selectionModel()->hasSelection());
}

bool IqAmeGeoPointsTableView::rowAvailableToBeRemoved(const int row)
{
    if (m_geoPointModel) {
        QString pointName = model()->data(model()->index(row, IqAmeGeoPointsModel::NAME_COLUMN)).toString();

        QList<IqAmeGeoPoint *> relativePoints = m_geoPointModel->point(pointName)->relativePoints();
        if (relativePoints.count() == 0) {
            return true;
        } else {


            QString dependsPoins;
            foreach (IqAmeGeoPoint *point, relativePoints) {
                dependsPoins += tr("\t\t\t\"%0\"\n", "Indent for Can not remove point message").arg(point->name());
            }

            QMessageBox::warning(this, tr("Can not remove point"), tr("Point \"%0\" can not removed.\n\n"
                                 "Depend on it the following points:"
                                 "\t%1")
                                 .arg(pointName)
                                 .arg(dependsPoins.trimmed()));

            return false;
        }
    }

    return false;
}


void IqAmeGeoPointsTableView::showPointDepending()
{
    QString pointName = model()->data(model()->index(currentIndex().row(), IqAmeGeoPointsModel::NAME_COLUMN)).toString();

    if (pointName.isEmpty())
        return;

    IqAmeGeoPoint *point = m_geoPointModel->point(pointName);

    if (!point)
        return;

    QString dependsPoints;
    foreach (IqAmeGeoPoint *dependPoint, point->relativePoints()) {
        dependsPoints += "\t\"" + dependPoint->name() + "\"\n";
    }

    if (dependsPoints.isEmpty())
        dependsPoints = tr("NONE");

    QMessageBox::information(this, tr("Point depending"), tr("Depending for point \"%0\"\n\n"
                             "Other point:"
                             "\t%1")
                             .arg(pointName)
                             .arg(dependsPoints.trimmed()));
}
