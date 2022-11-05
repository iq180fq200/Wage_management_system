#ifndef ppppp_____

#define ppppp_____

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/spinbutt.h>
#include <wx/richtext/richtextctrl.h>

//定义散点图每个点的内容
class person_point {
private:
    int old;
    int salary;
    double x;//点的位置
    double y;//点的位置
public:
    person_point(int Old, int Salary);
    void cal_y(void);
    void cal_x(void);
    double get_x(void) {
        return x;
    }
    double get_y(void) {
        return y;
    }
    //static int max_old;//最大年龄
    //static int min_old;
};

void init_point(void);

//定义柱状图的每条柱子,一个区间对应的人数
class column {
private:
    int upper_money;
    int lower_money;
    int num;//柱子编号，1，2，3，4，5
    int people;//人数

public:
    double height;//柱子的高度
    static const double column_width;//柱子宽度
    int bottom_x;//柱子左下角横坐标值相对于原点横坐标距离
    const int judge_in(const int& money);//判断是否在区间内
    void add_people(void);//增加1人
    void cal_height(void); //计算柱子高度
    int get_people(void) {
        return people;
    }
    column(int lower_m, int upper_m, int n);
    void init_people(void) {
        people = 0;
    }
};

class StartPanel : public wxPanel
{
public:
    StartPanel(wxPanel *parent);

    void OnQuit(wxCommandEvent & event);
    void OnStart(wxCommandEvent & event);
    void OnPaint(wxPaintEvent &event);

    wxButton *m_quit;
    wxButton *m_start;
    wxPanel *m_parent;

};

class InforPanel : public wxPanel
{
public:
    InforPanel(wxPanel *parent);
    static int page;  
    void OnFirst(wxCommandEvent & event);
    void OnLast(wxCommandEvent & event);
    void OnNext(wxCommandEvent &event);
    void OnPre(wxCommandEvent &event);
    void OnPaint(wxPaintEvent &event);

    wxBitmap firsticon;
    wxBitmap lasticon;
    wxBitmap nexticon;
    wxBitmap preicon;

    wxBitmapButton *m_first;
    wxBitmapButton *m_last;
    wxBitmapButton *m_next;
    wxBitmapButton *m_pre;
};

class EditPanel : public wxPanel
{
public:
    EditPanel(wxPanel *parent);
    static int page; //我加的
    static int choice;
    static int ID;
    static int age;
    static int position;
    static int flag;
    static int selectednumber;
    static wxString name;
    static wxString sex;
    void OnPaint(wxPaintEvent &event);
    void OnEdit(wxCommandEvent &event);
    void OnDelete(wxCommandEvent &event);
    void OnAdd(wxCommandEvent &event);
    void OnFirst(wxCommandEvent & event);
    void OnLast(wxCommandEvent & event);
    void OnNext(wxCommandEvent &event);
    void OnPre(wxCommandEvent &event);
    void OnHandle(wxCommandEvent &event);
    void OnSearch();
    void OnBack();

    wxBitmap editicon;
    wxBitmap deleteicon;
    wxBitmap addicon;
    wxBitmap firsticon;
    wxBitmap lasticon;
    wxBitmap nexticon;
    wxBitmap preicon;
    wxBitmap searchicon;
    wxBitmap searchiconselected;

    wxBitmapButton *m_edit;
    wxBitmapButton *m_delete;
    wxBitmapButton *m_add;
    wxBitmapButton *m_first;
    wxBitmapButton *m_last;
    wxBitmapButton *m_next;
    wxBitmapButton *m_pre;
    wxBitmapButton *m_search;

	wxComboBox *m_comboBox1;
	wxComboBox *m_comboBox2;

	void OnCombBoxSelect1(wxCommandEvent &event);
	void OnCombBoxSelect2(wxCommandEvent &event);
};

class WagePanel : public wxPanel
{
public:
    WagePanel(wxPanel *parent);
    static int page;
    void OnPaint(wxPaintEvent &event);

    void OnDetail(wxCommandEvent &event);
    void OnFirst(wxCommandEvent & event);
    void OnLast(wxCommandEvent & event);
    void OnNext(wxCommandEvent &event);
    void OnPre(wxCommandEvent &event);

    wxBitmap detailicon;
    wxBitmap firsticon;
    wxBitmap lasticon;
    wxBitmap nexticon;
    wxBitmap preicon;

    wxBitmapButton *m_detail;
    wxBitmapButton *m_first;
    wxBitmapButton *m_last;
    wxBitmapButton *m_next;
    wxBitmapButton *m_pre;

	wxComboBox *m_comboBox1;
	wxComboBox *m_comboBox2;

