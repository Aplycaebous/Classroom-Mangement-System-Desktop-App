#include "Date.h"

Date::Date(void)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    set_day(ltm->tm_mday);
    set_month(1 + ltm->tm_mon);
    set_year(1900 + ltm->tm_year);
}

Date::Date(int day_val, int month_val, int year_val)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    //In case the day, month or year doesn't receive appropriate values, it gets set to default value
    if(!set_day(day_val)) set_day(ltm->tm_mday);
    if(!set_month(month_val)) set_month(1 + ltm->tm_mon);
    if(!set_year(year_val)) set_year(1900 + ltm->tm_year);
}

bool Date::check_day(int val)
{
    if(val<32 && val>0)
    {
        day = val;
        return true;
    }
    else return false;
}

bool Date::check_month(int val)
{
    if (val < 13 && val > 0)
    {
        month = val;
        return true;
    }
    else return false;
}

bool Date::check_year(int val)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    if(val>=1900 + ltm->tm_year)
    {
        year = val;
        return true;
    }
    else return false;
}

bool Date::set_day(int val)
{
    if(check_day(val))
    {
        day = val;
        return true;
    }
    else return false;
}

bool Date::set_month(int val)
{
    if(check_month(val))
    {
        month = val;
        return true;
    }
    else return false;
}

bool Date::set_year(int val)
{
    if(check_year(val))
    {
        year = val;
        return true;
    }
    else return false;
}

int Date::get_day()
{
    return day;
}

int Date::get_month()
{
    return month;
}

int Date::get_year()
{
    return year;
}

string Date::get_date() //returns date for displaying or file output
{
    string s;
    s += to_string(day);
    s += "-";
    s += to_string(month);
    s += "-";
    s += to_string(year);
    return s;
}

bool Date::operator > (Date date_comp) //latest date has greater value
{
    if(this->get_year() > date_comp.get_year())
        return true;
    else if (this->get_year() == date_comp.get_year())
    {
        if (this->get_month() > date_comp.get_month())
            return true;
        else if (this->get_month() == date_comp.get_month())
        {
            if (this->get_day() > date_comp.get_day())
                return true;
            else return false;
        }
        else return false;
    }
    else return false;
}

bool Date::operator< (Date date_comp) //earlier date has smaller value
{
    if(this->get_year() < date_comp.get_year())
        return true;
    else if (this->get_year() == date_comp.get_year())
    {
        if (this->get_month() < date_comp.get_month())
            return true;
        else if (this->get_month() == date_comp.get_month())
        {
            if (this->get_day() < date_comp.get_day())
                return true;
            else return false;
        }
        else return false;
    }
    else return false;
}

bool Date::operator == (Date date_comp)
{
    if(this->get_year() == date_comp.get_year() && this->get_month() == date_comp.get_month() && this->get_day() == date_comp.get_day())
        return true;
    else return false;
}

bool Date::operator != (Date date_comp)
{
    if(date_comp == *this)
        return false;
    else return true;
}
