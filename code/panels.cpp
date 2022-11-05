#include <wx/stattext.h>
#include <wx/fontdlg.h>
#include "display.h"

#include <wx/statline.h>
#include <editdialogicon.xpm>
#include <adddialogicon.xpm>
#include <detaildialogicon.xpm>
#include"panels.h"
#include"Allworkers.h"
#include"SuperExcel.h"


int list[11];
static double table_height = 440;//表高
static double table_width = 500;//表宽
static double o_x = 85;//原点x的坐标
static double o_y = 130;//原点y的坐标
static int max_people;//人数最大区间的人数
int EditPanel::flag = 0;
int t_x = 120;
int t_y = 110;
int t1_x = 120;
int t1_y = 110;
int t_blink = 60;
static int max_salary;//最大工资
void init_column(void);
column c1(5000, 10000, 1);
column c2(10000, 15000, 2);
column c3(15000, 20000, 3);
column c4(20000, 25000, 4);
column c5(25000, 10000000, 5);
int /*person_point::*/max_old = 0;
int /*person_point::*/min_old = 100000;
const double column::column_width = 60;
int InforPanel::page = 1;
int EditPanel::page = 1;
int WagePanel::page = 1;
static int choice = -1;
int EditPanel::ID=-1;
int EditPanel::age=-1;
int EditPanel::position=-1;
wxString EditPanel::name="";
wxString EditPanel::sex="";
Employee temp;
int EditPanel::selectednumber = 0;
Employee employee[50];


const int column::judge_in(const int& money) {
    int in = 0;
    if (money >= lower_money && money < upper_money)
        in = 1;
    return in;
}

void column::add_people() {
    people++;
}
void column::cal_height() {
    height = table_height * people / max_people;
}

column::column(int lower_m, int upper_m, int n) :upper_money(upper_m), lower_money(lower_m), people(0), num(n) {
    int ww = (table_width - t_blink - (t_x - o_x)) / 4;
    bottom_x = t_x + (num - 1)*ww - o_x - 10;
}

void person_point::cal_x(void) {
    x = t1_x + 4 + (old - min_old)*((table_width - 10 - (t1_x - o_x))) / (max_old - min_old);
}

void person_point::cal_y(void) {
    y = o_y + 5 + table_height - (salary - 5000) * table_height / (max_salary - 5000);
}

person_point::person_point(int Old, int Salary) :old(Old), salary(Salary) {
    cal_y();
    cal_x();
}

void init_point(void) {
    SuperExcel excel("data.csv");
    Employee t;
    int s, o;
    max_salary = 0;
    for (int i = 1; i <= excel.GetTotal(); i++) {
        t = excel.GetEmployee(i);
        o = t.GetAge();
        s = t.GetSalary();
        if (o > /*person_point::*/max_old)
            /*person_point::*/max_old = o;
        if (o < /*person_point::*/min_old)
           /* person_point::*/min_old = o;
        if (s > max_salary)
            max_salary = s;
    }
    for (int i = 0; i < 10; i++) {
        if ((max_salary - 5000) % 10 == 0)
            break;
        else
            max_salary++;
    }
    for (int i = 0; i < 10; i++) {
        if ((/*person_point::*/max_old - /*person_point::*/min_old) % 10 == 0)
            break;
        else
            /*person_point::*/max_old++;
    }
}

void init_column(void) {
    c1.init_people();
    c2.init_people();
    c3.init_people();
    c4.init_people();
    c5.init_people();
    SuperExcel excel("data.csv");
    Employee t;
    int salary;
    for (int i = 1; i <= excel.GetTotal(); i++) {
        t = excel.GetEmployee(i);
        salary = t.GetSalary();
        c1.judge_in(salary) ? c1.add_people() : c2.judge_in(salary) ? c2.add_people() : c3.judge_in(salary)\
            ? c3.add_people() : c4.judge_in(salary) ? c4.add_people() : c5.add_people();
    }
    max_people = max(c5.get_people(), max(max(c1.get_people(), c2.get_people()), max(c3.get_people(), c4.get_people())));
    for (int i = 0; i < 10; i++) {
        if ((max_people = max_people + 1) % 10 == 0)
            break;
    }
    c1.cal_height();
    c2.cal_height();
    c3.cal_height();
    c4.cal_height();
    c5.cal_height();
}


void AnalyzePanel::draw_column_image(wxPaintDC &mydc) {
    init_column();
    draw_axis(mydc);
    draw_column(mydc);
}

void AnalyzePanel::draw_column(wxPaintDC &mydc) {
    wxColour col1, col2;
    col1.Set(wxT("#0c0c0c"));
    col2.Set(wxT("#000000"));
    //mydc.SetPen(col1);
    mydc.SetPen(*wxGREY_PEN);
    //mydc.SetBrush(col2);
    mydc.SetBrush(*wxGREY_BRUSH);
    mydc.DrawRectangle(o_x + c1.bottom_x, o_y + table_height - c1.height, c1.column_width, c1.height);
    mydc.DrawRectangle(o_x + c2.bottom_x, o_y + table_height - c2.height, c2.column_width, c2.height);
    mydc.DrawRectangle(o_x + c3.bottom_x, o_y + table_height - c3.height, c3.column_width, c3.height);
    mydc.DrawRectangle(o_x + c4.bottom_x, o_y + table_height - c4.height, c4.column_width, c4.height);
    mydc.DrawRectangle(o_x + c5.bottom_x, o_y + table_height - c5.height, c5.column_width, c5.height);
}

