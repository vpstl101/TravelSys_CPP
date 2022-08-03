#include "header/serverMainpage.h"


using namespace std;

void Page::ShowMenu()
{
    cout << "== 여행사 관리 서버 ==" << endl;
    cout << "1) 회원관리" << endl;
    cout << "2) 관광지 관리" << endl;
    cout << "3) 슉박 관리" << endl;
    cout << "4) 가이드 관리" <<endl;
    cout << "5) 종료" <<endl;
    cout << "번호를 선택하세요" << endl;
}

int Page::Select()
{
    cin >> choice;
    system("clear");
    
    switch (choice)
    {
    case 1:
        member.Menu();
        member.Sel();
        break;
    case 2:
        visit.Menu();
        visit.MenuSelect();
        break;
    case 3:
        stay.Menu();
        stay.MenuSelect();
        break;
    case 4:
        guide.Menu();
        guide.MenuSelect();
        break;
    case 5:
        cout<<"종료합니다"<<endl;
        return 1;
    default:
        cout << "잘못 입력하셨습니다" << endl;
        break;
    }
    return 0;
}