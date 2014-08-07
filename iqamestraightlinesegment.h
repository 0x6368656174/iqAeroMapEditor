#ifndef IQAMESTRAIGHTLINESEGMENT_H
#define IQAMESTRAIGHTLINESEGMENT_H

#include "iqamelinesegment.h"

class IqAmeStraightLineSegment : public IqAmeLineSegment
{
    Q_OBJECT
public:
    explicit IqAmeStraightLineSegment(QObject *parent = 0);

    virtual void paintGl(const QRectF &area, IqLayerView *layerView);
};

#endif // IQAMESTRAIGHTLINESEGMENT_H
