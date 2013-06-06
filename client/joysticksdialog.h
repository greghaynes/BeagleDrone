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
    
    private Q_SLOTS:
        void joysticksSeclectionChanged();
        void editJoystick();

    private:
        void setupActions();

        Ui::JoysticksDialog *ui;

};

#endif

