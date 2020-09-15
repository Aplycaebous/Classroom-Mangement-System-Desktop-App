#include "Record.h"

Record::Record()
{
    duration = 0;
    user_ID = "";
}

Record::Record(string user_val, Physical_location phy_val, Time time_val,int dur_val, Date date_val):Physical_location(phy_val),Time(time_val),Date(date_val)
{
    if(!set_duration(dur_val)) duration = 0;
    if(!set_user_ID(user_val)) user_ID = "";
}

bool Record::set_duration(int value) //In minutes
{
    if(value<=360 && value>0) //can't book classes for longer than 6 hours
    {
        duration = value;
        return true;
    }
    else return false;
}

bool Record::set_user_ID(string val)
{
    if(Student::check_student_id(val) || Staff::check_staff_id(val))
    {
        user_ID = val;
        return true;
    }
    else return false;
}

int Record::get_duration(void)
{
    return duration;
}

string Record::get_user_ID(void)
{
    return user_ID;
}

Physical_location Record::get_phy_loc_obj(void)
{
    return Physical_location(this->get_building_no(),this->get_room_no());
}

Time Record::get_time_obj(void)
{
    return Time(this->get_hour(),this->get_minute());
}

Date Record::get_date_obj(void)
{
    return Date(this->get_day(),this->get_month(),this->get_year());
}

bool Record::operator == (Record record_val)
{
    if(this->get_date_obj() == record_val.get_date_obj() && this->get_time_obj() == record_val.get_time_obj()
       && this->get_phy_loc_obj() == record_val.get_phy_loc_obj())
    {
        if(this->get_duration()==record_val.get_duration() && this->get_user_ID() == record_val.get_user_ID())
            return true;
        else return false;
    }
    else return false;
}

string Record::get_time_string(void)
{
    string s="";
    s+=this->get_time_12()+" to ";
    Time last_time=this->get_time_obj()+convert_duration(this->get_duration());

    s+=last_time.get_time_12();
    return s;
}
/*
void add_record(vector<Record*> &record,string id, Physical_location phy_val, Date date_val, Time time_val, int dur_val)
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
    ofs.open("C:\\Users\\tasni\\Documents\\RMS\\Record.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;
    myFile.open("C:\\Users\\tasni\\Documents\\RMS\\Record.csv");
    for(int i=0;i<rsize;i++)
    {
        myFile<<record[i]->get_user_ID()<<","<<record[i]->get_building_no()<<","<<record[i]->get_room_no()<<","<<record[i]->get_hour()<<","<<
        record[i]->get_minute()<<","<<record[i]->get_duration()<<","<<record[i]->get_day()<<","<<record[i]->get_month()<<","<<record[i]->get_year()<<endl;
    }
    fstream file("C:\\Users\\tasni\\Documents\\RMS\\log.txt",ios::in|ios::out|ios::app );
    file<<"Record "<<phy_val.get_physical_location()<<" at "<<time_val.get_time_24()<<" on "<<date_val.get_date()<<" was added by id: "<<id<<endl;
}

void delete_record(vector<Record*> &record,string id, Physical_location phy_val, Date date_val, Time time_val, int dur_val)
{
    int rsize=record.size();
    for(int i=0;i<rsize;i++)
    {
        if( record[i]->get_user_ID() == id && record[i]->get_phy_loc_obj() == phy_val && record[i]->get_time_obj() == time_val &&
            record[i]->get_duration() == dur_val && record[i]->get_date_obj() == date_val )
        {
            record.erase(record.begin()+i);
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
        myFile<<record[i]->get_user_ID()<<","<<record[i]->get_building_no()<<","<<record[i]->get_room_no()<<","<<record[i]->get_hour()<<","<<record[i]->get_minute()<<","
        <<record[i]->get_duration()<<","<<record[i]->get_day()<<","<<record[i]->get_month()<<","<<record[i]->get_year()<<endl;
    }
    fstream file("C:\\Users\\tasni\\Documents\\RMS\\log.txt",ios::in|ios::out|ios::app );
    file<<"Record "<<phy_val.get_physical_location()<<" at "<<time_val.get_time_24()<<" on "<<date_val.get_date()<<" was removed by id: "<<id<<endl;
}*/

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

/*bool clash(vector<Record*> record, Physical_location phy_val, Date date_val, Time time_val, int dur_val)
{
    vector<Room*> record_give;
    int rsize=record.size();
    for(int i=0;i<rsize;i++)
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
}*/
