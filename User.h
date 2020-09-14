#ifndef CLASSROOM_MANAGEMENT_SYSTEM_USER_H
#define CLASSROOM_MANAGEMENT_SYSTEM_USER_H

#include "Physical_location.h"
#include "Date.h"
#include "Time.h"
#include "Record.h"
#include "Room.h"
#include <bits/stdc++.h>
#include <iostream>
#include<fstream>
using namespace std;

class User
{
protected:
    string name;
    string password;
public:
    User();
    User(string nameval, string passval);
    bool check_password(string val);
    void set_name(string value);
    bool set_password(string val);
    string get_name(void);
    string get_password(void);
    virtual bool login(string id_val, string pass_val) = 0; //Make user an abstract class
    static void add_record(vector<User*> &user,vector<Record*> &record,string id, Physical_location phy_val, Date date_val, Time time_val, int dur_val);
    static void delete_record(vector<User*> &user,vector<Record*> &record,string id, Physical_location phy_val, Date date_val, Time time_val, int dur_val);

    //vector<Room*> search_record(vector<Record*> record_list, Physical_location phy_val, Time time_val, Date date_val, int dur_val);
    //bool clash(vector<Record*> record, Physical_location phy_val, Date date_val, Time time_val, int dur_val);
};


#endif //CLASSROOM_MANAGEMENT_SYSTEM_USER_H
