#ifndef CLASSROOM_MANAGEMENT_SYSTEM_PHYSICAL_LOCATION_H
#define CLASSROOM_MANAGEMENT_SYSTEM_PHYSICAL_LOCATION_H
#include <iostream>
using namespace std;

class Physical_location //Comprised of building_no and room_no to uniquely identify a room in our institution
{
protected:
    string building_no;
    string room_no;
public:
    Physical_location();
    Physical_location(string buildval, string roomval);
    bool check_room_no(string val);
    bool check_build_no(string val);
    bool set_building_no(string val);
    bool set_room_no(string val);
    string get_building_no(void);
    string get_room_no(void);
    string get_physical_location(void); //for displaying the physical location
    bool operator == (Physical_location phy_val);
    bool operator != (Physical_location phy_val);
};


#endif //CLASSROOM_MANAGEMENT_SYSTEM_PHYSICAL_LOCATION_H
