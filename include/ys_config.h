#ifndef YS_CONFIG_H
#define YS_CONFIG_H

#include "wx/frame.h"

class YardConfig: public wxFrame {
 public:

    YardConfig(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxRESIZE_BORDER|wxTAB_TRAVERSAL);
 
    virtual ~YardConfig();
 
    void OnCancel(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnBrowse(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnChange(wxCommandEvent& event);
    void OnDeleteConfig(wxCommandEvent& event);
 
    enum { ODBC = 0, ODBC_MYSQL };
 
 private:
     // Has the dialog been saved since last change?
     bool m_saved;
 
     // True if still in constructor
     bool m_construct;
 
     DECLARE_EVENT_TABLE()
};


#endif
