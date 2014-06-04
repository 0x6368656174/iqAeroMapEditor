#ifndef IQAMELINEATTRIBUTES_H
#define IQAMELINEATTRIBUTES_H

#include <QObject>

class IqAmeLineAttributes : public QObject
{
    Q_OBJECT
    Q_PROPERTY(IqAmeLineAttributes* baseAttributes READ baseAttributes WRITE setBaseAttributes NOTIFY baseAttributesChanged)
    Q_PROPERTY(Color color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(Texture texture READ texture WRITE setTexture NOTIFY textureChanged)
    Q_PROPERTY(Depth depth READ depth WRITE setDepth NOTIFY depthChanged)
    Q_PROPERTY(FillMode fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged)
    Q_ENUMS(Color)
    Q_ENUMS(Texture)
    Q_ENUMS(Depth)
    Q_ENUMS(FillMode)
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

    explicit IqAmeLineAttributes(QObject *parent = 0);

public:
    inline IqAmeLineAttributes *baseAttributes() const {return _baseAttributes;}
    void  setBaseAttributes(IqAmeLineAttributes *attributes);

    inline Color color() const {return _color;}
    void setColor(const Color color);

    inline Texture texture() const {return _texture;}
    void setTexture(const Texture texture);

    inline Depth depth() const {return _depth;}
    void setDepth(const Depth depth);

    inline FillMode fillMode() const {return _fillMode;}
    void setFillMode(const FillMode fillMode);

signals:
    void baseAttributesChanged();
    void colorChanged();
    void textureChanged();
    void depthChanged();
    void fillModeChanged();

private:
    IqAmeLineAttributes *_baseAttributes;
    Color _color;
    Texture _texture;
    Depth _depth;
    FillMode _fillMode;
};

#endif // IQAMELINEATTRIBUTES_H
