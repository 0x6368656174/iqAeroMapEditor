#ifndef IQAMETEXT_H
#define IQAMETEXT_H

#include "iqamenamedshapeobject.h"
#include "iqamegeopoint.h"
#include "iqametextgraphicsitem.h"

class IqAmeText : public IqAmeNamedShapeObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(IqAmeGeoPoint* point READ point WRITE setPoint NOTIFY pointChanged)
public:
    explicit IqAmeText(QObject *parent = Q_NULLPTR);

    ~IqAmeText();

    virtual IqAmeTextGraphicsItem *graphicsItem() Q_DECL_OVERRIDE;

    virtual void updateGraphicsItem() Q_DECL_OVERRIDE;

    virtual bool loadFromString(const QString &string);

public:
    QString text() const;
    void setText(const QString &text);

    IqAmeGeoPoint *point() const;
    void setPoint(IqAmeGeoPoint *point);

signals:
    void textChanged();
    void pointChanged();

private:
    QString m_text;
    IqAmeGeoPoint *m_point;
    IqAmeTextGraphicsItem *m_graphicsTextItem;
};

#endif // IQAMETEXT_H
