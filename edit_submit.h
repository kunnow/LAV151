#ifndef EDIT_SUBMIT_H
#define EDIT_SUBMIT_H

#include <QDialog>

namespace Ui {
class EditSubmitDialog;
}

class EditSubmitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditSubmitDialog(QWidget *parent = nullptr);
    ~EditSubmitDialog();

    void setData(const QString &date, const QString &timeStart, const QString &timeEnd);

    QString getTutorID() const;
    QString getDate() const;
    QString getTimeStart() const;
    QString getTimeEnd() const;
    QString getSubject() const;

private:
    Ui::EditSubmitDialog *ui;
};

#endif // EDIT_SUBMIT_H
