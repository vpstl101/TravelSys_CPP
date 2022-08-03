#include "header/member.h"
using namespace std;

void Member::Menu()
{
    cout << "(1) 회원목록 조회" << endl;
    cout << "(2) 회원정보 수정" << endl;
    cout << "(3) 회원정보 삭제" << endl;
    cout << "(4) 탈퇴회원 조회" << endl;
}

void Member::Sel()
{
    cin >> choice;
    system("clear");
    switch (choice)
    {
    case 1:
        Check();
        cout<<endl;
        break;
    case 2:
        Modify();
        cout<<endl;
        break;
    case 3:
        Delete();
        cout<<endl;
        break;
    case 4:
        Withdraw();
        cout<<endl;
        break;
    default:
        cout << "잘못 입력하셨습니다" << endl<<endl;
        break;
    }
}

void Member::Check()
{
    bool check = true;
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            cout << "== 일반 회원 ==" << endl;
            sprintf(query, "SELECT id, name FROM common");
        }
        else
        {
            cout << "== VIP 회원 ==" << endl;
            sprintf(query, "SELECT id, name FROM vip");
        }
        if (mysql_query(&DB.conn, query) != 0)
            fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
        else
        {
            DB.sql_result = mysql_store_result(&DB.conn);
            while ((DB.sql_row = mysql_fetch_row(DB.sql_result)) != NULL)
            {
                check = false;
                cout << "ID : " << DB.sql_row[0] << "\tName : " << DB.sql_row[1] << endl;
            }
            if (check)
                cout << "회원 목록이 없습니다" << endl;
        }
    }
}

void Member::Modify()
{
    int gradeChoice, sel;
    string ID, grade, column, change;
    cout << "정보를 수정할 회원등급을 선택하세요" << endl;
    cout << "1)일반\t2)vip" << endl;
    cin >> gradeChoice;
    switch (gradeChoice)
    {
    case 1:
        grade = "common";
        break;
    case 2:
        grade = "vip";
        break;
    default:
        cout << "잘못 입력하셨습니다" << endl;
        return;
    }
    cout << "회원 ID를 입력하세요" << endl;
    cin >> ID;
    cout << "수정할 항목을 선택하세요" << endl;
    cout << "1) PW\t2)name" << endl;
    cin >> sel;
    switch (sel)
    {
    case 1:
        column = "pw";
        cout << "변경할 PW를 입력하세요" << endl;
        break;
    case 2:
        column = "name";
        cout << "변경할 name을 입력하세요" << endl;
        break;
    default:
        cout << "잘못 입력하셨습니다" << endl;
        return;
    }
    cin >> change;
    sprintf(query, "UPDATE %s SET %s ='%s' where id = '%s'", grade.c_str(), column.c_str(), change.c_str(), ID.c_str());
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) == 0)
        {
            cout << "회원목록에 없는 회원입니다" << endl;
        }
        else
            cout << "수정되었습니다" << endl;
    }
}

void Member::Delete()
{
    int gradeChoice, sel;
    string ID, grade;
    cout << "정보를 삭제할 회원등급을 선택하세요" << endl;
    cout << "1)일반\t2)vip" << endl;
    cin >> gradeChoice;
    switch (gradeChoice)
    {
    case 1:
        grade = "common";
        break;
    case 2:
        grade = "vip";
        break;
    default:
        cout << "잘못 입력하셨습니다" << endl;
        return;
    }
    cout << "회원 ID를 입력하세요" << endl;
    cin >> ID;
    sprintf(query, "DELETE FROM %s WHERE id = '%s'", grade.c_str(), ID.c_str());
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) == 0)
        {
            cout << "회원목록에 없는 회원입니다" << endl;
        }
        else
        {
            sprintf(query, "INSERT INTO withdraw (id, membership) VALUES ('%s', '%s')", ID.c_str(), grade.c_str());
            if (mysql_query(&DB.conn, query) != 0)
                fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
            else
                cout << "삭제되었습니다" << endl;
        }
    }
}

void Member::Withdraw()
{
    bool check = true;
    cout << "== 탈퇴 회원 목록 ==" << endl;
    sprintf(query, "SELECT id, membership FROM withdraw");
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        while ((DB.sql_row = mysql_fetch_row(DB.sql_result)) != NULL)
        {
            check=false;
            cout << "ID : " << DB.sql_row[0] << "\tgrade : " << DB.sql_row[1] << endl;
        }
        if (check)
            cout << "탈퇴한 회원이 없습니다" << endl;
    }
}