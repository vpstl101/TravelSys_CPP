#include "visit.h"
using namespace std;

void Visit::Check()
{
    int num, sel;
    cout<<"1) 관광지 정보 조회"<<endl;
    cout<<"2) 숙박 정보 조회"<<endl;
    cin>>sel;
    switch(sel)
    {
        case 1:
            if(mysql_query(&DB.conn, "SELECT * FROM visit"))
                fprintf(stderr, "database error : %s\n", mysql_error(&DB.conn));
            else
            {
                DB.sql_result = mysql_store_result(&DB.conn);
                while((DB.sql_row = mysql_fetch_row(DB.sql_result)) != NULL)
                    cout << DB.sql_row[0] << ") " << DB.sql_row[1] << " : " << DB.sql_row[3] << "\n\t\t" << DB.sql_row[2] << endl;
            }
            break;
        case 2:
            if(mysql_query(&DB.conn, "SELECT * FROM stay"))
                fprintf(stderr, "database error : %s\n", mysql_error(&DB.conn));
            else
            {   
                DB.sql_result = mysql_store_result(&DB.conn);
                while ((DB.sql_row = mysql_fetch_row(DB.sql_result)) != NULL)
                    cout << DB.sql_row[0] << ") " << DB.sql_row[1] << " 주소 : " << DB.sql_row[2] << "  전화번호 : " << DB.sql_row[3] << endl;
            }
            break;           

        default:
            cout<<"잘못 입력하셨습니다"<<endl;
            break;
    }
    
    
    while(1)
    {
        cout<<"0) 뒤로가기"<<endl;
        cin>>num;
        if(num == 0)
            return;
    }
}   
