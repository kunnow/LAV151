#include "mainwindow.h"
#include "edit_submit.h"
#include "ui_mainwindow.h"
#include "inputvalidation.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MSU-IIT LAV");
    displayschedule();
    displayAppointment();
    displaytutor();
    displayRecords();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tutee_appointment_clicked()
{
    ui->stacked_Widget->setCurrentIndex(0);
}

void MainWindow::on_tutor_schedule_clicked()
{
    ui->stacked_Widget->setCurrentIndex(2);
}

void MainWindow::on_close_clicked()
{
    close();
}

QString generateAppointmentID()
{
    QSqlQuery query;
    query.exec("SELECT MAX(AppointmentID) FROM Books");

    QString newID;
    if (query.next())
    {
        QString lastID = query.value(0).toString();
        if (!lastID.isNull())
        {
            int lastNum = lastID.mid(4).toInt();
            int nextNum = lastNum + 1;
            newID = QString("LAV-%1").arg(nextNum, 3, 10, QChar('0'));
        }
        else
        {
            // If no existing appointments, start with LAV-001
            newID = "LAV-001";
        }
    }
    return newID;
}


QString generateScheduleID()
{
    QSqlQuery query;
    query.exec("SELECT MAX(ScheduleID) FROM Schedule");

    QString newID;
    if (query.next())
    {
        QString lastID = query.value(0).toString();
        if (!lastID.isNull())
        {
            int lastNum = lastID.mid(4).toInt();
            int nextNum = lastNum + 1;
            newID = QString("SHD-%1").arg(nextNum, 3, 10, QChar('0'));
        }
        else
        {
            // If no existing schedules, start with SHD-001
            newID = "SHD-001";
        }
    }
    return newID;
}


