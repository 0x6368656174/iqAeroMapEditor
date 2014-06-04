#include "iqamegeopointstableview.h"
#include <QInputDialog>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QModelIndexList>
#include <QMessageBox>

IqAmeGeoPointsTableView::IqAmeGeoPointsTableView(QWidget *parent) :
    QTableView(parent),
    _contextMenu(new QMenu(this)),
    _findBasePointAction(new QAction(this)),
    _addPointAction(new QAction(this)),
    _removePointAction(new QAction(this)),
    _pointDependingAction(new QAction(this)),
    _geoPointModel(NULL),
    _sortFilterModel(new QSortFilterProxyModel(this)),
    _delegate(new IqAmeGeoPointsTableDelegate(this))
{
    setItemDelegate(_delegate);

    QTableView::setModel(_sortFilterModel);

    _addPointAction->setText(tr("Add point"));
    _addPointAction->setIcon(QIcon("://icons/table_row_insert.png"));
    connect(_addPointAction, SIGNAL(triggered()), this, SLOT(addRow()));
    _contextMenu->addAction(_addPointAction);

    _removePointAction->setText(tr("Remove point"));
    _removePointAction->setIcon(QIcon("://icons/table_row_delete.png"));
    connect(_removePointAction, SIGNAL(triggered()), this, SLOT(removeSelectedRows()));
    _contextMenu->addAction(_removePointAction);

    _pointDependingAction->setText(tr("Point depending"));
    _pointDependingAction->setIcon(QIcon("://icons/arrow_switch.png"));
    connect(_pointDependingAction, SIGNAL(triggered()), this, SLOT(showPointDepending()));
    _contextMenu->addAction(_pointDependingAction);

    _findBasePointAction->setText(tr("Move to &base point"));
    _findBasePointAction->setShortcut(QKeySequence(tr("Ctrl+B", "Move to base point")));
    connect(_findBasePointAction, SIGNAL(triggered()), this, SLOT(findBasePoint()));
    _contextMenu->addAction(_findBasePointAction);

    connect(selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(checkActions(QModelIndex,QModelIndex)));
    connect(selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(checkSelection()));
    connect(model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(checkActions(QModelIndex,QModelIndex)));
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    setContextMenuPolicy(Qt::CustomContextMenu);
}

void IqAmeGeoPointsTableView::showContextMenu(const QPoint &pos)
{
    _currentIndex = indexAt(pos);

    if (_currentIndex.isValid())
        _contextMenu->exec(QCursor::pos());

    _currentIndex = QModelIndex();
}

void IqAmeGeoPointsTableView::checkActions(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    if (_geoPointModel)
    {
        _addPointAction->setEnabled(true);

        IqAmeGeoPoint *point = _geoPointModel->point(model()->data(model()->index(current.row(), IqAmeGeoPointsModel::NAME_COLUMN)).toString());

        if (point)
        {
            _removePointAction->setEnabled(true);

            if (point->definitionType() != IqAmeGeoPoint::Geo && point->basePoint())
            {
                _findBasePointAction->setEnabled(true);
            }
            else
            {
                _findBasePointAction->setEnabled(false);
            }
        }
    }
    else
    {
        _addPointAction->setEnabled(false);
        _removePointAction->setEnabled(false);
        _findBasePointAction->setEnabled(false);
    }
}

void IqAmeGeoPointsTableView::setModel(IqAmeGeoPointsModel *model)
{
    if (_geoPointModel != model)
    {
        _geoPointModel = model;

        _delegate->setSourceGeoPointsModel(_geoPointModel);
        _sortFilterModel->setSourceModel(_geoPointModel);
    }
}

void IqAmeGeoPointsTableView::findBasePoint()
{
    if (_geoPointModel)
    {
        QModelIndex current = _currentIndex;
        if (!current.isValid())
            current = currentIndex();

        QString basePointName = model()->data(model()->index(current.row(), IqAmeGeoPointsModel::BASE_POINT_COLUMN)).toString();

        if (!basePointName.isEmpty() && _geoPointModel)
        {
            int pointRow = _geoPointModel->row(_geoPointModel->point(basePointName));

            QModelIndex pointIndex = _sortFilterModel->mapFromSource(_geoPointModel->index(pointRow, 0));

            clearSelection();
            selectRow(pointIndex.row());
            showRow(pointIndex.row());
        }
    }
}

