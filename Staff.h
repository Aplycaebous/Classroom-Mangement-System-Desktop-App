#ifndef CLASSROOM_MANAGEMENT_SYSTEM_STAFF_H
#define CLASSROOM_MANAGEMENT_SYSTEM_STAFF_H
#include <iostream>
#include "User.h"
#include "Metadata.h"
using namespace std;

class Staff:public User
{
protected:
    string staff_id;
public:
    Staff();
    Staff(string val_name, string val_pass, string val_staff_id);
    Staff(User user_val, string staff_id_val);
    static bool check_staff_id(string val);
    bool set_staff_id(string val);
    string get_staff_id(void);
    bool login(string id_val, string pass_val);
};


#endif //CLASSROOM_MANAGEMENT_SYSTEM_STAFF_H
