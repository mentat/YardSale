#include "yardsale_wdr.h"
#include "ys_sale.h"

BEGIN_EVENT_TABLE(YardSaleScreen, wxFrame)
    EVT_BUTTON(ID_SALE_BACK, YardSaleScreen::OnExitButton)
END_EVENT_TABLE()

YardSaleScreen::YardSaleScreen(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style)
:wxFrame(parent, id, title, pos, size, style) {
    
    wxPanel * panel = new wxPanel(this);
    
    wxSizer * sizer = Sale(panel, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    Centre();
    
    wxImageList * list = new wxImageList();
    list->Add(YardBitmaps(9));
    
    wxListCtrl * listCtrl = (wxListCtrl *)FindWindow(ID_SALE_TRANS);
    listCtrl->AssignImageList(list,wxIMAGE_LIST_NORMAL);

    listCtrl->InsertColumn(0, wxT("Description"));
    listCtrl->InsertColumn(1, wxT("Price"));
    
    // Test
    listCtrl->InsertItem(0, "Hot Linux ass", 0);
    listCtrl->SetItem(0,1,"$9.69");
    listCtrl->SetColumnWidth(0, wxLIST_AUTOSIZE);
    
    
   // listCtrl->InsertItem(0,0);
   // listCtrl->InsertItem(0,1);
   // listCtrl->InsertItem(0,2);
   
}

YardSaleScreen::~YardSaleScreen()
{
    
}

void YardSaleScreen::OnExitButton(wxCommandEvent & event)
{
    Close(true);
    
}
