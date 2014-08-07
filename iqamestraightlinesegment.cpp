#include "iqamestraightlinesegment.h"
#include <QtOpenGL>
#include <QDebug>
#include <unistd.h>

IqAmeStraightLineSegment::IqAmeStraightLineSegment(QObject *parent) :
    IqAmeLineSegment(parent)
{
}

void IqAmeStraightLineSegment::paintGl(const QRectF &area, IqLayerView *layerView)
{
    Q_UNUSED(area);
    Q_UNUSED(layerView);
//    qDebug() << startPoint()->toGlPoint().x() << startPoint()->toGlPoint().y() << endPoint()->toGlPoint().x() << endPoint()->toGlPoint().y();
    glBegin(GL_LINES); //Будем рисовать линию
    glVertex3f(startPoint()->toGlPoint().x(),startPoint()->toGlPoint().y(), 0.0); //Начальная точка
    glVertex3f(endPoint()->toGlPoint().x(), endPoint()->toGlPoint().y(), 0); //Конечная точка
    glEnd();
}
