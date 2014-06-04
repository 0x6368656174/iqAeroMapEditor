#include "iqameatdmenueditdialog.h"
#include "ui_iqameatdmenueditdialog.h"

IqAmeAtdMenuEditDialog::IqAmeAtdMenuEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IqAmeAtdMenuEditDialog)
{
    ui->setupUi(this);
}

IqAmeAtdMenuEditDialog::~IqAmeAtdMenuEditDialog()
{
    delete ui;
}
