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
#ifndef YS_LOGIN_H
#define YS_LOGIN_H

/**
 * This is the customized login screen for YardSale.  The user will 
 * be asked for a username and password.  Also, a quick select icon will
 * allow the user to rapidly select her/his username.
 *
 * @author Jesse Lovelace
 * @version $Revision: 1.6 $
 */
class YardLogin: public wxDialog {
 public:
    /**
     * Constructs a Login window
     */
    YardLogin(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxSTAY_ON_TOP | wxRESIZE_BORDER);
    
    /// Destructor    
    virtual ~YardLogin();  
    
    /**
     * Exit button handler.
     * @param event The event being passed in.
     */
    void OnExitButton(wxCommandEvent & event);
    /**
     * Login button handler.
     * @param event The event being passed in.
     */
    void OnLogin(wxCommandEvent & event);
    
    private:
        
    DECLARE_EVENT_TABLE()
    
};

#endif
