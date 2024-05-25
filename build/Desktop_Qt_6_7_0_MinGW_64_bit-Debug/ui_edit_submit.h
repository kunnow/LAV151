/********************************************************************************
** Form generated from reading UI file 'edit_submit.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_SUBMIT_H
#define UI_EDIT_SUBMIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_EditSubmitDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label10_2;
    QLabel *label10_3;
    QLabel *label10_4;
    QLineEdit *newDate;
    QLineEdit *newTimeStart;
    QLineEdit *newTimeEnd;

    void setupUi(QDialog *EditSubmitDialog)
    {
        if (EditSubmitDialog->objectName().isEmpty())
            EditSubmitDialog->setObjectName("EditSubmitDialog");
        EditSubmitDialog->resize(410, 343);
        buttonBox = new QDialogButtonBox(EditSubmitDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 300, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label10_2 = new QLabel(EditSubmitDialog);
        label10_2->setObjectName("label10_2");
        label10_2->setGeometry(QRect(20, 40, 101, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("Rockwell")});
        font.setBold(true);
        label10_2->setFont(font);
        label10_3 = new QLabel(EditSubmitDialog);
        label10_3->setObjectName("label10_3");
        label10_3->setGeometry(QRect(20, 110, 101, 21));
        label10_3->setFont(font);
        label10_4 = new QLabel(EditSubmitDialog);
        label10_4->setObjectName("label10_4");
        label10_4->setGeometry(QRect(20, 180, 101, 21));
        label10_4->setFont(font);
        newDate = new QLineEdit(EditSubmitDialog);
        newDate->setObjectName("newDate");
        newDate->setGeometry(QRect(20, 70, 231, 21));
        newDate->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        newTimeStart = new QLineEdit(EditSubmitDialog);
        newTimeStart->setObjectName("newTimeStart");
        newTimeStart->setGeometry(QRect(20, 140, 231, 21));
        newTimeStart->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));
        newTimeEnd = new QLineEdit(EditSubmitDialog);
        newTimeEnd->setObjectName("newTimeEnd");
        newTimeEnd->setGeometry(QRect(20, 210, 231, 21));
        newTimeEnd->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"));

        retranslateUi(EditSubmitDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, EditSubmitDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, EditSubmitDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(EditSubmitDialog);
    } // setupUi

    void retranslateUi(QDialog *EditSubmitDialog)
    {
        EditSubmitDialog->setWindowTitle(QCoreApplication::translate("EditSubmitDialog", "Dialog", nullptr));
        label10_2->setText(QCoreApplication::translate("EditSubmitDialog", "Date", nullptr));
        label10_3->setText(QCoreApplication::translate("EditSubmitDialog", "Time Start", nullptr));
        label10_4->setText(QCoreApplication::translate("EditSubmitDialog", "Time End", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditSubmitDialog: public Ui_EditSubmitDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_SUBMIT_H
