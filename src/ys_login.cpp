#include "yardsale_wdr.h"
#include "ys_login.h"

BEGIN_EVENT_TABLE(YardLogin, wxDialog)
    EVT_BUTTON(ID_LOGIN_LOGIN, YardLogin::OnLogin)
    EVT_BUTTON(ID_LOGIN_EXIT, YardLogin::OnExitButton)
END_EVENT_TABLE()

YardLogin::YardLogin(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style)
:wxDialog(parent, id, title, pos, size, style) {
    
    wxPanel * panel = new wxPanel(this);
        
    wxSizer * sizer = Login(panel, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    wxImageList * list = new wxImageList();
    list->Add(YardBitmaps(3));
    list->Add(YardBitmaps(4));
    list->Add(YardBitmaps(5));
    
    wxListCtrl * listCtrl = (wxListCtrl *)FindWindow(ID_LOGIN_LIST);
    
    listCtrl->AssignImageList(list,wxIMAGE_LIST_NORMAL);
    listCtrl->InsertItem(0,0);
    listCtrl->InsertItem(0,1);
    listCtrl->InsertItem(0,2);
    
    Centre();
}

YardLogin::~YardLogin()
{
    
}

void YardLogin::OnExitButton(wxCommandEvent & event)
{
    wxLogDebug(wxT("OnExitButton"));
    
}

void YardLogin::OnLogin(wxCommandEvent & event)
{
    wxLogDebug(wxT("OnLogin"));
    EndModal(0);
    
}
