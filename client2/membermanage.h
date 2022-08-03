#ifndef __MEMBERMANAGE_H_
#define __MEMBERMANAGE_H_
#include "database.h"
using namespace std;

class Management  
{
private:
    char query[1024];
    int num;
    string login_id;
    Database DB;
public:
    void Manage_Choose(string id);
    void Cancel_Member();
    void Change_Member_Info();
    void withdraw(string id, string pw, string name, string type);
};

#endif //__MEMBERMANAGE_H_