#include "iqameline.h"
#include <QRegExp>
#include <QDebug>
#include <QRectF>

IqAmeLine::IqAmeLine(QObject *parent) :
    IqAmeShapeObject(parent),
    _outputAttributes(NULL),
    _autoUpdateBoundingBox(true)
{
}

void IqAmeLine::setOutputAttributes(IqAmeShapesAttributes *outputAttributes)
{
    if (_outputAttributes != outputAttributes)
    {
        _outputAttributes = outputAttributes;

        emit outputAttributesChanged();
    }
}

bool IqAmeLine::loadFromString(const QString &string)
{
    //Отключим автоматическое обновление bbox
    _autoUpdateBoundingBox = false;

    //    qDebug() << "Load Line :" << string;
    QRegExp lineRx("^\\s*(LINE|L)\\s*:\\s*(\\*([^\\*]*)\\*){0,1}");
    lineRx.setCaseSensitivity(Qt::CaseInsensitive);
    if (lineRx.indexIn(string) == -1)
        return false;

    setName(lineRx.cap(3));

    //Получим оставшуюся строку
    QString clearString = string.mid(lineRx.matchedLength());

    //Выделим комментарий
    QRegExp commentRx("\\*([^\\*]*)\\*\\W*$");
    if (commentRx.indexIn(clearString) != -1)
        setComment(commentRx.cap(1));

    //Удалим все комментарии из строки
    QRegExp extraCommentsRx("\\*[^\\*]*\\*");
    clearString.remove(extraCommentsRx);

    //Разделим на подлинии на основе атрибутов
    QRegExp attributeRx("<\\s*[^>]*\\s*>");
    attributeRx.setCaseSensitivity(Qt::CaseInsensitive);

    IqAmeShapesAttributes *previosSublineOutputAttribute = inputAttributes();
    setOutputAttributes(previosSublineOutputAttribute);

    int start = attributeRx.indexIn(clearString);
    int end = attributeRx.indexIn(clearString, start + 1);

    if (start == -1 && end == -1)
    {
        IqAmeSubLine *subline = new IqAmeSubLine(this);
        subline->setInputAttributes(previosSublineOutputAttribute);
        if (subline->loadFromString(clearString))
        {
            appendSubLine(subline);
            previosSublineOutputAttribute = subline->outputAttributes();
            setOutputAttributes(previosSublineOutputAttribute);
        }
        else
        {
            subline->deleteLater();
        }
    }

    while (start != -1)
    {
        IqAmeSubLine *subline = new IqAmeSubLine(this);
        subline->setInputAttributes(previosSublineOutputAttribute);

        QString sublineString;
        if (end != -1)
        {
            sublineString = clearString.mid(start, end - start);
        }
        else
        {
            sublineString = clearString.mid(start);
        }

        if (subline->loadFromString(sublineString))
        {
            appendSubLine(subline);
            previosSublineOutputAttribute = subline->outputAttributes();
            setOutputAttributes(previosSublineOutputAttribute);
        }
        else
        {
            qWarning() << tr("Can not parse subline string \"%0\". Skipped.").arg(sublineString);
            subline->deleteLater();
        }

        start = end;
        end = attributeRx.indexIn(clearString, start + 1);
    }

    //Включим автоматическое обновление bbox
    _autoUpdateBoundingBox = true;
    //Обновим bbox
    updateBoundingBox();

    return true;
}

void IqAmeLine::appendSubLine(IqAmeSubLine *subLine)
{
    if (subLine)
    {
        subLine->setParent(this);
        _subLines.append(subLine);

        updateBoundingBox();
    }
}

void IqAmeLine::insertSubLine(const int position, IqAmeSubLine *subLine)
{
    if (subLine)
    {
        subLine->setParent(this);
        _subLines.insert(position, subLine);

        updateBoundingBox();
    }
}

void IqAmeLine::removeSubLine(IqAmeSubLine *subLine)
{
    if (subLine)
    {
        _subLines.removeOne(subLine);
        subLine->deleteLater();

        updateBoundingBox();
    }
}

void IqAmeLine::paindGl(const QRectF &area, IqLayerView *layerView)
{
    foreach (IqAmeSubLine *subLine, _subLines)
    {
        //Если приметив входит в область
        QRectF boundingBox = subLine->boundingBox();
        if (area.intersects(boundingBox))
            subLine->paingGl(area, layerView);
    }
}

void IqAmeLine::updateBoundingBox()
{
    if (_autoUpdateBoundingBox)
    {
        QRectF result;
        QRectF subLineBoundingBox;

        foreach (IqAmeSubLine *subLine, _subLines)
        {
            subLineBoundingBox = subLine->boundingBox();
            result = result.unite(subLineBoundingBox);
        }

        setBoundingBox(result);
    }
}
