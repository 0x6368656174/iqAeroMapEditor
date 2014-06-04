#ifndef IQLAYERVIEW_H
#define IQLAYERVIEW_H

#include <QGLWidget>

class IqLayerView : public QGLWidget
{
    Q_OBJECT
public:
    explicit IqLayerView(QWidget *parent = 0);

//    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
};

#endif // IQLAYERVIEW_H