void MainWindow::on_add1_clicked()
{
    QString tuteeName = ui->fullname1->text().toUpper();
    QString tuteeID = ui->idnumber1->text();
    int yearLevelValue = ui->yearlevel1->value();
    QString courseCode = ui->coursecode1->text().toUpper();
    QString scheduleID = ui->scheduleid1->text();
    QString contactNumber = ui->contact_2->text();
    QString date, timeStart, timeEnd;

    // get schedule details
    QSqlQuery timeQuery;
    timeQuery.prepare("SELECT TimeStart, TimeEnd, ScheduleDate FROM schedule WHERE ScheduleID = :scheduleID");
    timeQuery.bindValue(":scheduleID", scheduleID);
    if (!timeQuery.exec())
    {
        qDebug() << "Error: Couldn't retrieve timeStart and timeEnd from the table" << timeQuery.lastError().text();
        return;
    }
    else
    {
        if (timeQuery.next())
        {
            timeStart = timeQuery.value("TimeStart").toString();
            timeEnd = timeQuery.value("TimeEnd").toString();
            date = timeQuery.value("ScheduleDate").toString();
        }
        else
        {
            qDebug() << "No schedule found for the given ScheduleID:" << scheduleID;
            return;
        }
    }

    // check for overlapping schedules
    QSqlQuery overlapQuery;
    overlapQuery.prepare("SELECT COUNT(*) FROM Books WHERE TuteeID = :tuteeID AND bookDate = :date AND "
                         "(TimeStart < :timeEnd AND TimeEnd > :timeStart)");
    overlapQuery.bindValue(":tuteeID", tuteeID);
    overlapQuery.bindValue(":date", date);
    overlapQuery.bindValue(":timeStart", timeStart);
    overlapQuery.bindValue(":timeEnd", timeEnd);

    if (!overlapQuery.exec())
    {
        qDebug() << "Error checking for overlapping schedules:" << overlapQuery.lastError().text();
        return;
    }
    else
    {
        overlapQuery.next();
        int count = overlapQuery.value(0).toInt();
        if (count > 0)
        {
            QMessageBox::warning(this, "Booking Error", "The schedule overlaps with an existing booking.");
            return;
        }
    }

    // insert tutee info if it's the first time a tutee is booking an appointment
    QSqlQuery checkTuteeQuery;
    checkTuteeQuery.prepare("SELECT COUNT(*) FROM tutee WHERE TuteeID = :TuteeID");
    checkTuteeQuery.bindValue(":TuteeID", tuteeID);

    if (!checkTuteeQuery.exec())
    {
        qDebug() << "Error checking tutee existence:" << checkTuteeQuery.lastError().text();
        return;
    }

    checkTuteeQuery.next();
    int tuteeCount = checkTuteeQuery.value(0).toInt();

    if (tuteeCount == 0)
    {
        QSqlQuery tuteeQuery;
        tuteeQuery.prepare("INSERT INTO tutee(TuteeID, Name, Course, YearLevel, tuteeContactNumber) VALUES (:TuteeID, :Name, :Course, :YearLevel, :contactNumber)");
        tuteeQuery.bindValue(":TuteeID", tuteeID);
        tuteeQuery.bindValue(":Name", tuteeName);
        tuteeQuery.bindValue(":Course", courseCode);
        tuteeQuery.bindValue(":YearLevel", yearLevelValue);
        tuteeQuery.bindValue(":contactNumber", contactNumber);

        if (!tuteeQuery.exec())
        {
            qDebug() << "Error inserting into tutee table:" << tuteeQuery.lastError().text();
            return;
        }
    }

    // get tutor id from schedule id
    QSqlQuery tutorQuery;
    tutorQuery.prepare("SELECT TutorID FROM schedule WHERE ScheduleID = :scheduleID");
    tutorQuery.bindValue(":scheduleID", scheduleID);
    if (!tutorQuery.exec())
    {
        qDebug() << "Error retrieving TutorID:" << tutorQuery.lastError().text();
        return;
    }

    QString tutorID;
    if (tutorQuery.next())
    {
        tutorID = tutorQuery.value(0).toString();
    }
    else
    {
        qDebug() << "No tutor found for the given ScheduleID:" << scheduleID;
        return;
    }

    // insert into books table
    QString appointmentID = generateAppointmentID();
    QSqlQuery query;
    query.prepare("INSERT INTO Books(AppointmentID, bookDate, timeStart, timeEnd, TutorID, TuteeID) "
                  "VALUES (:AppointmentID, :bookDate, :timeStart, :timeEnd, :TutorID, :TuteeID)");
    query.bindValue(":AppointmentID", appointmentID);
    query.bindValue(":bookDate", date);
    query.bindValue(":timeStart", timeStart);
    query.bindValue(":timeEnd", timeEnd);
    query.bindValue(":TutorID", tutorID);
    query.bindValue(":TuteeID", tuteeID);

    if (!query.exec())
    {
        qDebug() << "Error inserting into Books:" << query.lastError().text();
        return;
    }
    else
    {
        qDebug() << "Appointment inserted successfully!";

        // Delete the schedule from schedule table
        QSqlQuery deleteScheduleQuery;
        deleteScheduleQuery.prepare("DELETE FROM schedule WHERE ScheduleID = :scheduleID");
        deleteScheduleQuery.bindValue(":scheduleID", scheduleID);

        if (!deleteScheduleQuery.exec())
        {
            qDebug() << "Error deleting schedule:" << deleteScheduleQuery.lastError().text();
            return;
        }
    }

    ui->fullname1->clear();
    ui->idnumber1->clear();
    ui->coursecode1->clear();
    ui->scheduleid1->clear();
    ui->contact_2->clear();

    // Update UI
    displayschedule();
    displayAppointment();
}

