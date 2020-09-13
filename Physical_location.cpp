#include "Physical_location.h"
#include "Metadata.h"

Physical_location::Physical_location()
{
    building_no = "";
    room_no = "";
}

Physical_location::Physical_location(string buildval, string roomval)
{
    if(!set_building_no(buildval)) building_no = "";
    if(!set_room_no(roomval)) room_no = "";
}

bool Physical_location::check_room_no(string val)
{
    //checks if the size of string is okay
    if(val.size() != Metadata::get_room_no_size()) return false;
    else
    {
        for(int i=0;i<val.size();i++) //checks if every character is a digit or not
        {
            if(!isdigit(val[i])) return false;
        }
        return true;
    }
}

bool Physical_location::check_build_no(string val)
{
    //checks if the size of string is okay
    if(val.size() != Metadata::get_building_no_size()) return false;
    else
    {
        for(int i=0;i<val.size();i++) //checks if every character is a digit or not
        {
            if(!isdigit(val[i])) return false;
        }
        return true;
    }
}

bool Physical_location::set_building_no(string val)
{
    if(check_build_no(val))
    {
        building_no = val;
        return true;
    }
    else return false; //returning false means that building number has not been set
}

bool Physical_location::set_room_no(string val)
{
    if(check_room_no(val))
    {
        room_no = val;
        return true;
    }
    else return false; //returning false means that room number has not been set
}

string Physical_location::get_building_no(void)
{
    return building_no;
}

string Physical_location::get_room_no(void)
{
    return room_no;
}

string Physical_location::get_physical_location(void) //for displaying the physical location
{
    if(building_no == "" || room_no == "") return "";
    string s = building_no + "-" + room_no;
    return s;
}

bool Physical_location::operator == (Physical_location phy_val)
{
    if(phy_val.get_room_no() == this->get_room_no() && phy_val.get_building_no() == this->get_building_no())
        return true;
    else return false;
}

bool Physical_location::operator != (Physical_location phy_val)
{
    if(phy_val == *this)
        return false;
    else return true;
}