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
    explicit IqAmeMainWindow(QWidget *parent = Q_NULLPTR);
    ~IqAmeMainWindow();

private slots:
    void showPoints();
    void showLayer(IqAmeLayer *layer);
    void openFolder();
    void showLogs();
    void onLoadFinished();
    void updateRenderhints();

private:
    Ui::IQAMEMainWindow *ui;
    IqAmeLogDialog *m_logDialog;
    QTime m_loadTimer;
};

#endif // IQAMEMAINWINDOW_H
