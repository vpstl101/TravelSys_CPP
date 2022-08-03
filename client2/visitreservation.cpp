#include "visitreservation.h"
using namespace std;

void Visitreservation::Choose(string id)
{
    login_id = id;
    cout << "1.관광지 예약 2.예약 조회 3.날짜 변경" << endl;
    cin >> num;
    switch (num)
    {
    case 1:
        Reservation();
        break;
    case 2:
        Reser_Check();
        break;
    case 3:
        Change_Reser();
        break;
    default:
        break;
    }
}

void Visitreservation::Reservation() //방문예약
{
    string beach, date;
    cout << "== 관광지 방문 예약 ==" << endl;
    cout << "관광지를 입력하세요: ";
    cin >> beach;

    sprintf(query, "SELECT beach FROM visit WHERE beach = '%s'", beach.c_str());
    if (0 != mysql_query(&DB.conn, query))
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) != 0)
        {
            cout << "날짜 입력 ex) 2222-01-01" << endl;
            cin >> date;
            DB.sql_row = mysql_fetch_row(DB.sql_result);
            if (strcmp(DB.sql_row[0], beach.c_str()) == 0)
                Visit_date(beach, date); //함수
        }
        else
        {
            cout << "재입력 바람" << endl;
            return;
        }
    }
}

void Visitreservation::Visit_date(string beach, string date)
{
    sprintf(query, "INSERT INTO visitlist (id, visit, visitdate) VALUES ('%s', '%s', '%s')", login_id.c_str(), beach.c_str(), date.c_str());
    if (0 != mysql_query(&DB.conn, query))
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) != 0)
            cout << " 예약 되었습니다" << endl;
        else
        {
            cout << " 수정불가" << endl;
            return;
        }
    }
}

void Visitreservation::Reser_Check() //예약 확인
{
    sprintf(query, "SELECT id, visit, visitdate FROM visitlist WHERE id = '%s'", login_id.c_str());
    if (0 != mysql_query(&DB.conn, query))
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        cout << "==" << login_id << "=="
             << "님 예약내역" << endl;
        while ((DB.sql_row = mysql_fetch_row(DB.sql_result)) != NULL)
            cout << DB.sql_row[1] << ") " << DB.sql_row[2] << endl;
        return;
    }
}

void Visitreservation::Change_Reser() // 수정
{
    string beach, date, reser_num;
    int tep;
    sprintf(query, "SELECT num, visit, visitdate FROM visitlist WHERE id = '%s'", login_id.c_str());
    if (0 != mysql_query(&DB.conn, query))
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) != 0)
        {
            cout << "==" << login_id << "=="
                 << "님 예약내역" << endl;
            while ((DB.sql_row = mysql_fetch_row(DB.sql_result)) != NULL)
            {
                cout << DB.sql_row[0] << " " << DB.sql_row[1] << ") " << DB.sql_row[2] << endl;
            }
            cout << "예약된 번호를 입력해주세요 : ";
            cin >> reser_num;
            tep = stoi(reser_num);
            cout << "희망하는 변경 날짜 입력 ex) 2222-01-01" << endl;
            cin >> date;
        }
    }

    sprintf(query, "UPDATE visitlist SET visitdate='%s' WHERE id='%s' AND num='%d'", date.c_str(), login_id.c_str(), tep);
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) == 0)
            cout << "존재하지 않는 예약입니다" << endl;
        else
            cout << "예약이 수정 되었습니다" << endl;
    }
}
