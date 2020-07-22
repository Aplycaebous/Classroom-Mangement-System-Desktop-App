#include<bits/stdc++.h>
#include<ctime>
using namespace std;

const int room_no_size = 3; //Const int are used instead of macros since they ensure better type safety
const int no_of_buildings = 3; //Macros are text replacers which often replace unwanted texts

class Physical_location
{
protected:
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
    bool check_room_no(string s)
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
    bool check_build_no(string s)
    {
        if(s.size()==1)
        {
            char c = s[0];
            int n = static_cast<int>(c);
            if(n>0 && n<= no_of_buildings)
                return true;
        }
        return false;
    }
    bool set_building_no(string val)
    {
        if(check_build_no(val))
        {
            building_no = val;
            return true;
        }
        else
        {
            cout<<"Wrong building number"<<endl;
            building_no = "1";
            return false;
        }
    }
    bool set_room_no(string val)
    {
        if(check_room_no(val))
        {
            room_no = val;
            return true;
        }
        else
        {
            cout<<"Invalid room number"<<endl;
            room_no = "101";
            return false;
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
    string get_physical_location(void)
    {
        string s = building_no + "-" + room_no;
        return s;
    }
};

class Time
{
protected:
    int hour;
    int minute;
    //These two functions shouldn't be accessed by anyone outside this class to avoid storing undesirable values
    void set_hour(int val)
    {
        hour = val;
    }
    void set_minute(int val)
    {
        minute = val;
    }
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
        set_hour_check(val_hour);
        set_minute_check(val_minute);
        set_format(format);
    }
    bool set_hour_check(int val)
    {
        //sets the hour along with checking the validity
        if(val>0 && val<=12)
        {
            set_hour(val);
            return true;
        }
        else
        {
            cout<<"Invalid hour for time"<<endl;
            set_hour(1);
            return false;
        }
    }
    bool set_minute_check(int val)
    {
        //sets the minute along with checking the validity
        if(val>=0 && val<60)
        {
            set_minute(val);
            return true;
        }
        else
        {
            cout<<"Invalid minute for time"<<endl;
            set_minute(0);
            return false;
        }
    }
    bool set_format(string val)
    {
        transform(val.begin(), val.end(), val.begin(), ::toupper); //In case of lower case input
        if(val == "AM"||val=="PM")
        {
            if(val == "PM")
            {
                set_hour(get_hour()+12);
            }
            else
            {
                set_hour(get_hour());
            }
            return true;
        }
        else
        {
            cout<<"Invalid time format"<<endl;
            cout<<"Please enter AM or PM only"<<endl;
            return false;
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
    Time operator+(Time val)
    {
        Time temp;
        int extra_hour = 0;
        int total_min = this->get_minute()+val.get_minute();
        int total_hour = this->get_hour()+val.get_hour();
        if(total_min>=60)
        {
            temp.set_minute(total_min-60);
            extra_hour++;
        }
        else
        {
            set_minute(total_min);
        }
        if(total_hour + extra_hour>=24)
        {
            temp.set_hour(total_hour + extra_hour - 24);
        }
        else
            temp.set_hour(total_hour + extra_hour);
        return temp;
    };
    Time convert_duration(int min)
    {
        //returns a Time object for the duration in the minutes
        Time temp;
        temp.set_minute(min%60);
        temp.set_hour(min/60);
        return temp;
    }
    string get_time(void)
    {
        // returns a time string in 12-hour format
        string s;
        if(hour>12)
        {
            s+=to_string(hour-12);
        }
        else if(hour==0)
        {
            s+=to_string(hour+12);
        }
        else
        {
            s+=to_string(hour);
        }
        s+=":";
        s+=to_string(minute);
        s+=" ";
        if(hour>=12)
        {
            s+="PM";
        }
        else
        {
            s+="AM";
        }
        return s;
    }
};

class Date
{
protected:
    int day;
    int month;
    int year;
public:
    Date(void)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        set_day(ltm->tm_mday);
        set_month(1 + ltm->tm_mon);
        set_year(1900 + ltm->tm_year);
    }
    Date(int day_val, int month_val, int year_val)
    {
        set_day(day_val);
        set_month(month_val);
        set_year(year_val);
    }
    bool set_day(int val)
    {
        if(val<32 && val>0) {
            day = val;
            return true;
        }
        else
        {
            cout<<"Invalid day for date"<<endl;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            set_day(ltm->tm_mday);
            cout<<"Value set to current day by default"<<endl;
            return false;
        }
    }
    bool set_month(int val)
    {
        if(val<13 && val>0)
        {
            month = val;
            return true;
        }
        else
        {
            cout<<"Invalid month for date"<<endl;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            set_month(1 + ltm->tm_mon);
            cout<<"Value set to current month by default"<<endl;
            return false;
        }
    }
    bool set_year(int val)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        if(val>=1900 + ltm->tm_year)
        {
            year = val;
            return true;
        }
        else
        {
            cout<<"Invalid year for date"<<endl;
            set_year(1900 + ltm->tm_year);
            cout<<"Value set to current year by default"<<endl;
            return false;
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
    string get_date() //returns date for displaying or file output
    {
        string s;
        s += to_string(day);
        s += "-";
        s += to_string(month);
        s += "-";
        s += to_string(year);
        return s;
    }
};

class Admin
{
private:
    string username;
    string password;
    string contact_no;
    string email_address;
public:
    Admin()
    {
        set_username("system");
        set_password("system123");
    }
    Admin(string user_val, string pass_val, string cont_val,string email_val)
    {
        set_username(user_val);
        set_password(pass_val);
        set_contact_no(cont_val);
        set_email_address(email_val);
    }
    bool set_username(string val)
    {
        if(val.length()>32)
        {
            cout<<val<<" is an invalid username"<<endl;
            cout<<"Username must not contain more than 32 characters"<<endl;
            return false;
        }
        else if(val.length()>=6)
        {
            username = val;
            return true;
        }
        else
        {
            cout<<val<<" is an invalid username"<<endl;
            cout<<"Username must contain 6 characters at least"<<endl;
            return false;
        }
    }
    bool set_password(string val)
    {
        if(check_password(val))
        {
            set_password(val);
            return true;
        }
        return false;
    }
    bool set_contact_no(string val)
    {
        if(check_contact_no_validity(val))
        {
            contact_no = val;
            return true;
        }
        else
        {
            cout << "Invalid contact number" << endl;
            cout << "Make sure you DON'T write the country code before the number" << endl;
            return false;
        }
    }
    void set_email_address(string val)
    {
        email_address = val;
    }
    string get_username(void)
    {
        return username;
    }
    string get_password(void)
    {
        return password;
    }
    bool check_password(string val)
    {
        if(val.length()>32)
        {
            cout<<"Password for "<<get_username()<<" is too long"<<endl;
            cout<<"Admin password must not contain more than 32 characters"<<endl;
            return false;
        }
        else if(val.length()<8)
        {
            cout<<"Password for "<<get_username()<<" is too short"<<endl;
            cout<<"Admin password must contain 8 characters at least"<<endl;
            return false;
        }
        else
        {
            //check password complexity
            //must contain at least one character and one digit or something like that
            //admin password must be stronger than user password; make sure of that
            return true;
        }
    }
    bool check_contact_no_validity(string val)
    {
        if(val.size()==11)
        {
            for(int i=0;i<val.size();i++)
            {
                if(!isdigit(val[i]))
                {
                    return false;
                }
            }
            return true;
        }
        else
            return false;
    }
    bool login(string user_val, string pass_val)
    {
        if(user_val == get_username() && pass_val == get_password())
        {
            return true;
        }
        else
        {
            cout<<"Wrong username/password"<<endl;
            return false;
        }
    }
    //In main function we create admin with username and password
    //Admin can read and load classrooms
    //Admin can read and load user_list
    //Admin can check log file
};

class User
{
protected:
    string name;
    string password;
public:
    User()
    {
        set_name("");
        set_password("password123");
    }
    User(string nameval, string passval)
    {
        set_name(nameval);
        set_password(passval);
    }
    void set_name(string value)
    {
        name = value;
    }
    bool set_password(string val)
    {
        if(check_password(val))
        {
            password = val;
            return true;
        }
        return false;
    }
    string get_name(void)
    {
        return name;
    }
    string get_password(void)
    {
        return password;
    }
    bool check_password(string val)
    {
        if(val.length()>32)
        {
            cout<<"Password for is too long"<<endl;
            cout<<"User password must not contain more than 32 characters"<<endl;
            return false;
        }
        else if(val.length()<6)
        {
            cout<<"Password is too short"<<endl;
            cout<<"User password must contain 6 characters at least"<<endl;
            return false;
        }
        else
        {
            //check password complexity
            //must contain at least one character and one digit or something like that
            return true;
        }
    }
    virtual bool login() = 0;
};

class Student:public User
{
protected:
    string student_id;
    //student ID theke year, dept derive korae store korar option porae implement kora jai
    //staff der jonno similar kichu kora jai kintu porae korbo
    bool cr; //if CR or not
public:
    Student()
    {
        set_student_id("0");
        set_cr(false);
    }
    Student(string val_name, string val_pass, string val_std_id, bool val_cr):User(val_name,val_pass)
    {
        set_student_id(val_std_id);
        set_cr(val_cr);
    }
    void set_student_id(string val)
    {
        student_id = val;
    }
    void set_cr(bool val)
    {
        cr = val;
    }
    string get_student_id(void)
    {
        return student_id;
    }
    bool get_cr(void)
    {
        return  cr;
    }
    bool login(string id_val, string pass_val)
    {
        if(id_val == get_student_id() && pass_val == get_password())
        {
            return true;
        }
        else return false;
    }
};

class Staff:public User
{
protected:
    string staff_id;
public:
    Staff()
    {
        set_staff_id("0");
    }
    Staff(string val_name, string val_pass, string val_staff_id):User(val_name,val_pass)
    {
        set_staff_id(val_staff_id);
    }
    void set_staff_id(string val)
    {
        staff_id = val;
    }
    string get_staff_id(void)
    {
        return staff_id;
    }
    bool login(string id_val, string pass_val)
    {
        if(id_val == get_staff_id() && pass_val == get_password())
        {
            return true;
        }
        else return false;
    }
};

class Record:public Physical_location, public Time, public Date
{
protected:
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
    bool set_duration(int value) //In minutes
    {
        if(duration<=360) {
            duration = value;
            return true;
        }
        else
        {
            cout<<"Invalid time duration: Can not book records longer than 6 hours"<<endl;
            return false;
        }
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
protected:
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
    bool set_boards(int val)
    {
        if(val<0 || val>=10)
        {
            cout<<"Invalid no. of boards"<<endl;
            return false;
        }
        else
        {
            boards = val;
            return true;
        }
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
protected:
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
    bool set_capacity(int val)
    {
        if(val<0)
        {
            cout<<"Invalid capacity"<<endl;
            return false;
        }
        else
        {
            capacity = val;
            return true;
        }
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
    /*
    int no_of_users = 1;
    int val1,val2,val3;
    string a,b;
    User* user[no_of_users];
    user[0] = new User("180041120","Farhan","farhan123");
    cout<<"Enter your user ID:"<<endl;
    cin>>a;

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