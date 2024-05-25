#include <QSqlDatabase>
#include <QStringList>
bool isTutorIDValid(const QString &tutorID) {
    // Check if the string length is 9 characters
    if (tutorID.length() != 9)
        return false;

    // Check if the 5th character is '-'
    if (tutorID.at(4) != '-')
        return false;

    // Check if the first 4 characters and last 4 characters are integers
    for (int i = 0; i < 4; ++i) {
        if (!tutorID.at(i).isDigit() || !tutorID.at(i + 5).isDigit())
            return false;
    }

    // If all checks pass, return true
    return true;
}
bool isDateValid(const QString &dateStr) {
    QStringList dateParts = dateStr.split("-");
    if (dateParts.size() != 3) {
        return false;
    } else {
        int year = dateParts[0].toInt();
        int month = dateParts[1].toInt();
        int day = dateParts[2].toInt();
        return (year >= 1000 && year <= 9999 && month >= 1 && month <= 12 && day >= 1 && day <= 31);
    }
}

bool isTimeValid(const QString &timeStr) {
    QStringList timeParts = timeStr.split(":");
    if (timeParts.size() != 2) {
        return false;
    } else {
        int hour = timeParts[0].toInt();
        int minute = timeParts[1].toInt();
        return (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59);
    }
}
bool isContactValid(const QString &contact)
{
    if (contact.length() != 11)
        return false;

    for (const QChar &c : contact) {
        if (!c.isDigit())
            return false;
    }

    return true;
}


