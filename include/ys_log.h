#ifndef YS_LOG_H
#define YS_LOG_H

#include "wx/app.h"
#include "wx/log.h"
#include "wx/listctrl.h"

enum
{
    wxLOG_CONSOLE = 101
};

// Yes! Fuck you MI haters.
class YardLog: public wxListCtrl , public wxLog
{
public:
    YardLog(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, 
        const wxSize& size = wxDefaultSize, long style = wxLC_LIST, 
        const wxValidator& validator = wxDefaultValidator, 
        const wxString& name = "YardLog");
    
    ~YardLog();

protected:

    virtual void DoLog(wxLogLevel level, const wxChar *szString, time_t t);

};

DECLARE_LOG_FUNCTION(Con);

#endif
