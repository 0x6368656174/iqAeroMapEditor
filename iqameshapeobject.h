#ifndef IQAMEGRAPHICOBJECT_H
#define IQAMEGRAPHICOBJECT_H

#include <QObject>
#include <QMetaType>
#include <QRectF>
#include "iqlayerview.h"
#include "iqameshapesattributes.h"

class IqAmeShapeObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)
    Q_PROPERTY(IqAmeShapesAttributes* inputAttributes READ inputAttributes WRITE setInputAttributes NOTIFY inputAttributesChanged)
    Q_PROPERTY(IqAmeShapesAttributes* attributes READ attributes NOTIFY attributesChanged)
    Q_PROPERTY(IqAmeShapesAttributes* outputAttributes READ outputAttributes NOTIFY outputAttributesChanged)
    Q_PROPERTY(QRectF boundingBox READ boundingBox WRITE setBoundingBox NOTIFY boundingBoxChanged)

public:
    explicit IqAmeShapeObject(QObject *parent = 0);

    virtual ~IqAmeShapeObject();

    virtual void paindGl(const QRectF &area, IqLayerView *layerView) = 0;

    virtual bool loadFromString(const QString &string) = 0;

public:
    inline QString name() const {return _name;}
    void setName(const QString &name);

    inline QString comment() const {return _comment;}
    void setComment(const QString &comment);

    inline IqAmeShapesAttributes *inputAttributes() const {return _inputAttributes;}
    void  setInputAttributes(IqAmeShapesAttributes *attributes);

    inline IqAmeShapesAttributes *attributes() const {return _attributes;}
    void setAttributes(IqAmeShapesAttributes *attributes);

    virtual IqAmeShapesAttributes *outputAttributes() const;

    inline QRectF boundingBox() const {return _boundingBox;}

signals:
    void nameChanged();
    void commentChanged();
    void inputAttributesChanged();
    void attributesChanged();
    void outputAttributesChanged();
    void boundingBoxChanged();

protected:
    void setBoundingBox(const QRectF &boundingBox);

private:
    QString _name;
    QString _comment;
    IqAmeShapesAttributes *_inputAttributes;
    IqAmeShapesAttributes *_attributes;
    QRectF _boundingBox;
};

Q_DECLARE_METATYPE(IqAmeShapeObject *)

#endif // IQAMEGRAPHICOBJECT_H