void MainWindow::on_add2_clicked()
{
    QString tutorID = ui->tutorID->text();
    QString date = ui->date2->text();
    QString timeStart = ui->timestart2->text();
    QString timeEnd = ui->timeend2->text();

    if (!isDateValid(date)) {
        QMessageBox::critical(this, "Error", "Invalid Date format. Please enter a valid date in the format YYYY-MM-DD");
        return;
    }
    if (!isTimeValid(timeStart) || !isTimeValid(timeEnd)) {
        QMessageBox::critical(this, "Error", "Invalid Time format. Please enter a valid Time in the format HH:MM");
        return;
    }

    // Retrieve tutor's full name and subject based on tutorID
    QSqlQuery tutorQuery;
    tutorQuery.prepare("SELECT Name, Subject FROM tutor WHERE TutorID = :TutorID");
    tutorQuery.bindValue(":TutorID", tutorID);
    if (!tutorQuery.exec()) {
        qDebug() << "Error retrieving tutor info:" << tutorQuery.lastError();
        QMessageBox::critical(this, "Error", "Failed to retrieve tutor info");
        return;
    }

    if (!tutorQuery.next()) {
        qDebug() << "No tutor found for the given TutorID:" << tutorID;
        QMessageBox::critical(this, "Error", "No tutor found for the given TutorID");
        return;
    }

    QString tutorName = tutorQuery.value(0).toString();
    QString subject = tutorQuery.value(1).toString();

    // Check for overlapping schedules
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT ScheduleID FROM schedule WHERE TutorID = :TutorID AND ScheduleDate = :ScheduleDate AND "
                       "((TimeStart < :TimeEnd AND TimeEnd > :TimeStart))");
    checkQuery.bindValue(":TutorID", tutorID);
    checkQuery.bindValue(":ScheduleDate", date);
    checkQuery.bindValue(":TimeStart", timeStart);
    checkQuery.bindValue(":TimeEnd", timeEnd);

    if (!checkQuery.exec()) {
        qDebug() << "Error checking for overlapping schedules:" << checkQuery.lastError();
        QMessageBox::critical(this, "Error", "Failed to check for overlapping schedules");
        return;
    }

    if (checkQuery.next()) {
        qDebug() << "Overlapping schedule found for TutorID:" << tutorID;
        QMessageBox::critical(this, "Error", "The tutor already has a schedule that overlaps with the provided time.");
        return;
    }

    // Insert into schedule table
    QSqlQuery scheduleQuery;
    scheduleQuery.prepare("INSERT INTO schedule (ScheduleID, TimeStart, TimeEnd, ScheduleDate, TutorID) "
                          "VALUES (:ScheduleID, :TimeStart, :TimeEnd, :ScheduleDate, :TutorID)");
    scheduleQuery.bindValue(":ScheduleID", generateScheduleID());
    scheduleQuery.bindValue(":TimeStart", timeStart);
    scheduleQuery.bindValue(":TimeEnd", timeEnd);
    scheduleQuery.bindValue(":ScheduleDate", date);
    scheduleQuery.bindValue(":TutorID", tutorID);

    if (!scheduleQuery.exec()) {
        qDebug() << "Error inserting into schedule:" << scheduleQuery.lastError();
        QMessageBox::critical(this, "Error", "Failed to add schedule");
    } else {
        qDebug() << "Schedule inserted successfully!";
        QMessageBox::information(this, "Success", "Schedule Added successfully");
        // Clear the input fields
        ui->tutorID->clear();
        ui->date2->clear();
        ui->timestart2->clear();
        ui->timeend2->clear();
    }
    displayschedule();
}

void MainWindow::displayschedule() {
    QSqlQuery query;
    query.prepare("SELECT Schedule.ScheduleID, Schedule.TimeStart, Schedule.TimeEnd, Schedule.ScheduleDate, Schedule.TutorID, Tutor.Subject, Tutor.Name "
                  "FROM Schedule "
                  "INNER JOIN Tutor ON Schedule.TutorID = Tutor.TutorID");

    if (!query.exec()) {
        qDebug() << "Error executing display schedule:" << query.lastError().text();
        return;
    }

    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setColumnCount(7);
    ui->tableWidget_2->setHorizontalHeaderLabels({"Schedule I.D.", "Tutor I.D.", "Full Name", "Date", "Time Start", "Time End", "Subject"});
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QFont headerFont = ui->tableWidget_2->horizontalHeader()->font();
    headerFont.setBold(true);
    ui->tableWidget_2->horizontalHeader()->setFont(headerFont);

    QFont contentFont = ui->tableWidget_2->font();
    contentFont.setPointSize(contentFont.pointSize() - 2);

    int row = 0;
    while (query.next()) {
        QString ScheduleID = query.value("ScheduleID").toString();
        QString TimeStart = query.value("TimeStart").toString();
        QString TimeEnd = query.value("TimeEnd").toString();
        QString ScheduleDate = query.value("ScheduleDate").toString();
        QString TutorID = query.value("TutorID").toString();
        QString Subject = query.value("Subject").toString();
        QString TutorName = query.value("Name").toString();

        ui->tableWidget_2->insertRow(row);
        ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(ScheduleID));
        ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(TutorID));
        ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(TutorName));
        ui->tableWidget_2->setItem(row, 3, new QTableWidgetItem(ScheduleDate));
        ui->tableWidget_2->setItem(row, 4, new QTableWidgetItem(TimeStart));
        ui->tableWidget_2->setItem(row, 5, new QTableWidgetItem(TimeEnd));
        ui->tableWidget_2->setItem(row, 6, new QTableWidgetItem(Subject.toUpper()));

        for (int col = 0; col < ui->tableWidget_2->columnCount(); ++col) {
            QTableWidgetItem *item = ui->tableWidget_2->item(row, col);
            if (item) {
                // Set default size
                item->setSizeHint(QSize(100, 30));
                // Adjust size if content is larger
                QSize size = item->sizeHint();
                int requiredWidth = ui->tableWidget_2->fontMetrics().horizontalAdvance(item->text()) + 10; // 10 pixels padding
                if (requiredWidth > size.width()) {
                    size.setWidth(requiredWidth);
                    item->setSizeHint(size);
                }
            }
        }
        row++;
    }
    ui->tableWidget_2->resizeColumnsToContents();
}

