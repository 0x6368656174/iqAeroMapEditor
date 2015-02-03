#include "iqameshapesattributes.h"
#include <QRegExp>

IqAmeShapesAttributes::IqAmeShapesAttributes(QObject *parent) :
    QObject(parent),
    m_color(White),
    m_texture(FFFF),
    m_depth(Normal),
    m_fillMode(EmptyFill),
    m_textSize(R1)
{
    connect(this, &IqAmeShapesAttributes::colorChanged, this, &IqAmeShapesAttributes::rgbColorChanged);
    connect(this, &IqAmeShapesAttributes::colorChanged, this, &IqAmeShapesAttributes::penChanged);
    connect(this, &IqAmeShapesAttributes::textureChanged, this, &IqAmeShapesAttributes::penChanged);
    connect(this, &IqAmeShapesAttributes::depthChanged, this, &IqAmeShapesAttributes::penChanged);
    connect(this, &IqAmeShapesAttributes::textSizeChanged, this, &IqAmeShapesAttributes::fontChanged);
}

void IqAmeShapesAttributes::setColor(const Color color)
{
    if (m_color != color) {
        m_color = color;

        emit colorChanged();
    }
}

IqAmeShapesAttributes::Texture IqAmeShapesAttributes::texture() const
{
    return m_texture;
}

void IqAmeShapesAttributes::setTexture(const Texture texture)
{
    if (m_texture != texture) {
        m_texture = texture;
        emit textureChanged();
    }
}

IqAmeShapesAttributes::Depth IqAmeShapesAttributes::depth() const
{
    return m_depth;
}

void IqAmeShapesAttributes::setDepth(const Depth depth)
{
    if (m_depth != depth) {
        m_depth = depth;
        emit depthChanged();
    }
}

IqAmeShapesAttributes::FillMode IqAmeShapesAttributes::fillMode() const
{
    return m_fillMode;
}

void IqAmeShapesAttributes::setFillMode(const FillMode fillMode)
{
    if (m_fillMode != fillMode) {
        m_fillMode = fillMode;
        emit fillModeChanged();
    }
}

IqAmeShapesAttributes::TextSize IqAmeShapesAttributes::textSize() const
{
    return m_textSize;
}

void IqAmeShapesAttributes::setTextSize(const TextSize textSize)
{
    if (m_textSize != textSize) {
        m_textSize = textSize;
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

    if (attribueRx.indexIn(string) != -1) {
        if (!attribueRx.cap(1).isEmpty()) {
            QString color = attribueRx.cap(1);

            if (color.compare("BLACK", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::Black);
            } else if (color.compare("BLUE", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::Blue);
            } else if (color.compare("GREEN", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::Green);
            } else if (color.compare("CYAN", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::Cyan);
            } else if (color.compare("RED", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::Red);
            } else if (color.compare("MAGENTA", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::Magenta);
            } else if (color.compare("BROWN", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::Brown);
            } else if (color.compare("WHITE", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::White);
            } else if (color.compare("GRAY", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::Gray);
            } else if (color.compare("LBLUE", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::LBlue);
            } else if (color.compare("LGREEN", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::LGreen);
            } else if (color.compare("LCYAN", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::LCyan);
            } else if (color.compare("LRED", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::LRed);
            } else if (color.compare("LMAGENTA", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::LMagenta);
            } else if (color.compare("YELLOW", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::Yellow);
            } else if (color.compare("BRIGHTWHITE", Qt::CaseInsensitive) == 0) {
                setColor(IqAmeShapesAttributes::BrigthWhite);
            }
        }
        if (!attribueRx.cap(3).isEmpty()) {
            QString texture = attribueRx.cap(3);

            if (texture.compare("ffff", Qt::CaseInsensitive) == 0) {
                setTexture(IqAmeShapesAttributes::FFFF);
            } else if (texture.compare("ff00", Qt::CaseInsensitive) == 0) {
                setTexture(IqAmeShapesAttributes::FF00);
            } else if (texture.compare("e4e4", Qt::CaseInsensitive) == 0) {
                setTexture(IqAmeShapesAttributes::E4E4);
            } else if (texture.compare("aaaa", Qt::CaseInsensitive) == 0) {
                setTexture(IqAmeShapesAttributes::AAAA);
            }
        }
        if (!attribueRx.cap(5).isEmpty()) {
            QString depth = attribueRx.cap(5);

            if (depth.compare("normal", Qt::CaseInsensitive) == 0) {
                setDepth(IqAmeShapesAttributes::Normal);
            } else if (depth.compare("full", Qt::CaseInsensitive) == 0) {
                setDepth(IqAmeShapesAttributes::Full);
            }
        }
        if (!attribueRx.cap(7).isEmpty()) {
            QString fillMode = attribueRx.cap(7);

            if (fillMode.compare("fill", Qt::CaseInsensitive) == 0) {
                setFillMode(IqAmeShapesAttributes::Fill);
            } else if (fillMode.compare("empty", Qt::CaseInsensitive) == 0) {
                setFillMode(IqAmeShapesAttributes::EmptyFill);
            }
        }
        if (!attribueRx.cap(9).isEmpty()) {
            QString textSize = attribueRx.cap(9);

            if (textSize.compare("R1", Qt::CaseInsensitive) == 0) {
                setTextSize(R1);
            } else if (textSize.compare("R2", Qt::CaseInsensitive) == 0) {
                setTextSize(R2);
            } else if (textSize.compare("R3", Qt::CaseInsensitive) == 0) {
                setTextSize(R3);
            } else if (textSize.compare("R4", Qt::CaseInsensitive) == 0) {
                setTextSize(R4);
            }
        }
    }

    return true;
}

QColor IqAmeShapesAttributes::rgbColor() const
{
    switch (color()) {
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

QPen IqAmeShapesAttributes::pen() const
{
    QPen pen;
    QBrush brush (rgbColor());
    pen.setBrush(brush);
    switch (texture()) {
    case FFFF:
        pen.setStyle(Qt::SolidLine);
        break;
    case FF00:
        pen.setStyle(Qt::DashLine);
        break;
    case E4E4:
        pen.setStyle(Qt::DashDotLine);
        break;
    case AAAA:
        pen.setStyle(Qt::DotLine);
        break;
    }
    switch (depth()) {
    case Normal:
        pen.setWidth(1);
        break;
    case Full:
        pen.setWidth(2);
        break;
    }
    pen.setCosmetic(true);

    return pen;
}

QFont IqAmeShapesAttributes::font() const
{
    QFont font;
    font.setPixelSize(10);
    switch (textSize()) {
    case IqAmeShapesAttributes::R1:
        break;
    case IqAmeShapesAttributes::R2:
        font.setPixelSize(font.pixelSize() * 1.5);
        break;
    case IqAmeShapesAttributes::R3:
        font.setPixelSize(font.pixelSize() * 2);
        break;
    case IqAmeShapesAttributes::R4:
        font.setPixelSize(font.pixelSize() * 2.5);
        break;
    }

    return font;
}

IqAmeShapesAttributes::Color IqAmeShapesAttributes::color() const
{
    return m_color;
}

