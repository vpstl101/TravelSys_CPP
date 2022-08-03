#ifndef __SERVERMAINPAGE_H_
#define __SERVERMAINPAGE_H_

#include <iostream>
#include <stdlib.h>
#include "member.h"
#include "visit.h"
#include "stay.h"
#include "guide.h"

class Page
{
private:
    Member member;
    Visit visit;
    Stay stay;
    Guide guide;
    int choice;

public:
    void ShowMenu();
    int Select();
};

#endif
