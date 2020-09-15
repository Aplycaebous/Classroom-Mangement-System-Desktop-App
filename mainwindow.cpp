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
    ui->recordTable->setRowCount(0);
    ui->mainFrame->hide();
    ui->adminFrame->hide();
    stuidx=-1;
    stfidx=-1;
    admidx=-1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_vectors(vector<Admin> &a, vector<Room> &r, vector<Student> &stu, vector<Staff> &sta, vector<Record> &re)
{
    admin=std::move(a);
    room=std::move(r);
    student=std::move(stu);
    staff=std::move(sta);
    record=std::move(re);
}

void MainWindow::on_loginButton_clicked()
{
    bool success = false, ad = false;

    userid = (ui->Username->text()).toUtf8().constData();
    password = (ui->Password->text()).toUtf8().constData();

    //check validity of login id

    //check student
    int ssize=student.size();
    for(int i=0;i<ssize;i++)
    {
        if(student[i].get_id() == userid)
        {
            if(student[i].get_password() == password)
            {
                success=true;
                stuidx=i;
            }
            break;
        }
    }

    ssize=staff.size();
    for(int i=0;i<ssize;i++)
    {
        if(staff[i].get_id() == userid)
        {
            if(staff[i].get_password() == password)
            {
                success=true;
                stfidx=i;
            }
            break;
        }
    }

    ssize=admin.size();
    for(int i=0;i<ssize;i++)
    {
        if(admin[i].get_username() == userid)
        {
            if(admin[i].get_password() == password)
            {
                success=true;
                ad=true;
                admidx=i;
            }
            break;
        }
    }

    if(!success && !ad)
    {
        ui->loginError->show();
        return;
    }
    else if(success && !ad)
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
}



//main frame button frame actions
void MainWindow::on_RoomBook_clicked()
{
    ui->passwordFrame->hide();
    ui->recordsFrame->hide();
    ui->bookingFrame->show();
}

bool compare_record(Record rec1, Record rec2)
{
    if (rec1.get_date_obj() < rec2.get_date_obj())
    {
        return true;
    }
    else if(rec1.get_date_obj() == rec2.get_date_obj())
    {
        if(rec1.get_time_obj() < rec2.get_time_obj())
        {
            return true;
        }
        else if(rec1.get_time_obj() == rec2.get_time_obj())
        {
            if(rec1.get_duration()<rec2.get_duration())
                return true;
        }
    }
    return false;
}

void MainWindow::on_Records_clicked()
{
    ui->noitmselected->hide();
    ui->passwordFrame->hide();
    ui->bookingFrame->hide();
    ui->recordsFrame->show();
    if(ui->recordTable->rowCount()==0)
    {
        int rsize=record.size();
        for(int i=0;i<rsize;i++)
        {
            if(record[i].get_user_ID() == userid)
            {
                userrec.push_back(record[i]);
            }
        }
        sort(userrec.begin(),userrec.end(),compare_record);
        rsize=userrec.size();
        ui->recordTable->setRowCount(rsize);
        for(int i=0;i<rsize;i++)
        {
            QTableWidgetItem* item = new QTableWidgetItem((QString::fromStdString(userrec[i].get_date())));
            item->setTextAlignment( Qt::AlignCenter );
            ui->recordTable->setItem(i,0, item);
            item = new QTableWidgetItem((QString::fromStdString(userrec[i].get_time_string())));
            item->setTextAlignment( Qt::AlignCenter );
            ui->recordTable->setItem(i,1,item);
            item = new QTableWidgetItem((QString::fromStdString(userrec[i].get_physical_location())));
            item->setTextAlignment( Qt::AlignCenter );
            ui->recordTable->setItem(i,2,item);
        }
    }
}

void MainWindow::on_ChangePassword_clicked()
{
    ui->recordsFrame->hide();
    ui->bookingFrame->hide();
    ui->passwordFrame->show();
    ui->wrongcurrpasslabel->hide();
    ui->passdonotmatchlabel->hide();
    ui->invalidinputlabel->hide();
}

