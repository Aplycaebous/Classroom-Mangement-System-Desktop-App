#ifndef USER_H
#define USER_H

#include "Physical_location.h"
#include "Date.h"
#include "RMSTime.h"
#include "Room.h"
#include <vector>
#include <fstream>
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
    virtual bool set_id(string val) = 0;
    virtual string get_id(void) = 0;
};

#endif // USER_H
