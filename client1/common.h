#ifndef __COMMON_H_
#define __COMMON_H_

class Common : public Database 
{
private:
    Member c;
    int num;
    char query[1024];
public:
    Common();
    void Common_Login();
    void Member_Join();
    void Change_Member_Info();
    void Cancel_Member();
    void withdraw(string id, string pw, string name, string type);
    void Check_trip();
    void Come_In();
    void Common_Select();
};

#endif //__COMMON_H_
