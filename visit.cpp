#include "header/visit.h"
using namespace std;

void Visit::Menu()
{
    cout << "(1) 관광지 정보 조회" << endl;
    cout << "(2) 관광지 예약 관리" << endl;
}

void Visit::Check()
{
    sprintf(query, "SELECT * FROM visit");
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        while ((DB.sql_row = mysql_fetch_row(DB.sql_result)) != NULL)
            cout << DB.sql_row[0] << ") " << DB.sql_row[1] << " : " << DB.sql_row[3] << "\n\t\t" << DB.sql_row[2] << endl;
    }
}

void Visit::ManageCheck()
{
    bool check = true;
    sprintf(query, "SELECT * FROM visitlist");
    cout << "== 예약 내역 ==" << endl;
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        while ((DB.sql_row = mysql_fetch_row(DB.sql_result)) != NULL) // select 결과 없을 때 까지
        {
            cout << DB.sql_row[0] << "번 예약) " << DB.sql_row[1] << "님 예약날짜 : " << DB.sql_row[3] << " 장소 : " << DB.sql_row[2] << endl;
            check = false;
        }
        if (check)
            cout << "예약 내역이 없습니다" << endl;
    }
}

void Visit::ManageModify()
{
    int num, choose;
    string column, change;
    cout << "수정할 예약 번호를 입력하세요" << endl;
    cin >> num;
    sprintf(query, "SELECT num FROM visitlist WHERE num = %d", num);
    if (mysql_query(&DB.conn, query) != 0)
            fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) == 0)  // query 실행 결과로 나온 행 개수 0이면
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
        column = "visit";
        cout << "장소 입력" << endl;
        cin >> change;
        sprintf(query, "SELECT beach FROM visit WHERE beach = '%s'", change.c_str());
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
        break;
    case 2:
        int year, month, day;
        column = "visitdate";
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
    
    
    sprintf(query, "UPDATE visitlist SET %s ='%s' where num = %d", column.c_str(), change.c_str(), num);
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

void Visit::ManageDelete()
{
    int num;
    cout << "삭제할 예약 번호를 입력하세요" << endl;
    cin >> num;
    sprintf(query, "DELETE FROM visitlist where num = %d", num);
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


void Visit::ManageBook()
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
        cout<<"예약할 관광지를 입력하세요"<<endl;
        cin>>name;
        sprintf(query, "SELECT beach FROM visit WHERE beach = '%s'", name.c_str());
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
        sprintf(query, "INSERT INTO visitlist (id, visit, visitdate) VALUES ('%s','%s', '%s')", id.c_str(), name.c_str(), date.c_str());
        if (mysql_query(&DB.conn, query) != 0)
            fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
        else
            cout<<"예약이 완료되었습니다"<<endl;
    }

}

void Visit::Add()
{
    string beach, explain, addr;
    cout<<"관광지 이름을 입력하세요"<<endl;
    cin>> beach;
    cin.ignore();
    cout<<"관광지 설명을 입력하세요"<<endl;
    cin>> explain;
    cin.ignore();
    cout<<"관광지 주소를 입력하세요"<<endl;
    cin>> addr;
    cin.ignore();
    sprintf(query, "INSERT INTO visit (beach, summary, addr) VALUES ('%s', '%s', '%s')", beach.c_str(), explain.c_str(), addr.c_str());
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
        cout<<"추가되었습니다"<<endl;

}


void Visit::Edit()
{
    int num, visitnum;
    string change, column;
    cout<<"수정할 관광지 번호를 입력하세요"<<endl;
    cin>>visitnum;
    cin.ignore();
    sprintf(query, "SELECT num FROM visit WHERE num = '%d'", visitnum);
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
        cout<<"1) 관광지명 변경\t2) 관광지설명 변경\t3)관광지주소 변경"<<endl;
        cin>>num;
        switch(num)
        {
            case 1:
                cout<<"관광지명을 입력하세요"<<endl;
                column = "beach";
                cin>>change;
                break;
            case 2:
                cout<<"관광지설명을 입력하세요"<<endl;
                column = "summary";
                cin>>change;
                break;
            case 3:
                cout<<"관광지주소를 입력하세요"<<endl;
                column = "addr";
                cin>>change;
                break;
            default:
                cout<<"잘못 입력하셨습니다"<<endl;
                return;
        }
        sprintf(query, "UPDATE visit SET %s = '%s' WHERE num = %d", column.c_str(), change.c_str(), visitnum);
        if (mysql_query(&DB.conn, query) != 0)
            fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
        else
            cout << "수정되었습니다" << endl;
    }
}


void Visit::Remove()
{
    int num;
    cout<<"삭제할 관광지 번호를 입력하세요"<<endl;
    cin>>num;
    cin.ignore();
    sprintf(query, "DELETE FROM visit where num = %d", num);
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