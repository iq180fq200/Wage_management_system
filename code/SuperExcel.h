#ifndef ___SuperExcel___
#define ___SuperExcel___


#include <fstream>
#include <string>  
#include <iostream>  
#include <sstream>
#include"Allworkers.h"
using namespace std;
class SuperExcel
{
public:
    SuperExcel(string filename);  //构造函数,根据文件名打开文件
    Employee GetEmployee(int i);   //获取文件中第i行员工信息
    void AddEmployee(Employee& e);  //写入一个员工对象到文件最后一行
    int GetTotal();                 //获取所有员工数量
    int GetFired();                 //获取被开除的员工数量
    int GetCurrent();               //获取在岗员工
    void SaveObject(Employee &e);     //把修改后的员工对象传进来，这个函数替换掉文件中原来那个员工的信息,相当于编辑
    Employee findEmployeeByID(int ID);             //用于单个搜索    
    Employee findEmployeeByName(string name);      //用于单个搜索，只返回一个名字符合的对象，重名的话后面不返回
    int findEmployeeIndex(Employee&e);
    void deleteEmployee(Employee &e);
    //如果想搜索很多内容，用一个while循环加getEmployee(i)获得对象，再找符合的就行；循环结束的条件是getEmployee返回一个工号是-1的对象
    int getMax();
private:
    SuperExcel(const SuperExcel& excel); //不允许拷贝构造函数
    string filename;
    int total;
    int fired;
    int currentEmployee;
    Employee SplitString(string s);
    int Max;
};


#endif // !___SuperExcel___
