#ifndef IQAMEMAINWINDOW_H
#define IQAMEMAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

namespace Ui {
class IQAMEMainWindow;
}

class IqAmeLayer;

class IQAMEMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IQAMEMainWindow(QWidget *parent = 0);
    ~IQAMEMainWindow();

private slots:
    void showPoints();
    void showLayer(IqAmeLayer *layer);

private:
    Ui::IQAMEMainWindow *ui;
};

#endif // IQAMEMAINWINDOW_H
