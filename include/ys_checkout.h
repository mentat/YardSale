#ifndef YARD_CHECKOUT_H
#define YARD_CHECKOUT_H

#include "wx/dialog.h"

class YardCheckout: public wxDialog{
 public:
    
    /// This is the constructor you will most commonly use.
    YardCheckout(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString& name = wxT("YardCheckout"));
    /// Destructor
    virtual ~YardCheckout();
 
    void OnBack(wxCommandEvent& event);
    void OnPrint(wxCommandEvent& event);
    void OnFinish(wxCommandEvent& event);
 
 private:
    DECLARE_EVENT_TABLE()
 
};

#endif
