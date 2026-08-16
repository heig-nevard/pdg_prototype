#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "PasswordDelegate.h"
#include "passworddetailsdialog.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // UI Setup
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    for(QAction *action: ui->menubar->actions()){
        action->setEnabled(false);
    }


    // Model setup
    model = new QStandardItemModel(0, 5, this);
    model->setHorizontalHeaderLabels({"Title", "Username", "Password", "URL", "Description"});
    ui->tableView_passwords->setModel(model);
    ui->tableView_passwords->setItemDelegateForColumn(2, new PasswordDelegate(ui->tableView_passwords));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_check_masterpass_clicked()
{
    const QString pass = ui->lineEdit_masterpass->text();

    if(pass == "masterpass"){
        ui->stackedWidget->setCurrentWidget(ui->main_page);
        for(QAction *action: ui->menubar->actions()){
            action->setEnabled(true);
        }
        populateModelWithExampleData();
    }else{
        QMessageBox::warning(
            this,
            "Invalid password",
            "The password is incorrect."
            );
    }
}


void MainWindow::on_button_login_clicked()
{
    const QString username = ui->lineEdit_login_username->text();
    const QString password = ui->lineEdit_login_password->text();

    if(username == "nolan" && password == "pass"){
        ui->stackedWidget->setCurrentWidget(ui->masterpass_page);
    }else{
        QMessageBox::warning(
            this,
            "Invalid password or username",
            "The password or the username is incorrect."
            );
    }
}

void MainWindow::populateModelWithExampleData(){
    model->setItem(0, 0, new QStandardItem("Pass1"));
    model->setItem(0, 1, new QStandardItem("nolan"));
    model->setItem(0, 2, new QStandardItem("pass"));
    model->setItem(0, 3, new QStandardItem("localhost:8080"));
    model->setItem(0, 4, new QStandardItem("This is example password 1"));

    model->setItem(1, 0, new QStandardItem("Pass2"));
    model->setItem(1, 1, new QStandardItem("nolan"));
    model->setItem(1, 2, new QStandardItem("pass"));
    model->setItem(1, 3, new QStandardItem("localhost:8080"));
    model->setItem(1, 4, new QStandardItem("This is example password 2"));

    model->setItem(2, 0, new QStandardItem("Pass3"));
    model->setItem(2, 1, new QStandardItem("nolan"));
    model->setItem(2, 2, new QStandardItem("pass"));
    model->setItem(2, 3, new QStandardItem("localhost:8080"));
    model->setItem(2, 4, new QStandardItem("This is example password 3"));

    model->setItem(3, 0, new QStandardItem("Pass4"));
    model->setItem(3, 1, new QStandardItem("nolan"));
    model->setItem(3, 2, new QStandardItem("pass"));
    model->setItem(3, 3, new QStandardItem("localhost:8080"));
    model->setItem(3, 4, new QStandardItem("This is example password 4"));
}


void MainWindow::on_tableView_passwords_doubleClicked(const QModelIndex &index)
{
    PasswordDetailsDialog passwd_dialog(this, model, &index);
    passwd_dialog.exec();
}


void MainWindow::on_action_new_entry_triggered()
{
    PasswordDetailsDialog passwd_dialog(this, model, nullptr);
    passwd_dialog.exec();
}

