#include<bits/stdc++.h>
using namespace std;

class Physical_location
{
private:
    string building_no;
    string room_no;
public:
    Physical_location()
    {
        set_building_no("0");
        set_room_no("0");
    }
    Physical_location(string buildval, string roomval)
    {
        set_building_no(buildval);
        set_room_no(roomval);
    }
    void set_building_no(string val)
    {
        building_no = val;
    }
    void set_room_no(string val)
    {
        room_no = val;
    }
    void set_location(string buildval, string roomval)
    {
        set_building_no(buildval);
        set_room_no(roomval);
    }
    string get_building_no(void)
    {
        return building_no;
    }
    string get_room_no(void)
    {
        return room_no;
    }
    string get_location(void)
    {
        return building_no + " " + room_no;
    }
};

class Time
{
private:
    int hour;
    int minute;
public:
    Time()
    {
        set_hour(0);
        set_minute(0);
    }
    Time(int val_hour, int val_minute, string format)
    {
        set_hour(val_hour);
        set_minute(val_minute);
        set_format(format);
    }
    void set_hour(int val)
    {
        hour = val;
    }
    void set_minute(int val)
    {
        minute = val;
    }
    void set_format(string val)
    {
        transform(val.begin(), val.end(), val.begin(), ::toupper);
        if(val == "AM"||val=="PM")
        {
            if(val == "PM")
            {
                set_hour(get_hour()+12);
            }
        }
        else
        {
            cout<<"Invalid input"<<endl;
        }
    }
    void set_time(int val_hour, int val_minute, string format)
    {
        set_hour(val_hour);
        set_minute(val_minute);
        set_format(format);
    }
    int get_hour()
    {
        return hour;
    }
    int get_minute()
    {
        return minute;
    }
};

class User
{
private:
    int userid;
    string name;
public:
    User()
    {
        set_userid(0);
        set_name("");
    }
    User(int idval, string nameval)
    {
        set_userid(idval);
        set_name(nameval);
    }
    void set_userid(int value)
    {
        userid = value;
    }
    void set_name(string value)
    {
        name = value;
    }
    void set_user(int idval, string nameval)
    {
        set_userid(idval);
        set_name(nameval);
    }
    int get_userid(void)
    {
        return userid;
    }
    string get_name(void)
    {
        return name;
    }
};

class Date
{
private:
    int day;
    int month;
    int year;
public:
    Date()
    {
        set_day(1);
        set_month(1);
        set_year(1970);
    }
    Date(int day_val, int month_val, int year_val)
    {
        set_day(day_val);
        set_month(month_val);
        set_year(year_val);
    }
    void set_day(int val)
    {
        day = val;
    }
    void set_month(int val)
    {
        month = val;
    }
    void set_year(int val)
    {
        year = val;
    }
    void set_date(int day_val, int month_val, int year_val)
    {
        set_day(day_val);
        set_month(month_val);
        set_year(year_val);
    }
    int get_day()
    {
        return day;
    }
    int get_month()
    {
        return month;
    }
    int get_year()
    {
        return year;
    }
};

class Record
{
private:
    Physical_location physical_location;
    Time start_time;
    int duration;
    Date date;
    User user;

public:
    void set_phy_loc(string build_val, string room_no)
    {
        physical_location.set_location(build_val,room_no);
    }
    void set_st_time(int hour_val, int minute_val, string format_val)
    {
        start_time.set_time(hour_val,minute_val,format_val);
    }
    void set_duration(int value)
    {
        duration = value;
    }
    void set_user(int id_val, string name_val)
    {
        user.set_user(id_val,name_val);
    }
    void set_date(int day_val, int month_val, int year_val)
    {
        date.set_date(day_val, month_val, year_val);
    }
};

class Equipments
{
private:
    bool AC;
    int boards;
    bool projector;
public:
    Equipments()
    {
        set_ac(0);
        set_boards(0);
        set_projector(0);
    }
    Equipments(bool ac_val, int boards_val, bool pro_val)
    {
        set_ac(ac_val);
        set_boards(boards_val);
        set_projector(pro_val);
    }
    void set_ac(bool val)
    {
        AC = val;
    }
    void set_boards(int val)
    {
        if(val<0) cout<<"Invalid no. of boards"<<endl;
        else boards = val;
    }
    void set_projector(bool val)
    {
        projector = val;
    }
    void set_equipments(bool ac_val, int boards_val, bool pro_val)
    {
        set_ac(ac_val);
        set_boards(boards_val);
        set_projector(pro_val);
    }
    bool get_ac()
    {
        return AC;
    }
    int get_boards()
    {
        return boards;
    }
    bool get_projector()
    {
        return projector;
    }
};


class Room
{
private:
    Physical_location physicallocation;
    int capacity;
    Equipments equipments;
    vector<Record> record_vec;

public:
    void set_loc(string building_val, string room_val)
    {
        physicallocation.set_location(building_val,room_val);
    }
    void set_capacity(int val)
    {
        capacity = val;
    }
    void set_equipments(bool ac_val, int boards_val, bool projector_val)
    {
        equipments.set_equipments(ac_val,boards_val, projector_val);
    }

    string get_loc(void)
    {
        return physicallocation.get_location();
    }
    //show layout
    //find classroom/search
    //edit log class
};




int main()
{
    std::cout << "Hello, World!" << std::endl;
    return 0;
}