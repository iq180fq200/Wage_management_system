#include "display.h"
#include"icon.xpm"



# define TIMER_ID 1000
# define FRAME_HEIGHT 720
# define FRAME_WIDTH 720

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame(wxT("Enterprise Wages Management System"));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString&title) :wxFrame(NULL, wxID_ANY, title, wxDefaultPosition)
{
    
    SetIcon(wxIcon(icon_xpm));
    SetSize(FRAME_HEIGHT, FRAME_WIDTH);  //设置窗口大小
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    m_parent = new wxPanel(this, wxID_ANY);
    m_sp = new StartPanel(m_parent);
    m_ip = new InforPanel(m_parent);
    m_ep = new EditPanel(m_parent);
    m_wp = new WagePanel(m_parent);
    m_ap = new AnalyzePanel(m_parent);
    m_cp = new WageCalPanel(m_parent);
    m_app = new AnalyzePanel2(m_parent);
    m_up = new UserGuidePanel(m_parent);
    m_abp = new AboutPanel(m_parent);

    m_ip->Hide();
    m_ep->Hide();
    m_wp->Hide();
    m_ap->Hide();
    m_cp->Hide();
    m_app->Hide();
    m_up->Hide();
    m_abp->Hide();
    menubar = new wxMenuBar;

    start = new wxMenu;
    start->Append(wxID_HOME, wxT("Back To Home Page"));
    start->Append(wxID_INFO, wxT("Back To Infomation Page"));
    start->AppendSeparator();

    edit = new wxMenu;
    edit->Append(wxID_EDIT, wxT("Start Editing"));

    statistics = new wxMenu;
    statistics->Append(wxID_STATIC, wxT("Wage Data"));
    statistics->Append(wxID_FORWARD, wxT("Wage Analysis"));
    statistics->Append(wxID_BACKWARD, wxT("Wage Calculation Rules"));

    help = new wxMenu;
    help->Append(wxID_HELP, wxT("User Guide"));
    help->Append(wxID_ABOUT, wxT("About"));

    quit = new wxMenuItem(start, wxID_EXIT, wxT("&Quit\tCtrl+Q"));
    start->Append(quit);

    menubar->Append(start, wxT("Start"));
    menubar->Append(edit, wxT("Edit"));
    menubar->Append(statistics, wxT("Statistics"));
    menubar->Append(help, wxT("Help"));

    SetMenuBar(NULL);

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnQuit));
    Connect(wxID_HOME, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::BackStart));
    Connect(wxID_EDIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnEdit));
    Connect(wxID_INFO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::BackInfo));
    Connect(wxID_STATIC, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnWage));
    Connect(wxID_FORWARD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnAnalyze));
    Connect(wxID_BACKWARD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnWageCal));
    Connect(wxID_HELP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnUserGuide));
    Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnAbout));
    Center();
}


void MyFrame::OnQuit(wxCommandEvent &event)
{

    Close(true);

}

void MyFrame::BackStart(wxCommandEvent &event)
{
    MyFrame *comm = (MyFrame *)m_parent->GetParent();
    comm->m_ip->Hide();
    comm->m_sp->Show();
    comm->m_ep->Hide();
    comm->m_wp->Hide();
    comm->m_ap->Hide();
    comm->m_cp->Hide();
    comm->m_app->Hide();
    SetMenuBar(NULL);
    comm->m_up->Hide();
    comm->m_abp->Hide();
}

void MyFrame::OnEdit(wxCommandEvent &event)
{
    MyFrame *comm = (MyFrame *)m_parent->GetParent();
    comm->m_ip->Hide();
    comm->m_sp->Hide();
    comm->m_ep->Show();
    comm->m_wp->Hide();
    comm->m_ap->Hide();
    comm->m_cp->Hide();
    comm->m_app->Hide();
    comm->m_up->Hide();
    comm->m_abp->Hide();
}

void MyFrame::BackInfo(wxCommandEvent &event)
{
    MyFrame *comm = (MyFrame *)m_parent->GetParent();
    comm->m_sp->Hide();
    comm->m_ip->Show();
    comm->m_ep->Hide();
    comm->m_wp->Hide();
    comm->m_ap->Hide();
    comm->m_cp->Hide();
    comm->m_app->Hide();
    comm->m_up->Hide();
    comm->m_abp->Hide();
}

void MyFrame::OnWage(wxCommandEvent &event)
{
    MyFrame *comm = (MyFrame *)m_parent->GetParent();
    comm->m_sp->Hide();
    comm->m_ip->Hide();
    comm->m_ep->Hide();
    comm->m_wp->Show();
    comm->m_ap->Hide();
    comm->m_cp->Hide();
    comm->m_app->Hide();
    comm->m_up->Hide();
    comm->m_abp->Hide();
}

void MyFrame::OnAnalyze(wxCommandEvent &event)
{
    MyFrame *comm = (MyFrame *)m_parent->GetParent();
    comm->m_sp->Hide();
    comm->m_ip->Hide();
    comm->m_ep->Hide();
    comm->m_wp->Hide();
    comm->m_ap->Show();
    comm->m_cp->Hide();
    comm->m_app->Hide();
    comm->m_up->Hide();
    comm->m_abp->Hide();
}

void MyFrame::OnWageCal(wxCommandEvent &event)
{
    MyFrame *comm = (MyFrame *)m_parent->GetParent();
    comm->m_sp->Hide();
    comm->m_ip->Hide();
    comm->m_ep->Hide();
    comm->m_wp->Hide();
    comm->m_ap->Hide();
    comm->m_cp->Show();
    comm->m_app->Hide();
    comm->m_up->Hide();
    comm->m_abp->Hide();
}

void MyFrame::OnUserGuide(wxCommandEvent &event)
{
    MyFrame *comm = (MyFrame *)m_parent->GetParent();
    comm->m_sp->Hide();
    comm->m_ip->Hide();
    comm->m_ep->Hide();
    comm->m_wp->Hide();
    comm->m_ap->Hide();
    comm->m_cp->Hide();
    comm->m_app->Hide();
    comm->m_up->Show();
    comm->m_abp->Hide();
}

void MyFrame::OnAbout(wxCommandEvent &event)
{
    MyFrame *comm = (MyFrame *)m_parent->GetParent();
    comm->m_sp->Hide();
    comm->m_ip->Hide();
    comm->m_ep->Hide();
    comm->m_wp->Hide();
    comm->m_ap->Hide();
    comm->m_cp->Hide();
    comm->m_app->Hide();
    comm->m_up->Hide();
    comm->m_abp->Show();
}

wxMenuBar* MyFrame::getmenubar()
{
    return menubar;
}

