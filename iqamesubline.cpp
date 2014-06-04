#include "iqamesubline.h"
#include "iqamestraightlinesegment.h"
#include "iqameapplication.h"
#include <QRegExp>
#include <QDebug>
#include <QStringList>

IqAmeSubLine::IqAmeSubLine(QObject *parent) :
    QObject(parent),
    _attributes(new IqAmeLineAttributes(this))
{
}

void IqAmeSubLine::appendSegment(IqAmeLineSegment *segment)
{
    if (segment)
    {
        segment->setParent(this);
        _segments.append(segment);
    }
}

void IqAmeSubLine::insertSegment(const int position, IqAmeLineSegment *segment)
{
    if (segment)
    {
        segment->setParent(this);
        _segments.insert(position, segment);
    }
}

void IqAmeSubLine::removeSegment(IqAmeLineSegment *segment)
{
    if (segment)
    {
        _segments.removeOne(segment);
        segment->deleteLater();
    }
}

bool IqAmeSubLine::loadFromString(const QString &string)
{
    QRegExp sublineRx("<\\s*(BLACK|BLUE|GREEN|CYAN|RED|MAGENTA|BROWN|WHITE|GRAY|LBLUE|LGREEN|LCYAN|"
                      "LRED|LMAGENTA|YELLOW|BRIGHTWHITE){0,1}(\\s*,{0,1}\\s*(ffff|ff00|e4e4|aaaa)){0,1}(\\s*,{0,1}"
                      "\\s*(normal|full)){0,1}(\\s*,{0,1}\\s*(fill|empty)){0,1}\\s*>");
    sublineRx.setCaseSensitivity(Qt::CaseInsensitive);

    if (sublineRx.indexIn(string) != -1)
    {
        if (!sublineRx.cap(1).isEmpty())
        {
            QString color = sublineRx.cap(1);

            if (color.compare("BLACK", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::Black);
            }
            else if (color.compare("BLUE", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::Blue);
            }
            else if (color.compare("GREEN", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::Green);
            }
            else if (color.compare("CYAN", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::Cyan);
            }
            else if (color.compare("RED", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::Red);
            }
            else if (color.compare("MAGENTA", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::Magenta);
            }
            else if (color.compare("BROWN", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::Brown);
            }
            else if (color.compare("WHITE", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::White);
            }
            else if (color.compare("GRAY", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::Gray);
            }
            else if (color.compare("LBLUE", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::LBlue);
            }
            else if (color.compare("LGREEN", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::LGreen);
            }
            else if (color.compare("LCYAN", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::LCyan);
            }
            else if (color.compare("LRED", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::LRed);
            }
            else if (color.compare("LMAGENTA", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::LMagenta);
            }
            else if (color.compare("YELLOW", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::Yellow);
            }
            else if (color.compare("BRIGHTWHITE", Qt::CaseInsensitive) == 0)
            {
                attributes()->setColor(IqAmeLineAttributes::BrigthWhite);
            }
        }
        if (!sublineRx.cap(3).isEmpty())
        {
            QString texture = sublineRx.cap(3);

            if (texture.compare("ffff", Qt::CaseInsensitive) == 0)
            {
                attributes()->setTexture(IqAmeLineAttributes::FFFF);
            }
            else if (texture.compare("ff00", Qt::CaseInsensitive) == 0)
            {
                attributes()->setTexture(IqAmeLineAttributes::FF00);
            }
            else if (texture.compare("e4e4", Qt::CaseInsensitive) == 0)
            {
                attributes()->setTexture(IqAmeLineAttributes::E4E4);
            }
            else if (texture.compare("aaaa", Qt::CaseInsensitive) == 0)
            {
                attributes()->setTexture(IqAmeLineAttributes::AAAA);
            }
        }
        if (!sublineRx.cap(5).isEmpty())
        {
            QString depth = sublineRx.cap(5);

            if (depth.compare("normal", Qt::CaseInsensitive) == 0)
            {
                attributes()->setDepth(IqAmeLineAttributes::Normal);
            }
            else if (depth.compare("full", Qt::CaseInsensitive) == 0)
            {
                attributes()->setDepth(IqAmeLineAttributes::Full);
            }
        }
        if (!sublineRx.cap(7).isEmpty())
        {
            QString fillMode = sublineRx.cap(7);

            if (fillMode.compare("fill", Qt::CaseInsensitive) == 0)
            {
                attributes()->setFillMode(IqAmeLineAttributes::Fill);
            }
            else if (fillMode.compare("empty", Qt::CaseInsensitive) == 0)
            {
                attributes()->setFillMode(IqAmeLineAttributes::EmptyFill);
            }
        }
    }

    QString pointsString = string.mid(sublineRx.matchedLength());
    pointsString = pointsString.trimmed();

    if (!pointsString.isEmpty())
    {
        QRegExp pointRx ("([^,\\(\\)]*\\([^\\(]*\\)(,|$))|([^,\\(\\)]*(,|$))");
        QRegExp circleRx ("(.*)\\((.*)\\)");

        int start = pointRx.indexIn(pointsString);
        QString p1Name = pointsString.mid(start, pointRx.matchedLength() - 1);
        QString p2Name = "";

        while (start != -1 && pointRx.matchedLength() != 0)
        {
            start = pointRx.indexIn(pointsString, start + pointRx.matchedLength());

            p2Name = pointsString.mid(start, pointRx.matchedLength() - 1);

            if (!p1Name.trimmed().isEmpty() && !p2Name.trimmed().isEmpty())
            {
                if (circleRx.indexIn(p1Name) == -1)
                {

                    IqAmeGeoPoint *p1 = IqAmeApplication::aeroMapModel()->pointsModel()->point(p1Name.trimmed(), Qt::CaseInsensitive);
                    if (!p1)
                    {
                        continue;
                    }

                    if (circleRx.indexIn(p2Name) != -1)
                        p2Name = circleRx.cap(1);

                    IqAmeGeoPoint *p2 = IqAmeApplication::aeroMapModel()->pointsModel()->point(p2Name.trimmed(), Qt::CaseInsensitive);
                    if (!p2)
                    {
                        continue;
                    }

                    IqAmeStraightLineSegment *segment = new IqAmeStraightLineSegment(this);
                    segment->setStartPoint(p1);
                    segment->setEndPoint(p2);

                    appendSegment(segment);
                }
                else
                {
                    qWarning() << tr("Circle \"%0\" temporary skipped. Fixed in future.").arg(p1Name);
                }
            }

            p1Name = p2Name;
        }
    }

    return true;
}
