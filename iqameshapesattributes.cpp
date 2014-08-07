#include "iqameshapesattributes.h"
#include <QRegExp>

IqAmeShapesAttributes::IqAmeShapesAttributes(QObject *parent) :
    QObject(parent),
    _color(White),
    _texture(FFFF),
    _depth(Normal),
    _fillMode(EmptyFill),
    _textSize(R1)
{
}

void IqAmeShapesAttributes::setColor(const Color color)
{
    if (_color != color)
    {
        _color = color;

        emit colorChanged();
    }
}

void IqAmeShapesAttributes::setTexture(const Texture texture)
{
    if (_texture != texture)
    {
        _texture = texture;

        emit textureChanged();
    }
}

void IqAmeShapesAttributes::setDepth(const Depth depth)
{
    if (_depth != depth)
    {
        _depth = depth;

        emit depthChanged();
    }
}

void IqAmeShapesAttributes::setFillMode(const FillMode fillMode)
{
    if (_fillMode != fillMode)
    {
        _fillMode = fillMode;

        emit fillModeChanged();
    }
}

void IqAmeShapesAttributes::setTextSize(const TextSize textSize)
{
    if (_textSize != textSize)
    {
        _textSize = textSize;

        emit textSizeChanged();
    }
}

bool IqAmeShapesAttributes::loadFromString(const QString &string)
{
    QRegExp attribueRx("<\\s*"
                       "(BLACK|BLUE|GREEN|CYAN|RED|MAGENTA|BROWN|WHITE|GRAY|LBLUE|LGREEN|LCYAN|LRED|LMAGENTA|YELLOW|BRIGHTWHITE){0,1}"
                       "(\\s*,{0,1}\\s*(ffff|ff00|e4e4|aaaa)){0,1}"
                       "(\\s*,{0,1}\\s*(normal|full)){0,1}"
                       "(\\s*,{0,1}\\s*(fill|empty)){0,1}"
                       "(\\s*,{0,1}\\s*(R1|R2|R3|R4)){0,1}"
                       "\\s*>");

    if (attribueRx.indexIn(string) != -1)
    {
        if (!attribueRx.cap(1).isEmpty())
        {
            QString color = attribueRx.cap(1);

            if (color.compare("BLACK", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::Black);
            }
            else if (color.compare("BLUE", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::Blue);
            }
            else if (color.compare("GREEN", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::Green);
            }
            else if (color.compare("CYAN", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::Cyan);
            }
            else if (color.compare("RED", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::Red);
            }
            else if (color.compare("MAGENTA", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::Magenta);
            }
            else if (color.compare("BROWN", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::Brown);
            }
            else if (color.compare("WHITE", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::White);
            }
            else if (color.compare("GRAY", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::Gray);
            }
            else if (color.compare("LBLUE", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::LBlue);
            }
            else if (color.compare("LGREEN", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::LGreen);
            }
            else if (color.compare("LCYAN", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::LCyan);
            }
            else if (color.compare("LRED", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::LRed);
            }
            else if (color.compare("LMAGENTA", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::LMagenta);
            }
            else if (color.compare("YELLOW", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::Yellow);
            }
            else if (color.compare("BRIGHTWHITE", Qt::CaseInsensitive) == 0)
            {
                setColor(IqAmeShapesAttributes::BrigthWhite);
            }
        }
        if (!attribueRx.cap(3).isEmpty())
        {
            QString texture = attribueRx.cap(3);

            if (texture.compare("ffff", Qt::CaseInsensitive) == 0)
            {
                setTexture(IqAmeShapesAttributes::FFFF);
            }
            else if (texture.compare("ff00", Qt::CaseInsensitive) == 0)
            {
                setTexture(IqAmeShapesAttributes::FF00);
            }
            else if (texture.compare("e4e4", Qt::CaseInsensitive) == 0)
            {
                setTexture(IqAmeShapesAttributes::E4E4);
            }
            else if (texture.compare("aaaa", Qt::CaseInsensitive) == 0)
            {
                setTexture(IqAmeShapesAttributes::AAAA);
            }
        }
        if (!attribueRx.cap(5).isEmpty())
        {
            QString depth = attribueRx.cap(5);

            if (depth.compare("normal", Qt::CaseInsensitive) == 0)
            {
                setDepth(IqAmeShapesAttributes::Normal);
            }
            else if (depth.compare("full", Qt::CaseInsensitive) == 0)
            {
                setDepth(IqAmeShapesAttributes::Full);
            }
        }
        if (!attribueRx.cap(7).isEmpty())
        {
            QString fillMode = attribueRx.cap(7);

            if (fillMode.compare("fill", Qt::CaseInsensitive) == 0)
            {
                setFillMode(IqAmeShapesAttributes::Fill);
            }
            else if (fillMode.compare("empty", Qt::CaseInsensitive) == 0)
            {
                setFillMode(IqAmeShapesAttributes::EmptyFill);
            }
        }
        if (!attribueRx.cap(9).isEmpty())
        {
            QString textSize = attribueRx.cap(9);

            if (textSize.compare("R1", Qt::CaseInsensitive) == 0)
            {
                setTextSize(R1);
            }
            else if (textSize.compare("R2", Qt::CaseInsensitive) == 0)
            {
                setTextSize(R2);
            }
            else if (textSize.compare("R3", Qt::CaseInsensitive) == 0)
            {
                setTextSize(R3);
            }
            else if (textSize.compare("R4", Qt::CaseInsensitive) == 0)
            {
                setTextSize(R4);
            }
        }
    }

    return true;
}

QColor IqAmeShapesAttributes::toRGBColor() const
{
    switch (color())
    {
    case IqAmeShapesAttributes::Black:
        return QColor(0, 0, 0);
    case IqAmeShapesAttributes::Blue:
        return QColor(0, 0, 255);
    case IqAmeShapesAttributes::Green:
        return QColor(0, 255, 0);
    case IqAmeShapesAttributes::Cyan:
        return QColor(0, 255, 255);
    case IqAmeShapesAttributes::Red:
        return QColor(255, 0, 0);
    case IqAmeShapesAttributes::Magenta:
        return QColor(255, 0, 255);
    case IqAmeShapesAttributes::Brown:
        return QColor(150, 75, 0);
    case IqAmeShapesAttributes::White:
        return QColor(250, 250, 250);
    case IqAmeShapesAttributes::Gray:
        return QColor(128, 128, 128);
    case IqAmeShapesAttributes::LBlue:
        return QColor(173, 216, 230);
    case IqAmeShapesAttributes::LGreen:
        return QColor(144, 238, 144);
    case IqAmeShapesAttributes::LCyan:
        return QColor(224, 255, 255);
    case IqAmeShapesAttributes::LRed:
        return QColor(255, 80, 80);
    case IqAmeShapesAttributes::LMagenta:
        return QColor(255, 66, 249);
    case IqAmeShapesAttributes::Yellow:
        return QColor(255, 255, 0);
    case IqAmeShapesAttributes::BrigthWhite:
        return QColor(255, 255, 255);
    }

    return QColor("white");
}
