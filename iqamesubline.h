#ifndef IQAMESUBLINE_H
#define IQAMESUBLINE_H

#include <QObject>
#include <QRectF>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include "iqlayerview.h"
#include "iqameshapesattributes.h"
#include "iqamelinesegment.h"
#include "iqameshapeobject.h"
#include "iqamesublinegraphicsitem.h"

class IqAmeLine;
class IqAmeSubLine : public IqAmeShapeObject
{
    Q_OBJECT
public:
    explicit IqAmeSubLine(QObject *parent = Q_NULLPTR);

    ~IqAmeSubLine();

    IqAmeSublineGraphicsItem *graphicsItem();

    bool loadFromString(const QString &string);

    void appendSegment(IqAmeLineSegment *segment);

    void insertSegment(const int position, IqAmeLineSegment *segment);

    void removeSegment(IqAmeLineSegment *segment);

public:
    QList<IqAmeLineSegment *> segments() const;

    IqAmeLine *line() const;
    void setLine(IqAmeLine *line);

private:
    IqAmeLine *m_line;
    QList<IqAmeLineSegment *> m_segments;
    IqAmeSublineGraphicsItem *m_graphicsItem;
};

#endif // IQAMESUBLINE_H
