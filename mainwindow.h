#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

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
    ~MainWindow() override;

private slots:
    void on_button_check_masterpass_clicked();

    void on_button_login_clicked();

    void on_tableView_passwords_doubleClicked(const QModelIndex &index);

    void on_action_new_entry_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    void populateModelWithExampleData();
};
#endif // MAINWINDOW_H
