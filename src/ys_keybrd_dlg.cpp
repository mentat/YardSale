#include "wx/sizer.h"

#include "ys_keybrd.h"
#include "ys_keybrd_dlg.h"

YardKeybrdDlg::YardKeybrdDlg(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos, 
               const wxSize& size,
               long style)
:wxDialog(parent, id, title, pos, size, style)
{
    wxPanel * panel = new YardKeybrd(this);
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
 
    Centre();
}
