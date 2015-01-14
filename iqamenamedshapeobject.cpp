#include "iqamenamedshapeobject.h"

IqAmeNamedShapeObject::IqAmeNamedShapeObject(QObject *parent) :
    IqAmeShapeObject(parent)
{
}

QString IqAmeNamedShapeObject::name() const {
    return m_name;
}

void IqAmeNamedShapeObject::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

QString IqAmeNamedShapeObject::comment() const
{
    return m_comment;
}

void IqAmeNamedShapeObject::setComment(const QString &comment)
{
    if (m_comment != comment) {
        m_comment = comment;
        emit commentChanged();
    }
}
