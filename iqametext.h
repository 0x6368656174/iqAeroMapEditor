#ifndef IQAMETEXT_H
#define IQAMETEXT_H

#include "iqameshapeobject.h"
#include "iqamegeopoint.h"

class IqAmeText : public IqAmeShapeObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(IqAmeGeoPoint* point READ point WRITE setPoint NOTIFY pointChanged)
public:
    explicit IqAmeText(QObject *parent = 0);

    virtual void paindGl(const QRectF &area, IqLayerView *layerView);

    virtual bool loadFromString(const QString &string);

public:
    inline QString text() const {return _text;}
    void setText(const QString &text);

    inline IqAmeGeoPoint *point() const {return _point;}
    void setPoint(IqAmeGeoPoint *point);

signals:
    void textChanged();
    void pointChanged();

private:
    QString _text;
    IqAmeGeoPoint *_point;

    void updateBoundingBox();
};

#endif // IQAMETEXT_H
