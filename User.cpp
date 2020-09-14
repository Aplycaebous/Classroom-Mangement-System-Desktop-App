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

bool User::login(vector<User*> user_vec, string id, string password)
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

void add_record(vector<User*> &user,vector<Record*> &record,string id, Physical_location phy_val, Date date_val, Time time_val, int dur_val)
{
    int cross=0, rsize = record.size();
    for(int i=0;i<rsize;i++)
    {
        if( record[i]->get_phy_loc_obj() > phy_val)
        {
            break;
        }
        else if( record[i]->get_phy_loc_obj() < phy_val)
        {
            cross++;
        }
    }
    record.insert((record.begin() + cross), new Record(id, phy_val, time_val, dur_val, date_val));
    std::ofstream ofs;
    ofs.open("Record.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;
    myFile.open("Record.csv");
    for(int i=0;i<rsize;i++)
    {
        int hour;
        myFile<<record[i]->get_user_ID()<<","<<record[i]->get_building_no()<<","<<record[i]->get_room_no()<<","<<record[i]->get_hour()<<","<<
        record[i]->get_minute()<<","<<record[i]->get_duration()<<","<<record[i]->get_day()<<","<<record[i]->get_month()<<","<<record[i]->get_year()<<endl;
    }
    fstream file("log.txt",ios::in|ios::out|ios::app );
    file<<"Record "<<phy_val.get_physical_location()<<" at "<<time_val.get_time_24()<<" on "<<date_val.get_date()<<" was added by id: "<<id<<endl;
}

void delete_record(vector<User*> &user,vector<Record*> &record,string id, Physical_location phy_val, Date date_val, Time time_val, int dur_val)
{
    for(int i=0;i<record.size();i++)
    {
        if( record[i]->get_user_ID() == id && record[i]->get_phy_loc_obj() == phy_val && record[i]->get_time_obj() == time_val &&
            record[i]->get_duration() == dur_val && record[i]->get_date_obj() == date_val )
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
    for(int i=0;i<record.size();i++)
    {
        myFile<<record[i]->get_user_ID()<<","<<record[i]->get_building_no()<<","<<record[i]->get_room_no()<<","<<record[i]->get_hour()<<","<<record[i]->get_minute()<<","
        <<record[i]->get_duration()<<","<<record[i]->get_day()<<","<<record[i]->get_month()<<","<<record[i]->get_year()<<endl;
    }
    fstream file("log.txt",ios::in|ios::out|ios::app );
    file<<"Record "<<phy_val.get_physical_location()<<" at "<<time_val.get_time_24()<<" on "<<date_val.get_date()<<" was removed by id: "<<id<<endl;
}
/*
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
            Time rec_time = record[i]->get_time_obj();
            Time rec_end_time = (Time::convert_duration(record[i]->get_duration())+ rec_time);
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
