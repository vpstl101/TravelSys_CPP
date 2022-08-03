#ifndef __LOGIN_H_
#define __LOGIN_H_
#include "database.h"
using namespace std;

class Login  
{
private:
    int num;
    char query[1024];
    Database DB;
public:
    string Vip_Login();    
};

#endif //__LOGIN_H_