#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QPropertyAnimation>

#include "System_initializer.h"
#include <utility>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init_vectors(vector<Admin> &a, vector<Room> &r, vector<Student> &stu, vector<Staff> &sta, vector<Record> &re);

private slots:
    void on_loginButton_clicked();

    void on_Logout_clicked();

    void on_changePassbtn_clicked();

    void on_ChangePassword_clicked();

    void on_Records_clicked();

    void on_RoomBook_clicked();

    void on_delrecbtn_clicked();

    void on_bkbtn_clicked();

    void on_serbtn_clicked();

    void on_timestart_editingFinished();

    void on_timestart_userTimeChanged();

    void on_AddRoom_clicked();

    void on_Users_clicked();

    void on_adminChangePassword_clicked();

    void on_adminLogout_clicked();

    void on_changePassbtn_2_clicked();

    void on_addbtn_clicked();

    void on_adduserbtn_clicked();

    void on_usrtypbox_2_activated();

    void on_adduserbtn_2_clicked();

    void on_remvUserbtn_clicked();

    void on_chngUsrPass_clicked();

private:
    int stuidx, stfidx, admidx;
    bool usrrecload;
    string userid, password;
    vector<Admin> admin;
    vector<Room> room;
    vector<Student> student;
    vector<Staff> staff;
    vector<Record> record, userrec;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
