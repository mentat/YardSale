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
 
 private:
     DECLARE_EVENT_TABLE()
};


#endif
