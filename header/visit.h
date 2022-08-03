#ifndef __VISIT_H__
#define __VISIT_H__

#include <iostream>
#include "manage.h"
#include "database.h"

class Visit : public Manage
{

private:
    std::string id,name,date;
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
