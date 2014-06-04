#include "iqamelineattributes.h"

IqAmeLineAttributes::IqAmeLineAttributes(QObject *parent) :
    QObject(parent),
    _baseAttributes(NULL)
{
}

void IqAmeLineAttributes::setBaseAttributes(IqAmeLineAttributes *attributes)
{
    if (_baseAttributes != attributes)
    {
        _baseAttributes = attributes;

        emit baseAttributesChanged();
    }
}

void IqAmeLineAttributes::setColor(const Color color)
{
    if (_color != color)
    {
        _color = color;

        emit colorChanged();
    }
}

void IqAmeLineAttributes::setTexture(const Texture texture)
{
    if (_texture != texture)
    {
        _texture = texture;

        emit textureChanged();
    }
}

void IqAmeLineAttributes::setDepth(const Depth depth)
{
    if (_depth != depth)
    {
        _depth = depth;

        emit depthChanged();
    }
}

void IqAmeLineAttributes::setFillMode(const FillMode fillMode)
{
    if (_fillMode != fillMode)
    {
        _fillMode = fillMode;

        emit fillModeChanged();
    }
}
