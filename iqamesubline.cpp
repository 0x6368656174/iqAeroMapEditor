#include "iqamesubline.h"
#include "iqamestraightlinesegment.h"
#include "iqameapplication.h"
#include <QtOpenGL>
#include <QRegExp>
#include <QDebug>
#include <QStringList>

IqAmeSubLine::IqAmeSubLine(QObject *parent) :
    QObject(parent),
    _inputAttributes(NULL),
    _attributes(NULL),
    _autoUpdateBoundingBox(true)
{
}

void IqAmeSubLine::setInputAttributes(IqAmeShapesAttributes *attributes)
{
    if (_inputAttributes != attributes)
    {
        _inputAttributes = attributes;

        if (!_attributes)
            emit outputAttributesChanged();

        emit inputAttributesChanged();
    }
}

IqAmeShapesAttributes * IqAmeSubLine::outputAttributes() const
{
    if (_attributes)
    {
        return _attributes;
    }
    return _inputAttributes;
}

void IqAmeSubLine::appendSegment(IqAmeLineSegment *segment)
{
    if (segment)
    {
        segment->setParent(this);
        _segments.append(segment);

        updateBoundingBox();
    }
}

void IqAmeSubLine::insertSegment(const int position, IqAmeLineSegment *segment)
{
    if (segment)
    {
        segment->setParent(this);
        _segments.insert(position, segment);

        updateBoundingBox();
    }
}

void IqAmeSubLine::removeSegment(IqAmeLineSegment *segment)
{
    if (segment)
    {
        _segments.removeOne(segment);
        segment->deleteLater();

        updateBoundingBox();
    }
}

void IqAmeSubLine::setBoundingBox(const QRectF &boundingBox)
{
    if (_boundingBox != boundingBox)
    {
        _boundingBox = boundingBox;

        emit boundingBoxChanged();
    }
}

