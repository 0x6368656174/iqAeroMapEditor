#ifndef IQAMESTRAIGHTLINESEGMENT_H
#define IQAMESTRAIGHTLINESEGMENT_H

#include "iqamelinesegment.h"
#include <QGraphicsLineItem>

class IqAmeStraightLineSegment : public IqAmeLineSegment
{
    Q_OBJECT
public:
    explicit IqAmeStraightLineSegment(QObject *parent = Q_NULLPTR);

    virtual void drawSegment(QPainterPath *painterPath) const Q_DECL_OVERRIDE;

private:
    QGraphicsLineItem *m_graphicsItem;
};

#endif // IQAMESTRAIGHTLINESEGMENT_H
