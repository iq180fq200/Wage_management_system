#ifndef ___ALLWORKERS___
#define ___ALLWORKERS___

#include <string>
#include <iostream>

using namespace std;

#define EMPLOYEE_BASIC_SALARY 5000
#define MANAGER_BASIC_SALARY 8000
#define TECHNICAN_BASIC_SALARY 10000
#define NOTEXIST -1
enum { EMPLOYEE, TECHNICAN, MANAGER };


class Employee {
protected:
    int number;						//工号:不要以0开头，不然excel会自动去掉
    int position;                   //员工类别
    int age;						//年龄
    string name;					//姓名3
    string sex;						//性别
    string isFired;                 //是否被开除
    string startYear;
    void SetFired(bool cho);        //目的是不让使用者来开出员工而是通过excel来删除
public:
    Employee(int num, string na, int tage = 66, int tpositon = 0, string tsex = "male", string sta = "2020", string isF = "NO");  //需要自己输入工号、姓名的构造函数
    Employee();						//无参(默认)构造函数
    int GetNumber();					//获取工号     
    int GetAge();						//获取员工年龄
    string GetName();					//获取员工姓名
    string GetSex();					//获取员工性别
    string GetStartYear();
    string GetFired();                  //获取是否被开除信息
    int GetPosition();
    int GetSalary();           //计算工资
    void SetNumber(int num);            //修改工号
    void SetName(string tname);	//修改姓名
    void SetSex(string tsex);			//修改性别
    void SetAge(int tage);				//修改年龄    
    void SetStartYear(string start);
    void SetPosition(int po);

    friend class SuperExcel;
};



#endif // !___ALLWORKERS___


