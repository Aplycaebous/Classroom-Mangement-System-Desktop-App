#include "mainwindow.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    vector<Admin>ad;
    ad = System_initializer::read_admin();

    vector<Room>r;
    r = System_initializer::read_room();

    vector<Student>student;
    student = System_initializer::read_student();

    vector<Staff>staff;
    staff = System_initializer::read_staff();

    vector<Record>record;
    record = System_initializer::read_record();
    return a.exec();
}
