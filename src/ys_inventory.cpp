#include "wx/app.h"
#include "wx/wx.h"
#include "wx/treectrl.h"
#include "wx/spinctrl.h"

#include <sstream>
#include <vector>

#include "yardsale.h"
#include "ys_log.h"
#include "ys_util.h"
#include "ys_database.h"
#include "ys_exception.h"
#include "ys_inventory.h"
#include "ys_inv_type.h"

#include "extra/xrc/xmlres.h"

using namespace std;

BEGIN_EVENT_TABLE(YardInventory, wxDialog)
    EVT_TREE_SEL_CHANGED(XRCID("ID_INV_TREE"), YardInventory::OnChange)
    EVT_BUTTON(XRCID("ID_INV_NEW"), YardInventory::OnNew)
    EVT_BUTTON(XRCID("ID_INV_SEARCH"), YardInventory::OnSearch)
    EVT_BUTTON(XRCID("ID_INV_LEAVE"), YardInventory::OnExitButton)
    EVT_LIST_ITEM_SELECTED(XRCID("ID_INV_LIST"), YardInventory::OnSelect)
END_EVENT_TABLE()

DECLARE_APP(YardSale)

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

YardInventory::YardInventory(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style, const wxString& name)
:wxDialog(parent, id, title, pos, size, style, name) {
     
    wxXmlResource::Get()->Load("res/new_inv.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "ItemDisplay");
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());

    Centre();
   
    // set the window components 
    
    SetPointers();
    LoadTreeItems(m_tree);
    
}

YardInventory::~YardInventory()
{
    
}

void YardInventory::PopulateList()
{
    #if 0
    m_list->DeleteAllItems();
    
    wxLogDebug(wxT("Populating list"));
    for (int i = 0; i < m_objects.size(); i++)
    {       
        m_list->InsertItem(0, m_objects[i].GetSKU().c_str());
        m_list->SetItem(0,1, m_objects[i].GetBarCode().c_str());
        m_list->SetItem(0,2, m_objects[i].GetDescription().c_str());
        m_list->SetItem(0,3, m_objects[i].GetDepartment().c_str());
        m_list->SetItem(0,4, m_objects[i].GetQuantOnHandS().c_str());
        m_list->SetItem(0,5, m_objects[i].GetRetailPriceS().c_str());
        m_list->SetItem(0,6, m_objects[i].GetWholesalePriceS().c_str());
    }
    
    m_list->SetColumnWidth( 0, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 1, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 2, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 3, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 4, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 5, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 6, wxLIST_AUTOSIZE );
    #endif
}

void YardInventory::SetPointers()
{

    m_tree = static_cast<wxTreeCtrl *>(FindWindow(XRCID("ID_INV_TREE")));
    
    // details
    m_det_sku = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_INV_SKU")));
    m_det_name = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_INV_ITEMNAME")));
    m_det_desc = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_INV_DESC")));
    m_det_barcode = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_INV_BARCODE")));
    m_det_dept = static_cast<wxComboBox *>(FindWindow(XRCID("ID_INV_DEPARTMENT")));
    m_dep_dept_edit = static_cast<wxBitmapButton *>(FindWindow(XRCID("ID_INV_EDIT_DEPTS")));
    m_dep_group = static_cast<wxComboBox *>(FindWindow(XRCID("ID_INV_GROUP")));
    m_dep_group_edit = static_cast<wxBitmapButton *>(FindWindow(XRCID("ID_INV_EDIT_GROUPS")));
    m_dep_image = static_cast<wxStaticBitmap *>(FindWindow(XRCID("ID_INV_IMAGE")));
    m_dep_vendor = static_cast<wxComboBox *>(FindWindow(XRCID("ID_INV_VENDOR")));
    m_dep_vendor_edit = static_cast<wxBitmapButton *>(FindWindow(XRCID("ID_INV_EDIT_VENDOR")));
    
    // pricing
    m_price_retail = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_INV_PRICE")));
    m_price_wholesale = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_INV_WHOLESALE")));
    m_price_bulk = static_cast<wxListCtrl *>(FindWindow(XRCID("ID_INV_BULK_TALBE")));
    m_price_bulk_add = static_cast<wxButton *>(FindWindow(XRCID("ID_INV_ADD_BULK")));
    m_price_bulk_rm = static_cast<wxButton *>(FindWindow(XRCID("ID_INV_REMOVE_BULK")));
    m_price_tax = static_cast<wxComboBox *>(FindWindow(XRCID("ID_INV_TAX")));
    m_price_tax_edit = static_cast<wxBitmapButton *>(FindWindow(XRCID("ID_INV_TAX_EDIT")));
    
    m_ship_weight = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_INV_ITEM_WEIGHT")));
    m_ship_date_rec = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_INV_DATE_RECEIVED")));
    m_ship_oversized = static_cast<wxCheckBox *>(FindWindow(XRCID("ID_INV_OVERSIZED")));
    m_ship_freight = static_cast<wxCheckBox *>(FindWindow(XRCID("ID_INV_FREIGHT_ONLY")));
    
    m_stock_onhand = static_cast<wxSpinCtrl *>(FindWindow(XRCID("ID_INV_ON_HAND")));
    m_stock_onorder = static_cast<wxSpinCtrl *>(FindWindow(XRCID("ID_INV_ON_ORDER")));
    m_stock_reorder_lvl = static_cast<wxSpinCtrl *>(FindWindow(XRCID("ID_INV_REORDER_LEVEL")));
    m_stock_reorder_quant = static_cast<wxSpinCtrl *>(FindWindow(XRCID("ID_REORDER_QUANT")));

}

