#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QPropertyAnimation>

#include "System_initializer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_loginButton_clicked();
    void on_Logout_clicked();

    void on_changePassbtn_clicked();

    void on_ChangePassword_clicked();

    void on_Records_clicked();

    void on_RoomBook_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
