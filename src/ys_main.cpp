#include "yardsale_wdr.h"

#include "ys_main.h"
#include "ys_inventory.h"


BEGIN_EVENT_TABLE(YardMain, wxFrame)
    EVT_BUTTON(ID_MAIN_LOGOUT, YardMain::OnLogout)
    EVT_BUTTON(ID_MAIN_INVENTORY, YardMain::OnInventory)
END_EVENT_TABLE()


YardMain::YardMain(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style)
:wxFrame(parent, id, title, pos, size, style), m_max(false) {
    
    m_inventory = 0;
    
    wxPanel * panel = new wxPanel(this);
    wxImage::AddHandler(new wxPNGHandler);
    
    //panel->SetBackgroundColour(wxColor("BLUE VIOLET"));
    /// @todo Make these compiled into the binary.
    wxBitmap logo("images/ys_320x93.png", wxBITMAP_TYPE_PNG);
    
    wxBitmap inventory("images/ys_inventory_128x128.png", wxBITMAP_TYPE_PNG); 
    wxBitmap customer("images/ys_customer_128x128.png", wxBITMAP_TYPE_PNG);
    wxBitmap employee("images/ys_employee_128x128.png", wxBITMAP_TYPE_PNG);
    wxBitmap sales("images/ys_sale_128x128.png", wxBITMAP_TYPE_PNG);
    wxBitmap reports("images/ys_reports_128x128.png", wxBITMAP_TYPE_PNG);
    wxBitmap logout("images/ys_logout_128x128.png", wxBITMAP_TYPE_PNG);
    
    m_enlarge = new wxBitmap("images/ys_enlarge_64x64.png");
    m_shrink = new wxBitmap("images/ys_shrink_64x64.png");

    new wxStaticBitmap(panel, ID_MAIN_LOGO, logo, wxDefaultPosition);
     
    new wxBitmapButton(panel, ID_MAIN_INVENTORY, inventory, wxDefaultPosition);
    new wxBitmapButton(panel, ID_MAIN_CUSTOMER, customer, wxDefaultPosition);
    new wxBitmapButton(panel, ID_MAIN_EMPLOYEE, employee, wxDefaultPosition);
    new wxBitmapButton(panel, ID_MAIN_SALES, sales, wxDefaultPosition);
    new wxBitmapButton(panel, ID_MAIN_REPORTS, reports, wxDefaultPosition);
    new wxBitmapButton(panel, ID_MAIN_LOGOUT, logout, wxDefaultPosition);

    
    wxSizer * sizer = Main(panel, false, true);
    //sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    Centre();
 
}

YardMain::~YardMain()
{
    delete m_enlarge;
    delete m_shrink;
}

void YardMain::OnLogout(wxCommandEvent& event){
    
    Destroy();
}

void YardMain::OnMax(wxCommandEvent& event){    

}

void YardMain::OnInventory(wxCommandEvent& event){
    
    wxFrame * inventory = new YardInventory(this, -1, wxT("Inventory"));
    inventory->Show();
}