void MainWindow::displayAppointment() {

    QSqlQuery queryAppointment;
    queryAppointment.prepare("SELECT * FROM Books");

    if (!queryAppointment.exec()) {
        qDebug() << "Error executing query:" << queryAppointment.lastError().text();
        return;
    }

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels({"Appointment I.D.", "Date", "Time Start", "Time End", "Tutor I.D.", "Tutee I.D."});
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QFont headerFont = ui->tableWidget->horizontalHeader()->font();
    headerFont.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(headerFont);

    QFont contentFont = ui->tableWidget->font();
    contentFont.setPointSize(contentFont.pointSize() - 2);

    int row = 0;
    while (queryAppointment.next()) {
        QString AppointmentID = queryAppointment.value("AppointmentID").toString();
        QString bookDate = queryAppointment.value("bookDate").toString();
        QString TimeStart = queryAppointment.value("TimeStart").toString();
        QString TimeEnd = queryAppointment.value("TimeEnd").toString();
        QString TutorID = queryAppointment.value("TutorID").toString();
        QString TuteeID = queryAppointment.value("TuteeID").toString();

        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(AppointmentID));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(bookDate));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(TimeStart));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(TimeEnd));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(TutorID));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(TuteeID));

        for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = ui->tableWidget->item(row, col);
            if (item) {
                item->setSizeHint(QSize(100, 30)); // Adjust the size as needed
            }
        }
        row++;
    }
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::displaytutor() {
    QSqlQuery queryTutor;
    queryTutor.prepare("SELECT * FROM tutor");

    if (!queryTutor.exec()) {
        qDebug() << "Error executing query:" << queryTutor.lastError().text();
        return;
    }

    ui->tableWidget_3->setRowCount(0);
    ui->tableWidget_3->setColumnCount(4);
    ui->tableWidget_3->setHorizontalHeaderLabels({"I.D. Number", "Full Name", "Subject", "Contact Number"}); // Separate strings for each label
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QFont headerFont = ui->tableWidget_4->horizontalHeader()->font();
    headerFont.setBold(true);
    ui->tableWidget_3->horizontalHeader()->setFont(headerFont);

    QFont contentFont = ui->tableWidget_3->font();
    contentFont.setPointSize(contentFont.pointSize() - 2);

    int row = 0;
    while (queryTutor.next()) {
        QString tutorID = queryTutor.value("TutorID").toString();
        QString tutorName = queryTutor.value("Name").toString();
        QString tutorSubject = queryTutor.value("Subject").toString();
        QString tutorContact = queryTutor.value("tutorContactNumber").toString();
        ui->tableWidget_3->insertRow(row);
        ui->tableWidget_3->setItem(row, 0, new QTableWidgetItem(tutorID));
        ui->tableWidget_3->setItem(row, 1, new QTableWidgetItem(tutorName));
        ui->tableWidget_3->setItem(row, 2, new QTableWidgetItem(tutorSubject));
        ui->tableWidget_3->setItem(row, 3, new QTableWidgetItem(tutorContact));

        for (int col = 0; col < ui->tableWidget_3->columnCount(); ++col) {
            QTableWidgetItem *item = ui->tableWidget_3->item(row, col);
            if (item) {
                // Set default size
                item->setSizeHint(QSize(100, 30));
                // Adjust size if content is larger
                QSize size = item->sizeHint();
                int requiredWidth = ui->tableWidget_3->fontMetrics().horizontalAdvance(item->text()) + 10; // 10 pixels padding
                if (requiredWidth > size.width()) {
                    size.setWidth(requiredWidth);
                    item->setSizeHint(size);
                }
            }
        }
        row++;
    }
    ui->tableWidget_3->resizeColumnsToContents();
}

