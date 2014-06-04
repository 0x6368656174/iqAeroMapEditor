#include "iqlayerview.h"
#include <QDebug>
#include "iqamegeohelper.h"

using namespace GeographicLib;

IqLayerView::IqLayerView(QWidget *parent) :
    QGLWidget(parent)
{
}

//void IqLayerView::initializeGL()
//{
//    qglClearColor(Qt::black); // Черный цвет фона
//}

void IqLayerView::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void IqLayerView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу

    glLoadIdentity(); // загружаем матрицу

    glOrtho(-width()*1000,width()*1000,-height()*1000,height()*1000,0,1); // подготавливаем плоскости для матрицы

    IqAmeGeoHelper gh;
    gh.setLocalCartesianOrigin(48 + 31/60.0 + 41/3600.0, 135 + 11/60.0 + 70/3600.0); //Хабаровск

    qreal lat, lon;
    gh.coordinateFromString("N48584200 E135510600", lat, lon);

    qreal x, y, z;
    gh.toLocalCartesian(lat, lon, 0, x, y, z);

    qDebug() << x << y << z;

    glBegin(GL_LINES); //Будем рисовать линию
    glVertex3f(0.0,0.0,0.0); //Начальная точка
    glVertex3f(x, y, 0); //Конечная точка
    glEnd();
}
