#include "extra/xrc/xmlres.h"

#include "wx/log.h"
#include "wx/panel.h"
#include "wx/bmpbuttn.h"
#include "wx/datetime.h"
#include "wx/timer.h"
#include "wx/stattext.h"

#include "ys_footer.h"
#include "ys_bitmaps.h"
#include "ys_calc_dlg.h"
#include "ys_keybrd_dlg.h"

enum { FOOTER_TIMER_ID = 9999 };

BEGIN_EVENT_TABLE(YardFooter, wxPanel)
    EVT_TIMER(FOOTER_TIMER_ID, YardFooter::OnTimer)
    EVT_BUTTON(XRCID("ID_FOOTER_BACK"), YardFooter::OnBack)
    EVT_BUTTON(XRCID("ID_FOOTER_CALC"), YardFooter::OnCalc)
    EVT_BUTTON(XRCID("ID_FOOTER_KEY"), YardFooter::OnKeyboard)
    EVT_BUTTON(XRCID("ID_FOOTER_UNDO"), YardFooter::OnUndo)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(YardFooter, wxPanel)

YardFooter::YardFooter():wxPanel(),m_timer(0)
{
}

bool YardFooter::Create(wxWindow* parent, wxWindowID id, 
     const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    if ( !wxPanel::Create(parent, id, pos, size, style, name) )
        return false;
    
    wxLogDebug(wxT("YardFooter::Create"));
    wxXmlResource::Get()->Load("res/info-footer.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "Footer");

    // see if parent is main frame if so, hide back button

    wxWindow * parentWin = GetParent()->GetParent();
    
    wxASSERT(parentWin);
    if (parentWin->GetName() == wxT("YardMain"))
    {
        wxLogDebug(wxT("Name checks"));
        wxButton * back = static_cast<wxButton *>(FindWindow(XRCID("ID_FOOTER_BACK")));
        wxASSERT(back);
        back->Show(false);
    }
    
    m_timer = new wxTimer(this, FOOTER_TIMER_ID);
    m_timeTxt = (wxStaticText *)FindWindow(XRCID("ID_FOOTER_TIME"));
    
    wxDateTime now = wxDateTime::Now();
    
    m_timeTxt->SetLabel(now.FormatISOTime());  
    return true;
}

YardFooter::YardFooter(wxWindow* parent, wxWindowID id, 
     const wxPoint& pos, 
     const wxSize& size, 
     long style, 
     const wxString& name)
{
    Create(parent, id, pos, size, style, name);
}

YardFooter::~YardFooter()
{
    if (m_timer)
        m_timer->Stop();
    delete m_timer;
}
 
void YardFooter::OnTimer(wxTimerEvent& event)
{
    //wxDateTime now = wxDateTime::Now();
    
    //m_timeTxt->SetLabel(now.FormatISOTime());
    
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
    dlg->ShowModal();
    dlg->Destroy();
    
}

void YardFooter::OnUndo(wxCommandEvent & event)
{
    wxLogDebug(wxT("OnUndo"));
    
}