void MainWindow::displayRecords()
{
    QSqlQuery queryRecords;
    queryRecords.prepare("SELECT * FROM records");

    if (!queryRecords.exec()) {
        qDebug() << "Error executing query:" << queryRecords.lastError().text();
        return;
    }

    ui->tableWidget_4->setRowCount(0);
    ui->tableWidget_4->setColumnCount(6);
    ui->tableWidget_4->setHorizontalHeaderLabels({"Appointment I.D.", "Date", "Time Start", "Time End", "Tutor I.D.", "Tutee I.D."});
    ui->tableWidget_4->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QFont headerFont = ui->tableWidget_4->horizontalHeader()->font();
    headerFont.setBold(true);
    ui->tableWidget_4->horizontalHeader()->setFont(headerFont);

    QFont contentFont = ui->tableWidget_4->font();
    contentFont.setPointSize(contentFont.pointSize() - 2);

    int row = 0;
    while (queryRecords.next()) {
        QString AppointmentID = queryRecords.value("AppointmentID").toString();
        QString bookDate = queryRecords.value("bookDate").toString();
        QString TimeStart = queryRecords.value("TimeStart").toString();
        QString TimeEnd = queryRecords.value("TimeEnd").toString();
        QString TutorID = queryRecords.value("TutorID").toString();
        QString TuteeID = queryRecords.value("TuteeID").toString();

        ui->tableWidget_4->insertRow(row);
        ui->tableWidget_4->setItem(row, 0, new QTableWidgetItem(AppointmentID));
        ui->tableWidget_4->setItem(row, 1, new QTableWidgetItem(bookDate));
        ui->tableWidget_4->setItem(row, 2, new QTableWidgetItem(TimeStart));
        ui->tableWidget_4->setItem(row, 3, new QTableWidgetItem(TimeEnd));
        ui->tableWidget_4->setItem(row, 4, new QTableWidgetItem(TutorID));
        ui->tableWidget_4->setItem(row, 5, new QTableWidgetItem(TuteeID));

        for (int col = 0; col < ui->tableWidget_4->columnCount(); ++col) {
            QTableWidgetItem *item = ui->tableWidget_4->item(row, col);
            if (item) {
                item->setSizeHint(QSize(100, 30)); // Adjust the size as needed
            }
        }
        row++;
    }
    ui->tableWidget_4->resizeColumnsToContents();
}

void MainWindow::on_History_clicked()
{
    ui->stacked_Widget->setCurrentIndex(1);
}

