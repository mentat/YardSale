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

#include <vector>
#include "wx/treebase.h"
#include "wx/dialog.h"

#include "ys_inv_type.h"

class wxListCtrl;
class wxTreeCtrl;
class wxNotebook;
class wxStaticText;
/**
 * This is the main sale screen.  It contains the current transaction
 * information and an interface to add new items to the transaction.  
 * From the transaction screen you can access the payment screen.
 * 
 * @author Jesse Lovelace
 * @version \$Revision: 1.10 $$
 */
class YardSaleScreen: public wxDialog{
 public:
    
    /// This is the constructor you will most commonly use.
    YardSaleScreen(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString& name = wxT("YardSaleScreen"));
    /// Destructor
    virtual ~YardSaleScreen();
    
    /**
     * Exit button event handler
     */
    void OnExitButton(wxCommandEvent & event);
    void OnChange(wxTreeEvent& event);
    void OnRemove(wxCommandEvent& event);
    void OnCheckout(wxCommandEvent& event);
 
    private:
        
    //wxTreeCtrl * m_tree;
    wxNotebook * m_book;
    wxListCtrl * m_list;
    
    wxStaticText * m_subTotal;
    wxStaticText * m_tax;
    wxStaticText * m_total;
    void LoadTreeItems(wxTreeCtrl * tree);
    void CreateImageList(wxTreeCtrl * tree);
    
    std::vector<YardInvType> m_items;    
    
    DECLARE_EVENT_TABLE()
        
};

#endif
