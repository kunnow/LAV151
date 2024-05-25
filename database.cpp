#include "database.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QtSql>

bool connectToDB()
{
    QCoreApplication::addLibraryPath("C:\Qt\6.5.0\mingw_64\plugins");

    qDebug() << "Available SQL drivers:" << QSqlDatabase::drivers();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    if (!db.isValid()) {
        qDebug() << "Failed to load database driver. Available drivers:" << QSqlDatabase::drivers();
        return false;
    }

    db.setHostName("localhost");
    db.setDatabaseName("lav");
    db.setUserName("root");
    db.setPassword("shir1234");

    if (!db.open())
    {
        qDebug() << "Error: Database not connected" << db.lastError().text();
        return false;
    }
    else
    {
        qDebug() << "Database connected";
        return true;
    }
}
