#ifndef __GUIDEBOOKING_H__
#define __GUIDEBOOKING_H__

#include "database.h"
#include <iostream>

class GuideBooking
{
    private:
        int choice;
        char query[100];
        std::string name;
        std::string date;
        std::string loginID;
        Database DB;
    public:
        std::string GuideName();
        std::string Date();
        void Book();
        void Menu(std::string ID);
        void Choose();
        void Check();
        void Change();
        void Modify();
        void Delete();
};
#endif