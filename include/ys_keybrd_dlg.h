#ifndef YS_KEYBRD_DHG_H
#define YS_KEYBRD_DHG_H


#include "wx/dialog.h"
/**
 * This is the on-screen keyboard dialog for YardSale
 * @author Jesse Lovelace
 * @version \$Revision: 1.1 $$
 */ 
class YardKeybrdDlg: public wxDialog {
 public:
    /**
     * Constructs a Login window
     */
    YardKeybrdDlg(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxSTAY_ON_TOP | wxRESIZE_BORDER);
    
    
    private:
        
};

#endif
