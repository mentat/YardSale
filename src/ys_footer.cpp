#include "wx/panel.h"
#include "wx/bmpbuttn.h"
#include "wx/app.h"
#include "wx/datetime.h"
#include "wx/timer.h"

#include "ys_footer.h"
#include "ys_bitmaps.h"
#include "yardsale.h"
#include "yardsale_wdr.h"

enum { FOOTER_TIMER_ID = 9999 };

DECLARE_APP(YardSale)

BEGIN_EVENT_TABLE(YardFooter, wxPanel)
    EVT_TIMER(FOOTER_TIMER_ID, YardFooter::OnTimer)
END_EVENT_TABLE()

YardFooter::YardFooter(wxWindow* parent, wxWindowID id, 
     const wxPoint& pos, 
     const wxSize& size, 
     long style, 
     const wxString& name)
:wxPanel(parent, id, pos, size, style, name)
{
    
    new wxBitmapButton(this, ID_FOOTER_CALC, 
        wxGetApp().Images().GetBitmap(YardBitmaps::FOOT_CALC));
    new wxBitmapButton(this, ID_FOOTER_KEY, 
        wxGetApp().Images().GetBitmap(YardBitmaps::FOOT_KEY));
    new wxBitmapButton(this, ID_FOOTER_UNDO, 
        wxGetApp().Images().GetBitmap(YardBitmaps::FOOT_UNDO));
    wxSizer * sizer = InfoFooter(this, false, true);
    
    sizer->SetSizeHints(this);
    //sizer->GetMinSize());
    
    m_timer = new wxTimer(this, FOOTER_TIMER_ID);
    m_timeTxt = (wxStaticText *)FindWindow(ID_FOOTER_TIME);
    
    m_timer->Start(1000);
    
}

YardFooter::~YardFooter()
{
    delete m_timer;
}
 
void YardFooter::OnTimer(wxTimerEvent& event)
{
    wxDateTime now = wxDateTime::Now();
    
    m_timeTxt->SetLabel(now.FormatISOTime());
    
}


void YardFooter::OnCalc(wxCommandEvent& event)
{
    
    
}

void YardFooter::OnKeyboard(wxCommandEvent & event)
{
    
}
