#ifndef YARD_CHECKOUT_H
#define YARD_CHECKOUT_H

#include <vector>
#include "wx/dialog.h"
#include "ys_inv_type.h"
#include "receipt.h"
using namespace std;
class YardCalc;
class wxButton;

/**
 * The checkout screen.
 * \image html checkout.png
 * @author Jesse Lovelace
*/
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
    void OnCash(wxCommandEvent& event);
    
    enum PayMode { None, Cash, Visa, MC, Check, Tab, Account, CashDone };
 
 private:
     wxButton * m_cashButt;
     wxButton * m_checkButt;
     wxButton * m_tabButt;
     wxButton * m_visaButt;
     wxButton * m_mcButt;
     wxButton * m_accButt; 
     wxButton * m_backButt; 
     static Receipt m_rec;
     PayMode m_mode;
     YardCalc * m_calc;
     vector<YardInvType> * m_ref;
     double m_subTotal, m_tax, m_total, m_tender;
    
    DECLARE_EVENT_TABLE()
 
};

#endif
