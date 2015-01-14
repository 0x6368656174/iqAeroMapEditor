#ifndef IQAMENAMEDSHAPEOBJECT_H
#define IQAMENAMEDSHAPEOBJECT_H

#include "iqameshapeobject.h"

class IqAmeNamedShapeObject : public IqAmeShapeObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)
public:
    explicit IqAmeNamedShapeObject(QObject *parent = Q_NULLPTR);

public:
    QString name() const;
    void setName(const QString &name);

    QString comment() const;
    void setComment(const QString &comment);

signals:
    void nameChanged();
    void commentChanged();

private:
    QString m_name;
    QString m_comment;
};

#endif // IQAMENAMEDSHAPEOBJECT_H
