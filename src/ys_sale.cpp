#include "yardsale_wdr.h"
#include "ys_sale.h"

BEGIN_EVENT_TABLE(YardSaleScreen, wxFrame)
    EVT_BUTTON(ID_SALE_BACK, YardSaleScreen::OnExitButton)
END_EVENT_TABLE()

YardSaleScreen::YardSaleScreen(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style)
:wxFrame(parent, id, title, pos, size, style) {
    
    wxPanel * panel = new wxPanel(this);
    
    wxSizer * sizer = Sale(panel, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    Centre();
   
}

YardSaleScreen::~YardSaleScreen()
{
    
}

void YardSaleScreen::OnExitButton(wxCommandEvent & event)
{
    Close(true);
    
}
