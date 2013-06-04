#include "joysticksdialog.h"

#include "ui_joysticksdialog.h"

JoysticksDialog::JoysticksDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoysticksDialog)
{
    ui->setupUi(this);
}

JoysticksDialog::~JoysticksDialog()
{
    delete ui;
}
