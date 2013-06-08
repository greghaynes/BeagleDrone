#include "mainwindow.h"
#include "gimbalwidget.h"

#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow mw;
    mw.show();

    GimbalWidget g;
    g.show();

    return app.exec();
}
