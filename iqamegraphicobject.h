#ifndef IQAMEGRAPHICOBJECT_H
#define IQAMEGRAPHICOBJECT_H

#include <QObject>

class IqAmeGraphicObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit IqAmeGraphicObject(QObject *parent = 0);

public:
    inline QString name() const {return _name;}
    void setName(const QString &name);

    inline QString comment() const {return _comment;}
    void setComment(const QString &comment);

signals:
    void nameChanged();
    void commentChanged();

private:
    QString _name;
    QString _comment;
};

#endif // IQAMEGRAPHICOBJECT_H
