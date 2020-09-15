#include "User.h"

User::User()
{
    set_name("");
    set_password("password123");
}

User::User(string nameval, string passval)
{
    set_name(nameval);
    if(!set_password(passval)) set_password("password123"); //show error password set to default value password123
}

bool User::check_password(string val)
{
    if(val.length()>=24 || val.length()<6)
    return false;
    else
    {
        //check password complexity with more if conditions
        //must contain at least one character and one digit or something like that
        return true;
    }
}

void User::set_name(string value)
{
    name = value;
}

bool User::set_password(string val)
{
    if(check_password(val))
    {
        password = val;
        return true;
    }
    return false;
}

string User::get_name(void)
{
    return name;
}

string User::get_password(void)
{
    return password;
}

