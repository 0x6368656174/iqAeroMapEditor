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
    explicit IqAmeAtdMenuEditDialog(QWidget *parent = Q_NULLPTR);
    ~IqAmeAtdMenuEditDialog();

private:
    Ui::IqAmeAtdMenuEditDialog *ui;
};

#endif // IQAMEATDMENUEDITDIALOG_H
