#include "iqamenamedshapeobject.h"

IqAmeNamedShapeObject::IqAmeNamedShapeObject(QObject *parent) :
    IqAmeShapeObject(parent),
    m_visible(false)
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

bool IqAmeNamedShapeObject::visible() const
{
    return m_visible;
}

void IqAmeNamedShapeObject::setVisible(bool visible)
{
    if (m_visible != visible) {
        m_visible = visible;
        emit visibleChanged();
    }
}

bool IqAmeNamedShapeObject::interactive()
{
    foreach (QGraphicsItem *item, graphicsItems()) {
        if (item->flags() & QGraphicsItem::ItemIsSelectable)
            return true;
    }
    return false;
}

void IqAmeNamedShapeObject::setInteractive(bool interactive)
{
    if (this->interactive() != interactive) {
        foreach (QGraphicsItem *item, graphicsItems()) {
            item->setFlag(QGraphicsItem::ItemIsSelectable, interactive);
        }
        emit interactiveChanged();
    }
}
