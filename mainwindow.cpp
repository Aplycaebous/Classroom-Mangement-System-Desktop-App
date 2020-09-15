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
    usrrecload=false;
    ui->buildSelec->addItems({ "1", "2", "3"});
    ui->buildSelec_2->addItems({ "1", "2", "3"});
    ui->nomatchlabel->hide();
    ui->rmbked->hide();
    ui->roomprsnt->hide();
    ui->usrtypbox->addItems({ "Student", "Staff"});
    ui->usrtypbox_2->addItems({ "Student", "Staff", "Admin"});
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
    else if(success && ad)
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
    if(!usrrecload)
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
        usrrecload=true;
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


//booking frame actions
bool clash(vector<Record> record, Physical_location phy_val, Date date_val, Time time_val, int dur_val)
{
    vector<Room*> record_give;
    int rsize=record.size();
    for(int i=0;i<rsize;i++)
    {
        if( record[i].get_phy_loc_obj() == phy_val && record[i].get_date_obj() == date_val)
        {
            Time rec_time = record[i].get_time_obj();
            Time rec_end_time = (Time::convert_duration(record[i].get_duration())+ rec_time);
            Time in_end_time = (Time::convert_duration(dur_val) + time_val);

            if(rec_time > in_end_time || rec_end_time < time_val )
            {
                continue;
            }
            else return false;
        }
    }
    return true;
}

