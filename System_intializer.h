#ifndef CLASSROOM_MANAGEMENT_SYSTEM_SYSTEM_INTIALIZER_H
#define CLASSROOM_MANAGEMENT_SYSTEM_SYSTEM_INTIALIZER_H
#include "Room.h"
#include "Record.h"
#include "Admin.h"


class System_intializer
{
    //Add a function which adds an empty Admin object if the Admin.txt file doesn't exist
    //It can show a pop-up like first time use
    //New default admin created. Username: system. Password system123
    //i.e. for first time use only
public:
    static vector<Admin> read_admin();
    static vector<Room> read_room();
    static vector<Student> read_student();
    static vector<Staff> read_staff();
    static vector<Record>read_record();
};


#endif //CLASSROOM_MANAGEMENT_SYSTEM_SYSTEM_INTIALIZER_H
