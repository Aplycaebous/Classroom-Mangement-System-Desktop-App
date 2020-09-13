#ifndef CLASSROOM_MANAGEMENT_SYSTEM_DATE_H
#define CLASSROOM_MANAGEMENT_SYSTEM_DATE_H
#include <iostream>
#include<ctime>
using namespace std;

class Date
{
protected:
    int day;
    int month;
    int year;
public:
    Date(void);
    Date(int day_val, int month_val, int year_val);
    bool check_day(int val);
    bool check_month(int val);
    bool check_year(int val);
    bool set_day(int val);
    bool set_month(int val);
    bool set_year(int val);
    int get_day();
    int get_month();
    int get_year();
    string get_date(); //returns date for displaying or file output
    bool operator > (Date date_comp); //latest date has greater value
    bool operator < (Date date_comp); //earlier date has smaller value
    bool operator == (Date date_comp);
    bool operator != (Date date_comp);
};


#endif //CLASSROOM_MANAGEMENT_SYSTEM_DATE_H
