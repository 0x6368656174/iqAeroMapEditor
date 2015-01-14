#include "iqameline.h"
#include <QRegExp>
#include <QDebug>
#include <QRectF>
#include "iqameapplication.h"

IqAmeLine::IqAmeLine(QObject *parent) :
    IqAmeNamedShapeObject(parent),
    m_outputAttributes(Q_NULLPTR),
    m_graphicsItem(Q_NULLPTR)
{
}

IqAmeLine::~IqAmeLine()
{
    if (m_graphicsItem)
        delete m_graphicsItem;
}

IqAmeLineGraphicsItem *IqAmeLine::graphicsItem()
{
    if (!m_graphicsItem) {
        m_graphicsItem = new IqAmeLineGraphicsItem();
        m_graphicsItem->setLine(this);

        foreach (IqAmeSubLine *subLine, m_subLines) {
            Q_CHECK_PTR(subLine);
            m_graphicsItem->addToGroup(subLine->graphicsItem());
        }
    }

    return m_graphicsItem;
}

void IqAmeLine::updateGraphicsItem()
{
}

void IqAmeLine::setOutputAttributes(IqAmeShapesAttributes *outputAttributes)
{
    if (m_outputAttributes != outputAttributes)
    {
        m_outputAttributes = outputAttributes;

        emit outputAttributesChanged();
    }
}

bool IqAmeLine::loadFromString(const QString &string)
{
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

    return true;
}

void IqAmeLine::appendSubLine(IqAmeSubLine *subLine)
{
    if (subLine)
    {
        subLine->setParent(this);
        m_subLines.append(subLine);
        graphicsItem()->addToGroup(subLine->graphicsItem());
    }
}

void IqAmeLine::insertSubLine(const int position, IqAmeSubLine *subLine)
{
    if (subLine)
    {
        subLine->setParent(this);
        m_subLines.insert(position, subLine);
        graphicsItem()->addToGroup(subLine->graphicsItem());
    }
}

void IqAmeLine::removeSubLine(IqAmeSubLine *subLine)
{
    if (subLine)
    {
        m_subLines.removeOne(subLine);
        graphicsItem()->removeFromGroup(subLine->graphicsItem());
        subLine->deleteLater();
    }
}

QList<IqAmeSubLine *> IqAmeLine::subLines() const
{
    return m_subLines;
}

IqAmeShapesAttributes *IqAmeLine::outputAttributes() const
{
    return m_outputAttributes;
}
