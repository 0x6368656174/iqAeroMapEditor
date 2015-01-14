#include "iqamesubline.h"
#include "iqamestraightlinesegment.h"
#include "iqameapplication.h"
#include <QtOpenGL>
#include <QRegExp>
#include <QDebug>
#include <QStringList>

IqAmeSubLine::IqAmeSubLine(QObject *parent) :
    IqAmeShapeObject(parent),
    m_graphicsItem(Q_NULLPTR)
{
    connect(this, &IqAmeSubLine::outputAttributesChanged, this, &IqAmeSubLine::updateGraphicsItem);
}

IqAmeSubLine::~IqAmeSubLine()
{
    if (m_graphicsItem)
        delete m_graphicsItem;
}

IqAmeSublineGraphicsItem *IqAmeSubLine::graphicsItem()
{
    if (!m_graphicsItem) {
        m_graphicsItem = new IqAmeSublineGraphicsItem();
        m_graphicsItem->setSubLine(this);
        m_graphicsItem->updateCache();
    }

    return m_graphicsItem;
}

void IqAmeSubLine::updateGraphicsItem()
{
}

void IqAmeSubLine::appendSegment(IqAmeLineSegment *segment)
{
    if (segment) {
        segment->setParent(this);
        m_segments.append(segment);
    }
}

void IqAmeSubLine::insertSegment(const int position, IqAmeLineSegment *segment)
{
    if (segment) {
        segment->setParent(this);
        m_segments.insert(position, segment);
    }
}

void IqAmeSubLine::removeSegment(IqAmeLineSegment *segment)
{
    if (segment) {
        m_segments.removeOne(segment);
        segment->deleteLater();
    }
}

QList<IqAmeLineSegment *> IqAmeSubLine::segments() const
{
    return m_segments;
}

bool IqAmeSubLine::loadFromString(const QString &string)
{
    QRegExp attributeRx("<\\s*[^>]*\\s*>");
    attributeRx.setCaseSensitivity(Qt::CaseInsensitive);

    if (attributeRx.indexIn(string) != -1) {
        //Нашли атрибуты, создадим их
        if (!attributes()) {
            setAttributes(new IqAmeShapesAttributes(this));
        }
        attributes()->loadFromString(attributeRx.cap(0));
    }

    QString pointsString = string.mid(attributeRx.matchedLength());
    pointsString = pointsString.trimmed();

    if (!pointsString.isEmpty()) {
        QRegExp pointRx ("(([^,\\(\\)]*\\([^\\(]*\\))(,|$))|(([^,\\(\\)]*)(,|$))");
        QRegExp circleRx ("(.*)\\((.*)\\)");

        int start = pointRx.indexIn(pointsString);
        QString p1Name = pointRx.cap(2) + pointRx.cap(5);
        QString p2Name = "";

        while (start != -1 && pointRx.matchedLength() != 0) {
            start = pointRx.indexIn(pointsString, start + pointRx.matchedLength());

            p2Name = pointRx.cap(2) + pointRx.cap(5);

            if (!p1Name.trimmed().isEmpty() && !p2Name.trimmed().isEmpty()) {
                if (circleRx.indexIn(p1Name) == -1) {
                    IqAmeGeoPoint *p1 = IqAmeApplication::aeroMapModel()->pointsModel()->point(p1Name.trimmed(), Qt::CaseInsensitive);
                    if (!p1) {
                        //Если не нашли точку, то попробуем ее создать
                        IqAmeGeoPoint newPoint;
                        if (newPoint.fromCoordinate(p1Name)) {
                            int newPointRow = IqAmeApplication::aeroMapModel()->pointsModel()->rowCount();
                            IqAmeApplication::aeroMapModel()->pointsModel()->insertRow(newPointRow);
                            p1 = IqAmeApplication::aeroMapModel()->pointsModel()->at(newPointRow);
                            p1->setName(newPoint.name());
                            p1->setLatitude(newPoint.latitude());
                            p1->setLongitude(newPoint.longitude());
                        } else {
                            qWarning() << tr("Point \"%0\" not found and can not create. Skipped...").arg(p1Name);
                            p1Name = p2Name;
                            continue;
                        }
                    }

                    if (circleRx.indexIn(p2Name) != -1)
                        p2Name = circleRx.cap(1);

                    IqAmeGeoPoint *p2 = IqAmeApplication::aeroMapModel()->pointsModel()->point(p2Name.trimmed(), Qt::CaseInsensitive);
                    if (!p2) {
                        //Если не нашли точку, то попробуем ее создать
                        IqAmeGeoPoint newPoint;
                        if (newPoint.fromCoordinate(p2Name)) {
                            int newPointRow = IqAmeApplication::aeroMapModel()->pointsModel()->rowCount();
                            IqAmeApplication::aeroMapModel()->pointsModel()->insertRow(newPointRow);
                            p2 = IqAmeApplication::aeroMapModel()->pointsModel()->at(newPointRow);
                            p2->setName(newPoint.name());
                            p2->setLatitude(newPoint.latitude());
                            p2->setLongitude(newPoint.longitude());
                        } else {
                            qWarning() << tr("Point \"%0\" not found and can not create. Skipped...").arg(p2Name);
                            p1Name = p2Name;
                            continue;
                        }
                    }

                    IqAmeStraightLineSegment *segment = new IqAmeStraightLineSegment(this);
                    segment->setStartPoint(p1);
                    segment->setEndPoint(p2);
                    segment->setInputAttributes(outputAttributes());

                    appendSegment(segment);
                } else {
                    qWarning() << tr("Circle \"%0\" temporary skipped. Fixed in future.").arg(p1Name);
                }
            }

            p1Name = p2Name;
        }
    }

    return true;
}
