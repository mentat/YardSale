#include <vector>

#include "extra/xrc/xmlres.h"
#include "wx/app.h"
#include "wx/listctrl.h"
#include "wx/treectrl.h"
#include "wx/sizer.h"
#include "wx/log.h"
#include "wx/stattext.h"
#include "wx/notebook.h"
#include "wx/button.h"

#include "yardsale.h"
#include "ys_exception.h"
#include "ys_group.h"
#include "ys_inv_type.h"
#include "ys_sale.h"
#include "ys_database.h"
#include "ys_checkout.h"

#define SALE_BUTTON_HEIGHT  40
#define START_BUTTON_ID      14333
using namespace std;

BEGIN_EVENT_TABLE(YardSaleScreen, wxDialog)
    EVT_BUTTON(XRCID("ID_SALES_EXIT"), YardSaleScreen::OnExitButton)
    EVT_BUTTON(XRCID("ID_SALES_REMOVE"), YardSaleScreen::OnRemove)
    EVT_BUTTON(XRCID("ID_SALES_CHECKOUT"), YardSaleScreen::OnCheckout)
    EVT_BUTTON(-1, YardSaleScreen::OnItem)
    //EVT_TREE_ITEM_ACTIVATED(XRCID("ID_SALE_TREE"), YardSaleScreen::OnChange)
END_EVENT_TABLE()

DECLARE_APP(YardSale)

// -1 is group
class invItemData: public wxTreeItemData
{
 public:
    invItemData(long id): 
        wxTreeItemData(), m_id(id) {}
	~invItemData() {}
	
	const long GetID() { return m_id; }

 private:
	long m_id;	
};

YardSaleScreen::YardSaleScreen(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style, const wxString& name)
:wxDialog(parent, id, title, pos, size, style, name) {
    
    wxBusyCursor busy();
    wxXmlResource::Get()->Load("res/new_sales_wdr.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "Checkout");
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());   
    Centre();
    if (wxGetApp().Full())
        ShowFullScreen(true);
    
    m_list = static_cast<wxListCtrl *>(FindWindow(XRCID("ID_SALES_TRANS")));
    m_book = static_cast<wxNotebook *>(FindWindow(XRCID("ID_SALES_GROUPS")));
   
    m_subTotal = static_cast<wxStaticText *>(FindWindow(XRCID("ID_SALES_SUB")));
    m_tax = static_cast<wxStaticText *>(FindWindow(XRCID("ID_SALES_TAX")));
    m_total = static_cast<wxStaticText *>(FindWindow(XRCID("ID_SALES_TOTAL")));
    
    wxListItem itemCol;
    itemCol.m_mask = wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE;
    itemCol.m_text = _T("Item");
    itemCol.m_image = -1;
    m_list->InsertColumn(0, itemCol);
    itemCol.m_text = _T("#");
    m_list->InsertColumn(1, itemCol);
    itemCol.m_text = _T("Price");
    m_list->InsertColumn(2, itemCol);   
    
    m_list->SetColumnWidth( 0, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 1, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 2, wxLIST_AUTOSIZE );
    
    BuildNotebook(m_book);
    ///@todo Could make this static and only do it once per program run...?
    vector<YardTaxType> tax;
    try {
        tax = wxGetApp().DB().TaxTypeGetAll();
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (tax load): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    wxLogDebug(wxT("Loading %d tax types..."), tax.size());
    for (unsigned int i = 0; i < tax.size(); i++)
    {
        m_taxCache[tax[i].GetId()] = tax[i].GetPercent();
    }
    
}

void YardSaleScreen::OnItem(wxCommandEvent& event)
{
    
    long id = event.GetId();
    if (id < START_BUTTON_ID)
    {
        wxLogDebug(wxT("Bad event ID"));
        return;
    }
    
    YardInvType temp;
    try {
        temp = wxGetApp().DB().InventoryGet(m_lookup[id]);
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (item not loaded): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
      
    m_items.push_back(temp);
 
    m_list->InsertItem(0, temp.GetName().c_str(), 0);
    m_list->SetItemData(0, temp.GetKey());
    m_list->SetItem(0, 1, "1");
    m_list->SetItem(0, 2, temp.GetRetailPriceS().c_str());
   
    m_list->SetColumnWidth( 0, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 1, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 2, wxLIST_AUTOSIZE );
     
    // calc total
    m_sub = 0;
    m_totalPrice = 0;
    m_taxTotal = 0;
    for (int i = 0; i < m_items.size(); i++)
    {
        m_sub += m_items[i].GetRetailPrice();
        long taxid = m_items[i].GetTaxType();
        m_taxTotal += m_taxCache[taxid] * m_items[i].GetRetailPrice();
    }
    m_totalPrice = m_sub + m_taxTotal;
    
    m_subTotal->SetLabel(XMLNode::ToStr(m_sub, 2).c_str());
    m_tax->SetLabel(XMLNode::ToStr(m_taxTotal, 2).c_str()); 
    m_total->SetLabel(XMLNode::ToStr(m_sub + m_taxTotal, 2).c_str()); 
    
}

void YardSaleScreen::BuildNotebook(wxNotebook * nb)
{
    vector<YardGroup> groups;
    
    try {
        groups = wxGetApp().DB().GroupGetAll();
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (grp load): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    
    long id = START_BUTTON_ID;
    
    for (unsigned int i = 0; i < groups.size(); i++)
    {
        wxPanel * panel = new wxPanel(nb);
        wxFlexGridSizer *sizer = new wxFlexGridSizer( 3, 0, 0 );
                
        vector<YardInvType> items;
        try {
            items = wxGetApp().DB().InventoryGetInGroup(groups[i].GetId());
        }
        catch (YardDBException& e)            
        {
            wxLogDebug(wxT("Error (item load): %s, %s"),e.what(), e.GetSQL().c_str());
            return;
        }
        for (int k = 0; k < items.size(); k++)
        {
            wxLogDebug(wxT("Adding item %s, %d"), items[k].GetType().c_str(), items[k].GetKey());

            m_lookup[id] = items[k].GetKey();
            wxButton * button = new wxButton(panel, id++ , items[k].GetName().c_str());
            wxSize size = button->GetSize();
            
            size.SetHeight(SALE_BUTTON_HEIGHT);
            button->SetSize(size);
            button->SetBackgroundColour(*wxBLUE);
            sizer->Add(button,  0, wxALIGN_CENTER|wxALL, 5);
            
        }
        panel->SetAutoLayout( TRUE );
        panel->SetSizer(sizer);
        nb->AddPage(panel, groups[i].GetName().c_str());
    }
    
    
}

void YardSaleScreen::OnRemove(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnRemove"));
    
}

void YardSaleScreen::OnCheckout(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnCheckout"));
    YardCheckout * co = new YardCheckout(this, -1, wxT("Checkout"));
    co->SetInvRef(&m_items);
    co->SetCost(m_sub, m_taxTotal, m_totalPrice);
    if (co->ShowModal() == 0)
    {
        co->Destroy();
        Close();
    }
    co->Destroy();
}

YardSaleScreen::~YardSaleScreen()
{
    
}

void YardSaleScreen::OnExitButton(wxCommandEvent & event)
{
    wxLogDebug(wxT("YardSaleScreen::OnExitButton"));
    EndModal(0);
}
