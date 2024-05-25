#include "edit_submit.h"
#include "ui_edit_submit.h"

EditSubmitDialog::EditSubmitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditSubmitDialog)
{
    ui->setupUi(this);
     this->setWindowTitle("MSU-IIT LAV");
}

EditSubmitDialog::~EditSubmitDialog()
{
    delete ui;
}

void EditSubmitDialog::setData( const QString &date, const QString &timeStart, const QString &timeEnd)
{
    // Assuming you have QLineEdits with these names in your edit_submit.ui
    ui->newDate->setText(date);
    ui->newTimeStart->setText(timeStart);
    ui->newTimeEnd->setText(timeEnd);
}

QString EditSubmitDialog::getDate() const
{
    return ui->newDate->text();
}

QString EditSubmitDialog::getTimeStart() const
{
    return ui->newTimeStart->text();
}

QString EditSubmitDialog::getTimeEnd() const
{
    return ui->newTimeEnd->text();
}

