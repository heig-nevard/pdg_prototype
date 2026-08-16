#include "passworddetailsdialog.h"
#include "ui_passworddetailsdialog.h"

PasswordDetailsDialog::PasswordDetailsDialog(QWidget *parent, QStandardItemModel *model, const QModelIndex *index)
    : QDialog(parent)
    , ui(new Ui::PasswordDetailsDialog)
    , index(index)
{
    ui->setupUi(this);
    if(!model) throw new std::runtime_error("Model must cannot be null");
    this->model = model;
    if(index){
        setPasswordData();
    }
}

PasswordDetailsDialog::~PasswordDetailsDialog()
{
    delete ui;
}

void PasswordDetailsDialog::setPasswordData(){
    if(!model || !index->isValid()) return;

    int row = index->row();
    QModelIndex column0 = model->index(row, 0);
    QModelIndex column1 = model->index(row, 1);
    QModelIndex column2 = model->index(row, 2);
    QModelIndex column3 = model->index(row, 3);
    QModelIndex column4 = model->index(row, 4);

    QString title = column0.data(Qt::DisplayRole).toString();
    QString username = column1.data(Qt::DisplayRole).toString();
    QString password = column2.data(Qt::DisplayRole).toString();
    QString url = column3.data(Qt::DisplayRole).toString();
    QString desc = column4.data(Qt::DisplayRole).toString();

    ui->lineEdit_title->setText(title);
    ui->lineEdit_username->setText(username);
    ui->lineEdit_password->setText(password);
    ui->lineEdit_url->setText(url);
    ui->textEdit_description->setText(desc);
}

void PasswordDetailsDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Apply) {
        QString title = ui->lineEdit_title->text();
        QString username = ui->lineEdit_username->text();
        QString password = ui->lineEdit_password->text();
        QString url = ui->lineEdit_url->text();
        QString desc = ui->textEdit_description->toPlainText();

        if(index && index->isValid()){
            int row = index->row();
            model->setItem(row, 0, new QStandardItem(title));
            model->setItem(row, 1, new QStandardItem(username));
            model->setItem(row, 2, new QStandardItem(password));
            model->setItem(row, 3, new QStandardItem(url));
            model->setItem(row, 4, new QStandardItem(desc));
        }else{
            if(title == "" && username == "" && password == "" && url == "" && desc == "") return;
            model->appendRow({new QStandardItem(title), new QStandardItem(username), new QStandardItem(password), new QStandardItem(url), new QStandardItem(desc)});
        }
    }
    this->done(QDialog::Accepted);
}


void PasswordDetailsDialog::on_button_toggle_password_visibility_toggled(bool checked)
{
    if(checked){
        ui->button_toggle_password_visibility->setIcon(QIcon(":/icons/hide_password.png"));
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    }else{
        ui->button_toggle_password_visibility->setIcon(QIcon(":/icons/show_password.png"));
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    }
}

