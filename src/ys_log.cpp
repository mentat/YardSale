#include <iostream>

#include "ys_log.h"
#include "yardsale_wdr.h"

#include "wx/log.h"
#include "wx/image.h"
#include "wx/imaglist.h"
#include "wx/listctrl.h"
#include "wx/bitmap.h"

#include "images/stormtroop.xpm"
#include "images/yoda.xpm"
#include "images/boba_ship.xpm"
#include "images/dstar.xpm"

using namespace std;

YardLog::YardLog(wxWindow* parent, wxWindowID id, const wxPoint& pos, 
    const wxSize& size, long style, 
    const wxValidator& validator, 
    const wxString& name)
: wxListCtrl(parent, id, pos, size, style, validator, name)
{
 
    
    InsertColumn(0, wxT("Type"));
    InsertColumn(1, wxT("Message"));
    

    // prepare the imagelist
    enum { ICON_SIZE = 16 };
    
    wxImageList *imageList = new wxImageList(ICON_SIZE, ICON_SIZE, true);

    // order should be the same as in the switch below!

    imageList->Add( wxBitmap( stormtroop_xpm ).ConvertToImage().Rescale(ICON_SIZE, ICON_SIZE) );
    imageList->Add( wxBitmap( boba_ship_xpm ).ConvertToImage().Rescale(ICON_SIZE, ICON_SIZE) );
    imageList->Add( wxBitmap( yoda_xpm ).ConvertToImage().Rescale(ICON_SIZE, ICON_SIZE) );
    imageList->Add( wxBitmap( dstar_xpm ).ConvertToImage().Rescale(ICON_SIZE, ICON_SIZE) );
    

    SetImageList(imageList, wxIMAGE_LIST_SMALL);

    Show(true);
    
    delete wxLog::SetActiveTarget(this);
    
}


YardLog::~YardLog()
{
    wxLog::SetActiveTarget(NULL);
	delete GetImageList(wxIMAGE_LIST_SMALL);
}

void YardLog::DoLog(wxLogLevel level, const wxChar *szString, time_t t)
{
  int image;

  wxString string_type;
  cout << "LOG: " << szString << endl;

  switch ( level )
  {
  case wxLOG_Error:
    image = 0;
    string_type = wxT("Error");
    break;
  case wxLOG_Warning:
    image = 1;
    string_type = wxT("Warning");
    break;
  case wxLOG_FatalError:
    image = 0;
    string_type = wxT("Fatal error");
    break;
  case wxLOG_Message:
    image = 2;
    string_type = wxT("Message");
    break;
  case wxLOG_Info:
    image = 2;
    string_type = wxT("Info");
    break;
  case wxLOG_Status:
    image = 2;
    string_type = wxT("Status");
    break;
  case wxLOG_Debug:
    image = 1;
    string_type = wxT("Debug");
    break;
  case wxLOG_Trace:
    image = 2;
    string_type = wxT("Trace");
    break;
  case wxLOG_Progress:
    image = 2;
    string_type = wxT("Progress");
    break;
  case wxLOG_CONSOLE:
    image = 2;
    string_type = wxT("Console");
    break;
  case wxLOG_DB:
    image = 3;
    string_type = wxT("Database");
    break;
  case wxLOG_SQL: 
    { 
        image = 2;
        wxTextCtrl * sql = static_cast<wxTextCtrl *>(FindWindow(ID_DEBUG_SQL));
        if (sql)
            sql->SetValue(szString);
        string_type = wxT("SQL"); 
    }
    break;
  default:
    string_type = wxT("Unknown");
    image = 2;
    break;
  }

  InsertItem(0, string_type, image);
  SetItem(0,1,szString);

  SetColumnWidth(0, wxLIST_AUTOSIZE);
  SetColumnWidth(1, wxLIST_AUTOSIZE);

}

void wxLogCon(const wxChar* sxFormat,  ...)
{
    va_list argptr;
    va_start(argptr, sxFormat);
    wxLogGeneric(wxLOG_CONSOLE, sxFormat, argptr);
   // cout << sxFormat << endl;
    va_end(argptr);
    
}

void wxLogDB(const wxChar* sxFormat,  ...)
{
    va_list argptr;
    va_start(argptr, sxFormat);
    wxLogGeneric(wxLOG_DB, sxFormat, argptr);
   // cout << sxFormat << endl;
    va_end(argptr);
    
}

void wxLogSQL(const wxChar* sxFormat, ...)
{
    va_list argptr;
    va_start(argptr, sxFormat);
    wxLogGeneric(wxLOG_SQL, sxFormat, argptr);
   // cout << sxFormat << endl;
    va_end(argptr);
    
}
