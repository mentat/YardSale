#include "wx/panel.h"
#include "wx/bmpbuttn.h"
#include "wx/app.h"
#include "wx/datetime.h"
#include "wx/timer.h"

#include "ys_footer.h"
#include "ys_bitmaps.h"
#include "yardsale.h"
#include "yardsale_wdr.h"
#include "ys_calc_dlg.h"
#include "ys_keybrd_dlg.h"

enum { FOOTER_TIMER_ID = 9999 };

DECLARE_APP(YardSale)

BEGIN_EVENT_TABLE(YardFooter, wxPanel)
    EVT_TIMER(FOOTER_TIMER_ID, YardFooter::OnTimer)
    EVT_BUTTON(ID_FOOTER_BACK, YardFooter::OnBack)
    EVT_BUTTON(ID_FOOTER_CALC, YardFooter::OnCalc)
    EVT_BUTTON(ID_FOOTER_KEY, YardFooter::OnKeyboard)
    EVT_BUTTON(ID_FOOTER_UNDO, YardFooter::OnUndo)
END_EVENT_TABLE()

YardFooter::YardFooter(wxWindow* parent, wxWindowID id, 
     const wxPoint& pos, 
     const wxSize& size, 
     long style, 
     const wxString& name)
:wxPanel(parent, id, pos, size, style, name)
{
    // get bitmaps from loader
    new wxBitmapButton(this, ID_FOOTER_BACK,
        wxGetApp().Images().GetBitmap(YardBitmaps::SALE_BACK));
    new wxBitmapButton(this, ID_FOOTER_CALC, 
        wxGetApp().Images().GetBitmap(YardBitmaps::FOOT_CALC));
    new wxBitmapButton(this, ID_FOOTER_KEY, 
        wxGetApp().Images().GetBitmap(YardBitmaps::FOOT_KEY));
    new wxBitmapButton(this, ID_FOOTER_UNDO, 
        wxGetApp().Images().GetBitmap(YardBitmaps::FOOT_UNDO));
    wxSizer * sizer = InfoFooter(this, false, true);
    
    sizer->SetSizeHints(this);
    //sizer->GetMinSize());
    
    // see if parent is main frame if so, hide back button
    wxWindow * parentWin = GetParent()->GetParent();
    
    wxASSERT(parentWin);
    if (parentWin->GetName() == wxT("YardMain"))
    {
        wxLogDebug(wxT("Name checks"));
        wxButton * back = static_cast<wxButton *>(FindWindow(ID_FOOTER_BACK));
        wxASSERT(back);
        back->Show(false);
    }
    
    m_timer = new wxTimer(this, FOOTER_TIMER_ID);
    m_timeTxt = (wxStaticText *)FindWindow(ID_FOOTER_TIME);
    
    m_timer->Start(1000);
    
}

YardFooter::~YardFooter()
{
    m_timer->Stop();
    delete m_timer;
}
 
void YardFooter::OnTimer(wxTimerEvent& event)
{
    wxDateTime now = wxDateTime::Now();
    
    m_timeTxt->SetLabel(now.FormatISOTime());
    
}

void YardFooter::OnBack(wxCommandEvent& event)
{
    
    wxLogDebug(wxT("OnBack"));
    
    // get the parent of the parent
    wxWindow * parentWin = GetParent()->GetParent();
    
    wxASSERT(parentWin);
    
    // close it
    parentWin->Close();
}


void YardFooter::OnCalc(wxCommandEvent& event)
{
    
    wxLogDebug(wxT("OnCalc"));
    
    YardCalcDlg * dlg = new YardCalcDlg(this, -1, wxT("Calculator"));
    dlg->ShowModal();
    dlg->Destroy();
    
}

void YardFooter::OnKeyboard(wxCommandEvent & event)
{
    wxLogDebug(wxT("OnKeyboard"));
    YardKeybrdDlg * dlg = new YardKeybrdDlg(this, -1, wxT("Keyboard"));
    /*dlg->ShowModal();
    dlg->Destroy();*/
    
}

void YardFooter::OnUndo(wxCommandEvent & event)
{
    wxLogDebug(wxT("OnUndo"));
    
}
