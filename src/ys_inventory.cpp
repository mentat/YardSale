#include "ys_inventory.h"
#include "yardsale_wdr.h"

BEGIN_EVENT_TABLE(YardInventory, wxFrame)
    EVT_BUTTON(ID_INVENTORY_EXIT, YardInventory::OnExitButton)
END_EVENT_TABLE()

YardInventory::YardInventory(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style)
:wxFrame(parent, id, title, pos, size, style) {
    
    wxPanel * panel = new wxPanel(this);
    
    wxSizer * sizer = Inventory(panel, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    Centre();
   
}

YardInventory::~YardInventory()
{
    
}

void YardInventory::OnExitButton(wxCommandEvent & event)
{
    Close(true);
    
}
