#ifndef __MEMBER_H__
#define __MEMBER_H__

#include <iostream>
#include "database.h"
class Member
{
private:
    int choice;
    Database DB;
    char query[100];

public:
    void Menu();
    void Sel();
    void Check();
    void Modify();
    void Delete();
    void Withdraw();
};

#endif
