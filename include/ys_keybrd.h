/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004  Jesse Lovelace <jllovela@ncsu.edu>
    Copyright (C) 2004  Jay Johnston <jkjohnst@ncsu.edu>
 
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


#ifndef YS_CALC_H
#define YS_CALC_H

#include <stack>
#include "wx/panel.h"

class wxTextCtrl;

class YardKeybrd: public wxPanel {
 public:
     
    /**
     * The constructor for the class, nothing special
     */    
    YardKeybrd(wxWindow* parent, wxWindowID id = -1, 
        const wxPoint& pos = wxDefaultPosition, 
        const wxSize& size = wxDefaultSize, 
        long style = wxTAB_TRAVERSAL, 
        const wxString& name = "YardCalc");
    
    /// Destructor
    virtual ~YardKeybrd();
    
 private:
   	
    DECLARE_EVENT_TABLE()
	
	void OnButton(wxCommandEvent & event);
    void OnButtonSpace(wxCommandEvent & event);
    void OnButtonDelete(wxCommandEvent & event);
    void OnButtonShift(wxCommandEvent & event);

    void OnButtonClear(wxCommandEvent & event);
    void OnButtonDone(wxCommandEvent & event);
 
    void OnChar(wxCommandEvent & event);
    void AddString(wxString string);
    
	void RefreshScreen();
    
    void ClearScreen();
	
    wxTextCtrl * m_screen;
    wxString screencontents;
};

#endif
