#include "wx/app.h"

#include "yardsale.h"
#include "ys_bitmaps.h"

#include "yardsale_wdr.h"
#include "ys_sale.h"

BEGIN_EVENT_TABLE(YardSaleScreen, wxFrame)
    //EVT_BUTTON(ID_SALE_BACK, YardSaleScreen::OnExitButton)
END_EVENT_TABLE()

DECLARE_APP(YardSale)

YardSaleScreen::YardSaleScreen(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style, const wxString& name)
:wxFrame(parent, id, title, pos, size, style, name) {
    
    wxPanel * panel = new wxPanel(this);
    
    wxBitmapButton * trash = new wxBitmapButton(panel, ID_SALE_TRASH,
        wxGetApp().Images().GetBitmap(YardBitmaps::TRASH));
    
    wxSizer * sizer = Sale(panel, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    Centre();
    
    wxImageList * list = new wxImageList();
    list->Add(wxGetApp().Images().GetBitmap(YardBitmaps::TUX));
    
    wxListCtrl * listCtrl = (wxListCtrl *)FindWindow(ID_SALE_TRANS);
    listCtrl->AssignImageList(list,wxIMAGE_LIST_NORMAL);

    listCtrl->InsertColumn(0, wxT("Description"));
    listCtrl->InsertColumn(1, wxT("Price"));
    
    // Test
    #if 0
    listCtrl->InsertItem(0, "Fruit", 0);
    listCtrl->SetItem(0,1,"$9.69");
    listCtrl->SetColumnWidth(0, wxLIST_AUTOSIZE);
    #endif
    
}

YardSaleScreen::~YardSaleScreen()
{
    
}

void YardSaleScreen::OnExitButton(wxCommandEvent & event)
{
    Close(true);
    
}
