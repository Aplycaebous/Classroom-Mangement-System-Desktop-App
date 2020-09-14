#include "Metadata.h"

Metadata::Metadata()
{

}

int Metadata::get_staff_id_size(void)
{
    return staff_id_size;
}

int Metadata::get_student_id_size(void)
{
    return student_id_size;
}

int Metadata::get_room_no_size(void)
{
    return room_no_size;
}

int Metadata::get_building_no_size(void)
{
    return building_no_size;
}

int Metadata::room_no_size = 3;
int Metadata::building_no_size = 1;
int Metadata::student_id_size = 9;
int Metadata::staff_id_size = 8;
