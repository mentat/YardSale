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
#ifndef YS_DEBUG_SCREEN_H
#define YS_DEBUG_SCREEN_H

#include "wx/frame.h"
/**
 * The debug screen allows a user to see the active program log and 
 * selectively login to databases with a specified username and password.
 *
 * @author Jesse Lovelace
 */
class YardDebugScreen: public wxFrame {
 public:
    /// Window contructor    
    YardDebugScreen(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE);
    /// Destructor    
    virtual ~YardDebugScreen();
    
    /// Event called when user tries to connect to the database.
    void OnConnect(wxCommandEvent& event);
 
    /// Event called when user tries to disconnect to the database.
    void OnDisc(wxCommandEvent& event);
    
 private:
        
    DECLARE_EVENT_TABLE()
    
};

#endif
