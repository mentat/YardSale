#include "extra/xrc/xmlres.h"
#include "wx/sizer.h"
#include "wx/accel.h"
#include "wx/msgdlg.h"

#include "ys_debug.h"
#include "ys_bitmaps.h"
#include "ys_footer.h"
#include "ys_main.h"
#include "ys_inventory.h"
#include "ys_sale.h"
#include "ys_employee.h"
#include "ys_customer.h"
#include "ys_config.h"
#include "ys_reports.h"
#include "ys_log.h"

enum { ID_SHOW_LOG = 15000, ID_FULLSCREEN, ID_ABOUT, ID_CONFIG };

BEGIN_EVENT_TABLE(YardMain, wxFrame)
    EVT_BUTTON(XRCID("ID_MAIN_LOGOUT"), YardMain::OnLogout)
    EVT_BUTTON(XRCID("ID_MAIN_INVENTORY"), YardMain::OnInventory)
    EVT_BUTTON(XRCID("ID_MAIN_SALES"), YardMain::OnSale)
    EVT_BUTTON(XRCID("ID_MAIN_EMPLOYEE"), YardMain::OnEmployee)
    EVT_BUTTON(XRCID("ID_MAIN_CONFIG"), YardMain::OnOptions)
    EVT_BUTTON(XRCID("ID_MAIN_CUSTOMER"), YardMain::OnCustomer)
    EVT_BUTTON(XRCID("ID_MAIN_REPORTS"), YardMain::OnReports)

    EVT_MENU(ID_SHOW_LOG, YardMain::OnShowLog)
    EVT_MENU(ID_FULLSCREEN, YardMain::OnFullscreen)
    EVT_MENU(ID_ABOUT, YardMain::OnAbout)
    EVT_MENU(ID_CONFIG, YardMain::OnOptions)
END_EVENT_TABLE()

YardMain::YardMain(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style, const wxString& name)
:wxFrame(parent, id, title, pos, size, style, name) {
    
    wxXmlResource::Get()->Load("res/main.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "Main");
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());

    Centre();
    
    //ShowFullScreen(true,  wxFULLSCREEN_ALL);
    
    wxAcceleratorEntry entries[4];
    entries[0].Set(wxACCEL_CTRL,  (int) 'L',     ID_SHOW_LOG);
    entries[1].Set(wxACCEL_CTRL,  (int) 'F',     ID_FULLSCREEN);
    entries[2].Set(wxACCEL_CTRL, (int) 'A',     ID_ABOUT);
    entries[3].Set(wxACCEL_CTRL,  (int) 'C',    ID_CONFIG);
    wxAcceleratorTable accel(4, entries);
    SetAcceleratorTable(accel);
    
    m_log = new YardDebugScreen(this, -1, 
        wxT("Debug"), wxPoint(0,50));
#ifdef __WXDEBUG___
    m_log->Show();
#endif
    
    wxLogDebug(wxT("Main loaded..."));
}

YardMain::~YardMain()
{
}

void YardMain::OnShowLog(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnShowLog"));
    if (m_log->IsShown())
        m_log->Show(false);
    else
        m_log->Show(true);
}
    
void YardMain::OnFullscreen(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnShowFullscreen"));
    if (IsFullScreen())
        ShowFullScreen(false);
    else
        ShowFullScreen(true);
}
    
void YardMain::OnAbout(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnAbout"));
    wxMessageBox("YardSale: The Open Point of Sale\n\n"
                "Copyright (c) 2004 - Jesse Lovelace", "About YardSale",
                            wxOK, this);    
}

void YardMain::OnOptions(wxCommandEvent& event){
    
    YardConfig * conf = new YardConfig(this, -1, wxT("YardSale Configuration"));
    conf->ShowModal();
    conf->Destroy();
}

void YardMain::OnLogout(wxCommandEvent& event){
    
    wxLogDebug(wxT("OnLogout"));
    Destroy();
}

void YardMain::OnMax(wxCommandEvent& event){    

    wxLogDebug(wxT("OnMax"));
}

void YardMain::OnInventory(wxCommandEvent& event){
    
    wxLogDebug(wxT("OnInventory"));
    YardInventory * inventory = new YardInventory(this, -1, wxT("Inventory Management"));
    inventory->ShowModal();
    inventory->Destroy();
}

void YardMain::OnSale(wxCommandEvent & event) {
    
    wxLogDebug(wxT("OnSale"));
    YardSaleScreen * sales = new YardSaleScreen(this, -1, wxT("Sales"));
    sales->ShowModal();
    sales->Destroy();
}

void YardMain::OnEmployee(wxCommandEvent & event) {
    
    wxLogDebug(wxT("OnEmployee"));
    YardEmployee * employ = new YardEmployee(this, -1, wxT("Employee Management"));
    employ->ShowModal();
    employ->Destroy();
}

void YardMain::OnCustomer(wxCommandEvent & event) {
    
    wxLogDebug(wxT("OnCustomer"));
    YardCustomer * cust = new YardCustomer(this, -1, wxT("Customer Management"));
    cust->ShowModal();
    cust->Destroy();
}

void YardMain::OnReports(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnReports"));
    YardReports * rep = new YardReports(this, -1, wxT("Reporting"));
    rep->ShowModal();
    rep->Destroy();  
}
