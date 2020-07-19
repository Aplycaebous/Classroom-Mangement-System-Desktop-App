#include<bits/stdc++.h>
#define room_no_size 3

using namespace std;

class Physical_location
{
private:
    string building_no;
    string room_no;
public:
    Physical_location()
    {
        set_building_no("1");
        set_room_no("101");
    }
    Physical_location(string buildval, string roomval)
    {
        set_building_no(buildval);
        set_room_no(roomval);
    }
    bool check_room(string s)
    {
        if(s.length()!=room_no_size)
        {
            return false;
        }
        else
        {
            for(int i=0;i<s.length();i++)
            {
                if(!isdigit(s[i]))
                {
                    return false;
                }
            }
            return true;
        }
    }
    void set_building_no(string val)
    {
        //Since IUT has 3 academic buildings only
        if(val == "1" || val == "2" ||val == "3" )
            building_no = val;
        else
        {
            cout<<"Wrong building number"<<endl;
            building_no = "1";
        }
    }
    void set_room_no(string val)
    {
        if(check_room(val))
        {
            room_no = val;
        }
        else
        {
            cout<<"Invalid room number"<<endl;
            room_no = "101";
        }
    }
    string get_building_no(void)
    {
        return building_no;
    }
    string get_room_no(void)
    {
        return room_no;
    }
};

class Time
{
private:
    int hour;
    int minute;
public:
    //Time is stored in 24 hour format to simplify calculations
    //Input is taken in 12 hour format
    Time()
    {
        set_hour(1);
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
        if(val>0 && val<=12)
        {
            hour = val;
        }
        else
        {
            cout<<"Invalid hour for time"<<endl;
            hour = 1;
        }
    }
    void set_minute(int val)
    {
        if(val>=0 && val<60)
            minute = val;
        else
        {
            cout<<"Invalid minute for time"<<endl;
            minute = 0;
        }
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
    string userid;
    string name;
    string password;
public:
    User()
    {
        set_userid("0");
        set_name("");
        set_password("dsf5438534");
    }
    User(string idval, string nameval, string passval)
    {
        set_userid(idval);
        set_name(nameval);
        set_password(passval);
    }
    void set_userid(string value)
    {
        userid = value;
    }
    void set_name(string value)
    {
        name = value;
    }
    void set_password(string val)
    {
        password = val;
    }
    string get_userid(void)
    {
        return userid;
    }
    string get_name(void)
    {
        return name;
    }
    string get_password(void)
    {
        return password;
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
        if(val<32 && val>0)
            day = val;
        else
        {
            cout<<"Invalid day for date"<<endl;
            day = 1;
        }
    }
    void set_month(int val)
    {

        if(val<13 && val>0)
            month = val;
        else
        {
            cout<<"Invalid month for date"<<endl;
            month = 1;
        }
    }
    void set_year(int val)
    {
        if(val>2019)
            year = val;
        else
        {
            cout<<"Invalid year for date"<<endl;
            year = 1970;
        }
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

class Record:public Physical_location, public Time, public Date
{
private:
    int duration;
    string user_ID;

public:
    Record(void)
    {
        duration = 0;
        user_ID = "";
    }
    Record(string user_val, string build_val, string room_val, int hour_val, int min_val, string form_val,
    int dur_val, int day_val, int mon_val, int year_val)
    :Physical_location(build_val, room_val),Time(hour_val, min_val, form_val),
    Date(day_val,mon_val,year_val)
    {
        set_duration(dur_val);
        set_user_ID(user_val);
    }
    void set_duration(int value)
    {
        duration = value;
    }
    void set_user_ID(string val)
    {
        user_ID = val;
    }
    int get_duration(void)
    {
        return duration;
    }
    string get_user_ID(void)
    {
        return user_ID;
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

class Room: public Physical_location, public Equipments
{
private:
    int capacity;
    vector<Record> record_vec;
    //aita na korae class er array ba pointers use korte parish
    //oita better hoi since sir classe koraise

public:
    Room()
    {
        set_capacity(0);
    }
    Room(string build_val, string room_val, bool ac_val, int board_val, bool proj_val, int cap_val):
    Physical_location(build_val, room_val),Equipments(ac_val, board_val, proj_val)
    {
        set_capacity(cap_val);
    }
    void set_capacity(int val)
    {
        capacity = val;
    }
    int get_capacity(void)
    {
        return capacity;
    }
    vector<Record> get_record_vec(void)
    {
        return record_vec;
    }
    //show layout
    //find classroom/search
    //log class
    //book + delete entry
};

int main()
{
    int no_of_users = 1;
    int val1,val2,val3;
    string a,b;
    User* user[no_of_users];
    user[0] = new User("180041120","Farhan","farhan123");
    cout<<"Enter your user ID:"<<endl;
    cin>>a;
    /*
    for(int i=0;i<no_of_users;i++)
    {
        if(user[i]->get_userid()==a && user)
        {
            string user_id = a;
            cout<<"Enter your password:"<<endl;
            cin>>b;
            if(user[i]->get_password()==b)
            {
                //add a record AFTER validating function
                //just for testing, this won't be implemented in the actual program
                //We will search considering factors like capacity, equipments, record time etc;
                //After cross-checking the factors, if the classroom meets the given requirements
                //we use this function to add the record
                Record record;
                record.set_user_ID(user_id);
                cout<<"Enter the physical location (building number + room number)"<<endl;
                cin>>a>>b;
                record.set_phy_loc(a,b);
                cout<<"Enter the Date(day,month,year)"<<endl;
                cin>>val1>>val2>>val3;
                record.set_date(val1,val2,val3);
                cout<<"Enter the time(hour, min, format)"<<endl;
                cin>>val1>>val2>>a;
                record.set_st_time(val1,val2,a);
                cout<<"Enter the duration"<<endl;
                cin>>val1;
                record.set_duration(val1);
            }
            else cout<<"Wrong password"<<endl;
        }
    }
     */




}