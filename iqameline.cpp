#include "iqameline.h"
#include <QRegExp>
#include <QDebug>
#include <QRectF>
#include "iqameapplication.h"

IqAmeLine::IqAmeLine(QObject *parent) :
    IqAmeNamedShapeObject(parent),
    m_outputAttributes(Q_NULLPTR)
{
}

IqAmeLine::~IqAmeLine()
{
}

QList<QGraphicsItem *> IqAmeLine::graphicsItems()
{
    QList<QGraphicsItem *> result;
    foreach (IqAmeSubLine *subline, m_subLines) {
        Q_CHECK_PTR(subline);
        Q_CHECK_PTR(subline->graphicsItem());
        result << subline->graphicsItem();
    }
    return result;
}

void IqAmeLine::updateGraphicsItems()
{
    foreach (IqAmeSubLine *subline, m_subLines) {
        Q_CHECK_PTR(subline);
        Q_CHECK_PTR(subline->graphicsItem());
        subline->graphicsItem()->setVisible(visible());
        subline->graphicsItem()->updateCache();
    }
}

void IqAmeLine::setOutputAttributes(IqAmeShapesAttributes *outputAttributes)
{
    if (m_outputAttributes != outputAttributes) {
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

    if (start == -1 && end == -1) {
        IqAmeSubLine *subline = new IqAmeSubLine(this);
        subline->setInputAttributes(previosSublineOutputAttribute);
        if (subline->loadFromString(clearString)) {
            appendSubLine(subline);
            previosSublineOutputAttribute = subline->outputAttributes();
            setOutputAttributes(previosSublineOutputAttribute);
        }
        else {
            subline->deleteLater();
        }
    }

    while (start != -1) {
        IqAmeSubLine *subline = new IqAmeSubLine(this);
        subline->setInputAttributes(previosSublineOutputAttribute);

        QString sublineString;
        if (end != -1) {
            sublineString = clearString.mid(start, end - start);
        }
        else {
            sublineString = clearString.mid(start);
        }

        if (subline->loadFromString(sublineString)) {
            appendSubLine(subline);
            previosSublineOutputAttribute = subline->outputAttributes();
            setOutputAttributes(previosSublineOutputAttribute);
        }
        else {
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
    Q_CHECK_PTR(subLine);
    subLine->setParent(this);
    subLine->setLine(this);
    m_subLines.append(subLine);
}

void IqAmeLine::insertSubLine(const int position, IqAmeSubLine *subLine)
{
    Q_CHECK_PTR(subLine);
    subLine->setParent(this);
    subLine->setLine(this);
    m_subLines.insert(position, subLine);
}

void IqAmeLine::removeSubLine(IqAmeSubLine *subLine)
{
    Q_CHECK_PTR(subLine);
    subLine->setParent(Q_NULLPTR);
    subLine->setLine(Q_NULLPTR);
    m_subLines.removeOne(subLine);
}

QList<IqAmeSubLine *> IqAmeLine::subLines() const
{
    return m_subLines;
}

IqAmeShapesAttributes *IqAmeLine::outputAttributes() const
{
    return m_outputAttributes;
}
