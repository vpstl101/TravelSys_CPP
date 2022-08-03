#include "header/stay.h"
using namespace std;

void Stay::Menu()
{
    cout << "(1) 숙박업소 정보 조회" << endl;
    cout << "(2) 숙박업소 예약 관리" << endl;
}

void Stay::Check()
{
    sprintf(query, "SELECT * FROM stay");
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        while ((DB.sql_row = mysql_fetch_row(DB.sql_result)) != NULL)
            cout << DB.sql_row[0] << ") " << DB.sql_row[1] << " 주소 : " << DB.sql_row[2] << "  전화번호 : " << DB.sql_row[3] << endl;
    }
}

void Stay::ManageCheck()
{
    bool check = true;
    sprintf(query, "SELECT * FROM staylist");
    cout << "== 예약 내역 ==" << endl;
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        while ((DB.sql_row = mysql_fetch_row(DB.sql_result)) != NULL)
        {
            cout << DB.sql_row[0] << "번 예약) " << DB.sql_row[1] << "님 예약날짜 : " << DB.sql_row[3] << " 장소 : " << DB.sql_row[2] << endl;
            check = false;
        }
        if (check)
            cout << "예약 내역이 없습니다" << endl;
    }
}

void Stay::ManageModify()
{
    int num, choose;
    string column, change;
    cout << "수정할 예약 번호를 입력하세요" << endl;
    cin >> num;
    sprintf(query, "SELECT num FROM staylist WHERE num = %d", num);
    if (mysql_query(&DB.conn, query) != 0)
            fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) == 0)
        {
            cout << "없는 번호입니다" << endl;
            return;
        }
    }
    cout << "수정할 내역을 선택하세요" << endl;
    cout << "1) 예약장소\t2) 예약날짜" << endl;
    cin >> choose;
    switch (choose)
    {
    case 1:
        column = "stayname";
        cout << "장소 입력" << endl;
        cin >> change;
        sprintf(query, "SELECT stayname FROM stay WHERE stayname = '%s'", change.c_str());
        if (mysql_query(&DB.conn, query) != 0)
            fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
        else
        {
            DB.sql_result = mysql_store_result(&DB.conn);
            if (mysql_affected_rows(&DB.conn) == 0)
            {
                cout << "등록되지 않은 숙소입니다" << endl;
                return;
            }
        }
        break;
    case 2:
        int year, month, day;
        column = "staydate";
        cout << "연도 입력 ex)2022" << endl;
        cin >> year;
        if(year<2022)
        {
            cout<<"예약불가능한 연도입니다"<<endl;
            return;
        }
        else
            change = to_string(year);

        cout <<"월 입력 ex) 5"<< endl;
        cin>> month;
        if(month>0 && month<13)
        {
            if(month<10)
                change = change + "0";

            change = change + to_string(month);

        }
        else
        {
            cout<<"월 입력이 잘못되었습니다"<<endl;
            return;
        }
        cout <<"일 입력 ex) 10" << endl;
        cin>>day;
        if(month == 1 || month == 3 || month == 5 || month ==7 || month == 8 || month == 10 || month == 12)
        {
            if(day>0 && day<32)
            {
                if(day<10)
                    change = change + "0";
                
                change = change + to_string(day);
            }
            else
            {
                cout<<"잘못된 날짜입니다"<<endl;
                return;
            }
        } 
        else
        {
            if(day>0 && day<31)
            {
                if(day<10)
                    change = change + "0";
                
                change = change + to_string(day);
            }
            else
            {
                cout<<"잘못된 날짜입니다"<<endl;
                return;
            }
        }
        break;
    default:
        cout << "잘못 입력하셨습니다" << endl;
        return;
    }

    sprintf(query, "UPDATE staylist SET %s ='%s' where num = %d", column.c_str(), change.c_str(), num);
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) == 0)
            cout << "예약목록에 없습니다" << endl;
        else
            cout << "수정되었습니다" << endl;
    }
}

void Stay::ManageDelete()
{
    int num;
    cout << "삭제할 예약 번호를 입력하세요" << endl;
    cin >> num;
    sprintf(query, "DELETE FROM staylist where num = %d", num);
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) == 0)
            cout << "예약목록에 없는 번호입니다" << endl;
        else
            cout << "삭제되었습니다" << endl;
    }
}


