#include "wx/app.h"

#include <sstream>
#include <vector>

#include "yardsale.h"
#include "ys_log.h"
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
                   const wxPoint& pos, const wxSize& size, long style)
:wxFrame(parent, id, title, pos, size, style) {
     
    wxPanel * panel = new wxPanel(this);
    
    wxSizer * sizer = Inventory(panel, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    Centre();
    
    m_list = (wxListCtrl *)FindWindow(ID_INV_LIST);
    
    m_list->InsertColumn(0, wxT("SKU"));
    m_list->InsertColumn(1, wxT("BarCode"));
    m_list->InsertColumn(2, wxT("Description"));
    m_list->InsertColumn(3, wxT("Department"));
    m_list->InsertColumn(4, wxT("On Hand"));
    
    if (wxGetApp().DB().IsConnected())
    {
        wxLogDebug(wxT("Connected"));
       // vector<YardInvType> temp;
        
        try {
            m_objects = wxGetApp().DB().InvSearchSKU(10000);
        }
        catch (YardDBException &e)
        {
            wxLogDB(e.GetWhat().c_str());
            return;
        }
        
        for (int i = 0; i < m_objects.size(); i++)
        {
            wxLogDebug(wxT("In loop"));
            stringstream numconv;
            numconv << m_objects[i].GetSKU();
            m_list->InsertItem(0, numconv.str().c_str());
            numconv.clear();
            m_list->SetItem(0,1,m_objects[i].GetBarCode().c_str());
            m_list->SetItem(0,2,m_objects[i].GetDescription().c_str());
            m_list->SetItem(0,3,m_objects[i].GetDepartment().c_str());
        }
    }
    else
        wxLogDebug(wxT("Not Connected"));
    
    m_list->SetColumnWidth( 0, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 1, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 2, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 3, wxLIST_AUTOSIZE );
    m_list->SetColumnWidth( 4, wxLIST_AUTOSIZE );
    
}

YardInventory::~YardInventory()
{
    
}

void YardInventory::OnExitButton(wxCommandEvent & event)
{

}

void YardInventory::OnNew(wxCommandEvent & event) {
    
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
    
    wxTextCtrl * sku = (wxTextCtrl *)FindWindow(ID_INV_SKU);
    wxTextCtrl * barcode = (wxTextCtrl *)FindWindow(ID_INV_BARCODE);
    wxTextCtrl * name = (wxTextCtrl *)FindWindow(ID_INV_ITEMNAME);
    wxTextCtrl * price = (wxTextCtrl *)FindWindow(ID_INV_PRICE);
    wxTextCtrl * desc = (wxTextCtrl *)FindWindow(ID_INV_DESC);
    wxTextCtrl * wholesale = (wxTextCtrl *)FindWindow(ID_INV_WHOLESALE);
    
    stringstream numstr;
    numstr << m_objects[index].GetSKU();
    
    sku->SetValue(numstr.str().c_str());
    barcode->SetValue(m_objects[index].GetBarCode().c_str());
    name->SetValue(m_objects[index].GetItemType().c_str());
    
    stringstream pricestr;
    pricestr.precision(2);
    
    pricestr << showpoint << m_objects[index].GetRetailPrice();
    price->SetValue(pricestr.str().c_str());
    
    desc->SetValue(m_objects[index].GetDescription().c_str());
    
    stringstream wspricestr;
    wspricestr.precision(2);
    
    wspricestr << showpoint << m_objects[index].GetWholesalePrice();
    wholesale->SetValue(wspricestr.str().c_str());
}
