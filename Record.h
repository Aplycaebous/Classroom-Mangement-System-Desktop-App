#ifndef RECORD_H
#define RECORD_H

#include "Room.h"
#include "RMSTime.h"
#include "Date.h"
#include "Student.h"
#include "Staff.h"

using namespace std;

class Record : public Physical_location, public Time, public Date
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
    string get_time_string(void);
    bool operator == (Record record_val);
    //static vector<Record*> list_user_records(string id, vector<Record*> rec_in);
    //friend void add_record(vector<User*> &user,vector<Record*> &record,string id, Physical_location phy_val, Date date_val, Time time_val, int dur_val);
    //friend void delete_record(vector<User*> &user,vector<Record*> &record,string id, Physical_location phy_val, Date date_val, Time time_val, int dur_val);
};

#endif // RECORD_H
