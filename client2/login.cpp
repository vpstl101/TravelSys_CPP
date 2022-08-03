#include "login.h"
#include <iostream>

string Login::Vip_Login()
{
    string id, pw;
    cout << "ID :";
    cin >> id;
    cout << "pw :";
    cin >> pw;

    sprintf(query, "SELECT name FROM vip WHERE id ='%s' AND pw='%s'", id.c_str(), pw.c_str());
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
     else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) != 0)
        {
            DB.sql_row = mysql_fetch_row(DB.sql_result);
            cout << '\n'
                 << "로그인 완료" << endl;
            cout << "[VIP] " << DB.sql_row[0] << "님 어서오세요" << '\n'
                 << endl;
            mysql_free_result(DB.sql_result);
            return id;
        }
        else
        {
            cout << "로그인 정보가 올바르지 않습니다" << endl;
            return "0";
        }
    }
}
