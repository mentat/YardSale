#include "wx/app.h"

#include "ys_bitmaps.h"
#include "yardsale_wdr.h"
#include "ys_employee.h"
#include "yardsale.h"

DECLARE_APP(YardSale)

YardEmployee::YardEmployee(wxWindow* parent, wxWindowID id, 
    const wxString& title, const wxPoint& pos,
    const wxSize& size, long style)
:wxFrame(parent, id, title, pos, size, style) {
    
    wxPanel * panel = new wxPanel(this);
     
    (void *)new wxStaticBitmap(panel, ID_EMPLOY_PICTURE, 
        wxGetApp().Images().GetBitmap(YardBitmaps::MAIN_EMPLOY));
    
    wxSizer * sizer = Employee(panel, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    Centre();
    
}
    
YardEmployee::~YardEmployee()
{
   

}
