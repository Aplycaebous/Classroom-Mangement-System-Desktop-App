#ifndef EQUIPMENTS_H
#define EQUIPMENTS_H

#include <iostream>
using namespace std;

class Equipments
{
protected:
    bool AC;
    int boards;
    bool projector;
public:
    Equipments();
    Equipments(bool ac_val, int boards_val, bool pro_val);
    void set_ac(bool val);          //air-conditioned or not
    bool set_boards(int val);       //number of boards in the room
    void set_projector(bool val);   //has projector or not
    bool get_ac();
    int get_boards();
    bool get_projector();
};

#endif // EQUIPMENTS_H
