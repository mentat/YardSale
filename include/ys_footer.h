#ifndef YS_FOOTER_H
#define YS_FOOTER_H

#include "wx/panel.h"
#include "wx/timer.h"
class wxStaticText;

/**
 * The footer is a easy-access panel to launch the on-screen calc
 * and keyboard.  The footer also shows current time and has
 * the ability to undo operations.
 *
 * @author Jesse Lovelace
 * @version \$ Revision: $$
 */
class YardFooter: public wxPanel {
 public:
    YardFooter(wxWindow* parent, wxWindowID id = -1, 
     const wxPoint& pos = wxDefaultPosition, 
     const wxSize& size = wxDefaultSize, 
     long style = wxTAB_TRAVERSAL, 
     const wxString& name = "YardFooter");
 
    virtual ~YardFooter();
 
    void OnTimer(wxTimerEvent& event);
 
    void OnCalc(wxCommandEvent& event);
    void OnKeyboard(wxCommandEvent & event);
    void OnBack(wxCommandEvent& event);
    void OnUndo(wxCommandEvent& event);
 
 private:
     
    wxTimer * m_timer;
    wxStaticText *m_timeTxt;
     
    DECLARE_EVENT_TABLE()
 
};
 
#endif