	void OnCombBoxSelect1(wxCommandEvent &event);
	void OnCombBoxSelect2(wxCommandEvent &event);
};

class AnalyzePanel : public wxPanel
{
public:
    AnalyzePanel(wxPanel *parent);
    void OnScatter(wxCommandEvent & event);
    wxButton *m_scatter;
    wxPanel *m_parent;
    void OnPaint(wxPaintEvent &event);
    void draw_column_image(wxPaintDC &dc);
    void draw_axis(wxPaintDC &mydc);//画坐标轴
    void draw_column(wxPaintDC &mydc);//画五个柱形图

};

class AnalyzePanel2 : public wxPanel
{
public:
    AnalyzePanel2(wxPanel *parent);
    void OnColumn(wxCommandEvent & event);
    wxButton *m_column;
    wxPanel *m_parent;
    void OnPaint(wxPaintEvent &event);
    void draw_scatter_image(wxPaintDC &dc);
    void draw_axis(wxPaintDC &mydc);//画坐标轴
    void draw_point(wxPaintDC &mydc, person_point person);//画五个柱形图

};

class WageCalPanel : public wxPanel
{
public:
    WageCalPanel(wxPanel *parent);
    void OnPaint(wxPaintEvent &event);

    wxStaticText *text1;
    wxStaticText *text2;
    wxStaticText *text3;
    wxStaticText *text4;
};

class UserGuidePanel : public wxPanel
{
public:
    UserGuidePanel(wxPanel *parent);
    void OnPaint(wxPaintEvent &event);

    wxButton *button_info;
    wxButton *button_edit;
    wxButton *button_data;
    wxButton *button_anal;
    wxButton *button_calc;

    wxStaticText *text;
    wxStaticText *textinfo1;
    wxStaticText *textinfo2;
    wxStaticText *textedit1;
    wxStaticText *textedit2;
    wxStaticText *textdata1;
    wxStaticText *textdata2;
    wxStaticText *textanal1;
    wxStaticText *textanal2;
    wxStaticText *textcalc1;
    wxStaticText *textcalc2;

    void OnInfo(wxCommandEvent &event);
    void OnEdit(wxCommandEvent &event);
    void OnData(wxCommandEvent &event);
    void OnAnal(wxCommandEvent &event);
    void OnCalc(wxCommandEvent &event);
};

class AboutPanel : public wxPanel
{
public:
    AboutPanel(wxPanel *parent);
    void OnPaint(wxPaintEvent &event);
    wxStaticText *text1;
    wxStaticText *text2;
    wxStaticBitmap *male1;
    wxStaticBitmap *male2;
    wxStaticBitmap *female1;
    wxStaticBitmap *female2;
    wxStaticBitmap *female3;
};

class EditDialog : public wxDialog
{
public:
    EditDialog(const wxString & title,int num);
    void OnSave(wxCommandEvent &event);
    void OnBack(wxCommandEvent &event);
    wxTextCtrl * name_input;
    wxRadioButton * female;
    wxRadioButton * male;
    wxTextCtrl * age_input;
    wxRadioButton * worker;
    wxRadioButton * technician;
    wxRadioButton * manager;
};

class AddDialog : public wxDialog
{
public:
    AddDialog(const wxString & title);
    void OnSave(wxCommandEvent &event);
    void OnBack(wxCommandEvent &event);
    wxTextCtrl * name_input;
    wxRadioButton * female;
    wxRadioButton * male;
    wxTextCtrl * age_input;
    wxRadioButton * worker;
    wxRadioButton * technician;
    wxRadioButton * manager;
};

class WageDialog : public wxDialog
{
public:
    WageDialog(const wxString & title, int num);
    void OnBack(wxCommandEvent &event);
    void OnHello(wxCommandEvent &event);
    wxBitmap potrait;
    wxBitmapButton *m_map;
};

enum
{
    pageID_first = wxID_HIGHEST,
    pageID_pre,
    pageID_next,
    pageID_last,
    epageID_first,
    epageID_pre,
    epageID_next,
    epageID_last,
    inforID_edit, //编辑信息
    inforID_delete, //删除信息
    inforID_add,
    inforID_search,
    inforID_back,
    editID_back,
    editID_save,
    addID_back,
    addID_save,
    wageID_first,
    wageID_pre,
    wageID_next,
    wageID_last,
    wageID_detail,
    wageID_back,
    wageID_hello,
    AnaID_column,
    AnaID_scatter,
    boxID_search1,
    boxID_choice1,
    boxID_search2,
    boxID_choice2,
    buttonID_info,
    buttonID_edit,
    buttonID_data,
    buttonID_anal,
    buttonID_calc
};
#endif // ppppp_____
