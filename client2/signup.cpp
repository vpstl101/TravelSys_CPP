#include "signup.h"
#include <iostream>

void Signup::Vip_Join() 
{
    string id, pw, name;
    cout<< "ID : "<<endl;
    cin >>id;
    cout<< "PW : "<<endl;
    cin >>pw;
    cout<< "NAME : "<<endl;
    cin >>name;
    
    sprintf(query, "INSERT INTO vip(id, pw, name) VALUES ('%s', '%s', '%s')", id.c_str(), pw.c_str(), name.c_str());
    if (mysql_query(&DB.conn, query) != 0)
        fprintf(stderr, "database connect error : %s\n", mysql_error(&DB.conn));
    else
        cout << '\n'
             << "[VIP] "
             << "가입 완료" << endl;
}
