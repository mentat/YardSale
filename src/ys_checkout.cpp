#include "ys_checkout.h"
#include "extra/xrc/xmlres.h"
#include "wx/wx.h"
#include "wx/app.h"

#include "yardsale.h"
#include "ys_exception.h"
#include "ys_inv_type.h"
#include "ys_database.h"
#include "ys_calc.h"
#include "ys_config.h"

#include "receipt.h"

Receipt YardCheckout::m_rec;

BEGIN_EVENT_TABLE(YardCheckout, wxDialog)
    EVT_BUTTON(XRCID("ID_CO_BACK"), YardCheckout::OnBack)
    EVT_BUTTON(XRCID("ID_CO_PRINT"), YardCheckout::OnPrint)
    EVT_BUTTON(XRCID("ID_CO_FINISH"), YardCheckout::OnFinish)
    EVT_BUTTON(XRCID("ID_CO_CASH"), YardCheckout::OnCash)
END_EVENT_TABLE()

DECLARE_APP(YardSale)

YardCheckout::YardCheckout(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style, const wxString& name)
:wxDialog(parent, id, title, pos, size, style, name), m_mode(None), m_ref(0)
{
    m_rec.Init(YardConfig::GetPrinterPort().c_str());
    wxLogDebug(wxT("Setting printer to: %s"), YardConfig::GetPrinterPort().c_str());
    wxXmlResource::Get()->Load("res/checkout_wdr.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "CashOut");
    
    m_calc = new YardCalc(panel, -1);
    wxXmlResource::Get()->AttachUnknownControl(wxT("ID_CO_NUM_PAD"),
                                                m_calc);
    
     m_cashButt = static_cast<wxButton *>(FindWindow(XRCID("ID_CO_CASH")));
     m_checkButt = static_cast<wxButton *>(FindWindow(XRCID("ID_CO_CHECK")));
     m_tabButt = static_cast<wxButton *>(FindWindow(XRCID("ID_CO_TAB")));
     m_visaButt = static_cast<wxButton *>(FindWindow(XRCID("ID_CO_VISA")));
     m_mcButt = static_cast<wxButton *>(FindWindow(XRCID("ID_CO_MC")));
     m_accButt = static_cast<wxButton *>(FindWindow(XRCID("ID_CO_ACCOUNT")));
     m_backButt = static_cast<wxButton *>(FindWindow(XRCID("ID_CO_BACK")));
    
     m_calc->Disable();
     wxSizer * sizer = panel->GetSizer();
     sizer->SetSizeHints(this);
     SetSize(wxSize(600,400));
     Centre();  
     
     m_rec.Clear();

}

YardCheckout::~YardCheckout()
{
}

void YardCheckout::SetCost(double subTotal, double tax, double total)
{
    m_subTotal = subTotal;
    m_tax = tax;
    m_total = total;
    
    m_calc->SetCalcContents(total);
    
}

void YardCheckout::OnBack(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnBack"));
    EndModal(1);
}

void YardCheckout::OnPrint(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnPrint"));
    
    if (!m_ref)
    {
        wxLogDebug(wxT("No reference."));
        return;
    }
    
    for (unsigned int i = 0; i < m_ref->size(); i++)
    {
        wxLogDebug(wxT("ToPrinter: %s"), (*m_ref)[i].GetName().c_str());
        m_rec.additem((*m_ref)[i].GetName(), (*m_ref)[i].GetRetailPriceS());
    }
    
    m_rec.totdata(XMLNode::ToStr(m_subTotal, 2), XMLNode::ToStr(m_tax,2), XMLNode::ToStr(m_total, 2));
    
    if (m_mode == CashDone)
    {
        m_rec.change("Cash", XMLNode::ToStr(m_tender, 2), 
            XMLNode::ToStr(m_tender - m_total, 2));
    }
    
    m_rec.print();
    
}

void YardCheckout::OnCash(wxCommandEvent& event)
{
    if (m_mode == None)
    {
        m_calc->Enable();
        m_mode = Cash;
    
        m_cashButt->SetLabel(wxT("Done"));
        
        m_checkButt->Disable();
        m_tabButt->Disable();
        m_visaButt->Disable();
        m_mcButt->Disable();
        m_accButt->Disable();
        
        m_backButt->Disable();
        
    }
    else
    {
        m_tender = m_calc->GetCalcContents();
        m_calc->SetCalcContents(m_tender - m_total);       
        m_calc->Disable();
        m_mode = CashDone;

        //open drawer
    }
    
}

void YardCheckout::OnFinish(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnFinish"));
    EndModal(0);
    
}
