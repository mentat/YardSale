#include "ys_checkout.h"
#include "extra/xrc/xmlres.h"
#include "wx/wx.h"
#include "wx/app.h"

#include "yardsale.h"
#include "ys_exception.h"
#include "ys_inv_type.h"
#include "ys_database.h"
#include "ys_calc.h"

BEGIN_EVENT_TABLE(YardCheckout, wxDialog)
    EVT_BUTTON(XRCID("ID_CO_BACK"), YardCheckout::OnBack)
    EVT_BUTTON(XRCID("ID_CO_PRINT"), YardCheckout::OnPrint)
    EVT_BUTTON(XRCID("ID_CO_FINISH"), YardCheckout::OnFinish)
END_EVENT_TABLE()

DECLARE_APP(YardSale)

YardCheckout::YardCheckout(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style, const wxString& name)
:wxDialog(parent, id, title, pos, size, style, name) {
    
    wxXmlResource::Get()->Load("res/checkout_wdr.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "CashOut");
    
    YardCalc * calc = new YardCalc(panel, -1);
    wxXmlResource::Get()->AttachUnknownControl(wxT("ID_CO_NUM_PAD"),
                                                calc);
    
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());   
    Centre();
    
}

YardCheckout::~YardCheckout()
{
}

void YardCheckout::OnBack(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnBack"));
    EndModal(1);
}

void YardCheckout::OnPrint(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnPrint"));
    
}

void YardCheckout::OnFinish(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnFinish"));
    EndModal(0);
    
}
