#ifndef IQAMESHAPELINK_H
#define IQAMESHAPELINK_H

#include "iqamenamedshapeobject.h"

class IqAmeShapeLink
{
public:
    IqAmeShapeLink();

    IqAmeNamedShapeObject *namedShapeObject() const;
    void setNamedShapeObject(IqAmeNamedShapeObject *namedShapeObject);

private:
    IqAmeNamedShapeObject *m_namedShapeObject;
};

#endif // IQAMESHAPELINK_H
