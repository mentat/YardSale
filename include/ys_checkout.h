#ifndef YARD_CHECKOUT_H
#define YARD_CHECKOUT_H

#include <vector>
#include "wx/dialog.h"
#include "ys_inv_type.h"
using namespace std;
class YardCalc;

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

    void SetCost(double subTotal, double tax, double total);
    void SetInvRef(vector<YardInvType> * ref) { m_ref = ref; }
 
    void OnBack(wxCommandEvent& event);
    void OnPrint(wxCommandEvent& event);
    void OnFinish(wxCommandEvent& event);
 
 private:
     YardCalc * m_calc;
     vector<YardInvType> * m_ref;
     double m_subTotal, m_tax, m_total;
    
    DECLARE_EVENT_TABLE()
 
};

#endif
