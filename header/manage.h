#ifndef __MANAGE_H__
#define __MANAGE_H__

#include <iostream>
#include <stdlib.h>
#include "database.h"

class Manage
{
private:
    int choice;
protected:
    
    char query[1024];
    Database DB;

public:
    void ShowMenu();
    void ShowSelect();
    virtual void Menu() = 0;
    void MenuSelect();
    virtual void Check() = 0;
    virtual void Add() = 0;
    virtual void Edit() = 0;
    virtual void Remove() = 0;
    void ManageMenu();
    void ManageSelect();
    virtual void ManageBook() = 0;
    virtual void ManageCheck() = 0;
    virtual void ManageModify() = 0;
    virtual void ManageDelete() = 0;
};

#endif