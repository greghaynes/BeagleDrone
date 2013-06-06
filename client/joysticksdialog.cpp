#include "joysticksdialog.h"

#include "ui_joysticksdialog.h"
#include "ui_joystickeditdialog.h"

#include <QListWidgetItem>

class JoystickEditDialog : public QDialog
{

    public:
        JoystickEditDialog(QWidget *parent = 0);
        ~JoystickEditDialog();

        void setName(const QString &name);
        void setPath(const QString &path);

    private:
        Ui::JoystickEditDialog *ui;

};

class JoystickListItem : public QListWidgetItem
{
    public:
        JoystickListItem(const QString &text,
                         const QString &path,
                         QListWidget *parent = 0);

        QString path() const;

    private:
        QString m_path;
};

JoystickEditDialog::JoystickEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoystickEditDialog)
{
    ui->setupUi(this);
}

JoystickEditDialog::~JoystickEditDialog()
{
    delete ui;
}

void JoystickEditDialog::setName(const QString &name)
{
    ui->nameEdit->setText(name);
}

void JoystickEditDialog::setPath(const QString &path)
{
    //TODO
}

JoystickListItem::JoystickListItem(const QString &text,
                                   const QString &path,
                                   QListWidget *parent) :
    QListWidgetItem(text, parent),
    m_path(path)
{
}

QString JoystickListItem::path() const
{
    return m_path;
}

JoysticksDialog::JoysticksDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoysticksDialog)
{
    ui->setupUi(this);

    ui->editPushButton->setEnabled(false);

    JoystickListItem *new_joystick;
    new_joystick = new JoystickListItem("New Joystick",
                                        QString(),
                                        ui->joysticksListWidget);

    setupActions();
}

JoysticksDialog::~JoysticksDialog()
{
    delete ui;
}

void JoysticksDialog::joysticksSeclectionChanged()
{
    bool item_selected = ui->joysticksListWidget->selectedItems().size() != 0;
    ui->editPushButton->setEnabled(item_selected);
}

void JoysticksDialog::editJoystick()
{
    JoystickEditDialog *d = new JoystickEditDialog();

    QList<QListWidgetItem*> selected;
    selected = ui->joysticksListWidget->selectedItems();
    d->setName(selected[0]->text());
    d->exec();

    delete d;
}

void JoysticksDialog::setupActions()
{
    connect(ui->joysticksListWidget, SIGNAL(itemSelectionChanged()),
            this, SLOT(joysticksSeclectionChanged()));

    connect(ui->editPushButton, SIGNAL(clicked(bool)),
            this, SLOT(editJoystick()));
}

