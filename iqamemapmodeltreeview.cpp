#include "iqamemapmodeltreeview.h"

IqAmeMapModelTreeView::IqAmeMapModelTreeView(QWidget *parent) :
    QTreeView(parent),
    _mapModel(NULL)
{
    connect(this, SIGNAL(activated(QModelIndex)), this, SLOT(onActivated(QModelIndex)));
}

void IqAmeMapModelTreeView::setModel(IqAmeMapModel *model)
{
    if (_mapModel != model)
    {
        QTreeView::setModel(model);
        _mapModel = model;
    }
}

void IqAmeMapModelTreeView::onActivated(const QModelIndex &index)
{
    if (_mapModel)
    {
        if (!index.parent().isValid())
        {
            if (index.row() == 0)
            {
                emit pointsClicked();
            }
            else
            {
                emit layerClicked(static_cast<IqAmeLayer*>(index.internalPointer()));
            }
        }
        else
        {
            emit layerClicked(static_cast<IqAmeLayer*>(index.internalPointer()));
        }
    }
}
