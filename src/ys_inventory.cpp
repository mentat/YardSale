#include "wx/app.h"

#include <sstream>
#include <vector>

#include "yardsale.h"
#include "ys_log.h"
#include "ys_util.h"
#include "ys_database.h"
#include "ys_exception.h"
#include "ys_inventory.h"
#include "ys_inv_type.h"
#include "yardsale_wdr.h"

using namespace std;

BEGIN_EVENT_TABLE(YardInventory, wxFrame)
    EVT_BUTTON(ID_INV_NEW, YardInventory::OnNew)
    EVT_BUTTON(ID_INV_SEARCH, YardInventory::OnSearch)
    EVT_LIST_ITEM_SELECTED(ID_INV_LIST, YardInventory::OnSelect)
END_EVENT_TABLE()

DECLARE_APP(YardSale)

YardInventory::YardInventory(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style, const wxString& name)
:wxFrame(parent, id, title, pos, size, style, name) {
     
    wxPanel * panel = new wxPanel(this);
    
    wxSizer * sizer = Inventory(panel, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    // center the screen
    Centre();
    
    // set the window components 
    SetPointers();
    
    m_list->InsertColumn(0, wxT("SKU"));
    m_list->InsertColumn(1, wxT("BarCode"));
    m_list->InsertColumn(2, wxT("Description"));
    m_list->InsertColumn(3, wxT("Department"));
    m_list->InsertColumn(4, wxT("On Hand"));
    m_list->InsertColumn(5, wxT("Retail"));
    m_list->InsertColumn(6, wxT("Wholesale"));
    
    LoadFromDB();
    PopulateList();
    
}

YardInventory::~YardInventory()
{
    
}

void YardInventory::PopulateList()
{
    m_list->DeleteAllItems();
    
    wxLogDebug(wxT("Populating list"));
    for (int i = 0; i < m_objects.size(); i++)
    {       
        m_list->InsertItem(0, m_objects[i].GetSKU().c_str());
        m_list->SetItem(0,1, m_objects[i].GetBarCode().c_str());
        m_list->SetItem(0,2, m_objects[i].GetDescription().c_str());
        m_list->SetItem(0,3, m_objects[i].GetDepartment().c_str());
        m_list->SetItem(0,4, strIToA(m_objects[i].GetQuantOnHand()).c_str());
        m_list->SetItem(0,5, toMoney(m_objects[i].GetRetailPrice()).c_str());
        m_list->SetItem(0,6, toMoney(m_objects[i].GetWholesalePrice()).c_str());
    }
    
    m_list->SetColumnWidth( 0, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 1, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 2, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 3, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 4, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 5, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 6, wxLIST_AUTOSIZE );
}

void YardInventory::SetPointers()
{
    m_list = static_cast<wxListCtrl *>(FindWindow(ID_INV_LIST));
    m_barcode = static_cast<wxTextCtrl *>(FindWindow(ID_INV_BARCODE));
    m_sku = static_cast<wxTextCtrl *>(FindWindow(ID_INV_SKU));
    m_name = static_cast<wxTextCtrl *>(FindWindow(ID_INV_ITEMNAME));
    m_department = static_cast<wxTextCtrl *>(FindWindow(ID_INV_DEPARTMENT));
    m_type = static_cast<wxTextCtrl *>(FindWindow(ID_INV_TYPE));
    m_price = static_cast<wxTextCtrl *>(FindWindow(ID_INV_PRICE));
    m_wholesale = static_cast<wxTextCtrl *>(FindWindow(ID_INV_WHOLESALE));
    m_weight = static_cast<wxTextCtrl *>(FindWindow(ID_INV_WEIGHT));
    m_vendor = static_cast<wxTextCtrl *>(FindWindow(ID_INV_VENDOR));
    m_barCode = static_cast<wxTextCtrl *>(FindWindow(ID_INV_BARCODE));
    m_desc = static_cast<wxTextCtrl *>(FindWindow(ID_INV_DESC));
 
    m_freight = static_cast<wxCheckBox *>(FindWindow(ID_INV_FREIGHT));
    m_oversized = static_cast<wxCheckBox *>(FindWindow(ID_INV_OVERSIZE));
 
    m_onHand = static_cast<wxSpinCtrl *>(FindWindow(ID_INV_ONHAND));
    m_onOrder = static_cast<wxSpinCtrl *>(FindWindow(ID_INV_ONORDER));
    m_reOrder = static_cast<wxSpinCtrl *>(FindWindow(ID_INV_REORDER_LEVEL));
    
    m_tax = static_cast<wxChoice *>(FindWindow(ID_INV_TAX_TYPE));

}

void YardInventory::OnExitButton(wxCommandEvent & event)
{

}

void YardInventory::OnNew(wxCommandEvent & event) {
    wxLogDebug(wxT("OnNew"));
    
    YardInvType temp;
    temp.SetSKU(m_sku->GetValue().c_str());
    temp.SetBarCode(m_barcode->GetValue().c_str());
    temp.SetDescription(m_desc->GetValue().c_str()); 
    temp.SetDepartment(m_department->GetValue().c_str());
    temp.SetQuantOnHand(m_onHand->GetValue());
    temp.SetQuantOnOrder(m_onOrder->GetValue());
    temp.SetReorderLevel(m_reOrder->GetValue());
   
    temp.SetItemType(m_type->GetValue().c_str());
    double doubleTemp;
    wxString doubleTxt = m_weight->GetValue();
    if (!doubleTxt.ToDouble(&doubleTemp))
        doubleTemp = -1.0;
    
    temp.SetItemWeightLbs((float)doubleTemp);
    temp.SetTaxType(1);
    temp.SetVendorId(1);
    
    doubleTxt = m_price->GetValue();
    if (!doubleTxt.ToDouble(&doubleTemp))
        doubleTemp = -1.0;
    
    temp.SetRetailPrice((float)doubleTemp);
    temp.SetWholesalePrice((float)doubleTemp);
    
    try {
        wxGetApp().DB().AddInventoryItem(temp);
    }
    catch (YardDBException &e)
    {
        wxLogError(e.what());
    }
    
}

void YardInventory::LoadFromDB() {
    
     // Getting initial list of items
    if (wxGetApp().DB().IsConnected())
    {
        wxLogDebug(wxT("Connected"));
        
        try {
            m_objects = wxGetApp().DB().InvGet();
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
    
}


void YardInventory::OnSearch(wxCommandEvent & event){

}

void YardInventory::OnSelect(wxListEvent & event){

    long index = event.GetIndex();
    
    if (index >= m_objects.size() || (index < 0))
    {
        wxLogDebug(wxT("Invalid index"));
        return;
    }
    
    m_sku->SetValue(m_objects[index].GetSKU().c_str());
    m_barCode->SetValue(m_objects[index].GetBarCode().c_str());
    m_name->SetValue(m_objects[index].GetItemType().c_str());
    m_department->SetValue(m_objects[index].GetDepartment().c_str());
    m_type->SetValue(m_objects[index].GetItemType().c_str());
    
    m_price->SetValue(toMoney(m_objects[index].GetRetailPrice()).c_str());
    m_wholesale->SetValue(toMoney(m_objects[index].GetWholesalePrice()).c_str());
    m_weight->SetValue(strFToA(m_objects[index].GetItemWeightLbs()).c_str());
    m_desc->SetValue(m_objects[index].GetDescription().c_str());
    
}
