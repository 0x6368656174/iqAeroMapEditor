#ifndef IQAMEGRAPHICOBJECT_H
#define IQAMEGRAPHICOBJECT_H

#include <QObject>
#include <QMetaType>
#include <QRectF>
#include <QGraphicsItem>
#include "iqlayerview.h"
#include "iqameshapesattributes.h"

class IqAmeShapeObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(IqAmeShapesAttributes* inputAttributes READ inputAttributes WRITE setInputAttributes NOTIFY inputAttributesChanged)
    Q_PROPERTY(IqAmeShapesAttributes* attributes READ attributes NOTIFY attributesChanged)
    Q_PROPERTY(IqAmeShapesAttributes* outputAttributes READ outputAttributes NOTIFY outputAttributesChanged)

public:
    explicit IqAmeShapeObject(QObject *parent = Q_NULLPTR);

    virtual ~IqAmeShapeObject();

    virtual IqAmeShapesAttributes *outputAttributes() const;

public:
    IqAmeShapesAttributes *inputAttributes() const;
    void  setInputAttributes(IqAmeShapesAttributes *attributes);

    IqAmeShapesAttributes *attributes() const;
    void setAttributes(IqAmeShapesAttributes *attributes);

signals:
    void inputAttributesChanged();
    void attributesChanged();
    void outputAttributesChanged();

private:
    IqAmeShapesAttributes *m_inputAttributes;
    IqAmeShapesAttributes *m_attributes;
};

Q_DECLARE_METATYPE(IqAmeShapeObject *)

#endif // IQAMEGRAPHICOBJECT_H
