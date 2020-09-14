#ifndef METADATA_H
#define METADATA_H


class Metadata
{
private:
    static int room_no_size;
    static int building_no_size;
    static int student_id_size;
    static int staff_id_size;
public:
    Metadata();
    //future works can include setter functions for metadata so that it can be changed in the UI level by an admin
    static int get_room_no_size(void);
    static int get_building_no_size(void);
    static int get_student_id_size(void);
    static int get_staff_id_size(void);
    // To make Metadata an abstract class so that no instance of this class can be created
    virtual void abstract_func() = 0;
};

#endif // METADATA_H
