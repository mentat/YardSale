/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004 - Jesse Lovelace <jllovela@ncsu.edu>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef YS_LOG_H
#define YS_LOG_H

#include "wx/app.h"
#include "wx/log.h"
#include "wx/listctrl.h"

enum
{
    wxLOG_CONSOLE = 101,
    wxLOG_DB,
    wxLOG_SQL
};

// Yes! Fuck you MI haters.
/**
 * Logging widget, based on a wxListCtrl and wxLog
 * This widget resets the default logging system and
 * redirects all output to itself.  Different icons represent what
 * type of log message is being displayed.
 * 
 * @author Jesse Lovelace
 */
class YardLog: public wxListCtrl , public wxLog
{
public:
    YardLog(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, 
        const wxSize& size = wxDefaultSize, long style = wxLC_LIST, 
        const wxValidator& validator = wxDefaultValidator, 
        const wxString& name = "YardLog");
    YardLog():wxListCtrl() {}
    bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, 
        const wxSize& size = wxDefaultSize, long style = wxLC_LIST, 
        const wxValidator& validator = wxDefaultValidator, 
        const wxString& name = "YardLog");
    
    virtual ~YardLog();

protected:

    virtual void DoLog(wxLogLevel level, const wxChar *szString, time_t t);
    DECLARE_DYNAMIC_CLASS(YardLog)
};

DECLARE_LOG_FUNCTION(DB);
DECLARE_LOG_FUNCTION(Con);
DECLARE_LOG_FUNCTION(SQL);

#endif
