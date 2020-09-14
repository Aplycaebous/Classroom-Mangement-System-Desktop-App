#ifndef ADMIN_H
#define ADMIN_H

#include<sstream>
#include "Room.h"
#include "Staff.h"
#include "Student.h"
using namespace std;

class Admin
{
private:
    string username;
    string password;
    string contact_no;
    string email_address;
public:
    Admin();
    Admin(string user_val, string pass_val, string cont_val,string email_val);
    bool check_username(string val);
    bool check_password(string val);
    bool check_contact_no_validity(string val);
    bool set_username(string val);
    bool set_password(string val);
    bool set_contact_no(string val);
    void set_email_address(string val);
    string get_username(void);
    string get_password(void);
    string get_email(void);
    string get_contact_no(void);
    bool login(string user_val, string pass_val);
    //In main function we create admin with username and password
    //Admin can read and load classrooms (written)
    //Admin can read and load user_list (written)
    //Admin can check log file (written)
    //Admin can edit metadata (Done)

    /*vector<Room> create_room_file(string path)
    {

    }*/
    void add_room(vector<Room>&room,Physical_location phy_val,Equipments equip_val,int capacity);//paramenter list for rooms

    vector<Admin>create_admin_file(string path);

    vector<Student>create_student_file(string path);
    void add_student(vector<Student>&student,string val_name,string val_pass,string val_std_id,bool val_cr);
    vector<Staff>create_staff_file(string path);
    void add_staff( vector<Staff>&staff,string val_name,string val_pass,string val_staff_id  );
    void add_admin(vector<Admin>&admin,string user,string pass,string contact,string email);
    //for the remove functions we pass an array of rooms. Then we remove from array of rooms
    //and then upload that array in the file
    void remove_student(vector<Student>student,string val_std_id);
    void remove_staff(vector<Staff>&staff ,string val_staff_id  );
    void remove_admin(vector<Admin>admin,string user_val);
    void remove_room(vector<Room>room,string building_no,string room_no);
    void read_log(void);
};

#endif // ADMIN_H
