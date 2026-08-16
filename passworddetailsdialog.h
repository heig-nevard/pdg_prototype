#ifndef PASSWORDDETAILSDIALOG_H
#define PASSWORDDETAILSDIALOG_H

#include <QAbstractButton>
#include <QDialog>
#include <QStandardItem>

namespace Ui {
class PasswordDetailsDialog;
}

class PasswordDetailsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordDetailsDialog(QWidget *parent, QStandardItemModel *model, const QModelIndex *index);
    ~PasswordDetailsDialog();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_button_toggle_password_visibility_toggled(bool checked);

private:
    Ui::PasswordDetailsDialog *ui;
    QStandardItemModel *model;
    const QModelIndex *index;

    void setPasswordData();
};

#endif // PASSWORDDETAILSDIALOG_H
