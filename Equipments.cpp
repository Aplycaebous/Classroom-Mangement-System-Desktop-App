#include "Equipments.h"

Equipments::Equipments()
{
    set_ac(0);
    set_boards(0);
    set_projector(0);
}

Equipments::Equipments(bool ac_val, int boards_val, bool pro_val)
{
    set_ac(ac_val);
    set_boards(boards_val);
    set_projector(pro_val);
}

void Equipments::set_ac(bool val)
{
    AC = val;
}

bool Equipments::set_boards(int val)
{
    if(val<=0 || val>=10)
    {
        //cout<<"Invalid no. of boards"<<endl;
        return false;
    }
    else
    {
        boards = val;
        return true;
    }
}

void Equipments::set_projector(bool val)
{
    projector = val;
}

bool Equipments::get_ac()
{
    return AC;
}

int Equipments::get_boards()
{
    return boards;
}

bool Equipments::get_projector()
{
    return projector;
}

