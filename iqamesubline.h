#ifndef IQAMESUBLINE_H
#define IQAMESUBLINE_H

#include <QObject>
#include <QRectF>
#include "iqlayerview.h"
#include "iqameshapesattributes.h"
#include "iqamelinesegment.h"

class IqAmeSubLine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(IqAmeShapesAttributes* inputAttributes READ inputAttributes WRITE setInputAttributes NOTIFY inputAttributesChanged)
    Q_PROPERTY(IqAmeShapesAttributes* attributes READ attributes NOTIFY attributesChanged)
    Q_PROPERTY(IqAmeShapesAttributes* outputAttributes READ outputAttributes NOTIFY outputAttributesChanged)
    Q_PROPERTY(QRectF boundingBox READ boundingBox WRITE setBoundingBox NOTIFY boundingBoxChanged)
public:
    explicit IqAmeSubLine(QObject *parent = 0);

    void paingGl(const QRectF &area, IqLayerView *layerView);

    void appendSegment(IqAmeLineSegment *segment);

    void insertSegment(const int position, IqAmeLineSegment *segment);

    void removeSegment(IqAmeLineSegment *segment);

    bool loadFromString(const QString &string);

public:
    inline IqAmeShapesAttributes *inputAttributes() const {return _inputAttributes;}
    void  setInputAttributes(IqAmeShapesAttributes *attributes);

    inline IqAmeShapesAttributes *attributes() const {return _attributes;}
    void setAttributes(IqAmeShapesAttributes *attributes);

    IqAmeShapesAttributes *outputAttributes() const;

    inline QRectF boundingBox() const {return _boundingBox;}

signals:
    void inputAttributesChanged();
    void attributesChanged();
    void outputAttributesChanged();
    void boundingBoxChanged();

private:
    IqAmeShapesAttributes *_inputAttributes;
    IqAmeShapesAttributes *_attributes;
    QList<IqAmeLineSegment *> _segments;
    QRectF _boundingBox;
    bool _autoUpdateBoundingBox;

    void setBoundingBox(const QRectF &boundingBox);
    void updateBoundingBox();
};

#endif // IQAMESUBLINE_H
