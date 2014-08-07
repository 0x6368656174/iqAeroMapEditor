#include "iqameshapeobject.h"

IqAmeShapeObject::IqAmeShapeObject(QObject *parent) :
    QObject(parent),
    _inputAttributes(NULL),
    _attributes(NULL)
{
}

IqAmeShapeObject::~IqAmeShapeObject()
{
}

void IqAmeShapeObject::setName(const QString &name)
{
    if (_name != name)
    {
        _name = name;

        emit nameChanged();
    }
}

void IqAmeShapeObject::setComment(const QString &comment)
{
    if (_comment != comment)
    {
        _comment = comment;

        emit commentChanged();
    }
}

void IqAmeShapeObject::setInputAttributes(IqAmeShapesAttributes *attributes)
{
    if (_inputAttributes != attributes)
    {
        _inputAttributes = attributes;

        if (!_attributes)
            emit outputAttributesChanged();

        emit inputAttributesChanged();
    }
}

IqAmeShapesAttributes * IqAmeShapeObject::outputAttributes() const
{
    if (_attributes)
    {
        return _attributes;
    }
    return _inputAttributes;
}

void IqAmeShapeObject::setAttributes(IqAmeShapesAttributes *attributes)
{
    if (_attributes != attributes)
    {
        _attributes = attributes;

        emit attributesChanged();
        emit outputAttributesChanged();
    }
}

void IqAmeShapeObject::setBoundingBox(const QRectF &boundingBox)
{
    if (_boundingBox != boundingBox)
    {
        _boundingBox = boundingBox;

        emit boundingBoxChanged();
    }
}
