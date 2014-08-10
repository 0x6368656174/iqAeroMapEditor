#ifndef IQAMELOGDIALOG_H
#define IQAMELOGDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class IqAmeLogDialog;
}

class IqAmeLogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IqAmeLogDialog(QWidget *parent = 0);
    ~IqAmeLogDialog();

    static void addToDebug(const QString &text);
    static void addToWarning(const QString &text);
    static void addToCritical(const QString &text);
    static void addToFatal(const QString &text);

protected:
    static void addToAllLogs(const QString &text);
    void closeEvent(QCloseEvent *event);

public slots:
    void clear();

    Q_INVOKABLE void add(const QString &text);

private slots:
    void tryClose();

private:
    Ui::IqAmeLogDialog *ui;

    static QList<IqAmeLogDialog *> _dialogs;
};

#endif // IQAMELOGDIALOG_H