void MainWindow::on_edit2_2_clicked()
{
    int currentRow = ui->tableWidget_2->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Edit", "Please select a row to edit.");
        return;
    }

    QString scheduleID = ui->tableWidget_2->item(currentRow, 0)->text();
    QString tutorID;
    QString subject;
    QString date = ui->tableWidget_2->item(currentRow, 3)->text();
    QString timeStart = ui->tableWidget_2->item(currentRow, 4)->text();
    QString timeEnd = ui->tableWidget_2->item(currentRow, 5)->text();

    // retrieve current tutorid and its sugbject
    QSqlQuery query;
    query.prepare("SELECT TutorID, (SELECT Subject FROM Tutor WHERE TutorID = Schedule.TutorID) AS Subject FROM Schedule WHERE ScheduleID = :scheduleID");
    query.bindValue(":scheduleID", scheduleID);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Edit", "Failed to retrieve current TutorID and Subject: " + query.lastError().text());
        return;
    }

    tutorID = query.value("TutorID").toString();
    subject = query.value("Subject").toString();

    EditSubmitDialog editDialog(this);
    editDialog.setData(date, timeStart, timeEnd);
    if (editDialog.exec() == QDialog::Accepted) {
        // Update the database
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE Schedule SET ScheduleDate = :date, TimeStart = :timeStart, TimeEnd = :timeEnd WHERE ScheduleID = :scheduleID");
        updateQuery.bindValue(":date", editDialog.getDate());
        updateQuery.bindValue(":timeStart", editDialog.getTimeStart());
        updateQuery.bindValue(":timeEnd", editDialog.getTimeEnd());
        updateQuery.bindValue(":scheduleID", scheduleID);

        if (updateQuery.exec()) {
            // If datbase was updated successfully, reflect changes in the table too
            ui->tableWidget_2->item(currentRow, 3)->setText(editDialog.getDate());
            ui->tableWidget_2->item(currentRow, 4)->setText(editDialog.getTimeStart());
            ui->tableWidget_2->item(currentRow, 5)->setText(editDialog.getTimeEnd());
            QMessageBox::information(this, "Edit", "Schedule updated successfully!");
        } else {
            QMessageBox::warning(this, "Edit", "Failed to update schedule: " + updateQuery.lastError().text());
        }
    }
}

void MainWindow::on_AddTutor_clicked()
{
    ui->stacked_Widget->setCurrentIndex(3);
}

void MainWindow::on_add_page3_clicked()
{
    QString fullname_page3 = ui->fullname_page3->text().toUpper();
    QString idnumber_page3 = ui->idnumber_page3->text();
    QString subject_page3 = ui->subject_page3->text().toUpper();
    QString contact_page3 = ui->contact_page3->text();

    if(!isContactValid(contact_page3))
    {
        QMessageBox::critical(this, "Error", "Please make sure your contact number is 11 digits long");
        return;
    }

    if (!isTutorIDValid(idnumber_page3)) {
        QMessageBox::critical(this, "Error", "Invalid ID format. Please enter a valid ID in the format XXXX-XXXX");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO tutor(TutorID, Name, Subject, tutorContactNumber) VALUES (:tutorID, :tutorName, :subject2, :contactNumber)");
    query.bindValue(":tutorID", idnumber_page3);
    query.bindValue(":tutorName", fullname_page3);
    query.bindValue(":subject2", subject_page3);
    query.bindValue(":contactNumber", contact_page3);
    if (!query.exec())
    {
        QMessageBox::critical(this, "Error", "Failed adding tutor");
    } else
    {
        QMessageBox::information(this, "Success", "Tutor Added successfully");
        ui->fullname_page3->clear();
        ui->idnumber_page3->clear();
        ui->subject_page3->clear();
        ui->contact_page3->clear();
    }
    displaytutor();
}

void MainWindow::on_delete2_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Delete", "Please select a row to delete.");
        return;
    }

    QString appointmentID = ui->tableWidget->item(currentRow, 0)->text();

    // Confirm deletion
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this schedule?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        return;
    }

    // Retrieve appointment details
    QSqlQuery appointmentQuery;
    appointmentQuery.prepare("SELECT * FROM Books WHERE AppointmentID = :AppointmentID");
    appointmentQuery.bindValue(":AppointmentID", appointmentID);
    if (!appointmentQuery.exec()) {
        qDebug() << "Error retrieving appointment details:" << appointmentQuery.lastError();
        QMessageBox::critical(this, "Error", "Failed to retrieve appointment details from database.");
        return;
    }

    if (!appointmentQuery.next()) {
        qDebug() << "No appointment found with the given ID:" << appointmentID;
        QMessageBox::critical(this, "Error", "No appointment found with the given ID.");
        return;
    }

    // Extract schedule details from the appointment
    QString scheduleID = appointmentQuery.value("ScheduleID").toString();
    QString bookDate = appointmentQuery.value("bookDate").toString();
    QString timeStart = appointmentQuery.value("timeStart").toString();
    QString timeEnd = appointmentQuery.value("timeEnd").toString();
    QString tutorID = appointmentQuery.value("TutorID").toString();
    QString tuteeID = appointmentQuery.value("TuteeID").toString();

    // Generate a new schedule ID
    QString newScheduleID = generateScheduleID();

    // Insert the schedule back into the schedule table
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO schedule (ScheduleID, ScheduleDate, TimeStart, TimeEnd, TutorID) "
                        "VALUES (:ScheduleID, :ScheduleDate, :TimeStart, :TimeEnd, :TutorID)");
    insertQuery.bindValue(":ScheduleID", newScheduleID);
    insertQuery.bindValue(":ScheduleDate", bookDate);
    insertQuery.bindValue(":TimeStart", timeStart);
    insertQuery.bindValue(":TimeEnd", timeEnd);
    insertQuery.bindValue(":TutorID", tutorID);

    if (!insertQuery.exec()) {
        qDebug() << "Error inserting schedule:" << insertQuery.lastError();
        QMessageBox::critical(this, "Error", "Failed to insert schedule back into the database.");
        return;
    }

    // Delete the appointment from the database
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM Books WHERE AppointmentID = :AppointmentID");
    deleteQuery.bindValue(":AppointmentID", appointmentID);
    if (!deleteQuery.exec()) {
        qDebug() << "Error deleting appointment:" << deleteQuery.lastError();
        QMessageBox::critical(this, "Error", "Failed to delete appointment from database.");
        return;
    }

    // Update the UI to reflect changes
    displayschedule();
    displayAppointment();

    QMessageBox::information(this, "Delete", "Schedule deleted successfully and appointment moved back to schedule.\nNew schedule ID generated: " + newScheduleID);
}