void MainWindow::on_Logout_clicked()
{
    ui->mainFrame->hide();
    ui->loginFrame->show();
    ui->recordTable->setRowCount(0);
    stuidx=-1;
    stfidx=-1;
    admidx=-1;
}

//record frame actions
void MainWindow::on_delrecbtn_clicked()
{
    QItemSelectionModel *select = ui->recordTable->selectionModel();
    if(!select->hasSelection())
        ui->noitmselected->show();
    else
    {
        QModelIndexList selection = select->selectedRows();
        QModelIndex index = selection.at(0);
        int row=index.row();
        ui->recordTable->removeRow(row);
        int rsize=record.size();
        for(int i=0;i<rsize;i++)
        {
            if( record[i].get_user_ID() == userrec[row].get_user_ID() && record[i].get_phy_loc_obj() == userrec[row].get_phy_loc_obj() && record[i].get_time_obj() == userrec[row].get_time_obj() &&
                record[i].get_duration() == userrec[row].get_duration() && record[i].get_date_obj() == userrec[row].get_date_obj() )
            {
                record.erase(record.begin()+i);
                rsize--;
                break;
            }
        }
        std::ofstream ofs;
        ofs.open("C:\\Users\\tasni\\Documents\\RMS\\Record.csv", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        ofstream myFile;
        myFile.open("C:\\Users\\tasni\\Documents\\RMS\\Record.csv");
        for(int i=0;i<rsize;i++)
        {
            myFile<<record[i].get_user_ID()<<","<<record[i].get_building_no()<<","<<record[i].get_room_no()<<","<<record[i].get_hour()<<","<<record[i].get_minute()<<","
            <<record[i].get_duration()<<","<<record[i].get_day()<<","<<record[i].get_month()<<","<<record[i].get_year()<<endl;
        }
        fstream file("C:\\Users\\tasni\\Documents\\RMS\\log.txt",ios::in|ios::out|ios::app );
        file<<"Record "<<userrec[row].get_physical_location()<<" at "<<userrec[row].get_time_24()<<" on "<<userrec[row].get_date()<<" was removed by id: "<<userid<<endl;
        userrec.erase(userrec.begin()+row);
    }
}


//password frame actions
void MainWindow::on_changePassbtn_clicked()
{
    bool opass=false, npass=false;
    string currPass=(ui->currPassinput->text()).toUtf8().constData();
    string newPassw=(ui->newPassinput->text()).toUtf8().constData();
    string confPassw=(ui->confirmPassinput->text()).toUtf8().constData();
    if(currPass==password)
        opass=true;
    if(newPassw==confPassw && newPassw!="")
        npass=true;
    if(opass && npass)
    {
        if(stuidx!=-1 && student[stuidx].get_id()==userid)
            student[stuidx].set_password(newPassw);
        else if(stfidx!=-1 && staff[stfidx].get_id()==userid)
            staff[stfidx].set_password(newPassw);
    }
    else if (!opass && !npass)
    {
        ui->passdonotmatchlabel->hide();
        ui->wrongcurrpasslabel->hide();
        ui->invalidinputlabel->show();
        return;
    }
    else if (opass && !npass)
    {
        ui->invalidinputlabel->hide();
        ui->passdonotmatchlabel->hide();
        ui->wrongcurrpasslabel->show();
        return;
    }
    else if (!opass && npass)
    {
        ui->invalidinputlabel->hide();
        ui->wrongcurrpasslabel->hide();
        ui->passdonotmatchlabel->show();
        return;
    }
    ui->currPassinput->clear();
    ui->newPassinput->clear();
    ui->confirmPassinput->clear();
    ui->wrongcurrpasslabel->hide();
    ui->passdonotmatchlabel->hide();
    ui->invalidinputlabel->hide();
}

