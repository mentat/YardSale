#ifndef YS_CONFIG_H
#define YS_CONFIG_H

#include "wx/frame.h"

/**
 * This class manages configuration settings which are 
 * platform independant and therefore use dot files in Linux
 * and registry in Win32.
 *
 * @author Jesse Lovelace
 */
class YardConfig: public wxDialog {
 public:

    YardConfig(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_DIALOG_STYLE);
 
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
