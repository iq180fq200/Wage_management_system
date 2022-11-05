#include "panels.h"
#include <wx/wxprec.h>
#include "wx/wx.h"
#include <wx/timer.h>
#include "wx/dcbuffer.h"
#include <wx/msgdlg.h>


class MyApp :public wxApp  //我的应用程序，继承了wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame :public wxFrame  //我的窗口类，继承了wxFrame
{
public:
    MyFrame(const wxString&title);//构造函数

    void OnQuit(wxCommandEvent & event);
    void BackStart(wxCommandEvent & event);
    void OnEdit(wxCommandEvent &event);
    void BackInfo(wxCommandEvent &event);
    void OnWage(wxCommandEvent &event);
    void OnAnalyze(wxCommandEvent &event);
    void OnWageCal(wxCommandEvent &event);
    void OnUserGuide(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

    wxMenuBar* getmenubar();
    wxMenuBar *menubar;
    wxMenu *start;
    wxMenu *edit;
    wxMenu *statistics;
    wxMenu *help;
    wxMenuItem *quit;
    StartPanel *m_sp;
    InforPanel *m_ip;
    EditPanel *m_ep;
    WagePanel *m_wp;
    AnalyzePanel *m_ap;
    AnalyzePanel2 *m_app;
    WageCalPanel *m_cp;
    UserGuidePanel *m_up;
    AboutPanel *m_abp;
    wxPanel *m_parent;
};

