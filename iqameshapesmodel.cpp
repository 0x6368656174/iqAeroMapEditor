#include "iqameapplication.h"
#include "iqameshapesmodel.h"

#include "iqameline.h"

#include <QFile>
#include <QDebug>
#include <QRegExp>
#include <QStringList>

IqAmeShapesModel::IqAmeShapesModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

void IqAmeShapesModel::clear()
{
    emit beginRemoveRows(QModelIndex(), 0, rowCount() - 1);

    qDeleteAll(_shapes);

    _shapes.clear();

    emit endRemoveRows();
}

bool IqAmeShapesModel::loadFromFile(const QString &fileName, QString *lastError)
{
    clear();

    if (fileName.isEmpty())
        return false;

    if (!QFile::exists(fileName))
    {
        QString error = tr("File \"%0\" not exist.").arg(fileName);
        qWarning() << error;
        if (lastError)
            *lastError = error;

        return false;
    }

    qDebug() << tr("Starting parsing \"%0\"...").arg(fileName);

    QFile file (fileName);
    if (!file.open(QFile::ReadOnly))
    {
        QString error = tr("Can not open \"%0\" file.").arg(fileName);
        qWarning() << error;
        if (lastError)
            *lastError = error;

        return false;
    }

    QByteArray fileData = file.readAll();

    QString fileString = IqAmeApplication::defaultTextCodec()->toUnicode(fileData);

    QStringList fileStringList = fileString.split("\n");

    //Удалим имя
    fileStringList.removeFirst();

    QRegExp shapeRx ("^\\s*(LINE|L|TEXT|T|SYMB|S|FILL|F|SETA|SA|SETD|SD)\\s*:");
    shapeRx.setCaseSensitivity(Qt::CaseInsensitive);
    QString shape;
    QString shapeType;

    foreach (QString str, fileStringList)
    {
        if (shapeRx.indexIn(str) != -1)
        {
            //Обработаем приметив
            if (!shape.isEmpty() && (shapeType.compare("LINE", Qt::CaseInsensitive) == 0 || shapeType.compare("L", Qt::CaseInsensitive) == 0))
            {
                IqAmeLine *line = new IqAmeLine(this);
                if (line->loadFromString(shape))
                {
                    _shapes << line;
                }
                else
                {
                    qWarning() << tr("Can not parse line string \"%0\". Skipped.").arg(shape);
                    line->deleteLater();
                }
            }

            //Начат новый приметив
            shapeType = shapeRx.cap(1);
            shape = str.trimmed();
        }
        else
        {
            shape += " " + str.trimmed();
        }
    }

    return true;
}

QVariant IqAmeShapesModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    IqAmeGraphicObject *shape = _shapes.at(index.row());

    if (!shape)
        return QVariant();

    switch (role)
    {
    case Qt::DisplayRole:
    {
        switch (index.column())
        {
        case TYPE_COLUMN:
        {
            IqAmeLine *line = qobject_cast<IqAmeLine *>(shape);
            if (line)
            {
                return "L";
            }

            break;
        }
        case NAME_COLUMN:
        {
            return shape->name();

            break;
        }
        }

        break;
    }
    }

    return QVariant();
}
