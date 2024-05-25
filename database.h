#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>

bool connectToDB();

extern QSqlDatabase db;
#endif // DATABASE_H
