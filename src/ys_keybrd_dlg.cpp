#include "wx/wx.h"
#include "wx/sizer.h"
#include "extra/xrc/xmlres.h"

#include "ys_keybrd.h"
#include "ys_keybrd_dlg.h"

YardKeybrdDlg::YardKeybrdDlg(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos, 
               const wxSize& size,
               long style)
:wxDialog(parent, id, title, pos, size, style)
{
    m_panel = new YardKeybrd(this);
    wxSizer * sizer = m_panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
 
    Centre();

}

wxString YardKeybrdDlg::GetKeyboardContents(){
       return m_panel->GetKeyboardContents();
}
