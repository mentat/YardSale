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

DECLARE_APP(YardSale)

YardInventory::YardInventory(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style)
:wxFrame(parent, id, title, pos, size, style) {
     
    wxPanel * panel = new wxPanel(this);
    
    wxSizer * sizer = Inventory(panel, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    Centre();
    
    wxListCtrl * list = (wxListCtrl *)FindWindow(ID_INV_LIST);
    
    list->InsertColumn(0, wxT("SKU"));
    list->InsertColumn(1, wxT("BarCode"));
    list->InsertColumn(2, wxT("Description"));
    list->InsertColumn(3, wxT("Department"));
    list->InsertColumn(4, wxT("On Hand"));
    
    if (wxGetApp().DB().IsConnected())
    {
        wxLogMessage(wxT("Connected"));
        vector<YardInvType> temp;
        
        try {
            temp = wxGetApp().DB().InvSearchSKU(10000);
        }
        catch (YardDBException &e)
        {
            wxLogDB(e.GetWhat().c_str());
            return;
        }
        
        for (int i = 0; i < temp.size(); i++)
        {
            wxLogMessage(wxT("In loop"));
            stringstream numconv;
            numconv << temp[i].GetSKU();
            list->InsertItem(0, numconv.str().c_str());
            numconv.clear();
            list->SetItem(0,1,temp[i].GetBarCode().c_str());
            list->SetItem(0,2,temp[i].GetDescription().c_str());
            list->SetItem(0,3,temp[i].GetDepartment().c_str());
        }
    }
    else
        wxLogMessage(wxT("Not Connected"));
   
}

YardInventory::~YardInventory()
{
    
}

void YardInventory::OnExitButton(wxCommandEvent & event)
{

}
