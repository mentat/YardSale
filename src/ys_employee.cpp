#include "yardsale_wdr.h"
#include "ys_employee.h"
#include "yardsale.h"

YardEmployee::YardEmployee(wxWindow* parent, wxWindowID id, 
    const wxString& title, const wxPoint& pos,
    const wxSize& size, long style)
:wxFrame(parent, id, title, pos, size, style) {
    
    m_picture = 0;
    
    wxPanel * panel = new wxPanel(this);
    
    wxBitmap * picture = GetBitmap(ID_EMPLOY_PICTURE); 
    m_picture = new wxStaticBitmap(panel, ID_EMPLOY_PICTURE, *picture);
    
    wxSizer * sizer = Employee(panel, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    Centre();
    
}
    
YardEmployee::~YardEmployee()
{
    delete m_picture;

}
