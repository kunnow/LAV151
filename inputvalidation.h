#ifndef INPUTVALIDATION_H
#define INPUTVALIDATION_H
#include <QSqlDatabase>

bool isTutorIDValid(const QString &tutorID);
bool isDateValid(const QString &dateStr);
bool isTimeValid(const QString &timeStr);
bool isContactValid(const QString &contact);

#endif // INPUTVALIDATION_H
