#ifndef __GUIDE_H__
#define __GUIDE_H__

#include "manage.h"

class Guide : public Manage
{
private:
    std::string id, name, date;
    int year, month, day;

public:
    virtual void Menu();
    virtual void Check();
    virtual void ManageCheck();
    virtual void ManageModify();
    virtual void ManageDelete();
    virtual void ManageBook();
    virtual void Add();
    virtual void Edit();
    virtual void Remove();
};

#endif