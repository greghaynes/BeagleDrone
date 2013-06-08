#ifndef MOTORS_WIDGET_H
#define MOTORS_WIDGET_H

#include <QWidget>

namespace Ui
{
    class MotorsWidget;
}

class MotorsWidget : public QWidget
{
    Q_OBJECT

    public:
        MotorsWidget(QWidget *parent = 0);

    private:
        Ui::MotorsWidget *ui;

};

#endif

