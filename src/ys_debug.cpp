#include "yardsale_wdr.h"
#include "wx/app.h"
#include "wx/frame.h"

#include "yardsale.h"
#include "ys_log.h"
#include "ys_database.h"
#include "ys_debug.h"

BEGIN_EVENT_TABLE(YardDebugScreen, wxFrame)
    EVT_BUTTON(ID_DEBUG_DB_CONNECT, YardDebugScreen::OnConnect)
    EVT_BUTTON(ID_DEBUG_DB_DISC, YardDebugScreen::OnDisc)
END_EVENT_TABLE()

DECLARE_APP(YardSale)

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
    
    
    wxString dsn = ((wxTextCtrl *)FindWindow(ID_DEBUG_DSN))->GetValue();
    wxString user = ((wxTextCtrl *)FindWindow(ID_DEBUG_USER))->GetValue();
    wxString pass = ((wxTextCtrl *)FindWindow(ID_DEBUG_PASS))->GetValue();
    if (!wxGetApp().DB().Init(dsn.c_str(), user.c_str(), pass.c_str()))
    {
        wxLogDB(wxT("Cannot init DB"));
        return;
    }

    if (!wxGetApp().DB().connect())
    {
        wxLogDB(wxT("Cannot connect DB"));
    }
    
    
    
}

void YardDebugScreen::OnDisc(wxCommandEvent & event) {
  
    if (!wxGetApp().DB().disconnect())
        wxLogDB(wxT("Cannot disconnect from DB"));    
    
}
