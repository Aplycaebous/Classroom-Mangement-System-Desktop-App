#ifndef CLASSROOM_MANAGEMENT_SYSTEM_TIME_H
#define CLASSROOM_MANAGEMENT_SYSTEM_TIME_H
#include <iostream>
#include <algorithm>
using namespace std;

class Time
{
    //Time is stored in 24-hour format
protected:
    int hour;
    int minute;
public:
    Time();
    Time(int val_hour, int val_minute);
    Time(int val_hour, int val_minute, string format);
    bool check_hour_12(int val); //checks validity for input in 12 hour format
    bool check_hour_24(int val); //checks validity for input in 24 hour format
    bool check_minute(int val); //checks validity for minute
    bool set_hour(int val); //returns false if hour wasn't set properly
    bool set_minute(int val); //returns false if minute wasn't set properly
    int get_hour();
    int get_minute();
    string get_time_12(void); //returns a string of the time in 12-h format
    string get_time_24(void); //returns a string of the time in 24-h format
    static Time convert_duration(int min);
    static Time convert_to_24(int val_hour, int val_minute, string format); //converts a 12-h time value set to a time object
    Time operator + (Time val);
    bool operator == (Time time_val);
    bool operator != (Time time_val);
};


#endif //CLASSROOM_MANAGEMENT_SYSTEM_TIME_H
