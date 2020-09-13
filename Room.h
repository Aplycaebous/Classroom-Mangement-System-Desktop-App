#ifndef CLASSROOM_MANAGEMENT_SYSTEM_ROOM_H
#define CLASSROOM_MANAGEMENT_SYSTEM_ROOM_H
#include <iostream>
#include "Physical_location.h"
#include "Equipments.h"
using namespace std;

class Room: public Physical_location, public Equipments
{
protected:
    int capacity;
public:
    Room();
    Room(Physical_location phy_val, Equipments equip_val, int cap_val);
    bool set_capacity(int val);
    int get_capacity(void);
    Physical_location get_phy_loc_obj(void);
    Equipments get_equip_obj(void);
};

#endif //CLASSROOM_MANAGEMENT_SYSTEM_ROOM_H