void YardInventory::OnExitButton(wxCommandEvent & event)
{
    wxLogDebug("OnExit");
    EndModal(0);

}

void YardInventory::OnNew(wxCommandEvent & event) {
    wxLogDebug(wxT("OnNew"));
    #if 0
    YardInvType temp;
    temp.SetSKU(m_sku->GetValue().c_str());
    temp.SetBarCode(m_barcode->GetValue().c_str());
    temp.SetDescription(m_desc->GetValue().c_str()); 
    temp.SetDepartment(m_department->GetValue().c_str());
    temp.SetQuantOnHand(m_onHand->GetValue());
    temp.SetQuantOnOrder(m_onOrder->GetValue());
    temp.SetReorderLevel(m_reOrder->GetValue());
   
    temp.SetType(m_type->GetValue().c_str());
    double doubleTemp;
    wxString doubleTxt = m_weight->GetValue();
    
    if (!doubleTxt.ToDouble(&doubleTemp))
        doubleTemp = 0.0;
    
    temp.SetWeightLbs(doubleTemp);
    
    doubleTxt = m_price->GetValue();
    if (!doubleTxt.ToDouble(&doubleTemp))
        doubleTemp = 0.0;
    
    temp.SetRetailPrice(doubleTemp);
    temp.SetWholesalePrice(doubleTemp);
    
    try {
        wxGetApp().DB().InventoryAdd(temp);
    }
    catch (YardDBException &e)
    {
        wxLogDebug(wxT("Error (insert): %s\n%s"),e.what(), e.GetSQL().c_str());
        wxLogError(wxT("Error (insert): %s\n%s"),e.what(), e.GetSQL().c_str());
    }
    #endif
}

void YardInventory::LoadFromDB() {
    #if 0
     // Getting initial list of items
    if (wxGetApp().DB().IsConnected())
    {
        wxLogDebug(wxT("Connected"));
        
        try {
            m_objects = wxGetApp().DB().InventoryGetAll();
        }
        catch (YardDBException &e)
        {
            wxLogDB(e.GetWhat().c_str());
            wxLogDB(e.GetVarInfo().c_str());
            wxLogSQL(e.GetSQL().c_str());
            return;
        }
        // showing list to screen
       
    }
    else
        wxLogError(wxT("Not Connected"));
    #endif
}


void YardInventory::OnSearch(wxCommandEvent & event){

}

void YardInventory::OnSelect(wxListEvent & event){
#if 0
    long index = event.GetIndex();
    
    if (index >= m_objects.size() || (index < 0))
    {
        wxLogDebug(wxT("Invalid index"));
        return;
    }

    m_sku->SetValue(m_objects[index].GetSKU().c_str());
    m_barCode->SetValue(m_objects[index].GetBarCode().c_str());
    m_name->SetValue(m_objects[index].GetType().c_str());
    m_department->SetValue(m_objects[index].GetDepartment().c_str());
    m_type->SetValue(m_objects[index].GetType().c_str());
    
    m_price->SetValue(m_objects[index].GetRetailPriceS().c_str());
    m_wholesale->SetValue(m_objects[index].GetWholesalePriceS().c_str());
    m_weight->SetValue(m_objects[index].GetWeightLbsS().c_str());
    m_desc->SetValue(m_objects[index].GetDescription().c_str());
    #endif
}

