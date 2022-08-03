#ifndef __SIGNUP_H_
#define __SIGNUP_H_
#include "database.h"
using namespace std;
#include <iostream>
class Signup  
{
private:
    Database DB;
    int num;
    char query[1024];
public:
    void Vip_Join();    
};

#endif //__SIGNUP_H_