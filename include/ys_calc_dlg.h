\#ifndef YS_CALC_DLG_H
#define YS_CALC_DLG_H


#include "wx/dialog.h"
/**
 * This is the on-screen calculator dialog for YardSale
 * @author Jesse Lovelace
 * @version \$Revision: 1.3 $$
 */ 
class YardCalcDlg: public wxDialog {
 public:
    /**
     * Constructs a Login window
     */
    YardCalcDlg(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxSTAY_ON_TOP | wxRESIZE_BORDER);
    
    
    private:
        
};

#endif
