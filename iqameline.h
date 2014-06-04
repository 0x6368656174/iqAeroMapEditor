#ifndef IQAMELINE_H
#define IQAMELINE_H

#include "iqamegraphicobject.h"
#include "iqamesubline.h"

class IqAmeLine : public IqAmeGraphicObject
{
    Q_OBJECT
    Q_PROPERTY(IqAmeLineAttributes* baseAttributes READ baseAttributes WRITE setBaseAttributes NOTIFY baseAttributesChanged)

public:

    explicit IqAmeLine(QObject *parent = 0);

    bool loadFromString(const QString &string);

    void appendSubLine(IqAmeSubLine *subLine);

    void insertSubLine(const int position, IqAmeSubLine *subLine);

    void removeSubLine(IqAmeSubLine *subLine);

public:
    inline IqAmeLineAttributes *baseAttributes() const {return _baseAttributes;}
    void  setBaseAttributes(IqAmeLineAttributes *attributes);

signals:
    void baseAttributesChanged();

private:
    IqAmeLineAttributes *_baseAttributes;

    QList<IqAmeSubLine *> _subLines;
};

#endif // IQAMELINE_H