void add_record(vector<Record> record,string id, Physical_location phy_val, Date date_val, Time time_val, int dur_val)
{
    int cross=0, rsize = record.size();
    for(int i=0;i<rsize;i++)
    {
        if( record[i].get_phy_loc_obj() > phy_val)
        {
            break;
        }
        else if( record[i].get_phy_loc_obj() < phy_val)
        {
            cross++;
        }
    }
    record.insert((record.begin() + cross), Record(id, phy_val, time_val, dur_val, date_val));
    rsize++;
    std::ofstream ofs;
    ofs.open("C:\\Users\\tasni\\Documents\\RMS\\Record.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;
    myFile.open("C:\\Users\\tasni\\Documents\\RMS\\Record.csv");
    for(int i=0;i<rsize;i++)
    {
        myFile<<record[i].get_user_ID()<<","<<record[i].get_building_no()<<","<<record[i].get_room_no()<<","<<record[i].get_hour()<<","<<
        record[i].get_minute()<<","<<record[i].get_duration()<<","<<record[i].get_day()<<","<<record[i].get_month()<<","<<record[i].get_year()<<endl;
    }
    fstream file("C:\\Users\\tasni\\Documents\\RMS\\log.txt",ios::in|ios::out|ios::app );
    file<<"Record "<<phy_val.get_physical_location()<<" at "<<time_val.get_time_24()<<" on "<<date_val.get_date()<<" was added by id: "<<id<<endl;
}

void MainWindow::on_bkbtn_clicked()
{
    Date date_val(ui->calendarRMBK->selectedDate().day(),ui->calendarRMBK->selectedDate().month(),ui->calendarRMBK->selectedDate().year());
    Time time_start(ui->timestart->time().hour(),ui->timestart->time().minute()), time_end(ui->timeend->time().hour(),ui->timeend->time().minute());
    int dur_val=time_start-time_end;
    Physical_location phy_val((ui->buildSelec->currentText()).toUtf8().constData(),(ui->roomnoSelec->currentText()).toUtf8().constData());
    if(clash(record, phy_val, date_val, time_start, dur_val))
    {
        ui->rmbked->hide();
        add_record(record, userid, phy_val, date_val, time_start, dur_val);
        usrrecload=false;
    }
    else
        ui->rmbked->show();

}

void MainWindow::on_serbtn_clicked()
{
    ui->nomatchlabel->hide();
    ui->roomnoSelec->clear();
    int rsize=room.size(), capacity=ui->capspin->value(), boards=ui->boardspin->value();
    bool proj=ui->projchkbx->isChecked(),ac=ui->ACchkbx->isChecked();
    string build_val=(ui->buildSelec->currentText()).toUtf8().constData();
    for(int i=0;i<rsize;i++)
    {
        if(room[i].get_building_no()==build_val && room[i].get_capacity()>=capacity && room[i].get_projector()==proj && room[i].get_ac()==ac && room[i].get_boards()>=boards)
        {
            ui->roomnoSelec->addItem(QString::fromStdString(room[i].get_room_no()));
        }
    }
    if(ui->roomnoSelec->count()==0)
        ui->nomatchlabel->show();
}

void MainWindow::on_timestart_editingFinished()
{
    ui->timeend->setMinimumTime(ui->timestart->time().addSecs(1800));
}

void MainWindow::on_timestart_userTimeChanged()
{
    ui->timeend->setMinimumTime(ui->timestart->time().addSecs(1800));
}


//record frame actions
void MainWindow::on_delrecbtn_clicked()
{
    QItemSelectionModel *select = ui->recordTable->selectionModel();
    if(!select->hasSelection())
        ui->noitmselected->show();
    else
    {
        ui->noitmselected->hide();
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
                if(record[i].get_date_obj()<userrec[row].get_date_obj())
                {
                    if(record[i].get_time_obj() < userrec[row].get_time_obj())
                        continue;
                    else
                    {
                        ui->noitmselected->show();
                        return;
                    }
                }
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
void student_changepass(vector<Student>&student, int stuidx)
{
    std::ofstream ofs;
    ofs.open("C:\\Users\\tasni\\Documents\\RMS\\Student.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;
    myFile.open("C:\\Users\\tasni\\Documents\\RMS\\Student.csv");
    int ssize=student.size();
    for(int i=0;i<ssize;i++)
    {
        string temp_cr;
        if(student[i].get_cr())
            temp_cr="YES";
        else
            temp_cr="NO";

        myFile<<student[i].get_name()<<","<<student[i].get_password()<<","<<student[i].get_id()<<","<<temp_cr<<endl;
    }
    fstream file("C:\\Users\\tasni\\Documents\\RMS\\log.txt",ios::in|ios::out|ios::app );
    file<<"Student "<<student[stuidx].get_name()<<" changed the password"<<endl;
}

void staff_changepass(vector<Staff>&staff, int stfidx)
{
    std::ofstream ofs;
    ofs.open("C:\\Users\\tasni\\Documents\\RMS\\Staff.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;
    myFile.open("C:\\Users\\tasni\\Documents\\RMS\\Staff.csv");
    int ssize=staff.size();
    for(int i=0;i<ssize;i++)
        myFile<<staff[i].get_name()<<","<<staff[i].get_password()<<","<<staff[i].get_id()<<endl;
    fstream file("C:\\Users\\tasni\\Documents\\RMS\\log.txt",ios::in|ios::out|ios::app );
    file<<"Staff "<<staff[stfidx].get_name()<<" changed his password"<<endl;
}

void MainWindow::on_changePassbtn_clicked()
{
    bool opass=false, npass=false, mpass=false;
    string currPass=(ui->currPassinput->text()).toUtf8().constData();
    string newPassw=(ui->newPassinput->text()).toUtf8().constData();
    string confPassw=(ui->confirmPassinput->text()).toUtf8().constData();
    if(currPass==password)
        opass=true;
    if(newPassw==confPassw)
        mpass=true;
    if((stuidx!=-1 && student[stuidx].check_password(newPassw)) || (stfidx!=-1 && staff[stfidx].check_password(newPassw)))
        npass=true;
    if(opass && npass && mpass)
    {
        if(stuidx!=-1 && student[stuidx].get_id()==userid)
        {
            student[stuidx].set_password(newPassw);
            student_changepass(student,stuidx);
        }
        else if(stfidx!=-1 && staff[stfidx].get_id()==userid)
        {
            staff[stfidx].set_password(newPassw);
            staff_changepass(staff,stfidx);
        }
    }
    else if (!opass)
    {
        ui->passdonotmatchlabel->hide();
        ui->wrongcurrpasslabel->show();
        ui->invalidinputlabel->hide();
        return;
    }
    else if (!npass)
    {
        ui->passdonotmatchlabel->hide();
        ui->wrongcurrpasslabel->hide();
        ui->invalidinputlabel->show();
        return;
    }
    else if (!mpass)
    {
        ui->passdonotmatchlabel->show();
        ui->wrongcurrpasslabel->hide();
        ui->invalidinputlabel->hide();
        return;
    }
    ui->currPassinput->clear();
    ui->newPassinput->clear();
    ui->confirmPassinput->clear();
    ui->wrongcurrpasslabel->hide();
    ui->passdonotmatchlabel->hide();
    ui->invalidinputlabel->hide();
}


//admin frame button actions
void MainWindow::on_AddRoom_clicked()
{
    ui->addRoomframe->show();
    ui->adminpasswordFrame->hide();
    ui->addUserframe->hide();
}

void MainWindow::on_Users_clicked()
{
    ui->addRoomframe->hide();
    ui->adminpasswordFrame->hide();
    ui->addUserframe->show();
    ui->passdonotmatchlabel_3->hide();
    ui->invalidcredlabel->hide();
    ui->passdonotmatchlabel_4->hide();
    ui->invalidcredlabel_2->hide();
    ui->tabWidget->setCurrentIndex(0);
    ui->incorrpass->hide();
    ui->unabletodelete->hide();
    ui->unabletomodify->hide();
}

void MainWindow::on_adminChangePassword_clicked()
{
    ui->addRoomframe->hide();
    ui->adminpasswordFrame->show();
    ui->addUserframe->hide();
    ui->passdonotmatchlabel_2->hide();
    ui->wrongcurrpasslabel_2->hide();
    ui->invalidinputlabel_2->hide();
}

void MainWindow::on_adminLogout_clicked()
{
    ui->adminFrame->hide();
    ui->loginFrame->show();
}


//admin add room frame actions
void add_room(vector<Room>&room,Physical_location phy_val,Equipments equip_val,int capacity)//paramenter list for rooms
{
    int cross=0, rsize=room.size();
    for(int i=0;i<rsize;i++)
    {
        if( stoi(room[i].get_building_no()) >stoi(phy_val.get_building_no()))
        {
            break;
        }
        else if(stoi(room[i].get_building_no() ) <stoi(phy_val.get_building_no()))
        {
            cross++;
        }
        else if(stoi(room[i].get_building_no())==stoi(phy_val.get_building_no()))
        {
            if(stoi(room[i].get_room_no()) >stoi(phy_val.get_room_no()))
            {
                break;
            }
            else
            {
                cross++;
            }
        }
    }
    room.insert(room.begin()+cross,Room(phy_val,equip_val,capacity));
    rsize++;
    std::ofstream ofs;
    ofs.open("C:\\Users\\tasni\\Documents\\RMS\\Room.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;
    myFile.open("C:\\Users\\tasni\\Documents\\RMS\\Room.csv");
    for(int i=0;i<rsize;i++)
    {
        string temp_ac,temp_project;
        if(room[i].get_ac())
        {
            temp_ac="YES";
        }
        else
        {
            temp_ac="NO";
        }
        if(room[i].get_projector())
        {
            temp_project="YES";
        }
        else
        {
            temp_project="NO";
        }
        myFile<<room[i].get_building_no()<<","<<room[i].get_room_no()<<","<<temp_ac<<","<<room[i].get_boards()<<","<<temp_project<<","<<room[i].get_capacity()<<endl;
    }
    fstream file("C:\\Users\\tasni\\Documents\\RMS\\log.txt",ios::in|ios::out|ios::app );
    file<<"Room "<<phy_val.get_building_no()<<" "<<phy_val.get_room_no()<<" was added by the Admin"<<endl;
}

void MainWindow::on_addbtn_clicked()
{
    ui->roomprsnt->hide();
    Physical_location phy_val((ui->buildSelec_2->currentText()).toUtf8().constData(),(ui->roomnoinput->text()).toUtf8().constData());
    Equipments equip_val(ui->ACchkbx_2->isChecked(),ui->boardspin_2->value(),ui->projchkbx_2->isChecked());
    int capacity=ui->capspin_2->value(), rsize=room.size();
    for(int i=0; i<rsize; i++)
    {
        if(room[i].get_phy_loc_obj()==phy_val)
        {
            ui->roomprsnt->show();
            return;
        }
    }
    add_room(room,phy_val,equip_val,capacity);
}


//admin password frame actions
void admin_changepass(vector<Admin>&admin, int admidx)
{
    std::ofstream ofs;
    ofs.open("C:\\Users\\tasni\\Documents\\RMS\\Admin.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;
    myFile.open("C:\\Users\\tasni\\Documents\\RMS\\Admin.csv");
    int asize=admin.size();
    for(int i=0;i<asize;i++)
        myFile<<admin[i].get_username()<<","<<admin[i].get_password()<<","<<admin[i].get_contact_no()<<","<<admin[i].get_email()<<endl;
    fstream file("C:\\Users\\tasni\\Documents\\RMS\\log.txt",ios::in|ios::out|ios::app );
    file<<"Admin "<<admin[admidx].get_username()<<" changed his password"<<endl;
}

void MainWindow::on_changePassbtn_2_clicked()
{
    bool opass=false, npass=false, mpass=false;
    string currPass=(ui->currPassinput_2->text()).toUtf8().constData();
    string newPassw=(ui->newPassinput_2->text()).toUtf8().constData();
    string confPassw=(ui->confirmPassinput_2->text()).toUtf8().constData();
    if(currPass==password)
        opass=true;
    if(newPassw==confPassw)
        mpass=true;
    if(admidx!=-1 && admin[admidx].check_password(newPassw))
        npass=true;
    if(opass && npass && mpass)
    {
        admin[admidx].set_password(newPassw);
        admin_changepass(admin,admidx);
    }
    else if (!opass)
    {
        ui->passdonotmatchlabel_2->hide();
        ui->wrongcurrpasslabel_2->show();
        ui->invalidinputlabel_2->hide();
        return;
    }
    else if (!npass)
    {
        ui->passdonotmatchlabel_2->hide();
        ui->wrongcurrpasslabel_2->hide();
        ui->invalidinputlabel_2->show();
        return;
    }
    else if (!mpass)
    {
        ui->passdonotmatchlabel_2->show();
        ui->wrongcurrpasslabel_2->hide();
        ui->invalidinputlabel_2->hide();
        return;
    }
    ui->currPassinput_2->clear();
    ui->newPassinput_2->clear();
    ui->confirmPassinput_2->clear();
    ui->wrongcurrpasslabel_2->hide();
    ui->passdonotmatchlabel_2->hide();
    ui->invalidinputlabel_2->hide();
}


//admin user frame actions
void delete_record(vector<Record> &record,string id)
{
    int rsize=record.size();
    for(int i=0;i<rsize;i++)
    {
        if( record[i].get_user_ID() == id )
        {
            record.erase(record.begin()+i);
            break;
        }
    }
    rsize--;
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
    file<<"User "<<id<<" was deleted"<<endl;
}

void MainWindow::on_adduserbtn_clicked()
{
    ui->passdonotmatchlabel_3->hide();
    ui->invalidcredlabel->hide();
    if(ui->passinput->text()!=ui->confirmPassinput_5->text())
    {
        ui->passdonotmatchlabel_3->show();
        return;
    }
    if(ui->usrtypbox->currentText()=="Student")
        admin[admidx].add_student(student,ui->usernameinput->text().toUtf8().constData(),ui->passinput->text().toUtf8().constData(),ui->useridinput->text().toUtf8().constData(),0);
    else if(ui->usrtypbox->currentText()=="Staff")
        admin[admidx].add_staff(staff,ui->usernameinput->text().toUtf8().constData(),ui->passinput->text().toUtf8().constData(),ui->useridinput->text().toUtf8().constData());
    ui->usernameinput->clear();
    ui->passinput->clear();
    ui->confirmPassinput_5->clear();
    ui->useridinput->clear();
}

void MainWindow::on_usrtypbox_2_activated()
{
    ui->usrnamebox->clear();
    if(ui->usrtypbox_2->currentText()=="Student")
    {
        int ssize=student.size();
        for(int i=0; i<ssize; i++)
            ui->usrnamebox->addItem(QString::fromStdString(student[i].get_id()));
    }
    else if(ui->usrtypbox_2->currentText()=="Staff")
    {
        int ssize=staff.size();
        for(int i=0; i<ssize; i++)
            ui->usrnamebox->addItem(QString::fromStdString(staff[i].get_id()));
    }
    else if(ui->usrtypbox_2->currentText()=="Admin")
    {
        int ssize=admin.size();
        for(int i=0; i<ssize; i++)
            ui->usrnamebox->addItem(QString::fromStdString(admin[i].get_username()));
    }
}

void MainWindow::on_adduserbtn_2_clicked()
{
    ui->passdonotmatchlabel_4->hide();
    ui->invalidcredlabel_2->hide();
    if(ui->passinput_2->text()!=ui->confirmPassinput_6->text())
    {
        ui->passdonotmatchlabel_4->show();
        return;
    }
    admin[admidx].add_admin(admin,ui->usernameinput_2->text().toUtf8().constData(),ui->passinput_2->text().toUtf8().constData(),
                            ui->contactnoinput->text().toUtf8().constData(),ui->emailinput->text().toUtf8().constData());
    ui->usernameinput_2->clear();
    ui->passinput_2->clear();
    ui->confirmPassinput_6->clear();
    ui->contactnoinput->clear();
    ui->emailinput->clear();
}

void MainWindow::on_remvUserbtn_clicked()
{
    ui->incorrpass->hide();
    ui->unabletodelete->hide();
    if(ui->usrpassinput->text().toUtf8().constData()!=password)
    {
        ui->incorrpass->show();
        return;
    }
    if(ui->usrtypbox_2->currentText()=="Student")
        admin[admidx].remove_student(student,ui->usrnamebox->currentText().toUtf8().constData());
    else if(ui->usrtypbox_2->currentText()=="Staff")
        admin[admidx].remove_staff(staff,ui->usrnamebox->currentText().toUtf8().constData());
    else if(ui->usrtypbox_2->currentText()=="Admin")
    {
        if(ui->usrnamebox->currentText().toUtf8().constData()==userid)
        {
            ui->usrpassinput->clear();
            ui->unabletodelete->show();
            return;
        }
        admin[admidx].remove_admin(admin,ui->usrnamebox->currentText().toUtf8().constData());
    }
    ui->usrnamebox->clear();
    ui->usrpassinput->clear();
}

void MainWindow::on_chngUsrPass_clicked()
{
    ui->unabletomodify->hide();
    if(ui->usrtypbox_2->currentText()=="Student")
    {
        student[ui->usrnamebox->currentIndex()].set_password(ui->usrpassinput->text().toUtf8().constData());
        student_changepass(student,ui->usrnamebox->currentIndex());
    }
    else if(ui->usrtypbox_2->currentText()=="Staff")
    {
        staff[ui->usrnamebox->currentIndex()].set_password(ui->usrpassinput->text().toUtf8().constData());
        staff_changepass(staff,ui->usrnamebox->currentIndex());
    }
    else if(ui->usrtypbox_2->currentText()=="Admin")
        ui->unabletomodify->show();
    ui->usrnamebox->clear();
    ui->usrpassinput->clear();
}
