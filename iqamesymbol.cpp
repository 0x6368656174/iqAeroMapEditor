#include "iqamesymbol.h"
#include "iqameshapesattributes.h"
#include "iqameapplication.h"
#include <QRegExp>
#include <QDebug>
#include "iqameapplication.h"

IqAmeSymbol::IqAmeSymbol(QObject *parent) :
    IqAmeNamedShapeObject(parent),
    m_point(Q_NULLPTR),
    m_graphicsSymbolItem(Q_NULLPTR)
{
}

IqAmeSymbol::~IqAmeSymbol()
{
}

QList<QGraphicsItem *> IqAmeSymbol::graphicsItems()
{
    QList<QGraphicsItem *> result;
    result << symbolGraphicsItem();
    return result;
}

void IqAmeSymbol::updateGraphicsItems()
{
    IqAmeSymbolGraphicsItem *symbolItem = symbolGraphicsItem();
    Q_CHECK_PTR(symbolItem);
    symbolItem->setVisible(visible());
    symbolItem->updateCache();
}

IqAmeSymbolGraphicsItem *IqAmeSymbol::symbolGraphicsItem()
{
    if (!m_graphicsSymbolItem) {
        m_graphicsSymbolItem = new IqAmeSymbolGraphicsItem();
        m_graphicsSymbolItem->setSymbol(this);
        m_graphicsSymbolItem->setNamedShapeObject(this);
    }

    return m_graphicsSymbolItem;
}

bool IqAmeSymbol::loadFromString(const QString &string)
{
    QRegExp textRx("^\\s*(SYMP|S)\\s*:\\s*(\\*([^\\*]*)\\*){0,1}");
    textRx.setCaseSensitivity(Qt::CaseInsensitive);
    if (textRx.indexIn(string) == -1)
        return false;

    setName(textRx.cap(3));

    //Получим оставшуюся строку
    QString clearString = string.mid(textRx.matchedLength());

    //Выделим комментарий
    QRegExp commentRx("\\*([^\\*]*)\\*\\W*$");
    if (commentRx.indexIn(clearString) != -1)
        setComment(commentRx.cap(1));

    //Удалим все комментарии из строки
    QRegExp extraCommentsRx("\\*[^\\*]*\\*");
    clearString.remove(extraCommentsRx);

    //Выделим тип символа
    QRegExp symbolType("^\"(\\d+)\"(.*)");
    if (symbolType.indexIn(clearString.trimmed()) == -1)
        return false;
    switch (symbolType.cap(1).toInt()) {
    case 1:
        setType(PointRequedReport);
        break;
    case 2:
        setType(PointRequestReport);
        break;
    case 3:
        setType(Ndb);
        break;
    case 4:
        setType(ArtificalObstaclesWithouLight);
        break;
    case 6:
        setType(VorDme);
        break;
    case 7:
        setType(CivilAirport);
        break;
    case 8:
        setType(MixedAirport);
        break;
    case 9:
        setType(MilitaryAirport);
        break;
    default:
        qWarning() << tr("Symbol type \"%0\" not know. Symbol element skipped...")
                      .arg(symbolType.cap(1));
        return false;
    }
    clearString = symbolType.cap(2).trimmed();

    QString symbolString = clearString.trimmed();

    //Выделим атрибуты
    QRegExp attributeRx("(<\\s*[^>]*\\s*>)(.*)");
    attributeRx.setCaseSensitivity(Qt::CaseInsensitive);

    if (attributeRx.indexIn(clearString) != -1) {
        //Нашли атрибуты, создадим их
        if (!attributes()) {
            setAttributes(new IqAmeShapesAttributes(this));
        }
        attributes()->loadFromString(attributeRx.cap(1));
        symbolString = attributeRx.cap(2).trimmed();
    }

    QString pName = symbolString;

    if (!pName.isEmpty()) {
        IqAmeGeoPoint *p = IqAmeApplication::aeroMapModel()->pointsModel()->point(pName.trimmed(), Qt::CaseInsensitive);
        if (!p) {
            //Если не нашли точку, то попробуем ее создать
            IqAmeGeoPoint newPoint;
            if (newPoint.fromCoordinate(pName)) {
                int newPointRow = IqAmeApplication::aeroMapModel()->pointsModel()->rowCount();
                IqAmeApplication::aeroMapModel()->pointsModel()->insertRow(newPointRow);
                p = IqAmeApplication::aeroMapModel()->pointsModel()->at(newPointRow);
                p->setName(newPoint.name());
                p->setLatitude(newPoint.latitude());
                p->setLongitude(newPoint.longitude());
            } else {
                qWarning() << tr("Point \"%0\" not found and can not create. Symbol element skipped...").arg(pName);
                return false;
            }
        }

        setPoint(p);
        return true;
    }

    return false;
}

IqAmeSymbol::Type IqAmeSymbol::type() const
{
    return m_type;
}

void IqAmeSymbol::setType(const Type &type)
{
    m_type = type;
}

IqAmeGeoPoint *IqAmeSymbol::point() const
{
    return m_point;
}

void IqAmeSymbol::setPoint(IqAmeGeoPoint *geoPoint)
{
    if (m_point != geoPoint) {
        m_point = geoPoint;
        emit pointChanged();
    }
}
