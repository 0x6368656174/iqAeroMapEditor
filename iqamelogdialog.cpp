#include "iqamelogdialog.h"
#include <QDateTime>
#include "ui_iqamelogdialog.h"

QList<IqAmeLogDialog *> IqAmeLogDialog::_dialogs = QList<IqAmeLogDialog *>();

IqAmeLogDialog::IqAmeLogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IqAmeLogDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(tryClose()));

    _dialogs << this;
}

IqAmeLogDialog::~IqAmeLogDialog()
{
    _dialogs.removeOne(this);
    delete ui;
}

void IqAmeLogDialog::clear()
{
    ui->textBrowser->clear();
}

void IqAmeLogDialog::add(const QString &text)
{
    QLocale locale  (QLocale::English);
    QString date = locale.toString(QDateTime::currentDateTime(), "MMM dd hh:mm:ss");
    QString textToAdd = QString("%0: %1")
            .arg(date)
            .arg(text);

    ui->textBrowser->append(textToAdd);
}

void IqAmeLogDialog::addToDebug(const QString &text)
{
    QString textToAdd = QString("DEBUG: %0")
            .arg(text.trimmed());
    addToAllLogs(textToAdd);
}

void IqAmeLogDialog::addToWarning(const QString &text)
{
    QString textToAdd = QString("WARNING: %0")
            .arg(text.trimmed());
    addToAllLogs(textToAdd);
}

void IqAmeLogDialog::addToCritical(const QString &text)
{
    QString textToAdd = QString("CRITICAL: %0")
            .arg(text.trimmed());
    addToAllLogs(textToAdd);
}

void IqAmeLogDialog::addToFatal(const QString &text)
{
    QString textToAdd = QString("FATAL: %0")
            .arg(text.trimmed());
    addToAllLogs(textToAdd);
}

void IqAmeLogDialog::addToAllLogs(const QString &text)
{
    foreach (IqAmeLogDialog *dialog, _dialogs)
    {
        QMetaObject::invokeMethod(dialog,
                                  "add",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, text));
    }
}

void IqAmeLogDialog::tryClose()
{
    if (!QApplication::overrideCursor())
        hide();
}

void IqAmeLogDialog::closeEvent(QCloseEvent *event)
{
    if (!QApplication::overrideCursor())
        QDialog::closeEvent(event);
    event->ignore();
}
