
#include "header/serverMainpage.h"

int main(void)
{
    int exit = 0;
    Page page;
    while(exit == 0)
    {
        page.ShowMenu();
        exit = page.Select();
    }

    return 0;
}