#include "mainpage.h"
#include <unistd.h>

using namespace std;

void Page::MainPage()
{   
    system("clear");
    while(repeat)
    {   
        if(login == false)
        {            
            cout<<"1) 회원가입"<<endl;
            cout<<"2) 로그인"<<endl;
            cout<<"3) 종료"<<endl;
            cin>>num;
            cin.ignore();
            system("clear");
            repeat = true;
            switch(num)
            {
                case 1:
                    l.Vip_Join();
                    break;
                case 2:
                    loginID = v.Vip_Login();
                    if(loginID != "0")
                        login = true;
                    break;
                case 3:
                    repeat = false;
                    break;
                default:
                    cout<<"잘못 입력하셨습니다"<<endl;
                    break;
            }
        }
        else
            LoginPage(loginID);
    }
}

void Page::LoginPage(string loginID)
{
    sleep(1);
    system("clear");
    cout<<"1) 회원정보 수정/탈퇴"<<endl;
    cout<<"2) 관광지/숙박 정보 조회"<<endl;
    cout<<"3) 관광지 예약"<<endl;
    cout<<"4) 숙박 예약"<<endl;
    cout<<"5) 가이드 예약"<<endl; 
    cout<<"6) 로그아웃"<<endl;
    cin>>sel;
    cin.ignore();
    system("clear");
    switch(sel)
    {
        case 1:
            manage.Manage_Choose(loginID);
            break;
        case 2:
            visitcheck.Check();
            break;
        case 3:
            visit.Choose(loginID);
            break;
        case 4:
            stay.Menu(loginID);
            stay.Choose();
            break;
        case 5:
            guide.Menu(loginID);
            guide.Choose();
            break;
        case 6:
            login = false;
            break;
        default:
            cout<<"잘못 입력하셨습니다"<<endl;
            break;
    }
}