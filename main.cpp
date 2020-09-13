#include "mainwindow.h"
#include <QApplication>
#include<bits/stdc++.h>

#include<fstream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    vector<Admin>ad;
    ad = System_intializer::read_admin();

    vector<Room>r;
    r = System_intializer::read_room();

    vector<Student>student;
    student = System_intializer::read_student();

    vector<Staff>staff;
    staff = System_intializer::read_staff();

    vector<Record>record;
    record = System_intializer::read_record();
    return a.exec();
}