#ifndef CLASSROOM_MANAGEMENT_SYSTEM_STUDENT_H
#define CLASSROOM_MANAGEMENT_SYSTEM_STUDENT_H
#include "Metadata.h"
#include "User.h"
class Student:public User
{
protected:
    string student_id;
    bool cr; //if CR or not
public:
    Student();
    Student(string val_name, string val_pass, string val_std_id, bool val_cr);
    Student(User user_val, string std_id_val, bool val_cr);
    static bool check_student_id(string val);
    bool set_id(string val);
    void set_cr(bool val);
    string get_id(void);
    bool get_cr(void);
};

#endif //CLASSROOM_MANAGEMENT_SYSTEM_STUDENT_H
