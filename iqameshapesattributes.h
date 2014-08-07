#ifndef IQAMELINEATTRIBUTES_H
#define IQAMELINEATTRIBUTES_H

#include <QObject>
#include <QColor>

class IqAmeShapesAttributes : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Color color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(Texture texture READ texture WRITE setTexture NOTIFY textureChanged)
    Q_PROPERTY(Depth depth READ depth WRITE setDepth NOTIFY depthChanged)
    Q_PROPERTY(FillMode fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged)
    Q_PROPERTY(TextSize textSize READ textSize WRITE setTextSize NOTIFY textSizeChanged)
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

    explicit IqAmeShapesAttributes(QObject *parent = 0);

    bool loadFromString(const QString &string);

    QColor toRGBColor() const;

public:
    inline Color color() const {return _color;}
    void setColor(const Color color);

    inline Texture texture() const {return _texture;}
    void setTexture(const Texture texture);

    inline Depth depth() const {return _depth;}
    void setDepth(const Depth depth);

    inline FillMode fillMode() const {return _fillMode;}
    void setFillMode(const FillMode fillMode);

    inline TextSize textSize() const {return _textSize;}
    void setTextSize(const TextSize textSize);

signals:
    void colorChanged();
    void textureChanged();
    void depthChanged();
    void fillModeChanged();
    void textSizeChanged();

private:
    Color _color;
    Texture _texture;
    Depth _depth;
    FillMode _fillMode;
    TextSize _textSize;
};

#endif // IQAMELINEATTRIBUTES_H
