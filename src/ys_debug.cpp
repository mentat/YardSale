#include "yardsale_wdr.h"
#include "wx/frame.h"

#include "ys_debug.h"

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
