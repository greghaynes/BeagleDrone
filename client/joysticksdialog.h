#ifndef JOYSTICKS_DIALOG_H
#define JOYSTICKS_DIALOG_H

#include <QDialog>

namespace Ui
{
    class JoysticksDialog;
}

class JoysticksDialog : public QDialog
{
    Q_OBJECT

    public:
        JoysticksDialog(QWidget *parent = 0);
        ~JoysticksDialog();

    private:
        Ui::JoysticksDialog *ui;

};

#endif
