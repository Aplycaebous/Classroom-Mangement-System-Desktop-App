#include "Admin.h"

Admin::Admin()
{
    set_username("system");
    set_password("system123");
}
Admin::Admin(string user_val, string pass_val, string cont_val,string email_val)
{
    set_username(user_val);
    set_password(pass_val);
    set_contact_no(cont_val);
    set_email_address(email_val);
}
bool Admin::check_username(string val)
{
    int vsize=val.size();
    if(val.size()>24 || val.size()<8)
    {
        return false;
    }
    else if(val[0] == '~' || val[0] == '`' || val[0] == '-' || val[0] == ';'|| val[0] == ','|| val[0] == '.'|| val[0] == ':')
        return false;
    else
    {
        for(int i=0;i<vsize;i++)
        {
            if(val[i]=='/' || val[i]=='\\' )
                return false;
        }
        return true;
    }
}

bool Admin::check_password(string val)
{
    if(val.size()>24 || val.size()<8)
    {
        return false;
    }
    else
    {
    //check password complexity
    //must contain at least one character and one digit or something like that
    //admin password must be stronger than user password; make sure of that
        return true;
    }
}

bool Admin::check_contact_no_validity(string val)
{
    int vsize=val.size();
    if(val.size() == 11) //string length of a contact number is 11
    {
        for(int i=0;i<vsize;i++)
        {
            if(!isdigit(val[i]))
                return false;
        }
        return true;
    }
    else return false;
}

bool Admin::set_username(string val)
{
    if(check_username(val))
    {
        username = val;
        return true;
    }
    else return false;
}

bool Admin::set_password(string val)
{
    if(check_password(val))
    {
        password = val;
        return true;
    }
    return false;
}

bool Admin::set_contact_no(string val)
{
    if(check_contact_no_validity(val))
    {
        contact_no = val;
        return true;
    }
    else return false;
}

void Admin::set_email_address(string val)
{
    email_address = val;
}

string Admin::get_username(void)
{
    return username;
}

string Admin::get_password(void)
{
    return password;
}

string Admin::get_email(void)
{
    return email_address;
}

string Admin::get_contact_no(void)
{
    return contact_no;
}

//In main function we create admin with username and password
//Admin can read and load classrooms (written)
//Admin can read and load user_list (written)
//Admin can check log file (written)
//Admin can edit metadata (Done)

