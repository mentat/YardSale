#include "yardsale_wdr.h"
#include "wx/app.h"
#include "wx/frame.h"

#include "yardsale.h"
#include "ys_log.h"
#include "ys_exception.h"
#include "ys_database.h"
#include "ys_debug.h"

#include <string>
using namespace std;

BEGIN_EVENT_TABLE(YardDebugScreen, wxFrame)
  //  EVT_BUTTON(ID_DEBUG_DB_CONNECT, YardDebugScreen::OnConnect)
  //  EVT_BUTTON(ID_DEBUG_DB_DISC, YardDebugScreen::OnDisc)
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
#if 0        
   // wxString dsn = ((wxTextCtrl *)FindWindow(ID_DEBUG_DSN))->GetValue();
   // wxString user = ((wxTextCtrl *)FindWindow(ID_DEBUG_USER))->GetValue();
   // wxString pass = ((wxTextCtrl *)FindWindow(ID_DEBUG_PASS))->GetValue();

    //wxLogDebug("Info: %s, %s, %s", dsn.c_str(), user.c_str(), pass.c_str());
    
    try {
        wxGetApp().DB().Init(user.c_str(), pass.c_str(), dsn.c_str());
    } catch (YardDBException &e)
    {
        //((wxTextCtrl *)FindWindow(ID_DEBUG_SQL))->SetValue(e.GetSQL().c_str());
        wxLogDB(e.GetWhat().c_str());
    }
    
    try { 
        wxGetApp().DB().connect();
    } catch (YardDBException &e)
    {
       // ((wxTextCtrl *)FindWindow(ID_DEBUG_SQL))->SetValue(e.GetSQL().c_str());
        wxLogDB(e.GetWhat().c_str());
        return;
    }
    wxLogDB(wxT("Connected to %s"), dsn.c_str());
    #endif
}

void YardDebugScreen::OnDisc(wxCommandEvent & event) {
  
    try {
        wxGetApp().DB().disconnect();
    } catch (YardDBException &e)
    {
        ((wxTextCtrl *)FindWindow(ID_DEBUG_SQL))->SetValue(e.GetSQL().c_str());
        wxLogDB(e.GetWhat().c_str());
        return;
    }        
    wxLogDB(wxT("Disconnected"));
    
}
