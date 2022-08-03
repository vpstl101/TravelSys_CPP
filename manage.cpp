#include "header/manage.h"

using namespace std;

void Manage::MenuSelect()
{
    cin >> choice;
    cin.ignore();
    system("clear");
    switch (choice)
    {
    case 1:
        ShowMenu();
        ShowSelect();
        cout<<endl;
        break;
    case 2:
        ManageMenu();
        ManageSelect();
        cout<<endl;
        break;
    dafault:
        cout << "잘못 선택하셨습니다" << endl;
        break;
    }
}
void Manage::ShowMenu()
{
    cout<<"1) 조회"<<endl;
    cout<<"2) 추가"<<endl;
    cout<<"3) 변경"<<endl;
    cout<<"4) 삭제"<<endl;
}

void Manage::ShowSelect()
{
    cin>>choice;
    cin.ignore();
    system("clear");
    switch(choice)
    {
        case 1:
            Check();
            cout<<endl;
            break;
        case 2:
            Add();
            cout<<endl;
            break;
        case 3:
            Edit();
            cout<<endl;
            break;
        case 4:
            Remove();
            cout<<endl;
            break;
        default:
            cout<<"잘못 입력하셨습니다"<<endl<<endl;
            return;
    }

}

void Manage::ManageMenu()
{
    cout << "1) 예약조회" << endl;
    cout << "2) 예약추가" << endl;
    cout << "3) 예약변경" << endl;
    cout << "4) 예약취소" << endl;
}

void Manage::ManageSelect()
{
    cin >> choice;
    cin.ignore();
    system("clear");
    switch (choice)
    {
    case 1:
        ManageCheck();
        cout<<endl;
        break;
    case 2:
        ManageBook();
        cout<<endl;
        break;
    case 3:
        ManageModify();
        cout<<endl;
        break;
    case 4:
        ManageDelete();
        cout<<endl;
        break;
    default:
        cout << "잘못 입력하셨습니다" << endl<<endl;
        return;
    }
}
