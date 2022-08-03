#ifndef __VISITRESERVATION_H__
#define __VISITRESERVATION_H__
using namespace std;
#include "database.h"
#include <iostream>
#include <string>

class Visitreservation
{
private:
    Database DB;
    char query[1024];
    int num;
    string login_id;
public:
    void Choose(string id);
    void Reservation(); //방문예약
    void Visit_date(string beach, string date);
    void Reser_Check();
    void Change_Reser();
};

#endif