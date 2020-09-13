#ifndef CLASSROOM_MANAGEMENT_SYSTEM_USER_H
#define CLASSROOM_MANAGEMENT_SYSTEM_USER_H

#include "Physical_location.h"
#include "Date.h"
#include "Time.h"
#include "Record.h"
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
    void show_layout(void)
    {
        //Room and record are two seperated entities
        //They have one to many relationship
        //Physical_location is the foreign key in records
        //There will be two seperate files for rooms and records
        //
        //basically a display function which shows a list of all buildings (reads input from files)
        //you can then select a particular building and it will show all the rooms in that building
        //in our program, physical location is a combination of building number and room number
        //hence, if you want you can show the list of building no + room number at a time, provided that the list isn't too long
        //Remember to show them SERIALLY
        //you can then select a room and then it will show all the records in that room
        //you should make at least 2 seperate functions for this, one to show physical_locations
        //and another one to show all the records in a particular physical location
        //the second function will be like this
        //void display_records(Physical_location phy_loc_val)
    }
    //vector<Room*> search_record(vector<Record*> record_list, Physical_location phy_val, Time time_val, Date date_val, int dur_val);
    //bool clash(vector<Record*> record, Physical_location phy_val, Date date_val, Time time_val, int dur_val);
};


#endif //CLASSROOM_MANAGEMENT_SYSTEM_USER_H
