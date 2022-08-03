#include <iostream>
#include <string>
#include <cstring>

#include "database.h"
#include "member.h"
#include "common.h"

Common::Common() : num(0)
{
    strcpy(this->query, query);
}

void Common::Common_Login() // 1. 로그인
{
    sprintf(query, "SELECT name FROM common WHERE pw ='%s' AND id='%s'", c.PW_Get().c_str(), c.ID_Get().c_str());
    if (mysql_query(&conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&conn));
    else
    {
        sql_result = mysql_store_result(&conn);
        sql_row = mysql_fetch_row(sql_result);
        cout << '\n'
             << "로그인 완료" << endl;
        cout << "[일반 회원] " << sql_row[0] << "님 어서오세요" << '\n'
             << endl;
        mysql_free_result(sql_result);
        Common_Select();
    }
}

void Common::Member_Join() // 2. 회원가입
{
    sprintf(query, "INSERT INTO common(name, pw, id) VALUES ('%s', '%s', '%s')", c.Name_Get().c_str(), c.PW_Get().c_str(), c.ID_Get().c_str());
    if (mysql_query(&conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&conn));
    else
        cout << '\n'
             << "[일반 회원] "
             << "가입 완료" << endl;
}

void Common::Change_Member_Info() // 변경
{
    string id_r, pw_r;
    cout << '\n'
         << "패스워드 변경합니다" << endl;
    cout << "ID 확인 : ";
    cin >> id_r;
    cout << "변경할 PW : ";
    cin >> pw_r;

    sprintf(query, "UPDATE common SET pw='%s' WHERE id='%s'", pw_r.c_str(), id_r.c_str());
    if (mysql_query(&conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&conn));
    else
        cout << "패스워드 변경 완료 되었습니다" << endl;
}

void Common::Cancel_Member() // 탈퇴
{
    string name_r, id_r, pw_r;
    cout << "이름을 확인 합니다" << endl;
    name_r = c.Name_Get();
    sprintf(query, "SELECT id, pw FROM common WHERE name='%s'", name_r.c_str());

    if (mysql_query(&conn, query) != 0)
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&conn));
    else
    {
        cout << "ID를 확인 :";
        cin >> id_r;
        cout << "PW 확인합니다 :";
        cin >> pw_r;
        sql_result = mysql_store_result(&conn);
        sql_row = mysql_fetch_row(sql_result);
        if (strcmp(sql_row[0], id_r.c_str()) == 0 && strcmp(sql_row[1], pw_r.c_str()) == 0)
        {
            withdraw(id_r, pw_r, name_r, "common");
            mysql_free_result(sql_result);
        }
    }
}

void Common::withdraw(string id, string pw, string name, string type)
{
    sprintf(query, "INSERT INTO withdraw(id, membership) VALUES ('%s', '%s')", id.c_str(), type.c_str());
    if (mysql_query(&conn, query) != 0)
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&conn));
    else
    {
        sql_result = mysql_store_result(&conn);
        if (mysql_affected_rows(&conn) != 0)
        {
            sprintf(query, "DELETE FROM common WHERE id='%s' AND pw='%s' AND name='%s'", id.c_str(), pw.c_str(), name.c_str());
            if (mysql_query(&conn, query) != 0)
                fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&conn));
            else
                cout << "탈퇴가 완료되었습니다. 이용해 주셔서 감사합니다" << endl;
                exit(1);
        }
    }
}

void Common::Check_trip() //여행지 조회
{
    sprintf(query, "SELECT * FROM visit");
    if (0 != mysql_query(&conn, query))
        fprintf(stderr, "database connect error : %s\n", mysql_error(&conn));
    else
    {
        sql_result = mysql_store_result(&conn);
        while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
            cout << sql_row[0] << ") " << sql_row[1] << " " << sql_row[2] << endl;
    }
}

void Common::Come_In()
{
    bool temp;
    c.Show_Info();
    cin >> num;
    switch (num)
    {
    case 1: //로그인
        Common_Login();
        break;
    case 2: //회원 가입
        Member_Join();
        break;
    default:
        break;
    }
}

void Common::Common_Select()
{

    while (1)
    {
        c.Common_Info(); // Common 회원 목록
        cin >> num;
        switch (num)
        {
        case 1: //관광지 조회
            Check_trip();
            break;
        case 2: //수정
            Change_Member_Info();
            break;
        case 3: //탈퇴
            Cancel_Member();
            break;
        default:
            break;
        }
    }
}
