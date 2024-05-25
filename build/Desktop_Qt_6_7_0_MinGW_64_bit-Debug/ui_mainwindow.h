/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stacked_Widget;
    QWidget *page1;
    QLabel *label1;
    QLineEdit *fullname1;
    QLabel *label2;
    QLineEdit *idnumber1;
    QLabel *label3;
    QLineEdit *coursecode1;
    QSpinBox *yearlevel1;
    QLabel *label4;
    QLabel *label5;
    QLineEdit *scheduleid1;
    QTableWidget *tableWidget_2;
    QLineEdit *searchline2_2;
    QPushButton *search2_2;
    QPushButton *add1;
    QPushButton *edit2_2;
    QPushButton *delete2_2;
    QLineEdit *contact_2;
    QLabel *label5_2;
    QWidget *page4;
    QTableWidget *tableWidget_4;
    QWidget *page2;
    QLineEdit *tutorID;
    QLabel *label15;
    QLabel *label11;
    QLineEdit *timeend2;
    QLabel *label14;
    QLineEdit *date2;
    QLabel *label13;
    QLineEdit *timestart2;
    QPushButton *search2;
    QLineEdit *searchline2;
    QTableWidget *tableWidget;
    QPushButton *delete2;
    QPushButton *add2;
    QPushButton *done;
    QWidget *page3;
    QTableWidget *tableWidget_3;
    QLabel *label10_2;
    QLineEdit *fullname_page3;
    QLabel *label10_3;
    QLineEdit *idnumber_page3;
    QLineEdit *subject_page3;
    QLabel *label10_4;
    QPushButton *add_page3;
    QLabel *label10_5;
    QLineEdit *contact_page3;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *tutor_schedule;
    QPushButton *tutee_appointment;
    QPushButton *AddTutor;
    QPushButton *History;
    QSpacerItem *verticalSpacer;
    QPushButton *close;
    QFrame *frame;
    QFrame *frame_2;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1379, 714);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stacked_Widget = new QStackedWidget(centralwidget);
        stacked_Widget->setObjectName("stacked_Widget");
        stacked_Widget->setGeometry(QRect(150, 40, 1231, 631));
        page1 = new QWidget();
        page1->setObjectName("page1");
        label1 = new QLabel(page1);
        label1->setObjectName("label1");
        label1->setGeometry(QRect(40, 100, 101, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("Rockwell")});
        font.setBold(true);
        label1->setFont(font);
        fullname1 = new QLineEdit(page1);
        fullname1->setObjectName("fullname1");
        fullname1->setGeometry(QRect(40, 120, 231, 21));
        fullname1->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        label2 = new QLabel(page1);
        label2->setObjectName("label2");
        label2->setGeometry(QRect(40, 150, 101, 21));
        label2->setFont(font);
        idnumber1 = new QLineEdit(page1);
        idnumber1->setObjectName("idnumber1");
        idnumber1->setGeometry(QRect(40, 170, 231, 21));
        idnumber1->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        label3 = new QLabel(page1);
        label3->setObjectName("label3");
        label3->setGeometry(QRect(40, 200, 101, 21));
        label3->setFont(font);
        coursecode1 = new QLineEdit(page1);
        coursecode1->setObjectName("coursecode1");
        coursecode1->setGeometry(QRect(40, 270, 231, 21));
        coursecode1->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        yearlevel1 = new QSpinBox(page1);
        yearlevel1->setObjectName("yearlevel1");
        yearlevel1->setGeometry(QRect(40, 220, 231, 21));
        yearlevel1->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        yearlevel1->setMinimum(1);
        yearlevel1->setMaximum(4);
        label4 = new QLabel(page1);
        label4->setObjectName("label4");
        label4->setGeometry(QRect(40, 250, 101, 21));
        label4->setFont(font);
        label5 = new QLabel(page1);
        label5->setObjectName("label5");
        label5->setGeometry(QRect(40, 300, 101, 21));
        label5->setFont(font);
        scheduleid1 = new QLineEdit(page1);
        scheduleid1->setObjectName("scheduleid1");
        scheduleid1->setGeometry(QRect(40, 320, 231, 21));
        scheduleid1->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        tableWidget_2 = new QTableWidget(page1);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(370, 90, 791, 461));
        searchline2_2 = new QLineEdit(page1);
        searchline2_2->setObjectName("searchline2_2");
        searchline2_2->setGeometry(QRect(370, 50, 681, 21));
        search2_2 = new QPushButton(page1);
        search2_2->setObjectName("search2_2");
        search2_2->setGeometry(QRect(1070, 50, 83, 21));
        add1 = new QPushButton(page1);
        add1->setObjectName("add1");
        add1->setEnabled(true);
        add1->setGeometry(QRect(70, 420, 141, 31));
        edit2_2 = new QPushButton(page1);
        edit2_2->setObjectName("edit2_2");
        edit2_2->setGeometry(QRect(1080, 560, 74, 21));
        delete2_2 = new QPushButton(page1);
        delete2_2->setObjectName("delete2_2");
        delete2_2->setGeometry(QRect(980, 560, 74, 21));
        contact_2 = new QLineEdit(page1);
        contact_2->setObjectName("contact_2");
        contact_2->setGeometry(QRect(40, 380, 231, 21));
        contact_2->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        label5_2 = new QLabel(page1);
        label5_2->setObjectName("label5_2");
        label5_2->setGeometry(QRect(40, 350, 101, 21));
        label5_2->setFont(font);
        stacked_Widget->addWidget(page1);
        page4 = new QWidget();
        page4->setObjectName("page4");
        tableWidget_4 = new QTableWidget(page4);
        tableWidget_4->setObjectName("tableWidget_4");
        tableWidget_4->setGeometry(QRect(120, 80, 881, 541));
        stacked_Widget->addWidget(page4);
        page2 = new QWidget();
        page2->setObjectName("page2");
        tutorID = new QLineEdit(page2);
        tutorID->setObjectName("tutorID");
        tutorID->setGeometry(QRect(40, 150, 231, 21));
        tutorID->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        label15 = new QLabel(page2);
        label15->setObjectName("label15");
        label15->setGeometry(QRect(170, 230, 101, 21));
        label15->setFont(font);
        label11 = new QLabel(page2);
        label11->setObjectName("label11");
        label11->setGeometry(QRect(40, 120, 101, 21));
        label11->setFont(font);
        timeend2 = new QLineEdit(page2);
        timeend2->setObjectName("timeend2");
        timeend2->setGeometry(QRect(170, 260, 111, 21));
        timeend2->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        label14 = new QLabel(page2);
        label14->setObjectName("label14");
        label14->setGeometry(QRect(40, 230, 101, 21));
        label14->setFont(font);
        date2 = new QLineEdit(page2);
        date2->setObjectName("date2");
        date2->setGeometry(QRect(40, 200, 231, 21));
        date2->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        label13 = new QLabel(page2);
        label13->setObjectName("label13");
        label13->setGeometry(QRect(40, 180, 101, 21));
        label13->setFont(font);
        timestart2 = new QLineEdit(page2);
        timestart2->setObjectName("timestart2");
        timestart2->setGeometry(QRect(40, 260, 111, 21));
        timestart2->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        search2 = new QPushButton(page2);
        search2->setObjectName("search2");
        search2->setGeometry(QRect(1070, 50, 83, 21));
        searchline2 = new QLineEdit(page2);
        searchline2->setObjectName("searchline2");
        searchline2->setGeometry(QRect(370, 50, 681, 21));
        tableWidget = new QTableWidget(page2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(370, 90, 791, 461));
        delete2 = new QPushButton(page2);
        delete2->setObjectName("delete2");
        delete2->setGeometry(QRect(970, 560, 74, 21));
        add2 = new QPushButton(page2);
        add2->setObjectName("add2");
        add2->setEnabled(true);
        add2->setGeometry(QRect(200, 300, 74, 21));
        done = new QPushButton(page2);
        done->setObjectName("done");
        done->setGeometry(QRect(1080, 560, 83, 21));
        stacked_Widget->addWidget(page2);
        page3 = new QWidget();
        page3->setObjectName("page3");
        tableWidget_3 = new QTableWidget(page3);
        tableWidget_3->setObjectName("tableWidget_3");
        tableWidget_3->setGeometry(QRect(380, 110, 811, 491));
        label10_2 = new QLabel(page3);
        label10_2->setObjectName("label10_2");
        label10_2->setGeometry(QRect(60, 110, 101, 21));
        label10_2->setFont(font);
        fullname_page3 = new QLineEdit(page3);
        fullname_page3->setObjectName("fullname_page3");
        fullname_page3->setGeometry(QRect(60, 150, 231, 21));
        fullname_page3->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        label10_3 = new QLabel(page3);
        label10_3->setObjectName("label10_3");
        label10_3->setGeometry(QRect(60, 190, 101, 21));
        label10_3->setFont(font);
        idnumber_page3 = new QLineEdit(page3);
        idnumber_page3->setObjectName("idnumber_page3");
        idnumber_page3->setGeometry(QRect(60, 220, 231, 21));
        idnumber_page3->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        subject_page3 = new QLineEdit(page3);
        subject_page3->setObjectName("subject_page3");
        subject_page3->setGeometry(QRect(60, 290, 231, 21));
        subject_page3->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        label10_4 = new QLabel(page3);
        label10_4->setObjectName("label10_4");
        label10_4->setGeometry(QRect(60, 260, 101, 21));
        label10_4->setFont(font);
        add_page3 = new QPushButton(page3);
        add_page3->setObjectName("add_page3");
        add_page3->setEnabled(true);
        add_page3->setGeometry(QRect(220, 410, 74, 21));
        label10_5 = new QLabel(page3);
        label10_5->setObjectName("label10_5");
        label10_5->setGeometry(QRect(60, 320, 101, 21));
        label10_5->setFont(font);
        contact_page3 = new QLineEdit(page3);
        contact_page3->setObjectName("contact_page3");
        contact_page3->setGeometry(QRect(60, 360, 231, 21));
        contact_page3->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        stacked_Widget->addWidget(page3);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 40, 161, 631));
        groupBox->setStyleSheet(QString::fromUtf8(""));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(-10, 120, 161, 491));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 0, 0, 0);
        tutor_schedule = new QPushButton(layoutWidget);
        tutor_schedule->setObjectName("tutor_schedule");
        tutor_schedule->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(tutor_schedule);

        tutee_appointment = new QPushButton(layoutWidget);
        tutee_appointment->setObjectName("tutee_appointment");

        verticalLayout->addWidget(tutee_appointment);

        AddTutor = new QPushButton(layoutWidget);
        AddTutor->setObjectName("AddTutor");

        verticalLayout->addWidget(AddTutor);

        History = new QPushButton(layoutWidget);
        History->setObjectName("History");

        verticalLayout->addWidget(History);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        close = new QPushButton(layoutWidget);
        close->setObjectName("close");

        verticalLayout->addWidget(close);

        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 1381, 41));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(83, 79, 166);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(0, 670, 1381, 41));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(83, 79, 166);"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        MainWindow->setCentralWidget(centralwidget);
        groupBox->raise();
        stacked_Widget->raise();
        frame->raise();
        frame_2->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1379, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        stacked_Widget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "Full Name", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "I.D. Number", nullptr));
        idnumber1->setPlaceholderText(QCoreApplication::translate("MainWindow", "2022-0000", nullptr));
        label3->setText(QCoreApplication::translate("MainWindow", "Year Level", nullptr));
        coursecode1->setPlaceholderText(QCoreApplication::translate("MainWindow", "BSCS", nullptr));
        label4->setText(QCoreApplication::translate("MainWindow", " Course Code", nullptr));
        label5->setText(QCoreApplication::translate("MainWindow", "ScheduleI.D.", nullptr));
        scheduleid1->setPlaceholderText(QCoreApplication::translate("MainWindow", "2022-0000", nullptr));
        search2_2->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        add1->setText(QCoreApplication::translate("MainWindow", "Book", nullptr));
        edit2_2->setText(QCoreApplication::translate("MainWindow", "EDIT", nullptr));
        delete2_2->setText(QCoreApplication::translate("MainWindow", "DELETE", nullptr));
        contact_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "09552719447", nullptr));
        label5_2->setText(QCoreApplication::translate("MainWindow", "Contact Number", nullptr));
        tutorID->setPlaceholderText(QCoreApplication::translate("MainWindow", "2000-0000", nullptr));
        label15->setText(QCoreApplication::translate("MainWindow", "Time End", nullptr));
        label11->setText(QCoreApplication::translate("MainWindow", "I.D. Number", nullptr));
        label14->setText(QCoreApplication::translate("MainWindow", "Time Start", nullptr));
        label13->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        search2->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        delete2->setText(QCoreApplication::translate("MainWindow", "DELETE", nullptr));
        add2->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        done->setText(QCoreApplication::translate("MainWindow", "DONE", nullptr));
        label10_2->setText(QCoreApplication::translate("MainWindow", "Full Name", nullptr));
        label10_3->setText(QCoreApplication::translate("MainWindow", "ID Number", nullptr));
        label10_4->setText(QCoreApplication::translate("MainWindow", "Subject", nullptr));
        add_page3->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        label10_5->setText(QCoreApplication::translate("MainWindow", "Contact Number", nullptr));
        groupBox->setTitle(QString());
        tutor_schedule->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        tutee_appointment->setText(QCoreApplication::translate("MainWindow", "Tutee Appointment", nullptr));
        AddTutor->setText(QCoreApplication::translate("MainWindow", "Add a Tutor", nullptr));
        History->setText(QCoreApplication::translate("MainWindow", "History", nullptr));
        close->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
