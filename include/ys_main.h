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
#ifndef YARDSALE_MAIN_H
#define YARDSALE_MAIN_H

#include "wx/frame.h"

/**
 * YardMain is the main menu screen for YardSale, it displays
 * graphical buttons for accessing the inventory, employees, sales,
 * etc.
 * There is also a footer @see YardFooter which allows users to access
 * important utilities.
 *
 * @author Jesse Lovelace
 * @version \$Revision: 1.15 $$
 */
class YardMain: public wxFrame {
    public:
 
    /**
     * Constructor
     */
    YardMain(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE, 
               const wxString& name = wxT("YardMain"));
        
    virtual ~YardMain();
    
    /*-------------Event Handlers------------*/
    /// Logout button event handler
    void OnLogout(wxCommandEvent & event);
    /// Maximize handler
    void OnMax(wxCommandEvent & event);
    /// Inventory button handler
    void OnInventory(wxCommandEvent & event);
    /// Sales buttons
    void OnSale(wxCommandEvent & event);
    /// Employee button handler
    void OnEmployee(wxCommandEvent& event);
    void OnCustomer(wxCommandEvent& event);
    void OnReports(wxCommandEvent& event);
    /// Edit program options
    void OnOptions(wxCommandEvent& event);
    
    private:
        
    DECLARE_EVENT_TABLE()
};

#endif
