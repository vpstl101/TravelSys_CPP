#ifndef __MEMBER_H_
#define __MEMBER_H_

#include "database.h"
using namespace std;

class Member
{
private:
    string id;
    string pw;
    string name;
public:
    Member();
    string ID_Get();
    string PW_Get();
    string Name_Get();
    void Show_Info() const;
    void Common_Info() const;
};


#endif //__MEMBER_H_
