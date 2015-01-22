#include "iqamemainwindow.h"
#include <QApplication>

#include "iqamelayer.h"
#include "iqamelogdialog.h"

#if QT_VERSION >= 0x050000
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString msgToWrite (msg);
//    msgToWrite.append(QString("(file: %0, funcion: %1, line: %2)")
//               .arg(context.file)
//               .arg(context.function)
//               .arg(context.line));
#else
void myMessageOutput(QtMsgType type, const char *msg)
{
    QString msgToWrite (msg);
#endif
    switch (type) {
    case QtDebugMsg:
        IqAmeLogDialog::addToDebug(msgToWrite);
        break;
    case QtWarningMsg:
        IqAmeLogDialog::addToWarning(msgToWrite);
        break;
    case QtCriticalMsg:
        IqAmeLogDialog::addToCritical(msgToWrite);
        break;
    case QtFatalMsg:
        IqAmeLogDialog::addToFatal(msgToWrite);
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
