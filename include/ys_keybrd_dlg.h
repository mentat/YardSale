#ifndef YS_KEYBRD_DHG_H
#define YS_KEYBRD_DHG_H

#include "wx/dialog.h"

class YardKeybrd;
    
/**
 * This is the on-screen keyboard dialog for YardSale
 * @author Jay Johnston
 * @version \$Revision: 1.4 $$
 */ 
class YardKeybrdDlg: public wxDialog {
 public:
    /**
     * Constructs a Login window
     */
    YardKeybrdDlg(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_DIALOG_STYLE);
    
    wxString GetKeyboardContents();
 
    private:
        YardKeybrd * m_panel;
};

#endif
