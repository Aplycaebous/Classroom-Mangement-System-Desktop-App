#include "User.h"

User::User()
{
    set_name("");
    set_password("password123");
}

User::User(string nameval, string passval)
{
    set_name(nameval);
    if(!set_password(passval)) set_password("password123"); //show error password set to default value password123
}

bool User::check_password(string val)
{
    if(val.length()>=24 || val.length()<6)
    return false;
    else
    {
        //check password complexity with more if conditions
        //must contain at least one character and one digit or something like that
        return true;
    }
}

void User::set_name(string value)
{
    name = value;
}

bool User::set_password(string val)
{
    if(check_password(val))
    {
        password = val;
        return true;
    }
    return false;
}

string User::get_name(void)
{
    return name;
}

string User::get_password(void)
{
    return password;
}

static bool login(vector<User*> user_vec, string id, string password)
{
    for(int i=0;i<user_vec.size();i++)
    {
        if(user_vec[i]->get_id() == id)
        {
            if(user_vec[i]->get_password()==password)
                return true;
            else return false; //cout<<"Password didn't match"<<endl;
        }
    }
    //cout<<"ID not found"<<endl;
    return false;
}

/*
static void add_record(vector<User*> &user,vector<Record*> &record,string id, Physical_location phy_val, Date date_val, Time time_val, int dur_val)
{
    int cross=0, rsize = record.size();
    for(int i=0;i<rsize;i++)
    {
        if( stoi(record[i]->get_building_no()) >stoi(phy_val.get_building_no()))
        {
            break;
        }
        else if(stoi(record[i]->get_building_no() ) <stoi(phy_val.get_building_no()))
        {
            cross++;
        }
        else if(stoi(record[i]->get_building_no())==stoi(phy_val.get_building_no()))
        {
            if(stoi(record[i]->get_room_no()) >stoi(phy_val.get_room_no()))
            {
                break;
            }
            else
            {
                cross++;
            }
        }
    }

    record.insert((record.begin()+cross),Record(id, phy_val,time_val, dur_val,date_val));
    std::ofstream ofs;
    ofs.open("Record.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;
    myFile.open("Record.csv");
    for(int i=0;i<rsize;i++)
    {
        int hour;
        myFile<<record[i].get_user_ID()<<","<<record[i].get_building_no()<<","<<record[i].get_room_no()<<","<<hour<<","<<
        record[i].get_minute()<<","<<record[i].get_duration()<<","<<record[i].get_day()<<","<<record[i].get_month()<<","<<record[i].get_year()<<endl;
    }
    fstream file("log.txt",ios::in|ios::out|ios::app );
    file<<"Record "<<build_val<<" "<<room_val<<" at "<<hour_val<<" "<<min_val<<" "<<form_val<<" was added by the Student"<<endl;
}

void delete_record(vector<Student>&student,vector<Record>&record,int student_number, string build_val, string room_val, int hour_val, int min_val, string form_val,
                   int dur_val, int day_val, int mon_val, int year_val)
{

    //int cross=0;
    int rsize=record.size();
    for(int i=0;i<rsize;i++)
    {
        int hour;
        if( record[i].get_user_ID() == student[student_number].student_id &&
            record[i].get_building_no()==build_val &&
            record[i].get_room_no()==room_val &&
            record[i].get_hour() == hour_val &&
            record[i].get_minute()==min_val&&
            record[i].get_duration()==dur_val &&
            record[i].get_day() == day_val &&
            record[i].get_month() == mon_val &&
            record[i].get_year() == year_val )
        {
            record.erase(record.begin()+i);
            break;
        }
    }
    std::ofstream ofs;
    ofs.open("Record.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;
    myFile.open("Record.csv");

    for(int i=0;i<rsize;i++)
    {
        int hour;
        myFile<<record[i].get_user_ID()<<","<<record[i].get_building_no()<<","<<record[i].get_room_no()<<","<<hour<<","<<record[i].get_minute()<<","<<record[i].get_duration()<<","<<record[i].get_day()<<","<<record[i].get_month()<<","<<record[i].get_year()<<endl;
    }

    fstream file("log.txt",ios::in|ios::out|ios::app );
    file<<"Record "<<build_val<<" "<<room_val<<" at "<<hour_val<<" "<<min_val<<" "<<form_val<<" was removed by the Student"<<endl;
}


 vector<Room*> search_record(vector<Record*> record_list, Physical_location phy_val, Time time_val, Date date_val, int dur_val)
{
    vector<Room*> record_give;
    for(int i=0;i<record_list.size();i++)
    {
        if( record_list[i]->get_phy_loc_obj() == phy_val &&
            record_list[i]->get_time_obj() == time_val &&
            record_list[i]->get_date_obj() == date_val &&
            record_list[i]->get_duration() == dur_val )
            {
                record_give.push_back(record_list[i]);
                break;
             }
    }
    return record_give;
}
  */
 bool clash(vector<Record*> record, Physical_location phy_val, Date date_val, Time time_val, int dur_val)
{
    vector<Room*> record_give;
    for(int i=0;i<record.size();i++)
    {
        if( record[i]->get_phy_loc_obj() == phy_val && record[i]->get_date_obj() == date_val)
        {
            int temp_hour=record[i].get_hour();
            int temp_minute=record[i].get_minute();
            int temp_duration=record[i].get_duration();
            if(form_val=="PM")
            {
                hour_val+=12;
            }
            int record_total_minute=temp_hour*60 +temp_minute;
            int check_total_minute = hour_val*60 +min_val;
            if(record_total_minute+temp_duration<check_total_minute || check_total_minute+dur_val<record_total_minute )
            {
                continue;
            }
            else return false;
        }
    }
    return true;
}