/*vector<Room> create_room_file(string path)
{


}*/
void add_room(vector<Room>&room,Physical_location phy_val,Equipments equip_val,int capacity)//paramenter list for rooms
{
    int cross=0, rsize=room.size();
    for(int i=0;i<rsize;i++)
    {
        if( stoi(room[i].get_building_no()) >stoi(phy_val.get_building_no()))
        {
            break;
        }
        else if(stoi(room[i].get_building_no() ) <stoi(phy_val.get_building_no()))
        {
            cross++;
        }
        else if(stoi(room[i].get_building_no())==stoi(phy_val.get_building_no()))
        {
            if(stoi(room[i].get_room_no()) >stoi(phy_val.get_room_no()))
            {
                break;
            }
            else
            {
                cross++;
            }
        }
    }
    room.insert(room.begin()+cross,Room(phy_val,equip_val,capacity));
    std::ofstream ofs;
    ofs.open("Room.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;
    myFile.open("Room.csv");
    for(int i=0;i<rsize;i++)
    {
        string temp_ac,temp_project;
        if(room[i].get_ac())
        {
            temp_ac="YES";
        }
        else
        {
            temp_ac="NO";
        }
        if(room[i].get_projector())
        {
            temp_project="YES";
        }
        else
        {
            temp_project="NO";
        }
        myFile<<room[i].get_building_no()<<","<<room[i].get_room_no()<<","<<temp_ac<<","<<room[i].get_boards()<<room[i].get_capacity()<<endl;
    }

    fstream file("log.txt",ios::in|ios::out|ios::app );
    file<<"Room "<<phy_val.get_building_no()<<" "<<phy_val.get_room_no()<<" was added by the Admin"<<endl;
}

vector<Admin>create_admin_file(string path)
{
    vector<Admin>f_list;
    fstream fin;
    fin.open(path);
    string line,word;
    string Username, Password, Contact_no, Email_address;
    while (fin.good())
    {
        getline(fin, line);
        stringstream s(line);
        int second_count=0;
        Admin temp;
        int valid_flag=0;
        while (getline(s, word, ','))
        {
            if(second_count==0)
            {
                if( temp.set_username(word) )
                    {
                        Username=word;
                        second_count++;
                    }
                else
                {
                    valid_flag=1;
                    cout<<"UserName "<<word<<" is invalid"<<endl;
                    break;
                }
            }
            else if(second_count==1)
            {
                if( temp.set_password(word) )
                {
                    Password=word;
                    second_count++;
                }
                else
                {
                    valid_flag=1;
                    //cout<<"Password "<<word<<" is invalid"<<endl;
                    break;
                }
            }
            else if(second_count==2)
            {
                if( temp.set_contact_no(word) )
                {
                    Contact_no=word;
                    second_count++;
                }
                else
                {
                    valid_flag=1;
                    //cout<<"Contact No "<<word<<" is invalid"<<endl;
                    break;
                }
            }
            else if(second_count==3)
            {
                Email_address=word;
                second_count++;
            }
        }
        if(valid_flag==1)
        {
            continue;
        }
        f_list.push_back( Admin(Username,Password,Contact_no,Email_address) ) ;
    }
    std::ofstream file;
    file.open("Admin.csv",std::ios_base::app);
    string temp_ac;
    int fsize=f_list.size();
    for(int i=0;i<fsize;i++)
    {
        file<<f_list[i].get_username()<<","<<f_list[i].get_password()<<","<<f_list[i].get_contact_no()<<","<<f_list[i].get_email()<<endl;
    }
    return f_list;
}

vector<Student>create_student_file(string path)
{
    vector<Student>f_list;
    fstream fin;
    //int counti=0;

    fin.open(path);
    string line,word;;
    string username,password,student_id;
    bool cr;

    while (fin.good()) {
        // cout<<"nana"<<endl;
        getline(fin, line);
        stringstream s(line);
        int second_count=0;
        Student temp;
        int valid_flag=0;

        while (getline(s, word, ',')) {
            if(second_count==0)
            {
                username=word;
                second_count++;
            }
            else if(second_count==1)
            {
                if(temp.set_password(word))
                {
                    password=word;
                }
                else
                {
                    valid_flag=1;
                    cout<<"Password "<<word<<" is not valid"<<endl;
                    break;
                }

                second_count++;
            }
            else if(second_count==2)
            {
                if(temp.set_id(word))
                {
                    student_id=word;
                }
                else
                {
                    valid_flag=1;
                    cout<<"Student ID "<<word<<" is not valid"<<endl;
                    break;
                }
                second_count++;
            }
            else if(second_count==3)
            {
                if(word=="YES")
                {
                    cr=true;
                }
                else
                {
                    cr=false;
                }
            }

        }
        if(valid_flag)
        {
            continue;
        }

        f_list.push_back(Student(username,password,student_id,cr) );

        //counti++;

    }


    // counti--;
    //   f_list.pop_back();
    std::ofstream file;
    file.open("Student.csv",std::ios_base::app);
    string temp_ac;
    int fsize=f_list.size();
    for(int i=0;i<fsize;i++)
    {
        string temp;
        if(f_list[i].get_cr())
        {
            temp="YES";
        }
        else
        {
            temp="NO";
        }

        file<<f_list[i].get_name()<<","<<f_list[i].get_password()<<","<<f_list[i].get_id()<<","<<temp<<endl;
    }


return f_list;
}
void add_student(vector<Student>&student,string val_name,string val_pass,string val_std_id,bool val_cr)
{
    //checks the student doesn't prexist in the student.txt file
    //appends a new student_user in the room.txt file
    int check_exist=0, ssize=student.size();
    for(int i=0;i<ssize;i++)
    {
        if(stoi(student[i].get_id() )==stoi(val_std_id))
        {
            check_exist=1;
            break;
        }
    }
    if(check_exist)
    {
        return ;
    }

    std::ofstream file;
    file.open("Student.csv",std::ios_base::app);
    string temp_cr;
    if(val_cr)
    {
        temp_cr="YES";
    }
    else
    {
        temp_cr="NO";
    }
    file<<val_name<<","<<val_pass<<","<<val_std_id<<","<<temp_cr<<endl;
    student.push_back( Student(val_name,val_pass,val_std_id,val_cr) );

    fstream myfile("log.txt",ios::in | ios::out | ios::app );

    myfile<<"Student "<<val_std_id<<" was added by the Admin"<<endl;
}
vector<Staff>create_staff_file(string path)
{
vector<Staff>f_list;
fstream fin;
//int counti=0;

fin.open(path);
string line,word;;
string username,password,staff_id;


while (fin.good()) {
// cout<<"nana"<<endl;
getline(fin, line);
stringstream s(line);
int second_count=0;
Staff temp;
int valid_flag=0;

while (getline(s, word, ',')) {
if(second_count==0)
{

username=word;
second_count++;

}
else if(second_count==1)
{
if(temp.set_password(word))
{
password=word;
}
else
{
valid_flag=1;
cout<<"Password "<<word<<" is not valid"<<endl;
break;
}

second_count++;
}
else if(second_count==2)
{
if(temp.set_id(word))
{
staff_id=word;
}
else
{
valid_flag=1;
cout<<"Staff ID "<<word<<" is not valid"<<endl;
break;
}
second_count++;
}

}
if(valid_flag)
{
continue;
}

f_list.push_back(Staff(username,password,staff_id) );

//counti++;

}


// counti--;
//   f_list.pop_back();
std::ofstream file;
file.open("Staff.csv",std::ios_base::app);
string temp_ac;
int fsize=f_list.size();
for(int i=0;i<fsize;i++)
{
file<<f_list[i].get_name()<<","<<f_list[i].get_password()<<","<<f_list[i].get_id()<<endl;
}
return f_list;
}
void add_staff( vector<Staff>&staff,string val_name,string val_pass,string val_staff_id  )
{

    int check_exist=0, ssize=staff.size();
    for(int i=0;i<ssize;i++)
    {
        if(stoi(staff[i].get_id() )==stoi(val_staff_id))
        {
            check_exist=1;
            break;
        }
    }
    if(check_exist)
    {
        return ;
    }

    std::ofstream file;
    file.open("Staff.csv",std::ios_base::app);
    file<<val_name<<","<<val_pass<<","<<val_staff_id<<endl;
    staff.push_back( Staff(val_name,val_pass,val_staff_id) );

    fstream myfile("log.txt",ios::in|ios::out|ios::app );

    myfile<<"Staff "<<val_staff_id<<" was added by the Admin"<<endl;

}
void add_admin(vector<Admin>&admin,string user,string pass,string contact,string email)
{

    std::ofstream file;
    file.open("Admin.csv",std::ios_base::app);
    string temp_ac;

    file<<user<<","<<pass<<","<<contact<<","<<email<<endl;
    admin.push_back( Admin(user,pass,contact,email));
    fstream myfile("log.txt",ios::in|ios::out|ios::app );

    myfile<<"Admin "<<user<<" was added by the Admin"<<endl;

}
//for the remove functions we pass an array of rooms. Then we remove from array of rooms
//and then upload that array in the file
void remove_student(vector<Student>student,string val_std_id)
{
    int value=0, ssize=student.size();
    for(int i=0;i<ssize;i++)
    {
        if(student[i].get_id()==val_std_id)
        {
            value=i;
            break;
        }
    }
    student.erase(student.begin()+value);
    std::ofstream ofs;
    ofs.open("Student.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;
    myFile.open("Student.csv");
    for(int i=0;i<ssize;i++)
    {
        string temp_cr;
        if(student[i].get_cr())
        {
            temp_cr="YES";
        }
        else
        {
            temp_cr="NO";
        }

        myFile<<student[i].get_name()<<","<<student[i].get_password()<<","<<student[i].get_id()<<","<<temp_cr<<endl;
    }

    fstream file("log.txt",ios::in|ios::out|ios::app );

    file<<"Student "<<val_std_id<<" was removed by the Admin"<<endl;
}
void remove_staff(vector<Staff>&staff ,string val_staff_id  )
{
    int value=0, ssize=staff.size();
    for(int i=0;i<ssize;i++)
    {
        if(staff[i].get_id()==val_staff_id)
        {
            value=i;
            break;
        }
    }
    staff.erase(staff.begin()+value);
    std::ofstream ofs;
    ofs.open("Staff.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;
    myFile.open("Staff.csv");
    for(int i=0;i<ssize;i++)
    {
        myFile<<staff[i].get_name()<<","<<staff[i].get_password()<<","<<staff[i].get_id()<<endl;
    }
    fstream file("log.txt",ios::in|ios::out|ios::app );

    file<<"Staff "<<val_staff_id<<" was removed by the Admin"<<endl;


}
void remove_admin(vector<Admin>admin,string user_val)
{
    int value=0, asize=admin.size();
    for(int i=0;i<asize;i++)
    {
        if(admin[i].get_username()==user_val)
        {
            value=i;
            break;
        }
    }
    admin.erase(admin.begin()+value);
    std::ofstream ofs;
    ofs.open("Admin.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;
    myFile.open("Admin.csv");
    for(int i=0;i<asize;i++)
    {
        myFile<<admin[i].get_username()<<","<<admin[i].get_password()<<","<<admin[i].get_contact_no()<<","<<admin[i].get_email()<<endl;
    }

    fstream file("log.txt",ios::in|ios::out|ios::app );

    file<<"Admin "<<user_val<<" was removed by the Admin"<<endl;

}
void remove_room(vector<Room>room,string building_no,string room_no)
{

    int value=0, rsize=room.size();
    for(int i=0;i<rsize;i++)
    {

        if(room[i].get_building_no()==building_no && room[i].get_room_no()==room_no)
        {
            value=i;
            break;
        }
    }

    room.erase(room.begin()+value);

    std::ofstream ofs;
    ofs.open("Room.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream myFile;

    myFile.open("Room.csv");
    for(int i=0;i<rsize;i++)
    {
        string temp_ac,temp_project;
        if(room[i].get_ac())
        {
            temp_ac="YES";
        }
        else
        {
            temp_ac="NO";
        }
        if(room[i].get_projector())
        {
            temp_project="YES";
        }
        else
        {
            temp_project="NO";
        }
        myFile<<room[i].get_building_no()<<","<<room[i].get_room_no()<<","<<temp_ac<<","<<room[i].get_boards()<<room[i].get_capacity()<<endl;
    }

    fstream file("log.txt",ios::in|ios::out|ios::app );

    file<<"Room "<<building_no<<" "<<room_no<<" was removed by the Admin"<<endl;

}
void read_log(void)
{
    //shows the log_file on the screen
    //Present the data in a user friendly way (optional)
}