bool IqAmeSubLine::loadFromString(const QString &string)
{
    //Отключим автоматическое обновление bbox
    _autoUpdateBoundingBox = false;

    QRegExp attributeRx("<\\s*[^>]*\\s*>");
    attributeRx.setCaseSensitivity(Qt::CaseInsensitive);

    if (attributeRx.indexIn(string) != -1)
    {
        //Нашли атрибуты, создадим их
        if (!attributes())
        {
            setAttributes(new IqAmeShapesAttributes(this));
        }
        attributes()->loadFromString(attributeRx.cap(0));
    }

    QString pointsString = string.mid(attributeRx.matchedLength());
    pointsString = pointsString.trimmed();

    if (!pointsString.isEmpty())
    {
        QRegExp pointRx ("(([^,\\(\\)]*\\([^\\(]*\\))(,|$))|(([^,\\(\\)]*)(,|$))");
        QRegExp circleRx ("(.*)\\((.*)\\)");

        int start = pointRx.indexIn(pointsString);
        QString p1Name = pointRx.cap(2) + pointRx.cap(5);
        QString p2Name = "";

        while (start != -1 && pointRx.matchedLength() != 0)
        {
            start = pointRx.indexIn(pointsString, start + pointRx.matchedLength());

            p2Name = pointRx.cap(2) + pointRx.cap(5);

            if (!p1Name.trimmed().isEmpty() && !p2Name.trimmed().isEmpty())
            {
                if (circleRx.indexIn(p1Name) == -1)
                {
                    IqAmeGeoPoint *p1 = IqAmeApplication::aeroMapModel()->pointsModel()->point(p1Name.trimmed(), Qt::CaseInsensitive);
                    if (!p1)
                    {
                        //Если не нашли точку, то попробуем ее создать
                        IqAmeGeoPoint newPoint;
                        if (newPoint.fromCoordinate(p1Name))
                        {
                            int newPointRow = IqAmeApplication::aeroMapModel()->pointsModel()->rowCount();
                            IqAmeApplication::aeroMapModel()->pointsModel()->insertRow(newPointRow);
                            p1 = IqAmeApplication::aeroMapModel()->pointsModel()->at(newPointRow);
                            p1->setName(newPoint.name());
                            p1->setLatitude(newPoint.latitude());
                            p1->setLongitude(newPoint.longitude());
                        }
                        else
                        {
                            qWarning() << tr("Point \"%0\" not found and can not create. Skipped...").arg(p1Name);
                            p1Name = p2Name;
                            continue;
                        }
                    }

                    if (circleRx.indexIn(p2Name) != -1)
                        p2Name = circleRx.cap(1);

                    IqAmeGeoPoint *p2 = IqAmeApplication::aeroMapModel()->pointsModel()->point(p2Name.trimmed(), Qt::CaseInsensitive);
                    if (!p2)
                    {
                        //Если не нашли точку, то попробуем ее создать
                        IqAmeGeoPoint newPoint;
                        if (newPoint.fromCoordinate(p2Name))
                        {
                            int newPointRow = IqAmeApplication::aeroMapModel()->pointsModel()->rowCount();
                            IqAmeApplication::aeroMapModel()->pointsModel()->insertRow(newPointRow);
                            p2 = IqAmeApplication::aeroMapModel()->pointsModel()->at(newPointRow);
                            p2->setName(newPoint.name());
                            p2->setLatitude(newPoint.latitude());
                            p2->setLongitude(newPoint.longitude());
                        }
                        else
                        {
                            qWarning() << tr("Point \"%0\" not found and can not create. Skipped...").arg(p2Name);
                            p1Name = p2Name;
                            continue;
                        }
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

    //Включим автоматическое обновление bbox
    _autoUpdateBoundingBox = true;
    //Обновим bbox
    updateBoundingBox();

    return true;
}

void IqAmeSubLine::paingGl(const QRectF &area, IqLayerView *layerView)
{
    switch(outputAttributes()->texture())
    {
    case IqAmeShapesAttributes::FFFF:
        glLineStipple(1,0xFFFF);
        break;
    case IqAmeShapesAttributes::FF00:
        glLineStipple(1, 0xFF00);
        break;
    case IqAmeShapesAttributes::E4E4:
        glLineStipple(1, 0xE4E4);
        break;
    case IqAmeShapesAttributes::AAAA:
        glLineStipple(1, 0xAAAA);
        break;
    }

    switch (outputAttributes()->depth())
    {
    case IqAmeShapesAttributes::Normal:
        glLineWidth(1.0);
        break;
    case IqAmeShapesAttributes::Full:
        glLineWidth(3.0);
        break;
    }

    layerView->qglColor(outputAttributes()->toRGBColor());

    foreach (IqAmeLineSegment* segment, _segments)
    {
        segment->paintGl(area, layerView);
    }
}

void IqAmeSubLine::setAttributes(IqAmeShapesAttributes *attributes)
{
    if (_attributes != attributes)
    {
        _attributes = attributes;

        emit attributesChanged();
        emit outputAttributesChanged();
    }
}

void IqAmeSubLine::updateBoundingBox()
{
    if (_autoUpdateBoundingBox)
    {
        QPointF topLeft;
        QPointF bottomRight;

        QPointF point;
        foreach (IqAmeLineSegment* segment, _segments)
        {
            point = segment->startPoint()->toGlPoint();
            if (point.x() < topLeft.x())
            {
                topLeft.setX(point.x());
            } else if (point.x() > bottomRight.x())
            {
                bottomRight.setX(point.x());
            }
            if (point.y() < topLeft.y())
            {
                topLeft.setY(point.y());
            } else if (point.y() > bottomRight.y())
            {
                bottomRight.setY(point.y());
            }

            point = segment->endPoint()->toGlPoint();
            if (point.x() < topLeft.x())
            {
                topLeft.setX(point.x());
            } else if (point.x() > bottomRight.x())
            {
                bottomRight.setX(point.x());
            }
            if (point.y() < topLeft.y())
            {
                topLeft.setY(point.y());
            } else if (point.y() > bottomRight.y())
            {
                bottomRight.setY(point.y());
            }
        }

        setBoundingBox(QRectF(topLeft, bottomRight));
    }
}
