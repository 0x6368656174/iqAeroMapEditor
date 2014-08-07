#include "iqameapplication.h"
#include "iqameshapesmodel.h"

#include "iqameline.h"
#include "iqametext.h"

#include <QFile>
#include <QDebug>
#include <QRegExp>
#include <QStringList>

IqAmeShapesModel::IqAmeShapesModel(QObject *parent) :
    QAbstractTableModel(parent),
    _baseAttributes(new IqAmeShapesAttributes(this))
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

    qDebug() << tr("Starting parsing shapes from \"%0\"...").arg(fileName);

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

    QString fileString = QTextCodec::codecForName("IBM866")->toUnicode(fileData);

    QStringList fileStringList = fileString.split("\n");

    //Удалим имя
    fileStringList.removeFirst();

    QRegExp shapeRx ("^\\s*(LINE|L|TEXT|T|SYMB|S|FILL|F|SETA|SA|SETD|SD)\\s*:");
    shapeRx.setCaseSensitivity(Qt::CaseInsensitive);

    QStringList shapes;
    QStringList shapeTypes;
    foreach (QString str, fileStringList)
    {
        if (shapeRx.indexIn(str) != -1)
        {
            shapes.append(str.trimmed());
            shapeTypes.append(shapeRx.cap(1));
        }
        else
        {
            if (shapes.count() > 0)
                shapes.last().append(str.trimmed());
        }
    }

    //Уберем подряд идущие запятые, т.к. это ошибка синтаксиса
    QRegExp doubleCommaRx(",[\\s,]*,");

    IqAmeShapesAttributes *previosShapeOutputAttribute = _baseAttributes;

    for (int i = 0; i < shapes.count(); i++)
    {
        //Обработаем приметив
        QString shape = shapes[i];
        shape.replace(doubleCommaRx, ",");
        QString shapeType = shapeTypes[i];
        if (!shape.isEmpty())
        {
            if (shapeType.compare("LINE", Qt::CaseInsensitive) == 0 || shapeType.compare("L", Qt::CaseInsensitive) == 0)
            {
                IqAmeLine *line = new IqAmeLine(this);
                line->setInputAttributes(previosShapeOutputAttribute);
                if (line->loadFromString(shape))
                {
                    _shapes << line;
                    previosShapeOutputAttribute = line->outputAttributes();
                }
                else
                {
                    qWarning() << tr("Can not parse line string \"%0\". Skipped.").arg(shape);
                    line->deleteLater();
                }
            }
            else if (shapeType.compare("TEXT", Qt::CaseInsensitive) == 0 || shapeType.compare("T", Qt::CaseInsensitive) == 0)
            {
                IqAmeText *text = new IqAmeText(this);
                text->setInputAttributes(previosShapeOutputAttribute);
                if (text->loadFromString(shape))
                {
                    _shapes << text;
                    previosShapeOutputAttribute = text->outputAttributes();
                }
                else
                {
                    qWarning() << tr("Can not parse text string \"%0\". Skipped.").arg(shape);
                    text->deleteLater();
                }
            }
        }
    }

    return true;
}

QVariant IqAmeShapesModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    IqAmeShapeObject *shape = _shapes.at(index.row());

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
            IqAmeText *text = qobject_cast<IqAmeText *>(shape);
            if (text)
            {
                return "T";
            }

            break;
        }
        case NAME_COLUMN:
        {
            return shape->name();
        }
        }

        break;
    }
    case ShapeObject:
    {
        return QVariant::fromValue(shape);
    }
    }

    return QVariant();
}
