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
#ifndef YS_FOOTER_H
#define YS_FOOTER_H

#include "wx/panel.h"
#include "wx/timer.h"
class wxStaticText;

/**
 * The footer is a easy-access panel to launch the on-screen calc
 * and keyboard.  The footer also shows current time and has
 * the ability to undo operations.
 *
 * @author Jesse Lovelace
 * @version \$ Revision: $$
 */
class YardFooter: public wxPanel {
 public:
    YardFooter(wxWindow* parent, wxWindowID id = -1, 
     const wxPoint& pos = wxDefaultPosition, 
     const wxSize& size = wxDefaultSize, 
     long style = wxTAB_TRAVERSAL, 
     const wxString& name = "YardFooter");
    
    YardFooter();
    bool Create(wxWindow* parent, wxWindowID id = -1, 
     const wxPoint& pos = wxDefaultPosition, 
     const wxSize& size = wxDefaultSize, 
     long style = wxTAB_TRAVERSAL, 
     const wxString& name = "YardFooter");
 
 
    void Init();
 
    virtual ~YardFooter();
 
    void OnTimer(wxTimerEvent& event);
 
    void OnCalc(wxCommandEvent& event);
    void OnKeyboard(wxCommandEvent & event);
    void OnBack(wxCommandEvent& event);
    void OnUndo(wxCommandEvent& event);
 
 private:
     
    wxTimer * m_timer;
    wxStaticText *m_timeTxt;
     
    DECLARE_EVENT_TABLE()
    DECLARE_DYNAMIC_CLASS(YardFooter)
 
};
 
#endif
