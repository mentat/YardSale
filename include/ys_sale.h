/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004  Jesse Lovelace <jllovela@ncsu.edu>
 
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
#ifndef YS_SALE_H
#define YS_SALE_H

/**
 * This is the main sale screen.  It contains the current transaction
 * information. 
 * @author Jesse Lovelace
 * @version $Revision: 1.4 $
 */
class YardSaleScreen: public wxFrame{
    public:
        
    YardSaleScreen(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxRESIZE_BORDER|wxTAB_TRAVERSAL);
        
    virtual ~YardSaleScreen();
    
    /**
     * Exit button event handler
     */
    void OnExitButton(wxCommandEvent & event);
    
    private:
        
    DECLARE_EVENT_TABLE()
        
};

#endif
