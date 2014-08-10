#ifndef IQAMEMAINWINDOW_H
#define IQAMEMAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

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

private:
    Ui::IQAMEMainWindow *ui;
};

#endif // IQAMEMAINWINDOW_H
