#include "wx/sizer.h"

#include "ys_calc.h"
#include "ys_calc_dlg.h"

YardCalcDlg::YardCalcDlg(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos, 
               const wxSize& size,
               long style)
:wxDialog(parent, id, title, pos, size, style)
{
    m_panel = new YardCalc(this);
    wxSizer * sizer = m_panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
 
    Centre();
}

double YardCalcDlg::GetCalcContents(){
        return m_panel->GetCalcContents();
}
