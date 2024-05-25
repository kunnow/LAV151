#include "mainwindow.h"
#include "database.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!connectToDB())
    {
        return -1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
