#include "wx/sizer.h"

#include "ys_calc.h"
#include "ys_calc_dlg.h"

YardCalcDlg::YardCalcDlg(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos, 
               const wxSize& size,
               long style)
:wxDialog(parent, id, title, pos, size, style)
{
    wxPanel * panel = new YardCalc(this);
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
 
    Centre();
}
