
#include "yardsale_wdr.h"
#include "ys_employee.h"
#include "yardsale.h"

YardEmployee::YardEmployee(wxWindow* parent, wxWindowID id, 
    const wxString& title, const wxPoint& pos,
    const wxSize& size, long style)
:wxFrame(parent, id, title, pos, size, style) {
    
    wxPanel * panel = new wxPanel(this);
    
    wxBitmap * picture = GetBitmap(ID_EMPLOY_PICTURE); 
    (void *)new wxStaticBitmap(panel, ID_EMPLOY_PICTURE, *picture);
    delete picture;
    
    wxSizer * sizer = Employee(panel, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    Centre();
    
}
    
YardEmployee::~YardEmployee()
{
   

}
