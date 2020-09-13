#include <iostream>
#include "Metadata.h"
#include "Physical_location.h"
#include "Time.h"
#include "Date.h"
#include "Record.h"

int main() {
    //cout << Metadata::get_building_no_size() << endl;
    /*
    Physical_location phy_obj1("1","312");
    Physical_location phy_obj2;
    phy_obj2.set_building_no("1");
    phy_obj2.set_room_no("312");
    cout<<phy_obj1.get_physical_location()<<" "<<phy_obj2.get_physical_location()<<endl;
    cout<< (phy_obj1 == phy_obj2) <<endl;
     */
    /*
    Time a1(12,2);
    a1.set_hour(13);
    Time a2(1,2);
    //Time a3 = a1 + a2;
    cout<<a1.get_time_24()<<endl;
    cout<<a1.get_time_12()<<endl;
    cout<<Time::convert_duration(120).get_time_24()<<endl;
    cout<<(a1+a2).get_time_24()<<endl;
    */
    /*
    Date a;
    Date c;
    Date b(22,3,2000);
    cout<<(a!=b)<<endl;
    cout<<a.get_date()<<" "<<b.get_date()<<endl;
     */
    Time t;
    Date d;
    Physical_location p;
    Record r("190",p,t,90,d);
    vector<Record*> vec;
    vector<Record*> vec2;
    vec.push_back(new Record("191",p,t,91,d));
    vec2 = Record::list_user_records("191",vec);
    cout<<vec2[0]->get_year()<<endl;
    return 0;
}
