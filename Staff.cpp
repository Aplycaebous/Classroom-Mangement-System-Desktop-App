#include "Staff.h"

Staff::Staff()
{
    staff_id = "";
}

Staff::Staff(string val_name, string val_pass, string val_staff_id):User(val_name,val_pass)
{
    set_id(val_staff_id);
}

Staff::Staff(User user_val, string staff_id_val):User(user_val)
{
    set_id(staff_id_val);
}

bool Staff::check_staff_id(string val)
{
    int vsize=val.size();
    if(vsize!=Metadata::get_staff_id_size())
    {
        //cout<<"Invalid staff ID"<<endl<<"Size must be "<<Metadata::get_staff_id_size()<<" characters exactly"<<endl;
        return false;
    }
    else
     {
        for(int i=0;i<vsize;i++)
        {
            if(!isdigit(val[i]))
            {
                //cout<<"Character number:"<<i+1<<" is not a digit"<<endl;
                return false;
            }
        }
        return true;
     }
}

bool Staff::set_id(string val)
{
    if(check_staff_id(val))
    {
        staff_id = val;
        return true;
    }
    else return false;
}

string Staff::get_id(void)
{
    return staff_id;
}
