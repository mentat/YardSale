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

#include "wx/dialog.h"
#include "ys_inv_type.h"
class wxListCtrl;
class wxTextCtrl;
class wxChoice;
class wxSpinCtrl;
class wxCheckBox;   
class wxComboBox;    
class wxListEvent;
class wxButton;
class wxBitmapButton;
class wxStaticBitmap;
class wxTreeCtrl;
class wxTreeEvent;

/**
 * The inventory screen displays items in the inventory and allows seaching.
 * New items can also be added to the inventory via the "New Item" button.
 *
 * @author Jesse Lovelace
 * @version \$Revision: 1.20 $$
 */
class YardInventory: public wxDialog{
 public:
    
    /** 
     * Constructs an Inventory screen
     */    
    YardInventory(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString& name = wxT("YardInventory"));
    
    /// Destructor
    virtual ~YardInventory();
    
    /**
     * Exit button handler.
     * @param event The event being passed in.
     */
    void OnExitButton(wxCommandEvent & event);
    /**
     * New Item button handler.
     * @param event The event being passed in.
     */
    void OnNew(wxCommandEvent & event);
    /**
     * Search button handler.
     * @param event The event being passed in.
     */
    void OnSearch(wxCommandEvent & event);
    /**
     * Called when an item is selected in the list control.
     * @param event The event being passed in.
     */
    void OnSelect(wxListEvent & event);
    
    void OnChange(wxTreeEvent& event);
    
 private:
     
    void ShowItem(const YardInvType& item);
    YardInvType SaveItem();     
 
    void LoadTreeItems(wxTreeCtrl * tree);
     
    void LoadFromDB();
     
    /// Set all component pointers
    void SetPointers();
 
    /// Refresh list from vector data
    void PopulateList();
 
    DECLARE_EVENT_TABLE()
 
    wxTreeCtrl * m_tree;
    wxTextCtrl * m_det_sku;
    wxTextCtrl * m_det_name;
    wxTextCtrl * m_det_desc;
    wxTextCtrl * m_det_barcode;
    wxComboBox * m_det_dept;
    wxBitmapButton * m_dep_dept_edit;
    wxComboBox * m_dep_group;
    wxBitmapButton * m_dep_group_edit;
    wxStaticBitmap * m_dep_image;
    wxComboBox * m_dep_vendor;
    wxBitmapButton * m_dep_vendor_edit;
    
    // pricing
    wxTextCtrl * m_price_retail;
    wxTextCtrl * m_price_wholesale;
    wxListCtrl * m_price_bulk;
    wxButton * m_price_bulk_add;
    wxButton * m_price_bulk_rm;
    wxComboBox * m_price_tax;
    wxBitmapButton * m_price_tax_edit;
    
    wxTextCtrl * m_ship_weight;
    wxTextCtrl * m_ship_date_rec;
    wxCheckBox * m_ship_oversized;
    wxCheckBox * m_ship_freight;
    
    wxSpinCtrl * m_stock_onhand;
    wxSpinCtrl * m_stock_onorder;
    wxSpinCtrl * m_stock_reorder_lvl;
    wxSpinCtrl * m_stock_reorder_quant;
    
    //vector<YardInvType> m_objects;
};

#endif