void YardInventory::LoadTreeItems(wxTreeCtrl * tree)
{
    tree->AddRoot(wxT("Root"));
    tree->SetIndent(10);
	tree->SetSpacing(5);
    // load groups first
    
    vector<YardGroup> groups;
    
    try {
        groups = wxGetApp().DB().GroupGetAll();
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (grp load): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    
    for (unsigned int i = 0; i < groups.size(); i++)
    {
        wxTreeItemId groupid = tree->AppendItem(tree->GetRootItem(),
            groups[i].GetName().c_str(), -1,-1, new invItemData(-1));
        
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
            int img = -1; //items[k].GetGroupId() %  4;
            tree->AppendItem(groupid, items[k].GetName().c_str(), img, img,
                new invItemData(items[k].GetKey()));
        }
    }
    
    // load in vendors, taxes, departments
    vector<YardVendType> vends; 
    try {
        vends = wxGetApp().DB().VendorGetAll();
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (vend load): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    
    vector<YardCarrierType> carrier;
    try {
        carrier = wxGetApp().DB().CarrierGetAll();
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (carr load): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    
    vector<YardTaxType> tax;
    try {
        tax = wxGetApp().DB().TaxTypeGetAll();
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (tax load): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    
    //wxComboBox * m_dep_group;
    m_dep_group->Clear();
    for (unsigned int i = 0; i < groups.size(); i++)
    {
        m_dep_group->Append(groups[i].GetName().c_str(), (void*)groups[i].GetId());
    }
   // wxComboBox * m_price_tax;
    m_price_tax->Clear();
    for (unsigned int i = 0; i < tax.size(); i++)
    {
        m_price_tax->Append(tax[i].GetName().c_str(), (void*)tax[i].GetId());
    }
    //wxComboBox * m_det_dept->;
    
    //wxComboBox * m_dep_vendor;
    m_dep_vendor->Clear();
    for (unsigned int i = 0; i < vends.size(); i++)
    {
        m_dep_vendor->Append(vends[i].GetName().c_str(), (void*)vends[i].GetId());
    }

}

void YardInventory::OnChange(wxTreeEvent& event)
{
    invItemData * data = static_cast<invItemData *>(m_tree->GetItemData(event.GetItem()));

    if (!data)
        return;
    
    if (data->GetID() == -1)
    {
        return;
    }
    
    YardInvType temp;
    try {
        temp = wxGetApp().DB().InventoryGet(data->GetID());
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (item not loaded): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    
    //
    ShowItem(temp);
   
}

void YardInventory::ShowItem(const YardInvType& item)
{
    
    m_det_sku->SetValue(item.GetSKU().c_str());
    m_det_name->SetValue(item.GetName().c_str());
    m_det_desc->SetValue(item.GetDescription().c_str());
    m_det_barcode->SetValue(item.GetBarCode().c_str());
   
    //wxStaticBitmap * m_dep_image;
    
    // pricing
    m_price_retail->SetValue(item.GetRetailPriceS().c_str());
    m_price_wholesale->SetValue(item.GetWholesalePriceS().c_str());
    //wxListCtrl * m_price_bulk;
    
    m_ship_weight->SetValue(item.GetWeightLbsS().c_str());
    m_ship_date_rec->SetValue(item.GetDateLastReceived().ToString().c_str());
    m_ship_oversized->SetValue((item.IsOverSized()) ? true : false);
    m_ship_freight->SetValue((item.MustShipFreight()) ? true : false);
    
    m_stock_onhand->SetValue(item.GetQuantOnHand());
    m_stock_onorder->SetValue(item.GetQuantOnOrder());
    m_stock_reorder_lvl->SetValue(item.GetReorderLevel());
    m_stock_reorder_quant->SetValue(item.GetReorderQuantity());
    
}

YardInvType YardInventory::SaveItem()  
{
    
}
