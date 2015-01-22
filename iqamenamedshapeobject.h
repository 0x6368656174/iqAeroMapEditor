#ifndef IQAMENAMEDSHAPEOBJECT_H
#define IQAMENAMEDSHAPEOBJECT_H

#include "iqameshapeobject.h"

class IqAmeNamedShapeObject : public IqAmeShapeObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool interactive READ interactive WRITE setInteractive NOTIFY interactiveChanged)
public:
    explicit IqAmeNamedShapeObject(QObject *parent = Q_NULLPTR);

    virtual QList<QGraphicsItem *> graphicsItems() = 0;

    virtual void updateGraphicsItems() = 0;

    virtual bool loadFromString(const QString &string) = 0;

public:
    QString name() const;
    void setName(const QString &name);

    QString comment() const;
    void setComment(const QString &comment);

    bool visible() const;
    void setVisible(bool visible);

    bool interactive();
    void setInteractive(bool interactive);

signals:
    void nameChanged();
    void commentChanged();
    void visibleChanged();
    void interactiveChanged();

private:
    QString m_name;
    QString m_comment;
    bool m_visible;
};

#endif // IQAMENAMEDSHAPEOBJECT_H
