#ifndef YS_CALC_DLG_H
#define YS_CALC_DLG_H


#include "wx/dialog.h"

class YardCalc;
    
/**
 * This is the on-screen calculator dialog for YardSale
 * @author Jesse Lovelace
 * @version \$Revision: 1.6 $$
 */ 
class YardCalcDlg: public wxDialog {
 public:
    /**
     * Constructs a Login window
     */
    YardCalcDlg(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_DIALOG_STYLE);
    
    double GetCalcContents();
    private:
            YardCalc * m_panel;
        
};

#endif
