#ifndef YS_FOOTER_H
#define YS_FOOTER_H

#include "wx/panel.h"
#include "wx/timer.h"
class wxStaticText;

class YardFooter: public wxPanel {
 public:
    YardFooter(wxWindow* parent, wxWindowID id = -1, 
     const wxPoint& pos = wxDefaultPosition, 
     const wxSize& size = wxDefaultSize, 
     long style = wxTAB_TRAVERSAL, 
     const wxString& name = "YSFooterPanel");
 
    virtual ~YardFooter();
 
    void OnTimer(wxTimerEvent& event);
 
    void OnCalc(wxCommandEvent& event);
    void OnKeyboard(wxCommandEvent & event);
 
 private:
     
    wxTimer * m_timer;
    wxStaticText *m_timeTxt;
     
    DECLARE_EVENT_TABLE()
 
};
 
#endif
