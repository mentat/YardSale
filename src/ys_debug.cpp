#include "yardsale_wdr.h"
#include "wx/frame.h"

#include "ys_debug.h"

BEGIN_EVENT_TABLE(YardDebugScreen, wxFrame)
    EVT_BUTTON(ID_DEBUG_DB_CONNECT, YardDebugScreen::OnConnect)
    EVT_BUTTON(ID_DEBUG_DB_DISC, YardDebugScreen::OnDisc)
END_EVENT_TABLE()

YardDebugScreen::YardDebugScreen(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style)
    :wxFrame(parent, id, title, pos, size, style)
{
    wxSizer * sizer = DebugScreen(this, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
}

YardDebugScreen::~YardDebugScreen()
{
    
}

void YardDebugScreen::OnConnect(wxCommandEvent & event) {

    
}

void YardDebugScreen::OnDisc(wxCommandEvent & event) {
    
}
