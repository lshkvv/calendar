#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Личный Календарь");

    MainWindow w;
    w.setWindowTitle("Личный Календарь");
    w.resize(960, 620);
    w.show();

    return app.exec();
}
