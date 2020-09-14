#ifndef CLASSROOM_MANAGEMENT_SYSTEM_RECORD_H
#define CLASSROOM_MANAGEMENT_SYSTEM_RECORD_H

#include <iostream>
#include "Time.h"
#include "Physical_location.h"
#include "Date.h"
#include <bits/stdc++.h>
#include<fstream>
#include "Student.h"
#include "Staff.h"
using namespace std;

class Record: public Time, public Physical_location, public Date
{
protected:
    int duration;
    string user_ID;
public:
    Record();
    Record(string user_val, Physical_location phy_val, Time time_val,int dur_val, Date date_val);
    bool set_duration(int value); //In minutes
    bool set_user_ID(string val);
    int get_duration(void);
    string get_user_ID(void);
    Physical_location get_phy_loc_obj(void);
    Time get_time_obj(void);
    Date get_date_obj(void);
    bool operator == (Record record_val);
    static vector<Record*> list_user_records(string id, vector<Record*> rec_in);
};


#endif //CLASSROOM_MANAGEMENT_SYSTEM_RECORD_H
