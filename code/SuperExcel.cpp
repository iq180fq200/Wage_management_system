#include "SuperExcel.h"

SuperExcel::SuperExcel(string filename)
{

    this->filename = filename;
    int count = 0;
    int fir = 0;
    ifstream inf;
    inf.open(filename, ios::in);
    string s;
    int i=0;
    int num;
    Max = 0;
    if (!(filename.rfind(".csv") == string::npos))
    {
        while (getline(inf, s))
        {
            if (i == 0)
            {
                i++;
                continue;
            }
            num = SplitString(s).GetNumber();
            if (num > Max) Max = num;

            count++;   //计算总员工数
            if (s.find("YES") != string::npos)
                fir++;
        }
    }
    total = count;
    fired = fir;
    currentEmployee = total - fired;
    inf.close();
}

void SuperExcel::AddEmployee(Employee&e)
{
    if (filename.rfind(".csv") == string::npos)
    {
        //打开的不是excel文件
        return;
    }
    ofstream excel;
    excel.open(filename, ios::app);  //输入一个对象到文件末尾
    excel << e.GetNumber() << "," << e.GetName() << "," << e.GetSex() << "," << e.GetAge() << "," << e.GetPosition() << "," << e.GetStartYear() << "," << e.GetFired() << "," << endl;
    total++;
    currentEmployee++;
    excel.close();
}

//将字符串拆分成属性值
Employee SuperExcel::SplitString(string s)
{
    Employee e;
    ifstream excel;
    string item;
    size_t sec1 = 0, sec2;

    //通过字符串截取的方式获得，代码效率有点低，时间紧迫，回头有空再修改
        //获取工号
    sec2 = s.find_first_of(",");
    item = s.substr(sec1, sec2);
    e.SetNumber(atoi(item.c_str()));
    sec1 = sec2 + 1;
    s = s.substr(sec1);
    //获取姓名
    sec2 = s.find_first_of(",");
    item = s.substr(0, sec2);
    e.SetName(item);
    sec1 = sec2 + 1;
    s = s.substr(sec1);
    //获取性别
    sec2 = s.find_first_of(",");
    item = s.substr(0, sec2);
    e.SetSex(item);
    sec1 = sec2 + 1;
    s = s.substr(sec1);
    //获取年龄
    sec2 = s.find_first_of(",");
    item = s.substr(0, sec2);
    e.SetAge(atoi(item.c_str()));
    sec1 = sec2 + 1;
    s = s.substr(sec1);
    //获取职位
    sec2 = s.find_first_of(",");
    item = s.substr(0, sec2);
    e.SetPosition(atoi(item.c_str()));
    sec1 = sec2 + 1;
    s = s.substr(sec1);
    //获取入职年份
    sec2 = s.find_first_of(",");
    item = s.substr(0, sec2);
    e.SetStartYear(item);
    sec1 = sec2 + 1;
    s = s.substr(sec1);
    //获取开除信息
    sec2 = s.find_first_of(",");
    item = s.substr(0, sec2);
    if (item == "YES")
        e.SetFired(true);
    else
        e.SetFired(false);
    sec1 = sec2 + 1;
    s = s.substr(sec1);
    return e;
}

Employee SuperExcel::GetEmployee(int num)
{
    Employee e;
    e.SetNumber(NOTEXIST);

    if (num <= 0)
    {
        return e;   //不存在这个人，返回一个工号为-1的对象
    }
    int i;
    ifstream excel;
    string s, item;
    size_t sec1 = 0, sec2;
    excel.open(filename, ios::in);
    for (i = 0; i < num; i++)
    {
        getline(excel, s);  //抛弃前面的
    }
    if (getline(excel, s))        //如果这行内容存在
    {
        e = SplitString(s);
        excel.close();
        return e;
    }
    //超过总人数
    excel.close();
    return e;
}

int SuperExcel::GetTotal()
{
    return total;
}

int SuperExcel::GetFired()
{
    return fired;
}
int SuperExcel::GetCurrent()
{
    return currentEmployee;
}

void SuperExcel::SaveObject(Employee &e)
{
    if (filename.rfind(".csv") == string::npos)
    {
        //打开的不是excel文件
        return;
    }

    ifstream in;
    ofstream out;
    string s, ID, item;
    size_t sec1 = 0, sec2;
    ID = to_string(e.GetNumber());

    //首先将修改的内容输入到另一个文件里
    in.open(filename, ios::in);
    out.open("data2.csv", ios::out); //打开输出文件,会不会清空呢？打开同一个就会，所以先打开一个拷贝文件

    while (getline(in, s))
    {
        sec2 = s.find_first_of(",");
        item = s.substr(sec1, sec2);
        if (item != ID)
            out << s << endl;
        else
            out << e.GetNumber() << "," << e.GetName() << "," << e.GetSex() << "," << e.GetAge() << "," << e.GetPosition() << "," << e.GetStartYear() << "," << e.GetFired() << "," << endl;
    }

    in.close();
    out.close();

    //再将另一个文件的内容拷贝回来
    in.open("data2.csv", ios::in);
    out.open(filename, ios::out);
    while (getline(in, s))
    {
        out << s << endl;
    }
    in.close();
    out.close();

}

Employee SuperExcel::findEmployeeByID(int ID)
{
    ifstream in;
    string s, id, item;
    size_t sec1 = 0, sec2;
    Employee e;
    e.SetNumber(NOTEXIST);
    id = to_string(ID);
    in.open(filename, ios::in);

    while (getline(in, s))
    {
        //截取工号
        sec2 = s.find_first_of(",");
        item = s.substr(sec1, sec2);
        if (item == id)  //找到了那个人
        {
            e = SplitString(s);
            break;
        }
    }
    return e;
}

Employee SuperExcel::findEmployeeByName(string name)
{
    ifstream in;
    string s, item;
    Employee e;
    e.SetNumber(NOTEXIST);

    in.open(filename, ios::in);

    while (getline(in, s))
    {
        //截取工号

        if (name == SplitString(s).GetName())  //找到了那个人
        {
            e = SplitString(s);
            break;
        }
    }
    return e;       //如果找不到，返回的对象的工号就是-1
}

void SuperExcel::deleteEmployee(Employee &e)
{
    e.SetFired(true);
    ifstream in;
    ofstream out;
    string s, ID, name;
    int age;
    age = e.GetAge();
    name = e.GetName();

    //首先将修改的内容输入到另一个文件里
    in.open(filename, ios::in);
    out.open("data2.csv", ios::out); //一个拷贝文件

    while (getline(in, s))
    {
      
        if (name == SplitString(s).GetName() && age==SplitString(s).GetAge() )  //即不把这个对象的信息拷进去，相当于删除
            continue;
        else
            out << s << endl;  
    }

    in.close();
    out.close();

    //再将另一个文件的内容拷贝回来
    in.open("data2.csv", ios::in);
    out.open(filename, ios::out);
    while (getline(in, s))
    {
        out << s << endl;
    }
    in.close();
    out.close();
    total--;
    fired++;
    currentEmployee--;
}


int SuperExcel::findEmployeeIndex(Employee& e)
{
    ifstream in;
    string s, item;
    int index=-1;

    in.open(filename, ios::in);

    while (getline(in, s))
    {
        index++;
        //截取工号

        if (e.GetName() == SplitString(s).GetName())  //找到了那个人
        {
            
            break;
        }
    }
    return index;       //如果找不到，返回的对象的工号就是-1
}



int SuperExcel::getMax()
{
    Max += 1;
    return Max;
}