void MainWindow::on_delete2_2_clicked()
{
    int currentRow = ui->tableWidget_2->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Delete", "Please select a row to delete.");
        return;
    }

    QString scheduleID = ui->tableWidget_2->item(currentRow, 0)->text();

    // Confirm deletion
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this schedule?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        return;
    }

    // Delete from database
    QSqlQuery query;
    query.prepare("DELETE FROM schedule WHERE ScheduleID = :scheduleID");
    query.bindValue(":scheduleID", scheduleID);
    if (!query.exec()) {
        qDebug() << "Error deleting from schedule:" << query.lastError();
        QMessageBox::critical(this, "Error", "Failed to delete schedule from database.");
        return;
    }

    // Remove the row from the table widget
    ui->tableWidget_2->removeRow(currentRow);

    QMessageBox::information(this, "Delete", "Schedule deleted successfully.");
}

void MainWindow::on_done_clicked()
{
    // Get the selected row index from the appointment table
    int currentRow = ui->tableWidget->currentRow();

    // Ensure a row is selected
    if (currentRow < 0) {
        QMessageBox::warning(this, "Done", "Please select an appointment to mark as done.");
        return;
    }

    // Get the appointment details from the selected row
    QString appointmentID = ui->tableWidget->item(currentRow, 0)->text();
    QString date = ui->tableWidget->item(currentRow, 1)->text();
    QString timeStart = ui->tableWidget->item(currentRow, 2)->text();
    QString timeEnd = ui->tableWidget->item(currentRow, 3)->text();
    QString tutorID = ui->tableWidget->item(currentRow, 4)->text();
    QString tuteeID = ui->tableWidget->item(currentRow, 5)->text();

    // Move the appointment to the records table
    QSqlQuery moveQuery;
    moveQuery.prepare("INSERT INTO Records (AppointmentID, bookDate, TimeStart, TimeEnd, TutorID, TuteeID) "
                      "VALUES (:AppointmentID, :bookDate, :TimeStart, :TimeEnd, :TutorID, :TuteeID)");
    moveQuery.bindValue(":AppointmentID", appointmentID);
    moveQuery.bindValue(":bookDate", date);
    moveQuery.bindValue(":TimeStart", timeStart);
    moveQuery.bindValue(":TimeEnd", timeEnd);
    moveQuery.bindValue(":TutorID", tutorID);
    moveQuery.bindValue(":TuteeID", tuteeID);
    if (!moveQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to move appointment to records.");
        return;
    }

    // Delete the appointment from the appointment table
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM Books WHERE AppointmentID = :AppointmentID");
    deleteQuery.bindValue(":AppointmentID", appointmentID);
    if (!deleteQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete appointment from appointments.");
        return;
    }

    // Update the UI to reflect the changes
    displayAppointment(); // Refresh the appointments table
    displayRecords(); // Refresh the records table

    QMessageBox::information(this, "Done", "Appointment marked as done and moved to records.");
}

