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

class IqAmeSubLine : public IqAmeShapeObject
{
    Q_OBJECT
public:
    explicit IqAmeSubLine(QObject *parent = Q_NULLPTR);

    ~IqAmeSubLine();

    virtual IqAmeSublineGraphicsItem *graphicsItem() Q_DECL_OVERRIDE;

    virtual void updateGraphicsItem() Q_DECL_OVERRIDE;

    virtual bool loadFromString(const QString &string) Q_DECL_OVERRIDE;

    void appendSegment(IqAmeLineSegment *segment);

    void insertSegment(const int position, IqAmeLineSegment *segment);

    void removeSegment(IqAmeLineSegment *segment);

public:
    QList<IqAmeLineSegment *> segments() const;

private:
    QList<IqAmeLineSegment *> m_segments;
    IqAmeSublineGraphicsItem *m_graphicsItem;
};

#endif // IQAMESUBLINE_H
