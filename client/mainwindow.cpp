#include "mainwindow.h"
#include "joysticksdialog.h"

#include "ui_mainwindow.h"

#include <QAction>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureJoysticksTriggered()
{
    JoysticksDialog *j = new JoysticksDialog(this);
    if(j->exec()) {

    }
}

void MainWindow::setupActions()
{
    connect(ui->actionSelectJoystick, &QAction::triggered,
            this, &MainWindow::configureJoysticksTriggered);
}

