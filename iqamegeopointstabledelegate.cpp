#include "iqamegeopointstabledelegate.h"

#include <QComboBox>
#include <QLineEdit>
#include <QCompleter>
#include <QMessageBox>
#include "iqamegeopoint.h"
#include "iqamegeopointsmodel.h"

IqAmeGeoPointsTableDelegate::IqAmeGeoPointsTableDelegate(QObject *parent) :
    QStyledItemDelegate(parent),
    _sourceGeoPointsModel(NULL)
{
}

void IqAmeGeoPointsTableDelegate::setSourceGeoPointsModel(IqAmeGeoPointsModel *model)
{
    _sourceGeoPointsModel = model;
}

QWidget * IqAmeGeoPointsTableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.column())
    {
    case IqAmeGeoPointsModel::DEFINITION_TYPE_COLUMN:
    {
        QComboBox *editor = new QComboBox(parent);
        editor->addItem(tr("Geo"));
        editor->addItem(tr("Cartesian"));
        editor->addItem(tr("Polar"));

        return editor;
    }

    case IqAmeGeoPointsModel::BASE_POINT_COLUMN:
    {
        QLineEdit *editor = new QLineEdit(parent);

        QCompleter *completer = new QCompleter(editor);
        completer->setModel(const_cast<QAbstractItemModel *>(index.model()));
        completer->setCompletionColumn(IqAmeGeoPointsModel::NAME_COLUMN);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setCompletionRole(Qt::DisplayRole);

        editor->setCompleter(completer);

        return editor;
    }
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void IqAmeGeoPointsTableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch (index.column())
    {
    case IqAmeGeoPointsModel::DEFINITION_TYPE_COLUMN:
    {
        if (!editor)
            return;

        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        if (!comboBox)
            return;

        if (!_sourceGeoPointsModel)
            return;

        IqAmeGeoPoint *point = _sourceGeoPointsModel->point(index.model()->data(index.model()->index(index.row(), IqAmeGeoPointsModel::NAME_COLUMN)).toString());
        if (!point)
            return;

        switch (point->definitionType())
        {
        case IqAmeGeoPoint::Geo:
            comboBox->setCurrentIndex(0);
            break;
        case IqAmeGeoPoint::Cartesian:
            comboBox->setCurrentIndex(1);
            break;
        case IqAmeGeoPoint::Polar:
            comboBox->setCurrentIndex(2);
            break;
        }
        return;
    }

    case IqAmeGeoPointsModel::BASE_POINT_COLUMN:
    {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
        if (!lineEdit)
            return;

        QString currentBasePointName = index.data().toString();

        lineEdit->setText(currentBasePointName);
        return;
    }
    }

    QStyledItemDelegate::setEditorData(editor, index);
}

void IqAmeGeoPointsTableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch (index.column())
    {
    case IqAmeGeoPointsModel::DEFINITION_TYPE_COLUMN:
    {
        if (!editor)
            return;

        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        if (!comboBox)
            return;

        if (!_sourceGeoPointsModel)
            return;


        IqAmeGeoPoint *point = _sourceGeoPointsModel->point(model->data(model->index(index.row(), IqAmeGeoPointsModel::NAME_COLUMN)).toString());
        if (!point)
            return;

        switch (comboBox->currentIndex())
        {
        case 0:
            point->setDefinitionType(IqAmeGeoPoint::Geo);
            break;
        case 1:
            point->setDefinitionType(IqAmeGeoPoint::Cartesian);
            break;
        case 2:
            point->setDefinitionType(IqAmeGeoPoint::Polar);
            break;
        }

        model->setData(model->index(index.row(), IqAmeGeoPointsModel::DEFINITION_TYPE_COLUMN), QVariant());
        return;
    }
    case IqAmeGeoPointsModel::BASE_POINT_COLUMN:
    {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
        if (!lineEdit)
            return;

        if (!_sourceGeoPointsModel)
            return;

        IqAmeGeoPoint *point = _sourceGeoPointsModel->point(model->data(model->index(index.row(), IqAmeGeoPointsModel::NAME_COLUMN)).toString());
        if (!point)
            return;

        if (lineEdit->text().isEmpty())
        {
            point->setBasePoint(NULL);
        }
        else
        {
            IqAmeGeoPoint *basePoint = _sourceGeoPointsModel->point(lineEdit->text(), Qt::CaseInsensitive);

            if (!basePoint)
                QMessageBox::warning(NULL, tr("Base point setting failed."), tr("Point with name \"%0\" not exist.")
                                     .arg(lineEdit->text()));

            point->setBasePoint(basePoint);
        }

        model->setData(model->index(index.row(), IqAmeGeoPointsModel::BASE_POINT_COLUMN), QVariant());
        return;
    }
    }

    QStyledItemDelegate::setModelData(editor, model, index);
}
