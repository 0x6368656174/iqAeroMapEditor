#include "iqamemainwindow.h"
#include <QApplication>

#include "iqamelayer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IqAmeMainWindow w;
    w.show();

    return a.exec();
}