void IqAmeGeoPointsTableView::addRow()
{
    if (_geoPointModel)
    {
        bool ok = true;
        QString pointName = QInputDialog::getText(this, tr("Point name"), tr("Enter point name"), QLineEdit::Normal, "",&ok);
        IqAmeGeoPoint *existPoint = _geoPointModel->point(pointName, Qt::CaseInsensitive);
        while ((pointName.isEmpty() || existPoint) && ok)
        {
            if (pointName.isEmpty())
            {
                pointName =  QInputDialog::getText(this, tr("Point name"), tr("Point name must not empy! Enter point name"), QLineEdit::Normal, pointName, &ok);
                existPoint = _geoPointModel->point(pointName, Qt::CaseInsensitive);
                continue;
            }
            if (existPoint)
            {
                pointName =  QInputDialog::getText(this, tr("Point name"), tr("Point with this name already exist! Enter new point name"), QLineEdit::Normal, pointName, &ok);
                existPoint = _geoPointModel->point(pointName, Qt::CaseInsensitive);
                continue;
            }
        }

        if (!ok)
            return;

        QModelIndex current = _currentIndex;
        if (!current.isValid())
            current = currentIndex();

        int row = _sortFilterModel->mapToSource(current).row() + 1;

        _geoPointModel->insertRow(row);
        _geoPointModel->setData(_geoPointModel->index(row, IqAmeGeoPointsModel::NAME_COLUMN), pointName);

        QModelIndex pointIndex = _sortFilterModel->mapFromSource(_geoPointModel->index(row, 0));

        clearSelection();
        selectRow(pointIndex.row());
        showRow(pointIndex.row());
    }
}

void IqAmeGeoPointsTableView::removeSelectedRows()
{
    if (_geoPointModel)
    {
        QModelIndex current = _currentIndex;
        if (!current.isValid())
            current = currentIndex();

        QSet<int> rowToRemove;

        foreach (QModelIndex selection, selectionModel()->selectedIndexes())
        {
            rowToRemove << selection.row();
        }

        //Если мы тыкнули внутрь выделения, то удалим все выделение
        if (rowToRemove.contains(current.row()))
        {

            if (rowToRemove.isEmpty())
                return;

            QList<int> sortRowToRemove = rowToRemove.toList();
            qSort(sortRowToRemove);

            foreach (int row, sortRowToRemove)
            {
                if (!rowAvailableToBeRemoved(row))
                    return;
            }

            int fistRow = sortRowToRemove.first();

            for (int i = sortRowToRemove.count() - 1; i > -1; i--)
            {
                _geoPointModel->removeRow(_sortFilterModel->mapToSource(model()->index(sortRowToRemove[i], 0)).row());
            }

            clearSelection();
            selectRow(fistRow);
            showRow(fistRow);
        }
        else
        {
            //Иначе удалим только строку в которую тыкнули
            if (!rowAvailableToBeRemoved(current.row()))
                return;

            int row = current.row();

            _geoPointModel->removeRow(_sortFilterModel->mapToSource(current).row());

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
    if (_geoPointModel)
    {
        QString pointName = model()->data(model()->index(row, IqAmeGeoPointsModel::NAME_COLUMN)).toString();

        QList<IqAmeGeoPoint *> relativePoints = _geoPointModel->point(pointName)->relativePoints();
        if (relativePoints.count() == 0)
        {
            return true;
        }
        else
        {


            QString dependsPoins;
            foreach (IqAmeGeoPoint *point, relativePoints)
            {
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

    IqAmeGeoPoint *point = _geoPointModel->point(pointName);

    if (!point)
        return;

    QString dependsPoints;
    foreach (IqAmeGeoPoint *dependPoint, point->relativePoints())
    {
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
