#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tutee_appointment_clicked();
    void on_tutor_schedule_clicked();
    void on_close_clicked();

    void on_add1_clicked();
    void on_add2_clicked();
    void displayschedule();
    void displayAppointment();
    void displaytutor();
    void displayRecords();
    void on_History_clicked();

    void on_edit2_2_clicked();

    void on_AddTutor_clicked();


    void on_add_page3_clicked();

    void on_delete2_2_clicked();

    void on_delete2_clicked();



    void on_done_clicked();

    void on_search2_clicked();

    void on_search2_3_clicked();

    void on_search2_2_clicked();

    void on_search2_4_clicked();

    void on_reload1_clicked();

    void on_reload2_clicked();

    void on_reload3_clicked();

    void on_reload4_clicked();

    void on_delete3_clicked();

    void on_delete4_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
