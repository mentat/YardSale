#include "ys_checkout.h"
#include "extra/xrc/xmlres.h"
#include "wx/wx.h"
#include "wx/app.h"

#include "yardsale.h"
#include "ys_exception.h"
#include "ys_inv_type.h"
#include "ys_database.h"
#include "ys_calc.h"

#include "receipt.h"

BEGIN_EVENT_TABLE(YardCheckout, wxDialog)
    EVT_BUTTON(XRCID("ID_CO_BACK"), YardCheckout::OnBack)
    EVT_BUTTON(XRCID("ID_CO_PRINT"), YardCheckout::OnPrint)
    EVT_BUTTON(XRCID("ID_CO_FINISH"), YardCheckout::OnFinish)
END_EVENT_TABLE()

DECLARE_APP(YardSale)

YardCheckout::YardCheckout(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style, const wxString& name)
:wxDialog(parent, id, title, pos, size, style, name), m_ref(0) {
    
    wxXmlResource::Get()->Load("res/checkout_wdr.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "CashOut");
    
    m_calc = new YardCalc(panel, -1);
    wxXmlResource::Get()->AttachUnknownControl(wxT("ID_CO_NUM_PAD"),
                                                m_calc);
    
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());   
    Centre();
    
}

YardCheckout::~YardCheckout()
{
}

void YardCheckout::SetCost(double subTotal, double tax, double total)
{
    m_subTotal = subTotal;
    m_tax = tax;
    m_total = total;   
    
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
    
    Receipt rec("/dev/ttyS0");
    
    for (unsigned int i = 0; i < m_ref->size(); i++)
    {
        wxLogDebug(wxT("ToPrinter: %s"), (*m_ref)[i].GetName().c_str());
        rec.additem((*m_ref)[i].GetName(), (*m_ref)[i].GetRetailPriceS());
    }
    
    rec.totdata(XMLNode::ToStr(m_subTotal, 2), XMLNode::ToStr(m_tax,2), XMLNode::ToStr(m_total, 2));
    rec.print();
    
}

void YardCheckout::OnFinish(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnFinish"));
    EndModal(0);
    
}
