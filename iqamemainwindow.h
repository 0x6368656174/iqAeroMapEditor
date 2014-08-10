#ifndef IQAMEMAINWINDOW_H
#define IQAMEMAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QTime>
#include "iqamelogdialog.h"


namespace Ui {
class IQAMEMainWindow;
}

class IqAmeLayer;

class IqAmeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IqAmeMainWindow(QWidget *parent = 0);
    ~IqAmeMainWindow();

private slots:
    void showPoints();
    void showLayer(IqAmeLayer *layer);
    void openFolder();
    void showLogs();
    void onLoadFinished();

private:
    Ui::IQAMEMainWindow *ui;
    IqAmeLogDialog *_logDialog;
    QTime _loadTimer;
};

#endif // IQAMEMAINWINDOW_H
