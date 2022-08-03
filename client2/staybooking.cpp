#include "staybooking.h"
using namespace std;

void StayBooking::Menu(string ID)
{
    loginID = ID;
    cout<<"1) 숙박 예약 하기"<<endl;
    cout<<"2) 숙박 예약 조회"<<endl;
}

void StayBooking::Choose()
{
    cin>>choice;
    switch(choice)
    {
        case 1:
            Book();
            break;
        case 2:
            Check();
            break;
        default:
            cout<<"잘못 입력하셨습니다"<<endl;
            break;
    }
}

string StayBooking::Location()
{
    cout<<"숙소 명을 입력하세요"<<endl;
    cin>>where;
    sprintf(query, "SELECT stayname FROM stay WHERE stayname = '%s'", where.c_str());
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) == 0)
        {
                cout << "등록되지 않은 숙소입니다" << endl;
                return "0";
        }
    }
    return where;
    
}

string StayBooking::Date()
{
    int year, month, day;
    cout<<"예약 날짜의 연도를 입력하세요 ex)2022"<<endl;
    cin>>year;
    if(year<2022)
    {
        cout<<"예약불가능한 연도입니다"<<endl;
        return "0";
    }
    else
        date = to_string(year);

    cout <<"예약 날짜의 월을 입력하세요"<< endl;
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
        return "0";
    }
    cout <<"예약 날짜의 일을 입력하세요" << endl;
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
            return "0";
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
            return "0";
        }
    }
    return date;


}


void StayBooking::Book()
{
    where = Location();
    if(where == "0")
        return;
    
    date = Date();
    if(date == "0")
        return;
    
    sprintf(query, "INSERT INTO staylist (id, stayname, staydate) VALUES ('%s', '%s', '%s')", loginID.c_str(), where.c_str(), date.c_str());
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
        cout<<"예약이 완료되었습니다"<<endl;

}


void StayBooking::Check()
{
    cout<<"== 예약 목록 =="<<endl;
    int check = 0;
    sprintf(query, "SELECT stayname, staydate FROM staylist WHERE id = '%s'", loginID.c_str());
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        while ((DB.sql_row = mysql_fetch_row(DB.sql_result)) != NULL)
        {
            cout << loginID << "님 예약 날짜: " << DB.sql_row[1] << " 예약 숙소 : " << DB.sql_row[0] << endl;
            check++;
        }
        if (check == 0)
            cout << "예약 내역이 없습니다" << endl;
        else
            Change();
    }
}


void StayBooking::Change()
{
    cout<<"1) 예약내역 수정"<<endl;
    cout<<"2) 예약내역 삭제"<<endl;
    cout<<"3) 돌아가기"<<endl;
    cin>>choice;
    switch(choice)
    {
        case 1:
            Modify();
            break;
        case 2:
            Delete();
            break;
        default:
            if(choice != 3)
                cout<<"잘못 선택하셨습니다"<<endl;
            return;
    }
}


void StayBooking::Modify()
{
    cout<<"1) 날짜 수정"<<endl;
    cout<<"2) 숙소 수정"<<endl;
    cin>>choice;
    
    switch(choice)
    {
        case 1:
            cout<<"예약 날짜를 수정하고 싶은 ";
            where = Location();
            if(where == "0")
                return;
            cout<<"바꿀 ";
            date = Date();
            if(date == "0")
                return;
            sprintf(query, "UPDATE staylist SET staydate ='%s' where stayname = '%s' AND id = '%s'", date.c_str(), where.c_str(), loginID.c_str());
            if (mysql_query(&DB.conn, query) != 0)
                fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
            else
                cout<<"예약이 수정되었습니다"<<endl;
            break;

        case 2:
            cout<<"숙소를 수정하고 싶은 ";
            date = Date();
            if(date == "0")
                return;
            cout<<"바꿀 ";
            where = Location();
            if(where == "0")
                return;
            sprintf(query, "UPDATE staylist SET stayname ='%s' where staydate = '%s' AND id = '%s'", where.c_str(), date.c_str(), loginID.c_str());
            if (mysql_query(&DB.conn, query) != 0)
                fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
            else
            {
                DB.sql_result = mysql_store_result(&DB.conn);
                if (mysql_affected_rows(&DB.conn) == 0)
                    cout<<"존재하지 않는 예약입니다"<<endl;
                else
                    cout<<"예약이 수정되었습니다"<<endl;
            }
            break;

        default:
            cout<<"잘못 선택하셨습니다"<<endl;
            return;
    }
}

void StayBooking::Delete()
{
    cout<<"취소하고 싶은 ";
    where = Location();
    if(where == "0")
        return;
    cout<<"취소하고 싶은 ";
    date = Date();
    if(date == "0")
        return;
    sprintf(query, "DELETE FROM staylist WHERE stayname = '%s' AND staydate = '%s' AND id = '%s'", where.c_str(), date.c_str(), loginID.c_str());
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
    {
        DB.sql_result = mysql_store_result(&DB.conn);
        if (mysql_affected_rows(&DB.conn) == 0)
            cout<<"존재하지 않는 예약입니다"<<endl;
        else
            cout<<"예약이 취소되었습니다"<<endl;
    }

}