#include "Time.h"

Time::Time()
{
    set_hour(0);
    set_minute(0);
}

Time::Time(int val_hour, int val_minute)
{
    if(!set_hour(val_hour)) //Invalid input
        set_hour(0);
    if(!set_minute(val_minute)) //Invalid input
        set_minute(0);
}

Time::Time(int val_hour, int val_minute, string format)
{
    int in_min = Time::convert_to_24(val_hour,val_minute,format).get_minute();
    int in_hour = Time::convert_to_24(val_hour,val_minute,format).get_hour();
    set_minute(in_min);
    set_hour(in_hour);
}

bool Time::check_hour_12(int val) //checks validity for input in 12 hour format
{
    if(val>0 && val<=12) return true;
    else return false;
}

bool Time::check_hour_24(int val) //checks validity for input in 24 hour format
{
    if(val>=0 && val<24) return true;
    else return false;
}

bool Time::check_minute(int val) //checks validity for minute
{
    if(val>=0 && val<60) return true;
    else return false;
}

bool Time::set_hour(int val) //returns false if hour wasn't set properly
{
    if(check_hour_24(val))
    {
        hour = val;
        return true;
    }
    else return false;
}

bool Time::set_minute(int val) //returns false if minute wasn't set properly
{
    if(check_minute(val))
    {
        minute = val;
        return true;
    }
    else return false;
}

int Time::get_hour()
{
    return hour;
}

int Time::get_minute()
{
    return minute;
}

string Time::get_time_12(void)
{
    // returns a time string in 12-hour format
    string s;
    if(hour>12)
    {
        if(hour-12 < 10) s += "0";
        s += to_string(hour-12);
    }
    else if(hour==0)
    {
        s += to_string(hour+12);
    }
    else
     {
        if(hour<10) s+= "0";
        s += to_string(hour);
     }
    s+=":";
    if(minute<10) s+= "0";
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

string Time::get_time_24(void)
{
    string s = "";
    if(get_hour()<10) s += "0";
    s += to_string(get_hour());
    s += ":";
    if(get_minute()<10) s += "0";
    s += to_string(get_minute());
    return s;
}

Time Time::operator+(Time val)
{
    Time temp;
    int extra_hour = 0;
    int total_min = this->get_minute() + val.get_minute();
    int total_hour = this->get_hour() + val.get_hour();
    if(total_min>=60)
    {
        temp.set_minute(total_min-60);
        extra_hour++;
    }
    else
     {
        temp.set_minute(total_min);
     }
    if(total_hour + extra_hour>=24)
    {
        temp.set_hour(total_hour + extra_hour - 24);
    }
    else
        temp.set_hour(hour = total_hour + extra_hour);
    return temp;
};

Time Time::convert_duration(int min)
{
        //returns a Time object for the duration in the minutes
        //no validity is done for the input so this function is expecting a valid input lesser than 24 hours
        //of course, no one will book a classroom for a duration close to 24 hours
    return Time(min/60, min%60);
}

Time Time::convert_to_24(int val_hour, int val_minute, string format)
{
    Time temp;
    if(!temp.set_minute(val_minute)) temp.set_minute(0);

    transform(format.begin(), format.end(), format.begin(), ::toupper); //In case of lower case input
    if((format == "AM"||format=="PM") && temp.check_hour_12(val_hour))
    {
        if((format == "PM") && val_hour != 12) //For any PM time except 12 PM
        {
            temp.set_hour(val_hour+12);
        }
        else if((format == "AM") && val_hour == 12) //For 12 AM specifically
        {
            temp.set_hour(0);
        }
        else temp.set_hour(val_hour);
    }
    else temp.set_hour(0);
    return temp;
}

bool Time::operator == (Time time_val)
{
    if(this->get_hour() == time_val.get_hour() && this->get_minute() == time_val.get_minute())
        return true;
    else return false;
}

bool Time::operator != (Time time_val)
{
    if(time_val == *this)
        return false;
    else return true;
}

bool Time::operator >(Time val)
{
    if(this->get_hour()>val.get_hour())
        return true;
    else if(this->get_hour()==val.get_hour())
    {
        if(this->get_minute()>val.get_minute())
            return true;
    }
    return false;
}

bool Time::operator <(Time val)
{
    if(this->get_hour()<val.get_hour())
        return true;
    else if(this->get_hour()==val.get_hour())
    {
        if(this->get_minute()<val.get_minute())
            return true;
    }
    return false;
}