void AnalyzePanel::draw_axis(wxPaintDC &mydc) {
    mydc.SetPen(*wxLIGHT_GREY_PEN);
    mydc.DrawLine(wxPoint(o_x, o_y + table_height), wxPoint(o_x + table_width, o_y + table_height));
    mydc.DrawLine(wxPoint(o_x, o_y - 10), wxPoint(o_x, o_y + table_height));
    mydc.DrawLine(wxPoint(o_x, o_y - 10), wxPoint(o_x - 5, o_y - 5));
    mydc.DrawLine(wxPoint(o_x, o_y - 10), wxPoint(o_x + 5, o_y - 5));
    wxFont font4(10, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mydc.SetFont(font4);
    mydc.DrawText("number of people", o_x - 30, o_y - 25);
    mydc.DrawLine(wxPoint(o_x + table_width, o_y + table_height), wxPoint(o_x + table_width - 5, o_y + table_height - 5));
    mydc.DrawLine(wxPoint(o_x + table_width, o_y + table_height), wxPoint(o_x + table_width - 5, o_y + table_height + 5));
    mydc.DrawText("wage", o_x + table_width + 5, o_y + table_height - 10);
    //填入坐标
    wxFont font2(16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mydc.SetFont(font4);
    mydc.SetBackgroundMode(wxSOLID);
    mydc.SetTextForeground(*wxBLACK);
    mydc.SetTextBackground(*wxWHITE);
    int ww = (table_width - t_blink - (t_x - o_x)) / 4;
    mydc.DrawText("0-5k", t_x, t_y + table_height + 30);
    mydc.DrawText("5-10k", t_x + ww, t_y + table_height + 30);
    mydc.DrawText("10-15k", t_x + 2 * ww, t_y + table_height + 30);
    mydc.DrawText("15-20k", t_x + 3 * ww, t_y + table_height + 30);
    mydc.DrawText(">20k", t_x + 4 * ww, t_y + table_height + 30);
    int maxp = max_people;
    int pp = maxp / 10;
    wxFont font3(10, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mydc.SetFont(font3);
    mydc.SetBackgroundMode(wxSOLID);
    mydc.SetTextForeground(*wxBLACK);
    mydc.SetTextBackground(*wxWHITE);
    for (int i = 0; i <= 10; i++) {
        char s[10];
        sprintf(s, "%d", i*pp); // 将整数转换成字符串
        mydc.DrawText(s, o_x - 20, o_y + table_height - i * table_height / 10);
    }
}

void AnalyzePanel2::draw_scatter_image(wxPaintDC &mydc) {
    init_point();
    draw_axis(mydc);
    SuperExcel excel("data.csv");
    Employee t;
    for (int i = 1; i <= excel.GetTotal(); i++) {
        t = excel.GetEmployee(i);
        person_point person(t.GetAge(), t.GetSalary());
        draw_point(mydc, person);
    }
}

void AnalyzePanel2::draw_point(wxPaintDC &mydc, person_point person) {
    //画点
    wxColour col1, col2;
    col1.Set(wxT("#0c0c0c"));
    col2.Set(wxT("#000000"));
    //mydc.SetPen(col1);
    mydc.SetPen(*wxGREY_PEN);
    //mydc.SetBrush(col2);
    mydc.SetBrush(*wxGREY_BRUSH);
    mydc.DrawCircle(person.get_x(), person.get_y(), 3);
}

void AnalyzePanel2::draw_axis(wxPaintDC &mydc) {
    mydc.SetPen(*wxLIGHT_GREY_PEN);
    mydc.DrawLine(wxPoint(o_x, o_y + table_height + 15), wxPoint(o_x + table_width, o_y + table_height + 15));
    mydc.DrawLine(wxPoint(o_x, o_y - 10), wxPoint(o_x, o_y + table_height + 15));
    mydc.DrawLine(wxPoint(o_x, o_y - 10), wxPoint(o_x - 5, o_y - 5));
    mydc.DrawLine(wxPoint(o_x, o_y - 10), wxPoint(o_x + 5, o_y - 5));
    wxFont font4(10, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mydc.SetFont(font4);
    mydc.DrawText("salary", o_x - 20, o_y - 25);
    mydc.DrawLine(wxPoint(o_x + table_width, o_y + table_height + 15), wxPoint(o_x + table_width - 5, o_y + table_height + 15 - 5));
    mydc.DrawLine(wxPoint(o_x + table_width, o_y + table_height + 15), wxPoint(o_x + table_width - 5, o_y + table_height + 15 + 5));
    mydc.DrawText("age", o_x + table_width + 5, o_y + table_height + 15 - 10);
    //填入坐标
    //横轴：年龄
    wxFont font3(10, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mydc.SetFont(font3);
    mydc.SetBackgroundMode(wxSOLID);
    mydc.SetTextForeground(*wxBLACK);
    mydc.SetTextBackground(*wxWHITE);
    int ww = (table_width - 10 - (t1_x - o_x)) / 10;
    int aa = (/*person_point::*/max_old - /*person_point::*/min_old) / 10;
    int ss = (max_salary - 5000) / 10;
    for (int i = 0; i <= 10; i++) {
        char s[10];
        sprintf(s, "%d", (/*person_point::*/min_old)+aa * i); // 将整数转换成字符串
        mydc.DrawText(s, t1_x + ww * i, t1_y + table_height + 45);
    }
    //纵轴：工资
    for (int i = 0; i <= 10; i++) {
        char s[10];
        sprintf(s, "%d", 5000 + ss * i); // 将整数转换成字符串
        mydc.DrawText(s, o_x - 40, o_y + table_height - i * table_height / 10);
    }
}


//开屏界面
StartPanel::StartPanel(wxPanel * parent)
    : wxPanel(parent, -1, wxPoint(0, 0), wxSize(720, 720), wxBORDER_DEFAULT)
{
    m_parent = parent;


    m_quit = new wxButton(this, wxID_EXIT, wxT("QUIT"),
        wxPoint(310, 590), wxSize(100, 50));
    m_start = new wxButton(this, wxID_OPEN, wxT("START"),
        wxPoint(310, 530), wxSize(100, 50));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(StartPanel::OnQuit));
    Connect(wxID_OPEN, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(StartPanel::OnStart));
    Bind(wxEVT_PAINT, &StartPanel::OnPaint, this);

}

void StartPanel::OnQuit(wxCommandEvent & WXUNUSED(event))
{
    MyFrame *comm = (MyFrame *)m_parent->GetParent();
    comm->Close(true);
}

void StartPanel::OnStart(wxCommandEvent & WXUNUSED(event))
{
    MyFrame *comm = (MyFrame *)m_parent->GetParent();
    comm->m_sp->Hide();
    comm->m_ip->Show();
    comm->m_ep->Hide();
    comm->SetMenuBar(comm->getmenubar());
}

void StartPanel::OnPaint(wxPaintEvent&event)
{
    wxBufferedPaintDC mydc(this);
    mydc.SetPen(*wxWHITE_PEN);
    mydc.SetBrush(*wxWHITE_BRUSH);
    mydc.SetBackground(wxBrush(*wxWHITE, wxBRUSHSTYLE_SOLID));
    //获取窗口大小
    wxSize sz = GetClientSize();
    //要绘制的矩形大小
    wxCoord w = sz.x, h = sz.y;
    wxRect rectToDraw(0, 0, w, h);
    //只有在需要的时候才重新画以便提高效率
    if (IsExposed(rectToDraw))
        mydc.DrawRectangle(rectToDraw);
    wxInitAllImageHandlers();//添加对jpg图片读取的handel
    wxBitmap pic(wxT("start.jpg"), wxBITMAP_TYPE_JPEG);
    if (pic.Ok())
        mydc.DrawBitmap(pic, 175, 130);
    //定义一个wxFont类的对象font
    //构造函数wxFont::wxFont(字体大小、字体类型（书法、艺术）、斜体、)
    wxFont font(25, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    //利用DC类的成员函数SetFont设置字体
    mydc.SetFont(font);
    //设置背景透或者不透
    mydc.SetBackgroundMode(wxSOLID/*wxTRANSPARENT*/);
    //设置前景颜色
    mydc.SetTextForeground(*wxBLACK);
    //设置背景颜色
    mydc.SetTextBackground(*wxWHITE);
    //写字，文本wxString，位置wxPoint
    mydc.DrawText("Enterprise Wages Management System", 50, 40);
}


//显示信息界面
InforPanel::InforPanel(wxPanel * parent)
    : wxPanel(parent, -1, wxPoint(0, 0), wxSize(720, 720), wxBORDER_DEFAULT)
{
    m_parent = parent;

    firsticon.LoadFile("firsticon.bmp", wxBITMAP_TYPE_BMP);
    lasticon.LoadFile("lasticon.bmp", wxBITMAP_TYPE_BMP);
    nexticon.LoadFile("nexticon.bmp", wxBITMAP_TYPE_BMP);
    preicon.LoadFile("preicon.bmp", wxBITMAP_TYPE_BMP);

    int bitmapx = 220;
    int bitmapy = 560;
    int bitmapw = 50;
    m_first = new wxBitmapButton(this, pageID_first, firsticon,
        wxPoint(bitmapx, bitmapy), wxSize(30, 30), 0);
    Connect(pageID_first, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(InforPanel::OnFirst));
    m_pre = new wxBitmapButton(this, pageID_pre, preicon,
        wxPoint(bitmapx + bitmapw, bitmapy), wxSize(30, 30), 0);
    Connect(pageID_pre, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(InforPanel::OnPre));
    m_next = new wxBitmapButton(this, pageID_next, nexticon,
        wxPoint(bitmapx + 4 * bitmapw, bitmapy), wxSize(30, 30), 0);
    Connect(pageID_next, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(InforPanel::OnNext));
    m_last = new wxBitmapButton(this, pageID_last, lasticon,
        wxPoint(bitmapx + 5 * bitmapw, bitmapy), wxSize(30, 30), 0);
    Connect(pageID_last, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(InforPanel::OnLast));

    Bind(wxEVT_PAINT, &InforPanel::OnPaint, this);
}

void InforPanel::OnPaint(wxPaintEvent&event)
{
    wxBufferedPaintDC mydc(this);
    mydc.SetPen(*wxWHITE_PEN);
    mydc.SetBrush(*wxWHITE_BRUSH);
    mydc.SetBackground(wxBrush(*wxWHITE, wxBRUSHSTYLE_SOLID));
    //获取窗口大小
    wxSize sz = GetClientSize();
    //要绘制的矩形大小
    wxCoord w = sz.x, h = sz.y;
    wxRect rectToDraw(0, 0, w, h);

    //只有在需要的时候才重新画以便提高效率
    if (IsExposed(rectToDraw))
        mydc.DrawRectangle(rectToDraw);

    //显示Employee Information标题
    wxFont font1(18, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    mydc.SetFont(font1);
    mydc.SetBackgroundMode(wxSOLID/*wxTRANSPARENT*/);
    mydc.SetTextForeground(*wxBLACK);
    mydc.SetTextBackground(*wxWHITE);
    mydc.DrawText("Employee Information", 230, 40);

    //绘制表格框架
    int hh = 40;
    int ww = 120;
    int x = 60;
    int y = 100;
    mydc.SetPen(*wxLIGHT_GREY_PEN);
    mydc.DrawLine(wxPoint(x, y), wxPoint(x + 5 * ww, y));
    mydc.DrawLine(wxPoint(x, y + hh), wxPoint(x + 5 * ww, y + hh));
    mydc.DrawLine(wxPoint(x, y + 2 * hh), wxPoint(x + 5 * ww, y + 2 * hh));
    mydc.DrawLine(wxPoint(x, y + 3 * hh), wxPoint(x + 5 * ww, y + 3 * hh));
    mydc.DrawLine(wxPoint(x, y + 4 * hh), wxPoint(x + 5 * ww, y + 4 * hh));
    mydc.DrawLine(wxPoint(x, y + 5 * hh), wxPoint(x + 5 * ww, y + 5 * hh));
    mydc.DrawLine(wxPoint(x, y + 6 * hh), wxPoint(x + 5 * ww, y + 6 * hh));
    mydc.DrawLine(wxPoint(x, y + 7 * hh), wxPoint(x + 5 * ww, y + 7 * hh));
    mydc.DrawLine(wxPoint(x, y + 8 * hh), wxPoint(x + 5 * ww, y + 8 * hh));
    mydc.DrawLine(wxPoint(x, y + 9 * hh), wxPoint(x + 5 * ww, y + 9 * hh));
    mydc.DrawLine(wxPoint(x, y + 10 * hh), wxPoint(x + 5 * ww, y + 10 * hh));
    mydc.DrawLine(wxPoint(x, y + 11 * hh), wxPoint(x + 5 * ww, y + 11 * hh));

    mydc.DrawLine(wxPoint(x, y), wxPoint(x, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + ww, y), wxPoint(x + ww, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + 2 * ww, y), wxPoint(x + 2 * ww, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + 3 * ww, y), wxPoint(x + 3 * ww, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + 4 * ww, y), wxPoint(x + 4 * ww, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + 5 * ww, y), wxPoint(x + 5 * ww, y + 11 * hh));

    //填入表头
    wxFont font2(16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mydc.SetFont(font2);
    mydc.SetBackgroundMode(wxSOLID);
    mydc.SetTextForeground(*wxBLACK);
    mydc.SetTextBackground(*wxWHITE);
    int title_x = 75;
    int title_y = 110;
    mydc.DrawText("   ID   ", title_x, title_y);
    mydc.DrawText("  NAME  ", title_x + ww, title_y);
    mydc.DrawText(" GENDER ", title_x + 2 * ww, title_y);
    mydc.DrawText("  AGE   ", title_x + 3 * ww, title_y);
    mydc.DrawText("POSITION", title_x + 4 * ww, title_y);

    //默认显示第一页
    SuperExcel excel("data.csv");
    Employee e;
    int total = excel.GetTotal();
    int num = total % 10;
    int p = total / 10;
    int last = p + (num != 0 ? 1 : 0);
    //set
    mydc.SetPen(*wxWHITE_PEN);
    mydc.SetBrush(*wxWHITE_BRUSH);
    mydc.SetBackground(wxBrush(*wxWHITE, wxBRUSHSTYLE_SOLID));

    int i;
    string po;
    wxString _number;
    for (i = 1; i <= 10 && ((page - 1) * 10 + i) <= total; i++) {
        e = excel.GetEmployee((page - 1) * 10 + i);
        _number = wxString::Format("%06d", e.GetNumber());
        if (e.GetPosition() == 0)
            po = "Employee";
        else if (e.GetPosition() == 1)
            po = "Technican";
        else
            po = "Manager";
        mydc.DrawText(_number, title_x, title_y + hh * i);
        mydc.DrawText(e.GetName(), title_x + ww, title_y + hh * i);
        mydc.DrawText(e.GetSex(), title_x + ww * 2, title_y + hh * i);
        mydc.DrawText(to_string(e.GetAge()), title_x + ww * 3, title_y + hh * i);
        mydc.DrawText(po, title_x + ww * 4, title_y + hh * i);
    }
    
}

void InforPanel::OnFirst(wxCommandEvent & WXUNUSED(event))
{
    Refresh();
    page = 1;
}

void InforPanel::OnLast(wxCommandEvent & WXUNUSED(event))
{
    Refresh();
    SuperExcel excel("data.csv");
    Employee e;
    int total = excel.GetTotal();
    int num = total % 10;
    int p = total / 10;
    int last = p + (num != 0 ? 1 : 0);
    page = last;
}

void InforPanel::OnNext(wxCommandEvent & WXUNUSED(event))
{
    Refresh();
    SuperExcel excel("data.csv");
    Employee e;
    int total = excel.GetTotal();
    int num = total % 10;
    int p = total / 10;
    int last = p + (num != 0 ? 1 : 0);
    if (page != last) page++;
    else;
}

void InforPanel::OnPre(wxCommandEvent & WXUNUSED(event))
{
    Refresh();
    if (page > 1) page--;
    else;
}


//编辑信息界面
EditPanel::EditPanel(wxPanel * parent)
    : wxPanel(parent, -1, wxPoint(0, 0), wxSize(720, 720), wxBORDER_DEFAULT)
{
    m_parent = parent;

    Bind(wxEVT_PAINT, &EditPanel::OnPaint, this);

    //绘制录入新员工按钮
    addicon.LoadFile("addicon.bmp", wxBITMAP_TYPE_BMP);
    m_add = new wxBitmapButton(this, inforID_add, addicon,
        wxPoint(30, 60), wxSize(55, 55), 0);
    Connect(inforID_add, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(EditPanel::OnAdd));

    //绘制右侧删除编辑按钮
    editicon.LoadFile("editicon.bmp", wxBITMAP_TYPE_BMP);
    deleteicon.LoadFile("deleteicon.bmp", wxBITMAP_TYPE_BMP);

    int bitmapx = 630;
    int bitmapy = 175;
    int bitmapw = 35;
    int bitmaph = 40;

   /* m_edit = new wxBitmapButton(this, inforID_edit, editicon,
        wxPoint(bitmapx, bitmapy), wxSize(30, 30), 0);
    Connect(inforID_edit, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(EditPanel::OnEdit));
    m_delete = new wxBitmapButton(this, inforID_delete, deleteicon,
        wxPoint(bitmapx + bitmapw, bitmapy), wxSize(30, 30), 0);
    Connect(inforID_delete, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(EditPanel::OnDelete));
*/

    //默认显示第一页
    SuperExcel excel("data.csv");
    Employee e;
    int total = excel.GetTotal();
    int num = total % 10;
    int p = total / 10;
    int last = p + (num != 0 ? 1 : 0);
    //set
    
    int hh = 40;
    int i;
    int number;
    for (i = 1; i <= 10 && ((page - 1) * 10 + i) <= total; i++) {
   
        number = i;
        m_edit = new wxBitmapButton(this, inforID_edit+100+number, editicon,
            wxPoint(bitmapx, bitmapy+hh*i-hh), wxSize(30, 30), 0);
        Connect(inforID_edit+100+number, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(EditPanel::OnEdit));
        m_delete = new wxBitmapButton(this, inforID_delete+500+number, deleteicon,
            wxPoint(bitmapx + bitmapw, bitmapy+i*hh-hh), wxSize(30, 30), 0);
        Connect(inforID_delete+500+number, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(EditPanel::OnDelete));

    }





    //绘制翻页按钮
    firsticon.LoadFile("firsticon.bmp", wxBITMAP_TYPE_BMP);
    lasticon.LoadFile("lasticon.bmp", wxBITMAP_TYPE_BMP);
    nexticon.LoadFile("nexticon.bmp", wxBITMAP_TYPE_BMP);
    preicon.LoadFile("preicon.bmp", wxBITMAP_TYPE_BMP);

    int iconx = 180;
    int icony = 590;
    int iconw = 50;

    m_first = new wxBitmapButton(this, epageID_first, firsticon,
        wxPoint(iconx, icony), wxSize(30, 30), 0);
    Connect(epageID_first, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(EditPanel::OnFirst));
    m_pre = new wxBitmapButton(this, epageID_pre, preicon,
        wxPoint(iconx + iconw, icony), wxSize(30, 30), 0);
    Connect(epageID_pre, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(EditPanel::OnPre));
    m_next = new wxBitmapButton(this, epageID_next, nexticon,
        wxPoint(iconx + 4 * iconw, icony), wxSize(30, 30), 0);
    Connect(epageID_next, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(EditPanel::OnNext));
    m_last = new wxBitmapButton(this, epageID_last, lasticon,
        wxPoint(iconx + 5 * iconw, icony), wxSize(30, 30), 0);
    Connect(epageID_last, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(EditPanel::OnLast));

    //下拉框
    m_comboBox1 = new wxComboBox(this, boxID_search1, "", wxPoint(150, 70));
    m_comboBox2 = new wxComboBox(this, boxID_choice1, "", wxPoint(300, 70));
    m_comboBox1->Append(wxT("ID"));
    m_comboBox1->Append(wxT("NAME"));
    m_comboBox1->Append(wxT("GENDER"));
    m_comboBox1->Append(wxT("AGE"));
    m_comboBox1->Append(wxT("POSITION"));
    Connect(boxID_search1, wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(EditPanel::OnCombBoxSelect1));
    Connect(boxID_choice1, wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(EditPanel::OnCombBoxSelect2));

    //查询按钮
    searchicon.LoadFile("searchicon.bmp", wxBITMAP_TYPE_BMP);
    m_search = new wxBitmapButton(this, inforID_search,searchicon,
        wxPoint(450, 65), wxSize(30, 30), 0);
    Connect(inforID_search, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(EditPanel::OnHandle));
    searchiconselected.LoadFile("searchiconselected.bmp", wxBITMAP_TYPE_BMP);
}

void EditPanel::OnPaint(wxPaintEvent&event)
{
    wxBufferedPaintDC mydc(this);
    mydc.SetPen(*wxWHITE_PEN);
    mydc.SetBrush(*wxWHITE_BRUSH);
    mydc.SetBackground(wxBrush(*wxWHITE, wxBRUSHSTYLE_SOLID));
    //获取窗口大小
    wxSize sz = GetClientSize();
    //要绘制的矩形大小
    wxCoord w = sz.x, h = sz.y;
    wxRect rectToDraw(0, 0, w, h);
    //只有在需要的时候才重新画以便提高效率
    if (IsExposed(rectToDraw))
        mydc.DrawRectangle(rectToDraw);

    //显示Employee Information标题
    wxFont font1(16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    mydc.SetFont(font1);
    mydc.SetBackgroundMode(wxSOLID/*wxTRANSPARENT*/);
    mydc.SetTextForeground(*wxBLACK);
    mydc.SetTextBackground(*wxWHITE);
    mydc.DrawText("Editing and Searching", 20, 20);

    //绘制表格框架
    int hh = 40;
    int ww = 120;
    int x = 20;
    int y = 130;
    mydc.SetPen(*wxLIGHT_GREY_PEN);
    mydc.DrawLine(wxPoint(x, y), wxPoint(x + 5 * ww, y));
    mydc.DrawLine(wxPoint(x, y + hh), wxPoint(x + 5 * ww, y + hh));
    mydc.DrawLine(wxPoint(x, y + 2 * hh), wxPoint(x + 5 * ww, y + 2 * hh));
    mydc.DrawLine(wxPoint(x, y + 3 * hh), wxPoint(x + 5 * ww, y + 3 * hh));
    mydc.DrawLine(wxPoint(x, y + 4 * hh), wxPoint(x + 5 * ww, y + 4 * hh));
    mydc.DrawLine(wxPoint(x, y + 5 * hh), wxPoint(x + 5 * ww, y + 5 * hh));
    mydc.DrawLine(wxPoint(x, y + 6 * hh), wxPoint(x + 5 * ww, y + 6 * hh));
    mydc.DrawLine(wxPoint(x, y + 7 * hh), wxPoint(x + 5 * ww, y + 7 * hh));
    mydc.DrawLine(wxPoint(x, y + 8 * hh), wxPoint(x + 5 * ww, y + 8 * hh));
    mydc.DrawLine(wxPoint(x, y + 9 * hh), wxPoint(x + 5 * ww, y + 9 * hh));
    mydc.DrawLine(wxPoint(x, y + 10 * hh), wxPoint(x + 5 * ww, y + 10 * hh));
    mydc.DrawLine(wxPoint(x, y + 11 * hh), wxPoint(x + 5 * ww, y + 11 * hh));

    mydc.DrawLine(wxPoint(x, y), wxPoint(x, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + ww, y), wxPoint(x + ww, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + 2 * ww, y), wxPoint(x + 2 * ww, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + 3 * ww, y), wxPoint(x + 3 * ww, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + 4 * ww, y), wxPoint(x + 4 * ww, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + 5 * ww, y), wxPoint(x + 5 * ww, y + 11 * hh));

    //填入表头
    wxFont font2(16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mydc.SetFont(font2);
    mydc.SetBackgroundMode(wxSOLID);
    mydc.SetTextForeground(*wxBLACK);
    mydc.SetTextBackground(*wxWHITE);
    int title_x = 35;
    int title_y = 140;
    mydc.DrawText("   ID   ", title_x, title_y);
    mydc.DrawText("  NAME  ", title_x + ww, title_y);
    mydc.DrawText(" GENDER ", title_x + 2 * ww, title_y);
    mydc.DrawText("  AGE   ", title_x + 3 * ww, title_y);
    mydc.DrawText("POSITION", title_x + 4 * ww, title_y);

    //绘制员工信息
   //默认显示第一页
    SuperExcel excel("data.csv");
    Employee e;
    int total = excel.GetTotal();
    int num = total % 10;
    int p = total / 10;
    int last = p + (num != 0 ? 1 : 0);
    //set
    mydc.SetPen(*wxWHITE_PEN);
    mydc.SetBrush(*wxWHITE_BRUSH);
    mydc.SetBackground(wxBrush(*wxWHITE, wxBRUSHSTYLE_SOLID));

    int i, j;
    string po;
    wxString _number;
    switch (choice)
    {
    case -1:
        for (i = 1; i <= 10 && ((page - 1) * 10 + i) <= total; i++) {
            e = excel.GetEmployee((page - 1) * 10 + i);
            _number = wxString::Format("%06d", e.GetNumber());
            list[i] = excel.findEmployeeIndex(e);
            if (e.GetPosition() == 0)
                po = "Employee";
            else if (e.GetPosition() == 1)
                po = "Technican";
            else
                po = "Manager";
            mydc.DrawText(_number, title_x, title_y + hh * i);
            mydc.DrawText(e.GetName(), title_x + ww, title_y + hh * i);
            mydc.DrawText(e.GetSex(), title_x + ww * 2, title_y + hh * i);
            mydc.DrawText(to_string(e.GetAge()), title_x + ww * 3, title_y + hh * i);
            mydc.DrawText(po, title_x + ww * 4, title_y + hh * i);
        }
        for (j = i; j <= 10; j++)
        {
            list[j] = 0;
        }
        break;
    case 0:
        for (i = 1; i <= 10 && ((page - 1) * 10 + i) <= selectednumber; i++) {
            e = employee[(page - 1) * 10 + i];
            _number = wxString::Format("%06d", e.GetNumber());
            list[i] = excel.findEmployeeIndex(e);
            if (e.GetPosition() == 0)
                po = "Employee";
            else if (e.GetPosition() == 1)
                po = "Technican";
            else
                po = "Manager";
            mydc.DrawText(_number, title_x, title_y + hh * i);
            mydc.DrawText(e.GetName(), title_x + ww, title_y + hh * i);
            mydc.DrawText(e.GetSex(), title_x + ww * 2, title_y + hh * i);
            mydc.DrawText(to_string(e.GetAge()), title_x + ww * 3, title_y + hh * i);
            mydc.DrawText(po, title_x + ww * 4, title_y + hh * i);
        }

        for (j = i; j <= 10; j++)
        {
            list[j] = 0;
        }

        break;
    }

}

void EditPanel::OnEdit(wxCommandEvent & event)
{
    int id;
    SuperExcel excel("data.csv");
    int total=excel.GetTotal();
    id = list[event.GetId() - inforID_edit - 100];
    if (id >0)
    {
        EditDialog * m_editdialog = new EditDialog(_T("Information Editing"),id);

        m_editdialog->Show(true);
    }
    else
    {
        wxMessageBox(wxT("Employee not exists! You need to add an employee first!"));
    }
}

void EditPanel::OnDelete(wxCommandEvent & event)
{
    int index;
    index = list[event.GetId() - inforID_delete - 500];
    if (index > 0)
    {
        wxMessageDialog *dial = new wxMessageDialog(NULL,
            wxT("Are you sure to delete?"), wxT("Question"),
            wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
        if (dial->ShowModal() == wxID_YES && index > 0)
        {
            SuperExcel excel("data.csv");
            Employee e = excel.GetEmployee(index);
            excel.deleteEmployee(e);
        }
    }
    else if (index <= 0)
    {
        wxMessageBox(wxT("Employee not exists! You need to add an employee first!"));
    }
    /*
    wxMessageDialog *dial = new wxMessageDialog(NULL,
        wxT("No data"), wxT("Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
   */

}

void EditPanel::OnAdd(wxCommandEvent & WXUNUSED(event))
{
    AddDialog * m_Adddialog = new AddDialog(_T("Register a New Employee"));

    m_Adddialog->Show(true);
}

void EditPanel::OnFirst(wxCommandEvent & WXUNUSED(event))
{
    Refresh();
    page = 1;
}

void EditPanel::OnLast(wxCommandEvent & WXUNUSED(event))
{
    Refresh();
    SuperExcel excel("data.csv");
    Employee e;
    int total = excel.GetTotal();
    int num;
    int p;
    if (choice == -1)
    {
        num = total % 10;
        p = total / 10;
    }
    else if (choice == 0)
    {
        num = selectednumber % 10;
        p = selectednumber / 10;
    }
    int last = p + (num != 0 ? 1 : 0);
    page = last;
}


void EditPanel::OnNext(wxCommandEvent & WXUNUSED(event))
{
    Refresh();
    SuperExcel excel("data.csv");
    Employee e;
    int total = excel.GetTotal();
    int num;
    int p;
    if (choice == -1)
    {
        num = total % 10;
        p = total / 10;
    }
    else if (choice == 0)
    {
        num = selectednumber % 10;
        p = selectednumber / 10;
    }
    int last = p + (num != 0 ? 1 : 0);
    if (page != last) page++;
    else;

}

void EditPanel::OnPre(wxCommandEvent & WXUNUSED(event))
{
    Refresh();
    if (page > 1) page--;
    else;
}

void EditPanel::OnCombBoxSelect1(wxCommandEvent &event)
{
    SuperExcel excel("data.csv");
    Employee e;
    const int lowestage = 18;
    const int highestage = 65;
    int i;
    int a[100] = {};
    int age;
    int number = excel.GetTotal();
    wxString msg;
    m_comboBox2->Clear();
    switch (m_comboBox1->GetSelection())
    {
    case 0:
        for (i = 1; i <= number; i++)
        {
            e = excel.GetEmployee(i);
            msg = std::to_string(e.GetNumber());
            m_comboBox2->Append(msg);
        }
        break;
    case 1:
        for (i = 1; i <= number; i++)
        {
            e = excel.GetEmployee(i);
            msg = e.GetName();
            m_comboBox2->Append(msg);
        }
        break;
    case 2:
        m_comboBox2->Append(wxT("male"));
        m_comboBox2->Append(wxT("female"));
        break;
    case 3:
        for (i = 1; i <= number; i++)
        {
            e = excel.GetEmployee(i);
            age = e.GetAge();
            a[age] = 1;
        }
        for (i = lowestage; i <= highestage; i++)
        {
            if (a[i] == 1)
            {
                msg = std::to_string(i);
                m_comboBox2->Append(msg);
            }
        }
        break;
    case 4:
        for (i = 0; i <= 2; i++)
        {
            msg = to_string(i);
            m_comboBox2->Append(msg);
        }
        break;
    }
}

void EditPanel::OnCombBoxSelect2(wxCommandEvent &event)
{
    flag = 1;
}

void EditPanel::OnHandle(wxCommandEvent &event)
{
    if (flag == 1)
    {
        OnSearch();
        m_search->SetBitmap(searchiconselected);
        flag = 0;
    }
    else
    {
        OnBack();
        m_search->SetBitmap(searchicon);
        flag = 1;
    }
}

void EditPanel::OnSearch()
{
    wxString msg;
    int i, j;
    SuperExcel excel("data.csv");
    Employee e;
    int total = excel.GetTotal();
    choice = 0;
    switch (m_comboBox1->GetSelection())
    {
    case 0:
        msg = m_comboBox2->GetStringSelection();
        ID = atoi(msg.c_str());
        i = 1;
        for (j = 1; j <= total; j++) {
            e = excel.GetEmployee(j);
            if (e.GetNumber() == ID)
            {
                employee[i] = e;
                selectednumber = i;
                i++;
            }
        }
        break;
    case 1:
        name = m_comboBox2->GetStringSelection();
        i = 1;
        for (j = 1; j <= total; j++) {
            e = excel.GetEmployee(j);
            if (e.GetName() == name)
            {
                employee[i] = e;
                selectednumber = i;
                i++;
            }
        }
        break;
    case 2:
        sex = m_comboBox2->GetStringSelection();
        i = 1;
        for (j = 1; j <= total; j++) {
            e = excel.GetEmployee(j);
            if (e.GetSex() == sex)
            {
                employee[i] = e;
                selectednumber = i;
                i++;
            }
        }
        break;
    case 3:
        msg = m_comboBox2->GetStringSelection();
        age = atoi(msg.c_str());
        i = 1;
        for (j = 1; j <= total; j++) {
            e = excel.GetEmployee(j);
            if (e.GetAge() == age)
            {
                employee[i] = e;
                selectednumber = i;
                i++;
            }
        }
        break;
    case 4:
        msg = m_comboBox2->GetStringSelection();
        position = atoi(msg.c_str());
        i = 1;
        for (j = 1; j <= total; j++) {
            e = excel.GetEmployee(j);
            if (e.GetPosition() == position)
            {
                employee[i] = e;
                selectednumber = i;
                i++;
            }
        }
        break;
    }
    Refresh();
}

void EditPanel::OnBack()
{
    choice = -1;
    Refresh();
}

//编辑信息弹窗
EditDialog::EditDialog(const wxString & title,int num)
    : wxDialog(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(360, 360))
{
    SuperExcel excel("data.csv");
    temp = excel.GetEmployee(num);
    wxString _number;
    _number = wxString::Format("%06d", temp.GetNumber());

    wxPanel * panel = new wxPanel(this, wxID_ANY);

    wxBoxSizer * vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer * hbox = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText * id = new wxStaticText(panel, wxID_ANY, _number, wxPoint(15, 5));

    wxStaticBox   * name = new wxStaticBox(panel, wxID_ANY, _T("Name"), wxPoint(5, 25), wxSize(330, 60));
    name_input = new wxTextCtrl(panel, wxID_ANY, _T(""), wxPoint(15, 50));

    wxStaticBox   * gender = new wxStaticBox(panel, wxID_ANY, _T("Gender"), wxPoint(5, 90), wxSize(330, 50));
    female = new wxRadioButton(panel, wxID_ANY, _T("female"), wxPoint(15, 115), wxDefaultSize, wxRB_GROUP);
    male = new wxRadioButton(panel, wxID_ANY, _T("male"), wxPoint(115, 115));

    wxStaticBox   * age = new wxStaticBox(panel, wxID_ANY, _T("Age"), wxPoint(5, 145), wxSize(330, 60));
    age_input = new wxTextCtrl(panel, wxID_ANY, _T(""), wxPoint(15, 165));

    wxStaticBox   * position = new wxStaticBox(panel, wxID_ANY, _T("Position"), wxPoint(5, 205), wxSize(330, 50));
    worker = new wxRadioButton(panel, wxID_ANY, _T("worker"), wxPoint(15, 230), wxDefaultSize, wxRB_GROUP);
    technician = new wxRadioButton(panel, wxID_ANY, _T("technician"), wxPoint(115, 230));
    manager = new wxRadioButton(panel, wxID_ANY, _T("manager"), wxPoint(215, 230));

    wxButton * saveButton = new wxButton(this, editID_save, _T("Save"), wxDefaultPosition, wxSize(70, 30));
    wxButton * backButton = new wxButton(this, editID_back, _T("Back"), wxDefaultPosition, wxSize(70, 30));
    Connect(editID_save, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(EditDialog::OnSave));
    Connect(editID_back, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(EditDialog::OnBack));

    hbox->Add(saveButton, 1);
    hbox->Add(backButton, 1, wxLEFT, 5);

    vbox->Add(panel, 1);
    vbox->Add(hbox, 0, wxALIGN_CENTRE | wxTOP | wxBOTTOM, 10);
    SetIcon(wxIcon(editdialogicon_xpm));
    SetSizer(vbox);

    Centre();
    ShowModal();

    Destroy();
}

void EditDialog::OnSave(wxCommandEvent &WXUNUSED(event))
{
    SuperExcel excel("data.csv");
    temp.SetName(string((name_input->GetLineText(0)).mb_str()));
    if (female->GetValue()) temp.SetSex("female");
    else temp.SetSex("male");
    //age_adjust->SetValue(wxAtoi(age_input->GetLineText(0)));
    temp.SetAge(wxAtoi(age_input->GetLineText(0)));
    //temp.SetAge(age_adjust->GetValue());
    if (manager->GetValue()) temp.SetPosition(2);
    if (worker->GetValue()) temp.SetPosition(0);
    if (technician->GetValue()) temp.SetPosition(1);
    excel.SaveObject(temp);
    Destroy();
}

void EditDialog::OnBack(wxCommandEvent &WXUNUSED(event))
{
    Destroy();
}

//录入新员工弹窗
AddDialog::AddDialog(const wxString & title)
    :wxDialog(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(360, 360))
{
    wxPanel * panel = new wxPanel(this, wxID_ANY);

    wxBoxSizer * vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer * hbox = new wxBoxSizer(wxHORIZONTAL);

    wxStaticBox   * name = new wxStaticBox(panel, wxID_ANY, _T("Name"), wxPoint(5, 25), wxSize(330, 60));
    name_input = new wxTextCtrl(panel, wxID_ANY, _T(""), wxPoint(15, 50));

    wxStaticBox   * gender = new wxStaticBox(panel, wxID_ANY, _T("Gender"), wxPoint(5, 90), wxSize(330, 50));
    female = new wxRadioButton(panel, wxID_ANY, _T("female"), wxPoint(15, 115), wxDefaultSize, wxRB_GROUP);
    male = new wxRadioButton(panel, wxID_ANY, _T("male"), wxPoint(115, 115));

    wxStaticBox   * age = new wxStaticBox(panel, wxID_ANY, _T("Age"), wxPoint(5, 145), wxSize(330, 60));
    age_input = new wxTextCtrl(panel, wxID_ANY, _T(""), wxPoint(15, 165));

    wxStaticBox   * position = new wxStaticBox(panel, wxID_ANY, _T("Position"), wxPoint(5, 205), wxSize(330, 50));
    worker = new wxRadioButton(panel, wxID_ANY, _T("worker"), wxPoint(15, 230), wxDefaultSize, wxRB_GROUP);
    technician = new wxRadioButton(panel, wxID_ANY, _T("technician"), wxPoint(115, 230));
    manager = new wxRadioButton(panel, wxID_ANY, _T("manager"), wxPoint(215, 230));

    wxButton * saveButton = new wxButton(this, addID_save, _T("Save"), wxDefaultPosition, wxSize(70, 30));
    wxButton * backButton = new wxButton(this, addID_back, _T("Back"), wxDefaultPosition, wxSize(70, 30));
    Connect(addID_save, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(AddDialog::OnSave));
    Connect(addID_back, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(AddDialog::OnBack));

    hbox->Add(saveButton, 1);
    hbox->Add(backButton, 1, wxLEFT, 5);

    vbox->Add(panel, 1);
    vbox->Add(hbox, 0, wxALIGN_CENTRE | wxTOP | wxBOTTOM, 10);
    SetIcon(wxIcon(adddialogicon_xpm));
    SetSizer(vbox);

    Centre();
    ShowModal();

    Destroy();
}


void AddDialog::OnSave(wxCommandEvent &WXUNUSED(event))
{
    int year;
    SuperExcel excel("data.csv");
    temp.SetName(string((name_input->GetLineText(0)).mb_str()));
    if (female->GetValue()) temp.SetSex("female");
    else temp.SetSex("male");
    //age_adjust->SetValue(wxAtoi(age_input->GetLineText(0)));
    temp.SetAge(wxAtoi(age_input->GetLineText(0)));
    //temp.SetAge(age_adjust->GetValue());
    if (manager->GetValue()) temp.SetPosition(2);
    if (worker->GetValue()) temp.SetPosition(0);
    if (technician->GetValue()) temp.SetPosition(1);
    temp.SetNumber(excel.getMax());
    time_t nowtime;
    struct tm* p;
    time(&nowtime);
    p = localtime(&nowtime);
    year = p->tm_year + 1900;
    temp.SetStartYear(std::to_string(year));
    excel.AddEmployee(temp);
    Destroy();
}

void AddDialog::OnBack(wxCommandEvent &WXUNUSED(event))
{
    Destroy();
}


//工资信息显示界面
WagePanel::WagePanel(wxPanel * parent)
    : wxPanel(parent, -1, wxPoint(0, 0), wxSize(720, 720), wxBORDER_DEFAULT)
{
    m_parent = parent;

    Bind(wxEVT_PAINT, &WagePanel::OnPaint, this);

    //绘制右侧显示更多信息按钮
    detailicon.LoadFile("wagedetailicon.bmp", wxBITMAP_TYPE_BMP);

    int bitmapx = 570;
    int bitmapy = 175;
    int bitmaph = 40;

    //默认显示第一页
    SuperExcel excel("data.csv");
    Employee e;
    int total = excel.GetTotal();
    int num = total % 10;
    int p = total / 10;
    int last = p + (num != 0 ? 1 : 0);
    //set

    int hh = 40;
    int i;
    int number;
    for (i = 1; i <= 10 && ((page - 1) * 10 + i) <= total; i++) {

        number = i;
        m_detail = new wxBitmapButton(this, wageID_detail + 1000 + number, detailicon,
            wxPoint(bitmapx, bitmapy + hh * (i - 1)), wxSize(30, 30), 0);
        Connect(wageID_detail + 1000 + number, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(WagePanel::OnDetail));
    }

    //绘制翻页按钮
    firsticon.LoadFile("firsticon.bmp", wxBITMAP_TYPE_BMP);
    lasticon.LoadFile("lasticon.bmp", wxBITMAP_TYPE_BMP);
    nexticon.LoadFile("nexticon.bmp", wxBITMAP_TYPE_BMP);
    preicon.LoadFile("preicon.bmp", wxBITMAP_TYPE_BMP);

    int iconx = 180;
    int icony = 590;
    int iconw = 50;

    m_first = new wxBitmapButton(this, wageID_first, firsticon,
        wxPoint(iconx, icony), wxSize(30, 30), 0);
    Connect(wageID_first, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WagePanel::OnFirst));
    m_pre = new wxBitmapButton(this, wageID_pre, preicon,
        wxPoint(iconx + iconw, icony), wxSize(30, 30), 0);
    Connect(wageID_pre, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WagePanel::OnPre));
    m_next = new wxBitmapButton(this, wageID_next, nexticon,
        wxPoint(iconx + 4 * iconw, icony), wxSize(30, 30), 0);
    Connect(wageID_next, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WagePanel::OnNext));
    m_last = new wxBitmapButton(this, wageID_last, lasticon,
        wxPoint(iconx + 5 * iconw, icony), wxSize(30, 30), 0);
    Connect(wageID_last, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WagePanel::OnLast));

    /*m_comboBox1 = new wxComboBox(this, boxID_search2, "", wxPoint(100, 70));
    m_comboBox2 = new wxComboBox(this, boxID_choice2, "", wxPoint(300, 70));
    m_comboBox1->Append(wxT("ID"));
    m_comboBox1->Append(wxT("NAME"));
    m_comboBox1->Append(wxT("POSITION"));
    Connect(boxID_search2, wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(WagePanel::OnCombBoxSelect1));
    Connect(boxID_choice2, wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(WagePanel::OnCombBoxSelect2));*/
}

void WagePanel::OnPaint(wxPaintEvent&event)
{
    wxBufferedPaintDC mydc(this);
    mydc.SetPen(*wxWHITE_PEN);
    mydc.SetBrush(*wxWHITE_BRUSH);
    mydc.SetBackground(wxBrush(*wxWHITE, wxBRUSHSTYLE_SOLID));
    //获取窗口大小
    wxSize sz = GetClientSize();
    //要绘制的矩形大小
    wxCoord w = sz.x, h = sz.y;
    wxRect rectToDraw(0, 0, w, h);
    //只有在需要的时候才重新画以便提高效率
    if (IsExposed(rectToDraw))
        mydc.DrawRectangle(rectToDraw);

    //显示Employee Information标题
    wxFont font1(16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    mydc.SetFont(font1);
    mydc.SetBackgroundMode(wxSOLID/*wxTRANSPARENT*/);
    mydc.SetTextForeground(*wxBLACK);
    mydc.SetTextBackground(*wxWHITE);
    mydc.DrawText("Wage Information", 80, 50);

    //绘制表格框架
    int hh = 40;
    int ww = 120;
    int x = 80;
    int y = 130;
    mydc.SetPen(*wxLIGHT_GREY_PEN);
    mydc.DrawLine(wxPoint(x, y), wxPoint(x + 4 * ww, y));
    mydc.DrawLine(wxPoint(x, y + hh), wxPoint(x + 4 * ww, y + hh));
    mydc.DrawLine(wxPoint(x, y + 2 * hh), wxPoint(x + 4 * ww, y + 2 * hh));
    mydc.DrawLine(wxPoint(x, y + 3 * hh), wxPoint(x + 4 * ww, y + 3 * hh));
    mydc.DrawLine(wxPoint(x, y + 4 * hh), wxPoint(x + 4 * ww, y + 4 * hh));
    mydc.DrawLine(wxPoint(x, y + 5 * hh), wxPoint(x + 4 * ww, y + 5 * hh));
    mydc.DrawLine(wxPoint(x, y + 6 * hh), wxPoint(x + 4 * ww, y + 6 * hh));
    mydc.DrawLine(wxPoint(x, y + 7 * hh), wxPoint(x + 4 * ww, y + 7 * hh));
    mydc.DrawLine(wxPoint(x, y + 8 * hh), wxPoint(x + 4 * ww, y + 8 * hh));
    mydc.DrawLine(wxPoint(x, y + 9 * hh), wxPoint(x + 4 * ww, y + 9 * hh));
    mydc.DrawLine(wxPoint(x, y + 10 * hh), wxPoint(x + 4 * ww, y + 10 * hh));
    mydc.DrawLine(wxPoint(x, y + 11 * hh), wxPoint(x + 4 * ww, y + 11 * hh));

    mydc.DrawLine(wxPoint(x, y), wxPoint(x, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + ww, y), wxPoint(x + ww, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + 2 * ww, y), wxPoint(x + 2 * ww, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + 3 * ww, y), wxPoint(x + 3 * ww, y + 11 * hh));
    mydc.DrawLine(wxPoint(x + 4 * ww, y), wxPoint(x + 4 * ww, y + 11 * hh));

    //填入表头
    wxFont font2(16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mydc.SetFont(font2);
    mydc.SetBackgroundMode(wxSOLID);
    mydc.SetTextForeground(*wxBLACK);
    mydc.SetTextBackground(*wxWHITE);
    int title_x = 95;
    int title_y = 140;
    mydc.DrawText("   ID   ", title_x, title_y);
    mydc.DrawText("  NAME  ", title_x + ww, title_y);
    mydc.DrawText("POSITION", title_x + 2 * ww, title_y);
    mydc.DrawText("  WAGE  ", title_x + 3 * ww, title_y);

    //绘制员工信息
   //默认显示第一页
    SuperExcel excel("data.csv");
    Employee e;
    int total = excel.GetTotal();
    int num = total % 10;
    int p = total / 10;
    int last = p + (num != 0 ? 1 : 0);
    //set
    mydc.SetPen(*wxWHITE_PEN);
    mydc.SetBrush(*wxWHITE_BRUSH);
    mydc.SetBackground(wxBrush(*wxWHITE, wxBRUSHSTYLE_SOLID));

    int i;
    string po;
    wxString _number;
    for (i = 1; i <= 10 && ((page - 1) * 10 + i) <= total; i++) {
        e = excel.GetEmployee((page - 1) * 10 + i);
        _number = wxString::Format("%06d", e.GetNumber());
        if (e.GetPosition() == 0)
            po = "Employee";
        else if (e.GetPosition() == 1)
            po = "Technican";
        else
            po = "Manager";
        mydc.DrawText(_number, title_x, title_y + hh * i);
        mydc.DrawText(e.GetName(), title_x + ww, title_y + hh * i);
        mydc.DrawText(po, title_x + ww * 2, title_y + hh * i);
        mydc.DrawText(to_string(e.GetSalary()), title_x + ww * 3, title_y + hh * i);

    }
}

void WagePanel::OnCombBoxSelect1(wxCommandEvent &event)
{
    SuperExcel excel("data.csv");
    Employee e;
    int i;
    int number = excel.GetTotal();
    wxString msg;
    m_comboBox2->Clear();
    switch (m_comboBox1->GetSelection())
    {
    case 0:
        for (i = 1; i <= number; i++)
        {
            e = excel.GetEmployee(i);
            msg = std::to_string(e.GetNumber());
            m_comboBox2->Append(msg);
        }
        break;
    case 1:
        for (i = 1; i <= number; i++)
        {
            e = excel.GetEmployee(i);
            msg = e.GetName();
            m_comboBox2->Append(msg);
        }
        break;
    case 2:
        for (i = 1; i <= number; i++)
        {
            e = excel.GetEmployee(i);
            msg = std::to_string(e.GetPosition());
            m_comboBox2->Append(msg);
        }
        break;
    }
}

void WagePanel::OnCombBoxSelect2(wxCommandEvent &event)
{

}

void WagePanel::OnFirst(wxCommandEvent & WXUNUSED(event))
{
    Refresh();
    page = 1;
}

void WagePanel::OnLast(wxCommandEvent & WXUNUSED(event))
{
    Refresh();
    SuperExcel excel("data.csv");
    Employee e;
    int total = excel.GetTotal();
    int num = total % 10;
    int p = total / 10;
    int last = p + (num != 0 ? 1 : 0);
    page = last;
}

void WagePanel::OnNext(wxCommandEvent & WXUNUSED(event))
{
    Refresh();
    SuperExcel excel("data.csv");
    Employee e;
    int total = excel.GetTotal();
    int num = total % 10;
    int p = total / 10;
    int last = p + (num != 0 ? 1 : 0);
    if (page != last) page++;
    else;
}

void WagePanel::OnPre(wxCommandEvent & WXUNUSED(event))
{
    Refresh();
    if (page > 1) page--;
    else;
}

void WagePanel::OnDetail(wxCommandEvent &event)
{

    int id;
    SuperExcel excel("data.csv");
    int total = excel.GetTotal();
    id = event.GetId() - wageID_detail - 1000 + (page - 1) * 10;
    if (id <= total)
    {
        WageDialog * m_wagedialog = new WageDialog(_T("Detailed Wage Information"), id);

        m_wagedialog->Show(true);
    }
    else
    {
        wxMessageBox(wxT("Employee not exists! You need to add an employee first!"));
    }
}

WageDialog::WageDialog(const wxString & title, int num)
    :wxDialog(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(360, 360))
{
    //员工信息提取
    SuperExcel excel("data.csv");
    Employee e = excel.GetEmployee(num);
    wxString _number = wxString::Format("ID: %06d", e.GetNumber());
    wxString _name = wxString::Format("Name: %s", e.GetName());
    wxString _sex = wxString::Format("Gender: %s", e.GetSex());
    wxString _age = wxString::Format("Age: %d", e.GetAge());
    wxString _workingAge = wxString::Format("Working Age: %d", 2021 - atoi(e.GetStartYear().c_str()));
    wxString po;
    wxString baseMoney = wxT("Base Wage: ");
    wxString caculate=wxT("Salary = ");
    if (e.GetPosition() == 0)
    {
        po = wxString::Format("Position: Employee");
        baseMoney << EMPLOYEE_BASIC_SALARY;
        caculate << EMPLOYEE_BASIC_SALARY << " + " << "wAge" << " * 200";
    }
    else if (e.GetPosition() == 1)
    {
        po = wxString::Format("Position: Technican");
        baseMoney << TECHNICAN_BASIC_SALARY;
        caculate << TECHNICAN_BASIC_SALARY << " + " << "wAge" << " * 666";
    }
    else
    {
        po = wxString::Format("Position: Manager");
        baseMoney << MANAGER_BASIC_SALARY;
        caculate << MANAGER_BASIC_SALARY << " + " << "wAge" << " * 500";
    }
       
    wxString _startYear = wxString::Format("Working Since: %s", e.GetStartYear());
    wxString _total = wxString::Format("The monthly salary is: %d", e.GetSalary());

    //员工信息显示
    wxPanel * panel = new wxPanel(this, wxID_ANY);

    wxStaticBox * id = new wxStaticBox(this, wxID_ANY, _number,
        wxPoint(10, 15), wxSize(320, 250));

    wxStaticText * name = new wxStaticText(this, wxID_ANY,
        _name, wxPoint(150, 40));
    wxStaticText * gender = new wxStaticText(this, wxID_ANY,
        _sex, wxPoint(150, 60));
    wxStaticText * age = new wxStaticText(this, wxID_ANY,
        _age, wxPoint(150, 80));
    wxStaticText * position = new wxStaticText(this, wxID_ANY,
        po, wxPoint(150, 100));
    wxStaticText * time = new wxStaticText(this, wxID_ANY,
        _startYear, wxPoint(150, 120));
    wxStaticText * wokingage = new wxStaticText(this, wxID_ANY,
        _workingAge, wxPoint(150, 140));
   /* wxStaticText * manhour = new wxStaticText(this, wxID_ANY,
        wxT("Man_hours: 2500 h"), wxPoint(150, 160));*/
    wxStaticLine * line1 = new wxStaticLine(this, wxID_ANY,
        wxPoint(145, 180), wxSize(170, 3));
    wxStaticText * wage = new wxStaticText(this, wxID_ANY,
        baseMoney, wxPoint(150, 185), wxDefaultSize, wxALIGN_RIGHT);
    wxStaticText * bouns = new wxStaticText(this, wxID_ANY,
        caculate, wxPoint(150, 205), wxDefaultSize, wxALIGN_RIGHT);
    wxStaticLine * line2 = new wxStaticLine(this, wxID_ANY,
        wxPoint(145, 225), wxSize(120, 1));
    wxStaticText * total = new wxStaticText(this, wxID_ANY,
        _total, wxPoint(150, 230));

    wxButton * backButton = new wxButton(this, wageID_back, _T("Back"),
        wxPoint(260, 275), wxSize(70, 30));
    Connect(wageID_back, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WageDialog::OnBack));

    if (e.GetSex() == "male" && e.GetPosition() == 0)
        potrait.LoadFile("maleworker.bmp", wxBITMAP_TYPE_BMP);
    else if (e.GetSex() == "male" && e.GetPosition() == 1)
        potrait.LoadFile("maletechnician.bmp", wxBITMAP_TYPE_BMP);
    else if (e.GetSex() == "male" && e.GetPosition() == 2)
        potrait.LoadFile("malemanager.bmp", wxBITMAP_TYPE_BMP);
    else if (e.GetSex() == "female" && e.GetPosition() == 0)
        potrait.LoadFile("femaleworker.bmp", wxBITMAP_TYPE_BMP);
    else if (e.GetSex() == "female" && e.GetPosition() == 1)
        potrait.LoadFile("femaletechnician.bmp", wxBITMAP_TYPE_BMP);
    else
        potrait.LoadFile("femalemanager.bmp", wxBITMAP_TYPE_BMP);
    

    Connect(wageID_hello, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WageDialog::OnHello));
    
    m_map = new wxBitmapButton(this, wageID_hello, potrait,
        wxPoint(30, 50), wxSize(100, 100), 0);

    SetIcon(wxIcon(detaildialogicon_xpm));

    Centre();
    ShowModal();
    Destroy();
}

void WageDialog::OnBack(wxCommandEvent &WXUNUSED(event))
{
    Destroy();
}

void WageDialog::OnHello(wxCommandEvent &WXUNUSED(event))
{
    static bool flag = false;

    wxStaticText *hello1 = new wxStaticText(this, wxID_ANY, wxT("Hello!"), wxPoint(30, 160));
    wxStaticText *hello2 = new wxStaticText(this, wxID_ANY, wxT("I have more hair"), wxPoint(30, 180));
    wxStaticText *hello3 = new wxStaticText(this, wxID_ANY, wxT("than you."), wxPoint(30, 200));
}

void AnalyzePanel::OnScatter(wxCommandEvent & WXUNUSED(event))
{
    MyFrame *comm = (MyFrame *)m_parent->GetParent();
    comm->m_sp->Hide();
    comm->m_ip->Hide();
    comm->m_ep->Hide();
    comm->m_wp->Hide();
    comm->m_ap->Hide();
    comm->m_cp->Hide();
    comm->m_app->Show();
}


//工资分析界面
AnalyzePanel::AnalyzePanel(wxPanel * parent)
    : wxPanel(parent, -1, wxPoint(0, 0), wxSize(720, 720), wxBORDER_DEFAULT)
{
    m_parent = parent;
    m_scatter = new wxButton(this, AnaID_scatter, wxT("scatter analysis"),
        wxPoint(310, 60), wxSize(100, 50));
    Connect(AnaID_scatter, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(AnalyzePanel::OnScatter));
    Bind(wxEVT_PAINT, &AnalyzePanel::OnPaint, this);
}

void AnalyzePanel::OnPaint(wxPaintEvent&event)
{
    wxPaintDC mydc(this);
    mydc.SetPen(*wxWHITE_PEN);
    mydc.SetBrush(*wxWHITE_BRUSH);
    mydc.SetBackground(wxBrush(*wxWHITE, wxBRUSHSTYLE_SOLID));
    //获取窗口大小
    wxSize sz = GetClientSize();
    //要绘制的矩形大小
    wxCoord w = sz.x, h = sz.y;
    wxRect rectToDraw(0, 0, w, h);
    //只有在需要的时候才重新画以便提高效率
    if (IsExposed(rectToDraw))
        mydc.DrawRectangle(rectToDraw);

    //显示Employee Information标题
    wxFont font1(16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    mydc.SetFont(font1);
    mydc.SetBackgroundMode(wxSOLID/*wxTRANSPARENT*/);
    mydc.SetTextForeground(*wxBLACK);
    mydc.SetTextBackground(*wxWHITE);
    mydc.DrawText("Wage Analysis", 80, 20);
    draw_column_image(mydc);


}

void AnalyzePanel2::OnColumn(wxCommandEvent & WXUNUSED(event))
{
    MyFrame *comm = (MyFrame *)m_parent->GetParent();
    comm->m_sp->Hide();
    comm->m_ip->Hide();
    comm->m_ep->Hide();
    comm->m_wp->Hide();
    comm->m_ap->Show();
    comm->m_cp->Hide();
    comm->m_app->Hide();

}

AnalyzePanel2::AnalyzePanel2(wxPanel * parent)
    : wxPanel(parent, -1, wxPoint(0, 0), wxSize(720, 720), wxBORDER_DEFAULT)
{
    m_parent = parent;
    m_column = new wxButton(this, AnaID_column, wxT("column analysis"),
        wxPoint(310, 60), wxSize(100, 50));
    Connect(AnaID_column, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(AnalyzePanel2::OnColumn));
    Bind(wxEVT_PAINT, &AnalyzePanel2::OnPaint, this);
}

void AnalyzePanel2::OnPaint(wxPaintEvent&event)
{
    wxPaintDC mydc(this);
    mydc.SetPen(*wxWHITE_PEN);
    mydc.SetBrush(*wxWHITE_BRUSH);
    mydc.SetBackground(wxBrush(*wxWHITE, wxBRUSHSTYLE_SOLID));
    //获取窗口大小
    wxSize sz = GetClientSize();
    //要绘制的矩形大小
    wxCoord w = sz.x, h = sz.y;
    wxRect rectToDraw(0, 0, w, h);
    //只有在需要的时候才重新画以便提高效率
    if (IsExposed(rectToDraw))
        mydc.DrawRectangle(rectToDraw);

    //显示Employee Information标题
    wxFont font1(16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    mydc.SetFont(font1);
    mydc.SetBackgroundMode(wxSOLID/*wxTRANSPARENT*/);
    mydc.SetTextForeground(*wxBLACK);
    mydc.SetTextBackground(*wxWHITE);
    mydc.DrawText("Wage Analysis", 80, 20);
    draw_scatter_image(mydc);
}

//工资计算说明
WageCalPanel::WageCalPanel(wxPanel * parent)
    : wxPanel(parent, -1, wxPoint(0, 0), wxSize(720, 720), wxBORDER_DEFAULT)
{
    m_parent = parent;

    Bind(wxEVT_PAINT, &WageCalPanel::OnPaint, this);

    wxColour col;
    col.Set(wxT("#EBEBEB"));

    text1 = new wxStaticText(this, wxID_ANY, wxT("Wage Calculation Rules"), wxPoint(50, 60), wxSize(200, 40), wxALIGN_LEFT);
    text2 = new wxStaticText(this, wxID_ANY, wxT("Wage=Basic Salary+Wage Coefficient*Working Years\n\nWorking Years=Current Time-Entry Time\n\nCurrent Time is obtained by the computer in real time.\n"), wxPoint(50, 140), wxSize(200, 40), wxALIGN_LEFT);
    text3 = new wxStaticText(this, wxID_ANY, wxT("Different positions have different Basic Salaries and Wage Coeffieients.\n\nFor worker:Basic Salary=5000,Coefficient=200\n\nFor technican:Basic Salary=8000,Wage Coefficient=666\n\nFor manager:Basic Salary=10000,Wage Coefficient=500"), wxPoint(50, 260), wxSize(400, 400), wxALIGN_LEFT);
    text4 = new wxStaticText(this, wxID_ANY, wxT("Example:For worker Tony,his Basic Aalary=5000,his Wage Coefficient=200,\n\nhis Entry Time=1997.So his Wage=5000+200*(2021-1997)=9800."), wxPoint(50, 410), wxSize(400, 400), wxALIGN_LEFT);
    wxFont font1(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, _T("Times New Roman"), wxFONTENCODING_ISO8859_1);
    text1->SetFont(font1);
    text1->SetBackgroundColour(col);
    wxFont font2(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, _T("Arial"), wxFONTENCODING_ISO8859_1);
    text2->SetBackgroundColour(*wxWHITE);
    text3->SetBackgroundColour(*wxWHITE);
    text4->SetBackgroundColour(*wxWHITE);
    text2->SetFont(font2);
    text3->SetFont(font2);
    text4->SetFont(font2);
}

void WageCalPanel::OnPaint(wxPaintEvent&event)
{
    wxPaintDC mydc(this);
    mydc.SetPen(*wxWHITE_PEN);
    mydc.SetBrush(*wxWHITE_BRUSH);
    mydc.SetBackground(wxBrush(*wxWHITE, wxBRUSHSTYLE_SOLID));
    //获取窗口大小
    wxSize sz = GetClientSize();
    //要绘制的矩形大小
    wxCoord w = sz.x, h = sz.y;
    wxRect rectToDraw(0, 0, w, h);
    //只有在需要的时候才重新画以便提高效率
    if (IsExposed(rectToDraw))
        mydc.DrawRectangle(rectToDraw);

}

UserGuidePanel::UserGuidePanel(wxPanel * parent)
    : wxPanel(parent, -1, wxPoint(0, 0), wxSize(720, 720), wxBORDER_DEFAULT)
{
    m_parent = parent;

    Bind(wxEVT_PAINT, &UserGuidePanel::OnPaint, this);

    wxColour col1,col2;
    col1.Set(wxT("#F5F5F5"));
    col2.Set(wxT("#EBEBEB"));

    button_info = new wxButton(this,buttonID_info,wxT("Information Page"), wxPoint(35, 150), wxSize(180, 40));
    button_edit = new wxButton(this, buttonID_edit, wxT("Edit Page"), wxPoint(35, 240), wxSize(180, 40));;
    button_data = new wxButton(this, buttonID_data, wxT("Wage Data Page"), wxPoint(35, 330), wxSize(180, 40));;
    button_anal = new wxButton(this, buttonID_anal, wxT("Wage Analysis Page"), wxPoint(35, 420), wxSize(180, 40));;
    button_calc = new wxButton(this, buttonID_calc, wxT("Wage calculation Rules Page"), wxPoint(35, 500), wxSize(180, 40));;
    button_info->SetBackgroundColour(col1);
    button_edit->SetBackgroundColour(col1);
    button_data->SetBackgroundColour(col1);
    button_anal->SetBackgroundColour(col1);
    button_calc->SetBackgroundColour(col1);

    text = new wxStaticText(this, wxID_ANY, wxT("User Guide"), wxPoint(50, 60), wxSize(50, 40), wxALIGN_LEFT);
    wxFont font1(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, _T("Times New Roman"), wxFONTENCODING_ISO8859_1);
    text->SetFont(font1);
    text->SetBackgroundColour(col2);
    wxFont font2(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, _T("Arial"), wxFONTENCODING_ISO8859_1);
    wxFont font3(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, _T("Arial"), wxFONTENCODING_ISO8859_1);
    textinfo1= new wxStaticText(this, wxID_ANY, wxT("Information Page Instruction"), wxPoint(250, 150), wxSize(50, 40), wxALIGN_LEFT);
    textedit1= new wxStaticText(this, wxID_ANY, wxT("Edit Page Instruction"), wxPoint(250, 150), wxSize(50, 40), wxALIGN_LEFT);
    textdata1 = new wxStaticText(this, wxID_ANY, wxT("Wage Data Page Instruction"), wxPoint(250, 150), wxSize(50, 40), wxALIGN_LEFT);
    textanal1 = new wxStaticText(this, wxID_ANY, wxT("Wage Analysis Page Instruction"), wxPoint(250, 150), wxSize(50, 40), wxALIGN_LEFT);
    textcalc1 = new wxStaticText(this, wxID_ANY, wxT("Wage Calculation Page Instruction"), wxPoint(250, 150), wxSize(50, 40), wxALIGN_LEFT);
    textinfo2 = new wxStaticText(this, wxID_ANY, wxT("Display all worker's information, including ID, name, gender, \n\nage and position.\n\n\nClick the button down of the page to turn over."), wxPoint(250, 200), wxSize(50, 40), wxALIGN_LEFT);
    textedit2 = new wxStaticText(this, wxID_ANY, wxT("Edit and retrieve employee information.\n\n\nAdd new employee:\n\nClick the button at the top left and add new employee's\n\ninformation in the popup dialog.\n\nEdit existing employee's information:\n\nClick the button on the right side of the table and edit or\n\ndelete corresponding employee's information.\n\nSearch for employee's information:\n\nSelect filter condition in the drop-down box and click the\n\nsearch button to display eligible employees' information."), wxPoint(250, 200), wxSize(50, 40), wxALIGN_LEFT);
    textdata2 = new wxStaticText(this, wxID_ANY, wxT("Display employees'wage information.\n\n\nClick the button on the right side of the table and check\n\nout the corresponding employee's detailed information \n\nin the popup dialog."), wxPoint(250, 200), wxSize(50, 40), wxALIGN_LEFT);
    textanal2 = new wxStaticText(this, wxID_ANY, wxT("Display the distribution of employees' wage.\n\n\nClick the button on the top of the page to switch\n\nbetween scatter plot and histogram."), wxPoint(250, 200), wxSize(50, 40), wxALIGN_LEFT);
    textcalc2 = new wxStaticText(this, wxID_ANY, wxT("Display wage's calculation rules."), wxPoint(250,200), wxSize(50, 40), wxALIGN_LEFT);
    textinfo1->SetBackgroundColour(*wxWHITE);
    textinfo1->SetFont(font2);
    textedit1->SetBackgroundColour(*wxWHITE);
    textedit1->SetFont(font2);
    textdata1->SetBackgroundColour(*wxWHITE);
    textdata1->SetFont(font2);
    textanal1->SetBackgroundColour(*wxWHITE);
    textanal1->SetFont(font2);
    textcalc1->SetBackgroundColour(*wxWHITE);
    textcalc1->SetFont(font2);
    textinfo2->SetBackgroundColour(*wxWHITE);
    textinfo2->SetFont(font3);
    textedit2->SetBackgroundColour(*wxWHITE);
    textedit2->SetFont(font3);
    textdata2->SetBackgroundColour(*wxWHITE);
    textdata2->SetFont(font3);
    textanal2->SetBackgroundColour(*wxWHITE);
    textanal2->SetFont(font3);
    textcalc2->SetBackgroundColour(*wxWHITE);
    textcalc2->SetFont(font3);

    textinfo1->Hide();
    textedit1->Hide();
    textdata1->Hide();
    textanal1->Hide();
    textcalc1->Hide();
    textinfo2->Hide();
    textedit2->Hide();
    textdata2->Hide();
    textanal2->Hide();
    textcalc2->Hide();

    Connect(buttonID_info, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(UserGuidePanel::OnInfo));
    Connect(buttonID_edit, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(UserGuidePanel::OnEdit));
    Connect(buttonID_data, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(UserGuidePanel::OnData));
    Connect(buttonID_anal, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(UserGuidePanel::OnAnal));
    Connect(buttonID_calc, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(UserGuidePanel::OnCalc));
}

void UserGuidePanel::OnPaint(wxPaintEvent&event)
{
    wxPaintDC mydc(this);
    mydc.SetPen(*wxWHITE_PEN);
    mydc.SetBrush(*wxWHITE_BRUSH);
    mydc.SetBackground(wxBrush(*wxWHITE, wxBRUSHSTYLE_SOLID));
    //获取窗口大小
    wxSize sz = GetClientSize();
    //要绘制的矩形大小
    wxCoord w = sz.x, h = sz.y;
    wxRect rectToDraw(0, 0, w, h);
    //只有在需要的时候才重新画以便提高效率
    if (IsExposed(rectToDraw))
        mydc.DrawRectangle(rectToDraw);
}

void UserGuidePanel::OnInfo(wxCommandEvent&event)
{
    textinfo1->Show();
    textedit1->Hide();
    textdata1->Hide();
    textanal1->Hide();
    textcalc1->Hide();
    textinfo2->Show();
    textedit2->Hide();
    textdata2->Hide();
    textanal2->Hide();
    textcalc2->Hide();
}

void UserGuidePanel::OnEdit(wxCommandEvent&event)
{
    textinfo1->Hide();
    textedit1->Show();
    textdata1->Hide();
    textanal1->Hide();
    textcalc1->Hide();
    textinfo2->Hide();
    textedit2->Show();
    textdata2->Hide();
    textanal2->Hide();
    textcalc2->Hide();
}

void UserGuidePanel::OnData(wxCommandEvent&event)
{

    textinfo1->Hide();
    textedit1->Hide();
    textdata1->Show();
    textanal1->Hide();
    textcalc1->Hide();
    textinfo2->Hide();
    textedit2->Hide();
    textdata2->Show();
    textanal2->Hide();
    textcalc2->Hide();
}

void UserGuidePanel::OnAnal(wxCommandEvent&event)
{
    textinfo1->Hide();
    textedit1->Hide();
    textdata1->Hide();
    textanal1->Show();
    textcalc1->Hide();
    textinfo2->Hide();
    textedit2->Hide();
    textdata2->Hide();
    textanal2->Show();
    textcalc2->Hide();
}

void UserGuidePanel::OnCalc(wxCommandEvent&event)
{
    textinfo1->Hide();
    textedit1->Hide();
    textdata1->Hide();
    textanal1->Hide();
    textcalc1->Show();
    textinfo2->Hide();
    textedit2->Hide();
    textdata2->Hide();
    textanal2->Hide();
    textcalc2->Show();
}

AboutPanel::AboutPanel(wxPanel * parent)
    : wxPanel(parent, -1, wxPoint(0, 0), wxSize(720, 720), wxBORDER_DEFAULT)
{
    m_parent = parent;

    Bind(wxEVT_PAINT, &AboutPanel::OnPaint, this);

    wxColour col;
    col.Set(wxT("#EBEBEB"));

    text1 = new wxStaticText(this, wxID_ANY, wxT("About"), wxPoint(50, 60), wxSize(50, 40), wxALIGN_LEFT);
    text2 = new wxStaticText(this, wxID_ANY, wxT("Program Name:Enterprise Wages Management System\n\nProgram Edition:1.0(built:2021.1.10)\n\nProgram Instruction:first built in 2020.12.15,\nused for the course\"Object - oriented programming\"\n\nProgram Functions:\n1.Display of employees' basic information\n2.Display of employees' wage information\n3.Edit employees' information,register or delete an employee\n4.Filter the list of emplyees by given condition\n5.Analyze the distribution of employees' wages by scatter diagram and histogram\n\nOperating System:Windows 10 Home Edition(Chinese,x64)\n\nDeveloper Team:\n\nZhang Zechuan         Fang Zhiyang        Zhang Hao           Jin Zihao         Fang Hanxi"), wxPoint(50, 130), wxSize(200, 40), wxALIGN_LEFT);
    wxFont font1(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, _T("Times New Roman"), wxFONTENCODING_ISO8859_1);
    text1->SetFont(font1);
    text1->SetBackgroundColour(col);
    wxFont font2(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, _T("Arial"), wxFONTENCODING_ISO8859_1);
    text2->SetBackgroundColour(*wxWHITE);
    text2->SetFont(font2);
}

void AboutPanel::OnPaint(wxPaintEvent&event)
{
    wxPaintDC mydc(this);
    mydc.SetPen(*wxWHITE_PEN);
    mydc.SetBrush(*wxWHITE_BRUSH);
    mydc.SetBackground(wxBrush(*wxWHITE, wxBRUSHSTYLE_SOLID));
    //获取窗口大小
    wxSize sz = GetClientSize();
    //要绘制的矩形大小
    wxCoord w = sz.x, h = sz.y;
    wxRect rectToDraw(0, 0, w, h);
    //只有在需要的时候才重新画以便提高效率
    if (IsExposed(rectToDraw))
        mydc.DrawRectangle(rectToDraw);
    wxInitAllImageHandlers();//添加对jpg图片读取的handel
    wxBitmap pic1(wxT("zzc.png"), wxBITMAP_TYPE_PNG);
    wxBitmap pic2(wxT("fzy.png"), wxBITMAP_TYPE_PNG);
    wxBitmap pic3(wxT("zh.png"), wxBITMAP_TYPE_PNG);
    wxBitmap pic4(wxT("jzh.png"), wxBITMAP_TYPE_PNG);
    wxBitmap pic5(wxT("fhx.png"), wxBITMAP_TYPE_PNG);
    if (pic1.Ok())
        mydc.DrawBitmap(pic1, 50, 460);
    if (pic2.Ok())
        mydc.DrawBitmap(pic2, 180, 460);
    if (pic3.Ok())
        mydc.DrawBitmap(pic3, 300, 460);
    if (pic4.Ok())
        mydc.DrawBitmap(pic4, 400, 460);
    if (pic5.Ok())
        mydc.DrawBitmap(pic5, 505, 460);
}
