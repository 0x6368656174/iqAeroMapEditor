#ifndef IQAMEATDMENUEDITDIALOG_H
#define IQAMEATDMENUEDITDIALOG_H

#include <QDialog>

namespace Ui {
class IqAmeAtdMenuEditDialog;
}

class IqAmeAtdMenuEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IqAmeAtdMenuEditDialog(QWidget *parent = 0);
    ~IqAmeAtdMenuEditDialog();

private:
    Ui::IqAmeAtdMenuEditDialog *ui;
};

#endif // IQAMEATDMENUEDITDIALOG_H
