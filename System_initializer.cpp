#include "System_initializer.h"
#include <qfile.h>
#include <QTextStream>

vector<Admin> System_initializer::read_admin()
{
    vector<Admin>f_list;
    fstream fin;
    int counti=0;
    //QFile f(":/Admin.csv");
    fin.open("C:\\Users\\tasni\\Documents\\RMS\\Admin.csv", ios::in);
    string line,word;;
    string username,password,contact_no,email_address;

    while (fin.good()) {
        // cout<<"nana"<<endl;
        getline(fin, line);
        stringstream s(line);
        int second_count=0;

        while (getline(s, word, ',')) {
            if(second_count==0)
            {
                username=word;
                second_count++;
            }
            else if(second_count==1)
            {
                password=word;
                second_count++;
            }
            else if(second_count==2)
            {
                contact_no=word;
                second_count++;
            }
            else if(second_count==3)
            {
                email_address=word;
                second_count++;
            }
        }

        f_list.push_back( Admin(username,password,contact_no,email_address) ) ;
        counti++;
    }
    counti--;
    f_list.pop_back();
    return f_list;
}
vector<Room> System_initializer::read_room()
{
    vector<Room> r; // I WORKED WITH VECTOR FOR CONVENIENCE< I'LL CHANGE IT LATER AT THE END .
    fstream fin;
    int counti=0;
    fin.open("C:\\Users\\tasni\\Documents\\RMS\\Room.csv", ios::in);
    string line,word;;
    string building_val,room_val;
    bool ac_val,proj_val;
    int board_no,capacity;
    int number_of_room=0;
    while (fin.good())
    {
        getline(fin, line);
        stringstream s(line);
        number_of_room++;
        int second_count=0;
        while (getline(s, word, ','))
        {
            if(second_count==0)
            {
                building_val=word;
                second_count++;
            }
            else if(second_count==1)
            {
                room_val=word;
                second_count++;
            }
            else if(second_count==2)
            {
                if(word=="YES")
                {
                    ac_val=true;
                }
                else
                {
                    ac_val=false;
                }
                second_count++;
            }
            else if(second_count==3)
            {

                board_no=stoi(word);
                second_count++;
            }
            else if(second_count==4)
            {

                if(word=="YES")
                {
                    proj_val=true;
                }
                else
                {
                    proj_val=false;
                }

                second_count++;
            }
            else if(second_count==5)
            {
                capacity=stoi(word);
                second_count++;
            }
        }
        Physical_location pl(building_val,room_val);
        Equipments eq(ac_val,board_no,proj_val);

        r.push_back(Room(pl,eq,capacity)) ;
        counti++;
    }
    number_of_room--;
    r.pop_back();

    //ALL THE CASES IN THE UPPER LOOP ARE THE INPUT TAKEN FROM THE FILE



    return r;
}
vector<Student> System_initializer::read_student()
{

    vector<Student>f_list;
    fstream fin;
    int counti=0;

    fin.open("C:\\Users\\tasni\\Documents\\RMS\\Student.csv", ios::in);
    string line,word;;
    string username,password,student_id;
    bool cr;

    while (fin.good()) {
        // cout<<"nana"<<endl;
        getline(fin, line);
        stringstream s(line);
        int second_count=0;

        while (getline(s, word, ',')) {
            if(second_count==0)
            {
                username=word;
                second_count++;
            }
            else if(second_count==1)
            {
                password=word;
                second_count++;
            }
            else if(second_count==2)
            {
                student_id=word;
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
                second_count++;
            }


        }

        f_list.push_back(Student(username,password,student_id,cr) );

        counti++;

    }


    counti--;
    f_list.pop_back();
    return f_list;


}
vector<Staff> System_initializer::read_staff()
{
    vector<Staff>f_list;
    fstream fin;
    int counti=0;

    fin.open("C:\\Users\\tasni\\Documents\\RMS\\Staff.csv", ios::in);
    string line,word;;
    string username,password,student_id;


    while (fin.good()) {
        // cout<<"nana"<<endl;
        getline(fin, line);
        stringstream s(line);
        int second_count=0;

        while (getline(s, word, ',')) {
            if(second_count==0)
            {
                username=word;
                second_count++;
            }
            else if(second_count==1)
            {
                password=word;
                second_count++;
            }
            else if(second_count==2)
            {
                student_id=word;
                second_count++;
            }

        }

        f_list.push_back(Staff(username,password,student_id) );

        counti++;

    }


    counti--;
    f_list.pop_back();
    return f_list;



}
vector<Record> System_initializer::read_record()
{
    vector<Record>f_list;
    fstream fin;
    int counti=0;

    fin.open("C:\\Users\\tasni\\Documents\\RMS\\Record.csv", ios::in);
    string line,word;;
    string user_val,build_val,room_val,format;
    int hour,minute,duration,day,month,year;


    while (fin.good()) {
        getline(fin, line);
        stringstream s(line);
        int second_count=0;

        while (getline(s, word, ',')) {
            if(second_count==0)
            {
                user_val=word;

                second_count++;
            }
            else if(second_count==1)
            {
                build_val=word;

                second_count++;
            }
            else if(second_count==2)
            {
                room_val=word;

                second_count++;
            }
            else if(second_count==3)
            {
                hour=stoi(word);

                second_count++;
            }
            else if(second_count==4)
            {
                minute=stoi(word);

                second_count++;
            }
            else if(second_count==5)
            {
                duration=stoi(word);

                second_count++;
            }
            else if(second_count==6)
            {
                day=stoi(word);

                second_count++;
            }
            else if(second_count==7)
            {
                month=stoi(word);

                second_count++;
            }
            else if(second_count==8)
            {
                year=stoi(word);

                second_count++;
            }


        }
        Physical_location pl(build_val,room_val);
        Time t(hour,minute);
        Date d(day,month,year);


        f_list.push_back(Record(user_val,pl,t,duration,d) );

        counti++;

    }
    counti--;
    f_list.pop_back();
    return f_list;
}
