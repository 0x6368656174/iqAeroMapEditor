#include "iqameshapelink.h"

IqAmeShapeLink::IqAmeShapeLink() :
    m_namedShapeObject(Q_NULLPTR)
{
}

IqAmeNamedShapeObject *IqAmeShapeLink::namedShapeObject() const
{
    return m_namedShapeObject;
}

void IqAmeShapeLink::setNamedShapeObject(IqAmeNamedShapeObject *namedShapeObject)
{
    m_namedShapeObject = namedShapeObject;
}
