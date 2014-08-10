#include "iqamemainwindow.h"
#include <QApplication>

#include "iqamelayer.h"
#include "iqamelogdialog.h"

#if QT_VERSION >= 0x050000
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
#else
void myMessageOutput(QtMsgType type, const char *msg)
#endif
{
    switch (type) {
    case QtDebugMsg:
        IqAmeLogDialog::addToDebug(msg);
        break;
    case QtWarningMsg:
        IqAmeLogDialog::addToWarning(msg);
        break;
    case QtCriticalMsg:
        IqAmeLogDialog::addToCritical(msg);
        break;
    case QtFatalMsg:
        IqAmeLogDialog::addToFatal(msg);
        abort();
    }

}

int main(int argc, char *argv[])
{
#if QT_VERSION >= 0x050000
    qInstallMessageHandler(myMessageOutput);
#else
    qInstallMsgHandler(myMessageOutput);
#endif

    QApplication a(argc, argv);

    IqAmeMainWindow w;
    w.show();

    return a.exec();
}
