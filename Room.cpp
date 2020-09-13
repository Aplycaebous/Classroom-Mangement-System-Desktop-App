#include "Room.h"

Room::Room()
{
    set_capacity(0);
}

Room::Room(Physical_location phy_val, Equipments equip_val, int cap_val):Physical_location(phy_val),Equipments(equip_val)
{
    if(!set_capacity(cap_val)) set_capacity(0);
}

bool Room::set_capacity(int val)
{
    if(val<0) //neg number
    {
        return false;
    }
    else
    {
        capacity = val;
        return true;
    }
}

int Room::get_capacity(void)
{
    return capacity;
}

Physical_location Room::get_phy_loc_obj(void)
{
    return Physical_location(building_no,room_no);
}

Equipments Room::get_equip_obj()
{
    return Equipments(AC, boards,projector);
}