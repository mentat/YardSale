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
#ifndef YS_INVENTORY_H
#define YS_INVENTORY_H

#include "wx/frame.h"
#include "ys_inv_type.h"
class wxListCtrl;
class wxTextCtrl;
class wxChoice;
class wxSpinCtrl;
class wxCheckBox;    

/**
 * The inventory screen.
 * @author Jesse Lovelace
 * @version $Revision: 1.12 $
 */
class YardInventory: public wxFrame{
 public:
    
    /** 
     * Constructs an Inventory screen
     */    
    YardInventory(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxRESIZE_BORDER|wxTAB_TRAVERSAL,
               const wxString& name = wxT("YardInventory"));
    
    /// Destructor
    virtual ~YardInventory();
    
    /**
     * Exit button handler.
     * @param event The event being passed in.
     */
    void OnExitButton(wxCommandEvent & event);
    
    void OnNew(wxCommandEvent & event);
    void OnSearch(wxCommandEvent & event);
    void OnSelect(wxListEvent & event);
    
 private:
     
    /// Set all component pointers
    void SetPointers();
 
    /// Refresh list from vector data
    void PopulateList();
 
    DECLARE_EVENT_TABLE()
 
    wxTextCtrl * m_sku;
    wxTextCtrl * m_name;
    wxTextCtrl * m_department;
    wxTextCtrl * m_type;
    wxTextCtrl * m_price;
    wxTextCtrl * m_wholesale;
    wxTextCtrl * m_weight;
    wxTextCtrl * m_vendor;
    wxTextCtrl * m_barCode;
    wxTextCtrl * m_desc;
 
    wxCheckBox * m_freight;
    wxCheckBox * m_oversized;
 
    wxSpinCtrl * m_onHand;
    wxSpinCtrl * m_onOrder;
    wxSpinCtrl * m_reOrder;
    wxChoice * m_tax;
 
    wxListCtrl * m_list;
    vector<YardInvType> m_objects;
};

#endif
