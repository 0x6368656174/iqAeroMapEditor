#include "iqamegraphicobject.h"

IqAmeGraphicObject::IqAmeGraphicObject(QObject *parent) :
    QObject(parent)
{
}

void IqAmeGraphicObject::setName(const QString &name)
{
    if (_name != name)
    {
        _name = name;

        emit nameChanged();
    }
}

void IqAmeGraphicObject::setComment(const QString &comment)
{
    if (_comment != comment)
    {
        _comment = comment;

        emit commentChanged();
    }
}