void MainWindow::on_search2_clicked()
{
    QString searchText = ui->searchline2->text().trimmed();
    int rowCount = ui->tableWidget->rowCount();
    int columnCount = ui->tableWidget->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        bool match = false;
        for (int col = 0; col < columnCount; ++col) {
            QTableWidgetItem *item = ui->tableWidget->item(row, col);
            if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->tableWidget->setRowHidden(row, !match);
    }
}

void MainWindow::on_search2_3_clicked()
{
    QString searchText1 = ui->searchline2_3->text().trimmed();
    int rowCount = ui->tableWidget_3->rowCount();
    int columnCount = ui->tableWidget_3->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        bool match = false;
        for (int col = 0; col < columnCount; ++col) {
            QTableWidgetItem *item = ui->tableWidget_3->item(row, col);
            if (item && item->text().contains(searchText1, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->tableWidget_3->setRowHidden(row, !match);
    }
}

void MainWindow::on_search2_2_clicked()
{
    QString searchText2 = ui->searchline2_2->text().trimmed();
    int rowCount = ui->tableWidget_2->rowCount();
    int columnCount = ui->tableWidget_2->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        bool match = false;
        for (int col = 0; col < columnCount; ++col) {
            QTableWidgetItem *item = ui->tableWidget_2->item(row, col);
            if (item && item->text().contains(searchText2, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->tableWidget_2->setRowHidden(row, !match);
    }
}

void MainWindow::on_search2_4_clicked()
{
    QString searchText3 = ui->searchline2_4->text().trimmed();
    int rowCount = ui->tableWidget_4->rowCount();
    int columnCount = ui->tableWidget_4->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        bool match = false;
        for (int col = 0; col < columnCount; ++col) {
            QTableWidgetItem *item = ui->tableWidget_4->item(row, col);
            if (item && item->text().contains(searchText3, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->tableWidget_4->setRowHidden(row, !match);
    }
}

void MainWindow::on_reload1_clicked()
{
    displayAppointment();
    ui->searchline2->clear();
}

void MainWindow::on_reload2_clicked()
{
    displayschedule();
    ui->searchline2_2->clear();
}

void MainWindow::on_reload3_clicked()
{
    displaytutor();
    ui->searchline2_3->clear();
}

void MainWindow::on_reload4_clicked()
{
    displayRecords();
    ui->searchline2_4->clear();
}


void MainWindow::on_delete3_clicked()
{
    int currentRow = ui->tableWidget_4->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Delete", "Please select a row to delete.");
        return;
    }

    QString appointmentid = ui->tableWidget_4->item(currentRow, 0)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this record?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM Records WHERE AppointmentID = :appointmentid");
    query.bindValue(":appointmentid", appointmentid);
    if (!query.exec()) {
        qDebug() << "Error deleting from schedule:" << query.lastError();
        QMessageBox::critical(this, "Error", "Failed to delete records from database.");
        return;
    }

    ui->tableWidget_4->removeRow(currentRow);
    QMessageBox::information(this, "Delete", "Deleted successfully.");
}


void MainWindow::on_delete4_clicked()
{
    int currentRow = ui->tableWidget_3->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Delete", "Please select a row to delete.");
        return;
    }

    QString tutorid = ui->tableWidget_3->item(currentRow, 0)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this tutor data?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM Tutor WHERE TutorID = :tutorid");
    query.bindValue(":tutorid", tutorid);
    if (!query.exec()) {
        qDebug() << "Error deleting from schedule:" << query.lastError();
        QMessageBox::critical(this, "Error", "Failed to delete tutor data from database.");
        return;
    }

    ui->tableWidget_3->removeRow(currentRow);
    QMessageBox::information(this, "Delete", "Deleted successfully.");
}

