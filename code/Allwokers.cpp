#include"Allworkers.h"
#include <ctime>
#include <cstdio>
Employee::Employee()
{
    number = 666;
    position = EMPLOYEE;
    age = 66;
    name = "Nobody";
    sex = "male";
    startYear = "2020";
    isFired = "NO";
}

Employee::Employee(int num, string na, int tage, int tpositon, string tsex, string sta, string isF)
{
    number = num;
    name = na;
    age = tage;
    position = tpositon;
    sex = tsex;
    startYear = sta;
    isFired = isF;
}

int Employee::GetNumber()
{
    return number;
}
int Employee::GetAge()
{
    return age;
}

string Employee::GetName()
{
    return name;
}

string Employee::GetSex()
{
    return sex;
}
string Employee::GetStartYear()
{
    return startYear;
}

void Employee::SetName(string tname)
{
    name = tname;
}
void Employee::SetSex(string tsex)
{
    sex = tsex;
}
void Employee::SetStartYear(string start)
{
    startYear = start;
}
void Employee::SetAge(int tage)
{
    age = tage;
}

void Employee::SetNumber(int num)
{
    number = num;
}

int Employee::GetPosition()
{
    return position;
}

void Employee::SetPosition(int po)
{
    position = po;
}

string Employee::GetFired()
{
    return isFired;
}

void Employee::SetFired(bool cho)
{
    if (cho)
        isFired = "YES";
    else
        isFired = "NO";
}


int Employee::GetSalary()
{
    int currentYear;
    int startYear;
    int rate;
    int base;
    time_t nowtime;
    //首先创建一个time_t 类型的变量nowtime
    struct tm* p;
    //然后创建一个新时间结构体指针 p 
    time(&nowtime);
    //使用该函数就可得到当前系统时间，使用该函数需要将传入time_t类型变量nowtime的地址值。
    p = localtime(&nowtime);
    currentYear = p->tm_year + 1900;
    startYear = atoi(this->startYear.c_str());

    if (position == EMPLOYEE)
    {
        base = EMPLOYEE_BASIC_SALARY;
        rate = 200;
    }
    else if (position == TECHNICAN)
    {
        base = TECHNICAN_BASIC_SALARY;
        rate = 666;
    }
    else if (position == MANAGER)
    {
        base = MANAGER_BASIC_SALARY;
        rate = 500;
    }
    return base + (currentYear - startYear)*rate;
}
