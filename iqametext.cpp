#include "iqametext.h"
#include "iqameshapesattributes.h"
#include "iqameapplication.h"
#include <QRegExp>
#include <QDebug>
#include "iqameapplication.h"

IqAmeText::IqAmeText(QObject *parent) :
    IqAmeNamedShapeObject(parent),
    m_point(Q_NULLPTR),
    m_graphicsTextItem(Q_NULLPTR)
{
}

IqAmeText::~IqAmeText()
{
    if (m_graphicsTextItem && !m_graphicsTextItem->parentItem())
        delete m_graphicsTextItem;
}

QList<QGraphicsItem *> IqAmeText::graphicsItems()
{
    QList<QGraphicsItem *> result;
    result << textGraphicsItem();
    return result;
}

IqAmeTextGraphicsItem *IqAmeText::textGraphicsItem()
{
    if (!m_graphicsTextItem) {
        m_graphicsTextItem = new IqAmeTextGraphicsItem();
        m_graphicsTextItem->setText(this);
        m_graphicsTextItem->setNamedShapeObject(this);
    }

    return m_graphicsTextItem;
}

void IqAmeText::updateGraphicsItems()
{
    IqAmeTextGraphicsItem *textItem = textGraphicsItem();
    Q_CHECK_PTR(textItem);
    textItem->setVisible(visible());
    textItem->updateCache();
}

void IqAmeText::setText(const QString &text)
{
    if (m_text != text) {
        m_text = text;
        emit textChanged();
    }
}

IqAmeGeoPoint *IqAmeText::point() const
{
    return m_point;
}

void IqAmeText::setPoint(IqAmeGeoPoint *geoPoint)
{
    if (m_point != geoPoint) {
        m_point = geoPoint;
        emit pointChanged();
    }
}

bool IqAmeText::loadFromString(const QString &string)
{
    //    qDebug() << "Load Text :" << string;
    QRegExp textRx("^\\s*(TEXT|T)\\s*:\\s*(\\*([^\\*]*)\\*){0,1}");
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

    //Выделим атрибуты
    QRegExp attributeRx("(<\\s*[^>]*\\s*>)(.*)");
    attributeRx.setCaseSensitivity(Qt::CaseInsensitive);

    if (attributeRx.indexIn(string) != -1) {
        //Нашли атрибуты, создадим их
        if (!attributes()) {
            setAttributes(new IqAmeShapesAttributes(this));
        }
        attributes()->loadFromString(attributeRx.cap(1));
    }

    QString textString = attributeRx.cap(2);
    textString = textString.trimmed();

    QRegExp stringRx("([^\\/]*)\\s*\\/([^\\/]*)\\/");

    if (stringRx.indexIn(textString) != -1) {
        QString pName = stringRx.cap(1);

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
                qWarning() << tr("Point \"%0\" not found and can not create. Text element skipped...").arg(pName);
                return false;
            }
        }

        setPoint(p);
        setText(stringRx.cap(2));

        return true;
    }

    return false;
}

QString IqAmeText::text() const
{
    return m_text;
}
