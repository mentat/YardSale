#include "extra/xrc/xmlres.h"
#include "wx/sizer.h"

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


BEGIN_EVENT_TABLE(YardMain, wxFrame)
    EVT_BUTTON(XRCID("ID_MAIN_LOGOUT"), YardMain::OnLogout)
    EVT_BUTTON(XRCID("ID_MAIN_INVENTORY"), YardMain::OnInventory)
    EVT_BUTTON(XRCID("ID_MAIN_SALES"), YardMain::OnSale)
    EVT_BUTTON(XRCID("ID_MAIN_EMPLOYEE"), YardMain::OnEmployee)
    EVT_BUTTON(XRCID("ID_MAIN_CONFIG"), YardMain::OnOptions)
    EVT_BUTTON(XRCID("ID_MAIN_CUSTOMER"), YardMain::OnCustomer)
    EVT_BUTTON(XRCID("ID_MAIN_REPORTS"), YardMain::OnReports)
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
    
    YardDebugScreen * debug = new YardDebugScreen(this, -1, 
        wxT("Debug"), wxPoint(0,50));
    debug->Show();
    
    wxLogDebug(wxT("Main loaded..."));
}

YardMain::~YardMain()
{
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
