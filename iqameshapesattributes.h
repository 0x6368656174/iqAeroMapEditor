#ifndef IQAMELINEATTRIBUTES_H
#define IQAMELINEATTRIBUTES_H

#include <QObject>
#include <QColor>
#include <QPen>
#include <QFont>

class IqAmeShapesAttributes : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Color color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(Texture texture READ texture WRITE setTexture NOTIFY textureChanged)
    Q_PROPERTY(Depth depth READ depth WRITE setDepth NOTIFY depthChanged)
    Q_PROPERTY(FillMode fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged)
    Q_PROPERTY(TextSize textSize READ textSize WRITE setTextSize NOTIFY textSizeChanged)
    Q_PROPERTY(QColor rgbColor READ rgbColor NOTIFY rgbColorChanged)
    Q_PROPERTY(QPen pen READ pen NOTIFY penChanged)
    Q_PROPERTY(QFont font READ font NOTIFY fontChanged)
    Q_ENUMS(Color)
    Q_ENUMS(Texture)
    Q_ENUMS(Depth)
    Q_ENUMS(FillMode)
    Q_ENUMS(TextSize)
public:
    enum Color
    {
        Black,
        Blue,
        Green,
        Cyan,
        Red,
        Magenta,
        Brown,
        White,
        Gray,
        LBlue,
        LGreen,
        LCyan,
        LRed,
        LMagenta,
        Yellow,
        BrigthWhite
    };

    enum Texture
    {
        FFFF, //! < Сплошная
        FF00, //! < Штриховая
        E4E4, //! < Штрих-пунктирная
        AAAA  //! < Пунктирная
    };

    enum Depth
    {
        Normal,
        Full
    };

    enum FillMode
    {
        Fill,
        EmptyFill
    };

    enum TextSize
    {
        R1,
        R2,
        R3,
        R4
    };

    explicit IqAmeShapesAttributes(QObject *parent = Q_NULLPTR);

    bool loadFromString(const QString &string);

    QColor rgbColor() const;

    QPen pen() const;

    QFont font() const;

public:
    Color color() const;
    void setColor(const Color color);

    Texture texture() const;
    void setTexture(const Texture texture);

    Depth depth() const;
    void setDepth(const Depth depth);

    FillMode fillMode() const;
    void setFillMode(const FillMode fillMode);

    TextSize textSize() const;
    void setTextSize(const TextSize textSize);

signals:
    void colorChanged();
    void textureChanged();
    void depthChanged();
    void fillModeChanged();
    void textSizeChanged();
    void rgbColorChanged();
    void penChanged();
    void fontChanged();

private:
    Color m_color;
    Texture m_texture;
    Depth m_depth;
    FillMode m_fillMode;
    TextSize m_textSize;
};

#endif // IQAMELINEATTRIBUTES_H
