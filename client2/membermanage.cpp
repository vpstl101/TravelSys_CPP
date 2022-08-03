#include "membermanage.h"
#include <unistd.h>

using namespace std;

void Management::Manage_Choose(string id)
{
    login_id = id;
    cout<<"1.수정/변경 2.탈퇴"<<endl;
    cin>>num;
    switch (num)
    {
    case 1:
        Change_Member_Info();
        break;
    case 2:
        Cancel_Member();
        break;
    default:
        break;
    }
}

void Management::Change_Member_Info() // 변경
{
    string pw;
    cout << '\n'
         << "패스워드 변경합니다" << endl;
    cout << "변경 PW : ";
    cin >> pw;

    sprintf(query, "UPDATE vip SET pw='%s' WHERE id='%s'", pw.c_str(), login_id.c_str());
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) != 0)
            cout << "패스워드 변경 완료 되었습니다" << endl;
        else
        {
            cout << "ID 틀렸습니다" << endl;
            return;
        }
    }
}

void Management::Cancel_Member() // 탈퇴
{
    string name, pw, id;
    cout << "이름을 확인 합니다" << endl;
    cin>>name;

    sprintf(query, "SELECT id, pw FROM vip WHERE name='%s'", name.c_str());

    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) != 0)
        {
            cout << "ID를 확인 :";
            cin >> id;
            cout << "PW 확인합니다 :";
            cin >> pw;
            DB.sql_row = mysql_fetch_row(DB.sql_result);
            if (strcmp(DB.sql_row[0], id.c_str()) == 0 && strcmp(DB.sql_row[1], pw.c_str()) == 0)
            {
                withdraw(id, pw, name, "vip"); //함수
                mysql_free_result(DB.sql_result);
            }
            else
            {
                cout << " 틀렸습니다" << endl;
                return;
            }
        }
        else
        {
            cout << " 틀렸습니다" << endl;
            return;
        }
    }
}

void Management::withdraw(string id, string pw, string name, string type)
{
    sprintf(query, "INSERT INTO withdraw(id, membership) VALUES ('%s', '%s')", id.c_str(), type.c_str());
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) != 0)
        {
            sprintf(query, "DELETE FROM vip WHERE id='%s' AND pw='%s' AND name='%s'", id.c_str(), pw.c_str(), name.c_str());
            if (mysql_query(&DB.conn, query) != 0)
                fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&DB.conn));
            else
                cout << "탈퇴가 완료되었습니다. 이용해 주셔서 감사합니다" << endl;
            exit(1);
        }
    }
}
