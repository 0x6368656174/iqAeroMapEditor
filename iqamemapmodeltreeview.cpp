#include "iqamemapmodeltreeview.h"

IqAmeMapModelTreeView::IqAmeMapModelTreeView(QWidget *parent) :
    QTreeView(parent),
    m_mapModel(Q_NULLPTR)
{
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(onActivated(QModelIndex)));
}

void IqAmeMapModelTreeView::setModel(IqAmeMapModel *model)
{
    if (m_mapModel != model) {
        QTreeView::setModel(model);
        m_mapModel = model;
    }
}

void IqAmeMapModelTreeView::onActivated(const QModelIndex &index)
{
    if (m_mapModel) {
        if (!index.parent().isValid()) {
            if (index.row() == 0) {
                emit pointsClicked();
            } else {
                emit layerClicked(static_cast<IqAmeLayer*>(index.internalPointer()));
            }
        } else {
            emit layerClicked(static_cast<IqAmeLayer*>(index.internalPointer()));
        }
    }
}
