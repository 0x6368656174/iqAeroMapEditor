#include "iqameshapeobject.h"

IqAmeShapeObject::IqAmeShapeObject(QObject *parent) :
    QObject(parent),
    m_inputAttributes(Q_NULLPTR),
    m_attributes(Q_NULLPTR),
    m_graphicsItem(Q_NULLPTR)
{
}

IqAmeShapeObject::~IqAmeShapeObject()
{
}

IqAmeShapesAttributes *IqAmeShapeObject::inputAttributes() const
{
    return m_inputAttributes;
}

void IqAmeShapeObject::setInputAttributes(IqAmeShapesAttributes *attributes)
{
    if (m_inputAttributes != attributes) {
        m_inputAttributes = attributes;

        if (!m_attributes)
            emit outputAttributesChanged();

        emit inputAttributesChanged();
    }
}

IqAmeShapesAttributes *IqAmeShapeObject::attributes() const
{
    return m_attributes;
}

IqAmeShapesAttributes * IqAmeShapeObject::outputAttributes() const
{
    if (m_attributes) {
        return m_attributes;
    }
    return m_inputAttributes;
}

void IqAmeShapeObject::setAttributes(IqAmeShapesAttributes *attributes)
{
    if (m_attributes != attributes) {
        m_attributes = attributes;

        emit attributesChanged();
        emit outputAttributesChanged();
    }
}
