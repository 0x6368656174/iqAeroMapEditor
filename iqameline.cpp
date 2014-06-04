#include "iqameline.h"
#include <QRegExp>
#include <QDebug>

IqAmeLine::IqAmeLine(QObject *parent) :
    IqAmeGraphicObject(parent),
    _baseAttributes(NULL)
{
}

bool IqAmeLine::loadFromString(const QString &string)
{
    QRegExp lineRx("^\\s*(LINE|L)\\s*:\\s*(\\*([^\\*]*)\\*){0,1}");
    lineRx.setCaseSensitivity(Qt::CaseInsensitive);
    if (lineRx.indexIn(string) == -1)
        return false;

    setName(lineRx.cap(3));

    //Получим оставшуюся строку
    QString clearString = string.mid(lineRx.matchedLength());

    //Выделим комментарий
    QRegExp commentRx("\\*(.*)\\*[^\\*]*$");
    if (commentRx.indexIn(clearString) != -1)
        setComment(commentRx.cap(1));

    //Удалим все комментарии из строки
    QRegExp extraCommentsRx("\\*+[^\\*]*\\*+");
    clearString.remove(extraCommentsRx);

    //Разделим на подлинии
    QRegExp sublineRx("<\\s*(BLACK|BLUE|GREEN|CYAN|RED|MAGENTA|BROWN|WHITE|GRAY|LBLUE|LGREEN|LCYAN|"
                      "LRED|LMAGENTA|YELLOW|BRIGHTWHITE){0,1}(\\s*,{0,1}\\s*(ffff|ff00|e4e4|aaaa)){0,1}(\\s*,{0,1}"
                      "\\s*(normal|full)){0,1}(\\s*,{0,1}\\s*(fill|empty)){0,1}\\s*>");
    sublineRx.setCaseSensitivity(Qt::CaseInsensitive);

    IqAmeLineAttributes *bAttribute = baseAttributes();
    int start = sublineRx.indexIn(clearString);
    int end = sublineRx.indexIn(clearString, start + 1);

    if (start == -1 && end == -1)
    {
        IqAmeSubLine *subline = new IqAmeSubLine(this);
        subline->attributes()->setBaseAttributes(bAttribute);
        if (subline->loadFromString(clearString))
        {
            appendSubLine(subline);
            bAttribute = subline->attributes();
        }
        else
        {
            subline->deleteLater();
        }
    }

    while (start != -1)
    {
        IqAmeSubLine *subline = new IqAmeSubLine(this);
        subline->attributes()->setBaseAttributes(bAttribute);

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
            bAttribute = subline->attributes();
        }
        else
        {
            qWarning() << tr("Can not parse subline string \"%0\". Skipped.").arg(sublineString);
            subline->deleteLater();
        }

        start = end;
        end = sublineRx.indexIn(clearString, start + 1);
    }

    return true;
}

void IqAmeLine::appendSubLine(IqAmeSubLine *subLine)
{
    if (subLine)
    {
        subLine->setParent(this);
        _subLines.append(subLine);
    }
}

void IqAmeLine::insertSubLine(const int position, IqAmeSubLine *subLine)
{
    if (subLine)
    {
        subLine->setParent(this);
        _subLines.insert(position, subLine);
    }
}

void IqAmeLine::removeSubLine(IqAmeSubLine *subLine)
{
    if (subLine)
    {
        _subLines.removeOne(subLine);
        subLine->deleteLater();
    }
}

void IqAmeLine::setBaseAttributes(IqAmeLineAttributes *attributes)
{
    if (_baseAttributes != attributes)
    {
        _baseAttributes = attributes;

        emit baseAttributesChanged();
    }
}
