#ifndef IQAMESUBLINE_H
#define IQAMESUBLINE_H

#include <QObject>
#include "iqamelineattributes.h"
#include "iqamelinesegment.h"

class IqAmeSubLine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(IqAmeLineAttributes* attributes READ attributes CONSTANT)

public:
    explicit IqAmeSubLine(QObject *parent = 0);

    void appendSegment(IqAmeLineSegment *segment);

    void insertSegment(const int position, IqAmeLineSegment *segment);

    void removeSegment(IqAmeLineSegment *segment);

    bool loadFromString(const QString &string);

public:
    inline IqAmeLineAttributes *attributes() const {return _attributes;}

private:
    IqAmeLineAttributes *_attributes;
    QList<IqAmeLineSegment *> _segments;
};

#endif // IQAMESUBLINE_H
