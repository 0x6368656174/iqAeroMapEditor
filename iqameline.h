#ifndef IQAMELINE_H
#define IQAMELINE_H

#include "iqameshapeobject.h"
#include "iqamesubline.h"

class IqAmeLine : public IqAmeShapeObject
{
    Q_OBJECT
public:

    explicit IqAmeLine(QObject *parent = 0);

    virtual void paindGl(const QRectF &area, IqLayerView *layerView);

    virtual bool loadFromString(const QString &string);

    void appendSubLine(IqAmeSubLine *subLine);

    void insertSubLine(const int position, IqAmeSubLine *subLine);

    void removeSubLine(IqAmeSubLine *subLine);

public:
    inline virtual IqAmeShapesAttributes * outputAttributes() const {return _outputAttributes;}

private:
    QList<IqAmeSubLine *> _subLines;
    IqAmeShapesAttributes * _outputAttributes;
    bool _autoUpdateBoundingBox;

    void setOutputAttributes(IqAmeShapesAttributes * outputAttributes);

    void updateBoundingBox();
};

#endif // IQAMELINE_H