void Stay::ManageBook()
{
    cout<<"예약할 아이디를 입력하세요"<<endl;
    cin>>id;
    sprintf(query, "SELECT id FROM common WHERE id = '%s'", id.c_str());
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) == 0)
        {
            sprintf(query, "SELECT id FROM vip WHERE id = '%s'", id.c_str());
            if (mysql_query(&DB.conn, query) != 0)
                fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
            else
                DB.sql_result = mysql_store_result(&DB.conn);
                if (mysql_affected_rows(&DB.conn) == 0)
                {
                    cout<<"회원목록에 없는 ID입니다"<<endl;
                    return;
                }
        }
        cout<<"예약할 숙소를 입력하세요"<<endl;
        cin>>name;
        sprintf(query, "SELECT stayname FROM stay WHERE stayname = '%s'", name.c_str());
        if (mysql_query(&DB.conn, query) != 0)
            fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
        else
        {
            DB.sql_result = mysql_store_result(&DB.conn);
            if (mysql_affected_rows(&DB.conn) == 0)
            {
                cout << "등록되지 않은 관광지입니다" << endl;
                return;
            }
        }
        cout<<"예약할 날짜를 입력하세요"<<endl;
        cout << "연도 입력 ex)2022" << endl;
        cin >> year;
        if(year<2022)
        {
            cout<<"예약불가능한 연도입니다"<<endl;
            return;
        }
        else
        date = to_string(year);
        cout <<"월 입력 ex) 5"<< endl;
        cin>> month;
        if(month>0 && month<13)
        {
            if(month<10)
                date = date + "0";
            date = date + to_string(month);
        }
            else
            {
                cout<<"월 입력이 잘못되었습니다"<<endl;
                return;
            }
            cout <<"일 입력 ex) 10" << endl;
            cin>>day;
            if(month == 1 || month == 3 || month == 5 || month ==7 || month == 8 || month == 10 || month == 12)
            {
                if(day>0 && day<32)
                {
                    if(day<10)
                        date = date + "0";
                    
                    date = date + to_string(day);
                }
                else
                {
                    cout<<"잘못된 날짜입니다"<<endl;
                    return;
                }
            } 
            else
            {
                if(day>0 && day<31)
                {
                    if(day<10)
                        date = date + "0";
                
                    date = date + to_string(day);
                }
                else
                {
                    cout<<"잘못된 날짜입니다"<<endl;
                    return;
                }
            }
            sprintf(query, "INSERT INTO staylist (id, stayname, staydate) VALUES ('%s','%s', '%s')", id.c_str(), name.c_str(), date.c_str());
            if (mysql_query(&DB.conn, query) != 0)
                fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
            else
                cout<<"예약이 완료되었습니다"<<endl;

    }
}


void Stay::Add()
{
    string stay, number, addr;
    cout<<"숙소 이름을 입력하세요"<<endl;
    cin>> stay;
    cin.ignore();
    cout<<"숙소 주소를 입력하세요"<<endl;
    cin>> addr;
    cin.ignore();
    cout<<"숙소 전화번호를 입력하세요"<<endl;
    cin>> number;
    cin.ignore();
    sprintf(query, "INSERT INTO stay (stayname, stayaddr, staynumber) VALUES ('%s', '%s', '%s')", stay.c_str(), addr.c_str(), number.c_str());
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
        cout<<"추가되었습니다"<<endl;

}


void Stay::Edit()
{
    int num, staynum;
    string change, column;
    cout<<"수정할 숙소 번호를 입력하세요"<<endl;
    cin>>staynum;
    cin.ignore();
    sprintf(query, "SELECT num FROM visit WHERE num = '%d'", staynum);

    if(mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database error : %s\n", mysql_error(&DB.conn));
    else
    {   
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) == 0)
        {
            cout << "등록되지 않은 번호입니다" << endl;
            return;
        }
        cout<<"1) 숙소명 변경\t2) 숙소주소 변경\t3)숙소 전화번호 변경"<<endl;
        cin>>num;
        switch(num)
        {
            case 1:
                cout<<"숙소명을 입력하세요"<<endl;
                column = "stayname";
                cin>>change;
                break;
            case 2:
                cout<<"숙소주소을 입력하세요"<<endl;
                column = "stayaddr";
                cin>>change;
                break;
            case 3:
                cout<<"숙소전화번호를 입력하세요"<<endl;
                column = "staynumber";
                cin>>change;
                break;
            default:
                cout<<"잘못 입력하셨습니다"<<endl;
                return;
        }
        sprintf(query, "UPDATE stay SET %s = '%s' WHERE num = %d", column.c_str(), change.c_str(), staynum);
        if (mysql_query(&DB.conn, query) != 0)
            fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
        else
            cout << "수정되었습니다" << endl;
    }
}


void Stay::Remove()
{
    int num;
    cout<<"삭제할 숙소 번호를 입력하세요"<<endl;
    cin>>num;
    cin.ignore();
    sprintf(query, "DELETE FROM stay where num = %d", num);
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) == 0)
            cout << "목록에 없는 번호입니다" << endl;
        else
            cout << "삭제되었습니다" << endl;
    }

}