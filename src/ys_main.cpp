#include "wx/app.h"

#include "yardsale_wdr.h"


#include "ys_debug.h"
#include "ys_bitmaps.h"
#include "yardsale.h"
#include "ys_main.h"
#include "ys_inventory.h"
#include "ys_sale.h"
#include "ys_employee.h"
#include "ys_config.h"
#include "ys_log.h"


BEGIN_EVENT_TABLE(YardMain, wxFrame)
    EVT_BUTTON(ID_MAIN_LOGOUT, YardMain::OnLogout)
    EVT_BUTTON(ID_MAIN_INVENTORY, YardMain::OnInventory)
    EVT_BUTTON(ID_MAIN_SALES, YardMain::OnSale)
    EVT_BUTTON(ID_MAIN_EMPLOYEE, YardMain::OnEmployee)
    EVT_MENU(ID_MAIN_MENU_CONFIG, YardMain::OnOptions)
END_EVENT_TABLE()

DECLARE_APP(YardSale)

YardMain::YardMain(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style)
:wxFrame(parent, id, title, pos, size, style), m_max(false) {
    
    m_inventory = 0;
    SetMenuBar(MainBar());
    wxPanel * panel = new wxPanel(this);
    
    //panel->SetBackgroundColour(wxColor("BLUE VIOLET"));
    /// @todo Make these compiled into the binary.
    /*wxBitmap logo("images/ys_320x93.png", wxBITMAP_TYPE_PNG);
    
    wxBitmap inventory("images/ys_inventory_128x128.png", wxBITMAP_TYPE_PNG); 
    wxBitmap customer("images/ys_customer_128x128.png", wxBITMAP_TYPE_PNG);
    wxBitmap employee("images/ys_employee_128x128.png", wxBITMAP_TYPE_PNG);
    wxBitmap sales("images/ys_sale_128x128.png", wxBITMAP_TYPE_PNG);
    wxBitmap reports("images/ys_reports_128x128.png", wxBITMAP_TYPE_PNG);
    wxBitmap logout("images/ys_logout_128x128.png", wxBITMAP_TYPE_PNG);
    
    m_enlarge = new wxBitmap("images/ys_enlarge_64x64.png");
    m_shrink = new wxBitmap("images/ys_shrink_64x64.png");*/

    new wxStaticBitmap(panel, ID_MAIN_LOGO,
        wxGetApp().Images().GetBitmap(YardBitmaps::MAIN_LOGO), wxDefaultPosition);
     
    new wxBitmapButton(panel, ID_MAIN_INVENTORY, 
        wxGetApp().Images().GetBitmap(YardBitmaps::MAIN_INV), wxDefaultPosition);
    new wxBitmapButton(panel, ID_MAIN_CUSTOMER, 
        wxGetApp().Images().GetBitmap(YardBitmaps::MAIN_CUST), wxDefaultPosition);
    new wxBitmapButton(panel, ID_MAIN_EMPLOYEE, 
        wxGetApp().Images().GetBitmap(YardBitmaps::MAIN_EMPLOY), wxDefaultPosition);
    new wxBitmapButton(panel, ID_MAIN_SALES, 
        wxGetApp().Images().GetBitmap(YardBitmaps::MAIN_SALE), wxDefaultPosition);
    new wxBitmapButton(panel, ID_MAIN_REPORTS, 
        wxGetApp().Images().GetBitmap(YardBitmaps::MAIN_REPORT), wxDefaultPosition);
    new wxBitmapButton(panel, ID_MAIN_LOGOUT, 
        wxGetApp().Images().GetBitmap(YardBitmaps::MAIN_LOGOUT), wxDefaultPosition);

    
    wxSizer * sizer = Main(panel, false, true);
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
    wxFrame * inventory = new YardInventory(this, -1, wxT("Inventory"));
    inventory->Show();
}

void YardMain::OnSale(wxCommandEvent & event) {
    
    wxLogDebug(wxT("OnSale"));
    wxFrame * sales = new YardSaleScreen(this, -1, wxT("Sales"));
    sales->Show();
}

void YardMain::OnEmployee(wxCommandEvent & event) {
    
    wxLogDebug(wxT("OnEmployee"));
    wxFrame * employ = new YardEmployee(this, -1, wxT("Employee"));
    employ->Show();
}
