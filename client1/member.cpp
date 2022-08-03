#include <iostream>
#include <string>
#include <cstring>
#include "member.h"
#include "common.h"
#include "database.h"


Member::Member()
{
    this->id = id;
    this->pw = pw;
    this->name = name;
}

string Member::ID_Get()
{
    cout << "ID: ";
    cin >> id;
    return id;
}

string Member::PW_Get()
{
    cout << "PW: ";
    cin >> pw;
    return pw;
}

string Member::Name_Get()
{
    cout << "Name: ";
    cin >> name;
    return name;
}

void Member::Show_Info() const
{
    cout << "=== 여행사 입니다 ===" << endl;
    cout << "1. 로그인" << endl;
    cout << "2. 회원가입" << endl;
    cout << "입력: ";
}

void Member::Common_Info() const
{
    cout << "=== 일반 회원 목록 ===" << endl;
    cout << "1. 관광지 조회" << endl;
    cout << "2. 내정보 수정" << endl;
    cout << "3. 탈퇴" << endl;
    cout << "입력: ";
}