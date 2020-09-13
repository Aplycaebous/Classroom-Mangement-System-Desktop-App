#include "Student.h"

Student::Student()
{
    student_id = "";
    set_cr(false);
}

Student::Student(string val_name, string val_pass, string val_std_id, bool val_cr):User(val_name,val_pass)
{
    if(!set_student_id(val_std_id)) student_id = "";
    set_cr(val_cr);
}

Student::Student(User user_val, string val_std_id, bool val_cr):User(user_val)
{
    if(!set_student_id(val_std_id)) student_id = "";
    set_cr(val_cr);
}

bool Student::check_student_id(string val)
{
    if(val.size() != Metadata::get_student_id_size()) return false;
    else
    {
        for(int i=0;i<val.size();i++)
        {
            if(!isdigit(val[i]))
            {
                return false;
            }
        }
        return true;
    }
}

bool Student::set_student_id(string val)
{
    if(check_student_id(val))
    {
        student_id = val;
        return true;
    }
    else return false;
}

void Student::set_cr(bool val)
{
    cr = val;
}

string Student::get_student_id(void)
{
    return student_id;
}

bool Student::get_cr(void)
{
    return  cr;
}

bool Student::login(string id_val, string pass_val)
{
    if(id_val == get_student_id() && pass_val == get_password())
    {
        return true;
    }
    else return false;
}