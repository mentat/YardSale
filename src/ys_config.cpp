#include "ys_config.h"
#include "yardsale_wdr.h"


BEGIN_EVENT_TABLE(YardConfig, wxFrame)
    EVT_BUTTON(ID_CONFIG_SAVE, YardConfig::OnSave)
    EVT_BUTTON(ID_CONFIG_CANCEL, YardConfig::OnCancel)
END_EVENT_TABLE()

YardConfig::YardConfig(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos, const wxSize& size, long style)

:wxFrame(parent, id, title, pos, size, style)
{    
    wxPanel * panel = new wxPanel(this);
    
    wxSizer * sizer = Config(panel, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    Centre();
}
 
YardConfig::~YardConfig()
{}
 
void YardConfig::OnCancel(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnCancel"));
    Close();
}

void YardConfig::OnSave(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnSave"));
}
