#include "motorswidget.h"

#include "ui_motorswidget.h"

MotorsWidget::MotorsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotorsWidget)
{
    ui->setupUi(this);
}

