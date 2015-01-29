#ifndef IQAMESYMBOL_H
#define IQAMESYMBOL_H

#include "iqamenamedshapeobject.h"
#include "iqamegeopoint.h"
#include "iqamesymbolgraphicsitem.h"

class IqAmeSymbol : public IqAmeNamedShapeObject
{
    Q_OBJECT
    Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(IqAmeGeoPoint* point READ point WRITE setPoint NOTIFY pointChanged)
    Q_ENUMS(Type)
public:
    enum Type
    {
        PointRequedReport = 1,              //!< Пункт обязательного доклада (ПОД)
        PointRequestReport = 2,             //!< Пункт доклада по запросу органа УВД
        Ndb = 3,                            //!< Отдельная приводная радиостанция (ОПРС), отдельный приводной радиомояк (ОПРМ)
        ArtificalObstaclesWithouLight = 4,  //!< Искуственное препятствие без светоограждения
        VorDme = 6,                         //!< Всенаправленный азимутальный радиомаяк и всенаправленный дальномерный радиомаяк
        CivilAirport = 7,                   //!< Аэродром гражданской авиации
        MixedAirport = 8,                   //!< Аэродром совместного базирования
        MilitaryAirport = 9                 //!< Аэродром государственной авиации
    };

    explicit IqAmeSymbol(QObject *parent = 0);
    ~IqAmeSymbol();

    virtual QList<QGraphicsItem *> graphicsItems() Q_DECL_OVERRIDE;

    virtual void updateGraphicsItems() Q_DECL_OVERRIDE;

    virtual bool loadFromString(const QString &string) Q_DECL_OVERRIDE;

public:
    IqAmeGeoPoint *point() const;
    void setPoint(IqAmeGeoPoint *point);

    Type type() const;
    void setType(const Type &type);

signals:
    void typeChanged();
    void pointChanged();

private:
    IqAmeSymbolGraphicsItem *symbolGraphicsItem();

private:
    Type m_type;
    IqAmeGeoPoint *m_point;
    IqAmeSymbolGraphicsItem *m_graphicsSymbolItem;
};

#endif // IQAMESYMBOL_H
