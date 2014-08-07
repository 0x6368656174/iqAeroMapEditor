#include "iqametext.h"
#include "iqameshapesattributes.h"
#include "iqameapplication.h"
#include <QRegExp>
#include <QDebug>

IqAmeText::IqAmeText(QObject *parent) :
    IqAmeShapeObject(parent),
    _point(NULL)
{
}

void IqAmeText::setText(const QString &text)
{
    if (_text != text)
    {
        _text = text;

        emit textChanged();
    }
}

void IqAmeText::setPoint(IqAmeGeoPoint *geoPoint)
{
    if (_point != geoPoint)
    {
        _point = geoPoint;

        updateBoundingBox();
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

    if (attributeRx.indexIn(string) != -1)
    {
        //Нашли атрибуты, создадим их
        if (!attributes())
        {
            setAttributes(new IqAmeShapesAttributes(this));
        }
        attributes()->loadFromString(attributeRx.cap(1));
    }

    QString textString = attributeRx.cap(2);
    textString = textString.trimmed();

    QRegExp stringRx("([^\\/]*)\\s*\\/([^\\/]*)\\/");

    if (stringRx.indexIn(textString) != -1)
    {
        QString pName = stringRx.cap(1);

        IqAmeGeoPoint *p = IqAmeApplication::aeroMapModel()->pointsModel()->point(pName.trimmed(), Qt::CaseInsensitive);
        if (!p)
        {
            //Если не нашли точку, то попробуем ее создать
            IqAmeGeoPoint newPoint;
            if (newPoint.fromCoordinate(pName))
            {
                int newPointRow = IqAmeApplication::aeroMapModel()->pointsModel()->rowCount();
                IqAmeApplication::aeroMapModel()->pointsModel()->insertRow(newPointRow);
                p = IqAmeApplication::aeroMapModel()->pointsModel()->at(newPointRow);
                p->setName(newPoint.name());
                p->setLatitude(newPoint.latitude());
                p->setLongitude(newPoint.longitude());
            }
            else
            {
                qWarning() << tr("Point \"%0\" not found and can not create. Text element skipped...").arg(pName);
                return false;
            }
        }

        setPoint(p);
        setText(stringRx.cap(2));
    }

    updateBoundingBox();
    return true;
}

void IqAmeText::updateBoundingBox()
{
    if (point())
    {
        QRectF pointBox (point()->toGlPoint(), QSizeF(1, 1));

        setBoundingBox(pointBox);
    }
}

void IqAmeText::paindGl(const QRectF &area, IqLayerView *layerView)
{
    Q_UNUSED(area);
    QFont font;
    font.setPointSize(6);
    switch (outputAttributes()->textSize())
    {
    case IqAmeShapesAttributes::R1:
        break;
    case IqAmeShapesAttributes::R2:
        font.setPointSize(font.pointSize() * 1.5);
        break;
    case IqAmeShapesAttributes::R3:
        font.setPointSize(font.pointSize() * 2);
        break;
    case IqAmeShapesAttributes::R4:
        font.setPointSize(font.pointSize() * 2.5);
        break;
    }

    layerView->qglColor(outputAttributes()->toRGBColor());

    if (point())
    {
        QPoint screenPoint = layerView->mapFromGeo(point()->toGlPoint());
        layerView->renderText(screenPoint.x(), screenPoint.y(), text(), font);
    }
}
