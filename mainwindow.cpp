#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Username->hide();
    ui->Password->hide();
    ui->loginButton->hide();
    ui->loginError->hide();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->loginImg, "geometry");
    animation->setDuration(1200);
    double i;
    for(i=0;i<=1;i+=.1)
    {
        animation->setKeyValueAt(i, QRect(683-(261*i),70*i,544*i,617*i));
    }
    animation->start();
    connect(animation,SIGNAL(finished()) ,ui->Username, SLOT(show()));
    connect(animation,SIGNAL(finished()) ,ui->Password, SLOT(show()));
    connect(animation,SIGNAL(finished()) ,ui->loginButton, SLOT(show()));
    ui->recordTable->setRowCount(1);
    ui->recordTable->setItem(0,0,new QTableWidgetItem("x"));
    ui->mainFrame->hide();
    ui->adminFrame->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    bool success = false, admin = false;
    //bool checkadmin=false;
    QString username=ui->Username->text();
    QString password=ui->Password->text();
    //check validity of login id
    if(username=="test" && password=="test")
        success=true;
    if(username=="admin" && password=="admin")
    {
        success=true;
        admin=true;
    }
    if(!success && !admin)
    {
        ui->loginError->show();
        return;
    }
    else if(success && !admin)
    {
        ui->loginFrame->hide();
        ui->mainFrame->show();
        ui->bookingFrame->show();
        ui->passwordFrame->hide();
        ui->recordsFrame->hide();
    }
    else
    {
        ui->loginFrame->hide();
        ui->adminFrame->show();
        ui->addRoomframe->show();
        ui->adminpasswordFrame->hide();
        ui->addUserframe->hide();
    }
    ui->Username->clear();
    ui->Password->clear();
    username="";
    password="";
}



//main frame button frame actions
void MainWindow::on_RoomBook_clicked()
{
    ui->passwordFrame->hide();
    ui->recordsFrame->hide();
    ui->bookingFrame->show();
}

void MainWindow::on_Records_clicked()
{
    ui->passwordFrame->hide();
    ui->bookingFrame->hide();
    ui->recordsFrame->show();
}

void MainWindow::on_ChangePassword_clicked()
{
    ui->recordsFrame->hide();
    ui->bookingFrame->hide();
    ui->passwordFrame->show();
}

void MainWindow::on_Logout_clicked()
{
    ui->mainFrame->hide();
    ui->loginFrame->show();
    ui->recordTable->setRowCount(0);
}

//record frame actions


//password frame actions
void MainWindow::on_changePassbtn_clicked()
{
    bool success=false;
    QString currPass=ui->currPassinput->text();
    QString newPassw=ui->newPassinput->text();
    QString confPassw=ui->confirmPassinput->text();
    if(success)
    {

    }
}
