//------------------------------------------------------------------------------
// Source code generated by wxDesigner from file: yardsale.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifdef __GNUG__
    #pragma implementation "yardsale_wdr.h"
#endif

// For compilers that support precompilation
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// Include private header
#include "yardsale_wdr.h"


// Custom source
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
#include "ys_calc.h"
#include "ys_log.h"
#include "ys_footer.h"

// Implement window functions

wxSizer *Splash( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxWindow *item1 = parent->FindWindow( ID_SPLASH_LOGO );
    wxASSERT( item1 );
    item0->Add( item1, 0, wxALIGN_CENTER|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *Login( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 1, 0, 0 );
    item0->AddGrowableCol( 0 );
    item0->AddGrowableRow( 1 );

    wxFlexGridSizer *item1 = new wxFlexGridSizer( 2, 0, 0 );
    item1->AddGrowableCol( 1 );

    wxStaticText *item2 = new wxStaticText( parent, ID_TEXT, wxT("Username:"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->Add( item2, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item3 = new wxTextCtrl( parent, ID_TEXTCTRL, wxT(""), wxDefaultPosition, wxSize(170,-1), 0 );
    item1->Add( item3, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item4 = new wxStaticText( parent, ID_TEXT, wxT("Password:"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->Add( item4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item5 = new wxTextCtrl( parent, ID_LOGIN_PASSWORD, wxT(""), wxDefaultPosition, wxSize(120,-1), wxTE_PASSWORD );
    item1->Add( item5, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item0->Add( item1, 0, wxGROW|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxListCtrl *item6 = new wxListCtrl( parent, ID_LOGIN_LIST, wxDefaultPosition, wxSize(160,130), wxLC_ICON|wxSUNKEN_BORDER );
    item0->Add( item6, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxGridSizer *item7 = new wxGridSizer( 2, 0, 0 );

    wxButton *item8 = new wxButton( parent, ID_LOGIN_LOGIN, wxT("Login"), wxDefaultPosition, wxDefaultSize, 0 );
    item7->Add( item8, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item9 = new wxButton( parent, ID_LOGIN_EXIT, wxT("Exit"), wxDefaultPosition, wxDefaultSize, 0 );
    item7->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item7, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *MainText( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 2, 0, 0 );
    item0->AddGrowableCol( 0 );
    item0->AddGrowableCol( 1 );
    item0->AddGrowableRow( 0 );
    item0->AddGrowableRow( 1 );
    item0->AddGrowableRow( 2 );
    item0->AddGrowableRow( 3 );

    wxButton *item1 = new wxButton( parent, ID_MAIN_INVENTORY, wxT("Inventory Management"), wxDefaultPosition, wxSize(265,35), 0 );
    item1->SetFont( wxFont( 20, wxROMAN, wxNORMAL, wxNORMAL ) );
    item0->Add( item1, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxButton *item2 = new wxButton( parent, ID_MAIN_SALES, wxT("Sales Cashier"), wxDefaultPosition, wxSize(265,35), 0 );
    item2->SetFont( wxFont( 20, wxROMAN, wxNORMAL, wxNORMAL ) );
    item0->Add( item2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxButton *item3 = new wxButton( parent, ID_MAIN_CUSTOMER, wxT("Customer Information"), wxDefaultPosition, wxSize(265,35), 0 );
    item3->SetFont( wxFont( 20, wxROMAN, wxNORMAL, wxNORMAL ) );
    item0->Add( item3, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxButton *item4 = new wxButton( parent, ID_MAIN_REPORTS, wxT("Reports"), wxDefaultPosition, wxSize(265,35), 0 );
    item4->SetFont( wxFont( 20, wxROMAN, wxNORMAL, wxNORMAL ) );
    item0->Add( item4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxButton *item5 = new wxButton( parent, ID_MAIN_EMPLOYEE, wxT("Employee Information"), wxDefaultPosition, wxSize(265,35), 0 );
    item5->SetFont( wxFont( 20, wxROMAN, wxNORMAL, wxNORMAL ) );
    item0->Add( item5, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxButton *item6 = new wxButton( parent, ID_MAIN_LOGOUT, wxT("Logout"), wxDefaultPosition, wxSize(265,35), 0 );
    item6->SetFont( wxFont( 20, wxROMAN, wxNORMAL, wxNORMAL ) );
    item0->Add( item6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *Inventory( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 1, 0, 0 );
    item0->AddGrowableCol( 0 );
    item0->AddGrowableRow( 2 );

    wxFlexGridSizer *item1 = new wxFlexGridSizer( 4, 0, 0 );
    item1->AddGrowableCol( 1 );
    item1->AddGrowableCol( 3 );

    wxFlexGridSizer *item2 = new wxFlexGridSizer( 2, 0, 0 );
    item2->AddGrowableCol( 0 );
    item2->AddGrowableCol( 1 );

    wxFlexGridSizer *item3 = new wxFlexGridSizer( 2, 0, 0 );
    item3->AddGrowableCol( 1 );

    wxStaticText *item4 = new wxStaticText( parent, ID_TEXT, wxT("SKU"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item5 = new wxTextCtrl( parent, ID_INV_SKU, wxT(""), wxDefaultPosition, wxSize(140,-1), 0 );
    item3->Add( item5, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item6 = new wxStaticText( parent, ID_TEXT, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item6, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item7 = new wxTextCtrl( parent, ID_INV_ITEMNAME, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item3->Add( item7, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item8 = new wxStaticText( parent, ID_TEXT, wxT("Department"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item8, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item9 = new wxTextCtrl( parent, ID_INV_DEPARTMENT, wxT(""), wxDefaultPosition, wxSize(70,-1), 0 );
    item3->Add( item9, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item10 = new wxStaticText( parent, ID_TEXT, wxT("Item Type"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item10, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item11 = new wxTextCtrl( parent, ID_INV_TYPE, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item3->Add( item11, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item12 = new wxStaticText( parent, ID_TEXT, wxT("Price"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item12, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item13 = new wxTextCtrl( parent, ID_INV_PRICE, wxT(""), wxDefaultPosition, wxSize(70,-1), 0 );
    item3->Add( item13, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item14 = new wxStaticText( parent, ID_TEXT, wxT("Wholesale"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item14, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item15 = new wxTextCtrl( parent, ID_INV_WHOLESALE, wxT(""), wxDefaultPosition, wxSize(150,-1), 0 );
    item3->Add( item15, 0, wxALL, 5 );

    wxStaticText *item16 = new wxStaticText( parent, ID_TEXT, wxT("Weight (lbs)"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item16, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item17 = new wxTextCtrl( parent, ID_INV_WEIGHT, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item3->Add( item17, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item18 = new wxStaticText( parent, ID_TEXT, wxT("Vendor"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item18, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item19 = new wxTextCtrl( parent, ID_INV_VENDOR, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item3->Add( item19, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item20 = new wxStaticText( parent, ID_TEXT, wxT("Tax Type"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item20, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxString strs21[] = 
    {
        wxT("ChoiceItem")
    };
    wxChoice *item21 = new wxChoice( parent, ID_INV_TAX_TYPE, wxDefaultPosition, wxSize(100,-1), 1, strs21, 0 );
    item3->Add( item21, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item2->Add( item3, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxFlexGridSizer *item22 = new wxFlexGridSizer( 2, 0, 0 );
    item22->AddGrowableCol( 1 );
    item22->AddGrowableRow( 1 );

    wxStaticText *item23 = new wxStaticText( parent, ID_TEXT, wxT("Bar Code"), wxDefaultPosition, wxDefaultSize, 0 );
    item22->Add( item23, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item24 = new wxTextCtrl( parent, ID_INV_BARCODE, wxT(""), wxDefaultPosition, wxSize(120,-1), 0 );
    item22->Add( item24, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item25 = new wxStaticText( parent, ID_TEXT, wxT("Description"), wxDefaultPosition, wxDefaultSize, 0 );
    item22->Add( item25, 0, wxALIGN_RIGHT|wxALL, 5 );

    wxTextCtrl *item26 = new wxTextCtrl( parent, ID_INV_DESC, wxT(""), wxDefaultPosition, wxSize(150,-1), wxTE_MULTILINE );
    item22->Add( item26, 0, wxGROW|wxALL, 5 );

    item22->Add( 20, 20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxCheckBox *item27 = new wxCheckBox( parent, ID_INV_FREIGHT, wxT("Freight Only"), wxDefaultPosition, wxDefaultSize, 0 );
    item22->Add( item27, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item22->Add( 20, 20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxCheckBox *item28 = new wxCheckBox( parent, ID_INV_OVERSIZE, wxT("Oversized"), wxDefaultPosition, wxDefaultSize, 0 );
    item22->Add( item28, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item29 = new wxStaticText( parent, ID_TEXT, wxT("On Hand"), wxDefaultPosition, wxDefaultSize, 0 );
    item22->Add( item29, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxSpinCtrl *item30 = new wxSpinCtrl( parent, ID_INV_ONHAND, wxT("0"), wxDefaultPosition, wxSize(100,-1), 0, 0, 1000000, 0 );
    item22->Add( item30, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item31 = new wxStaticText( parent, ID_TEXT, wxT("On Order"), wxDefaultPosition, wxDefaultSize, 0 );
    item22->Add( item31, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxSpinCtrl *item32 = new wxSpinCtrl( parent, ID_INV_ONORDER, wxT("0"), wxDefaultPosition, wxSize(100,-1), 0, 0, 1000000, 0 );
    item22->Add( item32, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item33 = new wxStaticText( parent, ID_TEXT, wxT("Reorder Level"), wxDefaultPosition, wxDefaultSize, 0 );
    item22->Add( item33, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxSpinCtrl *item34 = new wxSpinCtrl( parent, ID_INV_REORDER_LEVEL, wxT("0"), wxDefaultPosition, wxSize(100,-1), 0, 0, 100000, 0 );
    item22->Add( item34, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item2->Add( item22, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item1->Add( item2, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxBoxSizer *item35 = new wxBoxSizer( wxVERTICAL );

    wxButton *item36 = new wxButton( parent, ID_INV_NEW, wxT("New Item"), wxDefaultPosition, wxDefaultSize, 0 );
    item35->Add( item36, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item37 = new wxButton( parent, ID_INV_SEARCH, wxT("Search"), wxDefaultPosition, wxDefaultSize, 0 );
    item37->SetToolTip( wxT("Search by text in field") );
    item35->Add( item37, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item38 = new wxButton( parent, ID_INV_CLEAR, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
    item35->Add( item38, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticLine *item39 = new wxStaticLine( parent, ID_LINE, wxDefaultPosition, wxSize(20,-1), wxLI_HORIZONTAL );
    item35->Add( item39, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxButton *item40 = new wxButton( parent, ID_INV_SAVE, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
    item40->Enable( FALSE );
    item35->Add( item40, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item41 = new wxButton( parent, ID_INV_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    item35->Add( item41, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticLine *item42 = new wxStaticLine( parent, ID_LINE, wxDefaultPosition, wxSize(20,-1), wxLI_HORIZONTAL );
    item35->Add( item42, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxButton *item43 = new wxButton( parent, ID_INV_CLEAR_RESULTS, wxT("Clear Results"), wxDefaultPosition, wxDefaultSize, 0 );
    item35->Add( item43, 0, wxALIGN_CENTER|wxALL, 5 );

    item1->Add( item35, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticLine *item44 = new wxStaticLine( parent, ID_LINE, wxDefaultPosition, wxSize(20,-1), wxLI_HORIZONTAL );
    item0->Add( item44, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxListCtrl *item45 = new wxListCtrl( parent, ID_INV_LIST, wxDefaultPosition, wxSize(160,140), wxLC_REPORT|wxSUNKEN_BORDER );
    item0->Add( item45, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    YardFooter *item46 = new YardFooter( parent, ID_PANEL, wxDefaultPosition, wxSize(200,90), 0 );
    item0->Add( item46, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *Main( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 1, 0, 0 );
    item0->AddGrowableCol( 0 );
    item0->AddGrowableRow( 0 );

    wxFlexGridSizer *item1 = new wxFlexGridSizer( 2, 0, 0 );
    item1->AddGrowableCol( 0 );
    item1->AddGrowableCol( 1 );
    item1->AddGrowableRow( 0 );
    item1->AddGrowableRow( 4 );

    wxWindow *item2 = parent->FindWindow( ID_MAIN_LOGO );
    wxASSERT( item2 );
    item1->Add( item2, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item1->Add( 320, 20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxWindow *item3 = parent->FindWindow( ID_MAIN_INVENTORY );
    wxASSERT( item3 );
    item1->Add( item3, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 20 );

    wxWindow *item4 = parent->FindWindow( ID_MAIN_SALES );
    wxASSERT( item4 );
    item1->Add( item4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 20 );

    wxWindow *item5 = parent->FindWindow( ID_MAIN_CUSTOMER );
    wxASSERT( item5 );
    item1->Add( item5, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 20 );

    wxWindow *item6 = parent->FindWindow( ID_MAIN_REPORTS );
    wxASSERT( item6 );
    item1->Add( item6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 20 );

    wxWindow *item7 = parent->FindWindow( ID_MAIN_EMPLOYEE );
    wxASSERT( item7 );
    item1->Add( item7, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 20 );

    wxWindow *item8 = parent->FindWindow( ID_MAIN_LOGOUT );
    wxASSERT( item8 );
    item1->Add( item8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 20 );

    item0->Add( item1, 0, wxGROW|wxALL, 5 );

    YardFooter *item9 = new YardFooter( parent, ID_PANEL, wxDefaultPosition, wxSize(200,90), 0 );
    item0->Add( item9, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *Sale( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 1, 0, 0 );
    item0->AddGrowableCol( 0 );
    item0->AddGrowableRow( 0 );

    wxFlexGridSizer *item1 = new wxFlexGridSizer( 2, 0, 0 );
    item1->AddGrowableCol( 0 );
    item1->AddGrowableRow( 0 );

    wxFlexGridSizer *item2 = new wxFlexGridSizer( 1, 0, 0 );
    item2->AddGrowableCol( 0 );
    item2->AddGrowableRow( 1 );

    wxStaticBox *item4 = new wxStaticBox( parent, -1, wxT("Customer") );
    wxStaticBoxSizer *item3 = new wxStaticBoxSizer( item4, wxVERTICAL );

    wxFlexGridSizer *item5 = new wxFlexGridSizer( 2, 0, 0 );

    wxStaticText *item6 = new wxStaticText( parent, ID_TEXT, wxT("First Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item7 = new wxStaticText( parent, ID_TEXT, wxT("William"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item8 = new wxStaticText( parent, ID_TEXT, wxT("Middle Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item9 = new wxStaticText( parent, ID_TEXT, wxT("Joe"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item10 = new wxStaticText( parent, ID_TEXT, wxT("Last Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item11 = new wxStaticText( parent, ID_TEXT, wxT("Smith"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item12 = new wxStaticText( parent, ID_TEXT, wxT("Address 1"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item12, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item13 = new wxStaticText( parent, ID_TEXT, wxT("256 Elderberry Lane"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item14 = new wxStaticText( parent, ID_TEXT, wxT("Address 2"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item14, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item15 = new wxStaticText( parent, ID_TEXT, wxT("Apt 33"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item3->Add( item5, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxButton *item16 = new wxButton( parent, ID_BUTTON, wxT("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item16, 0, wxALIGN_CENTER|wxALL, 5 );

    item2->Add( item3, 0, wxGROW|wxALL, 5 );

    wxFlexGridSizer *item17 = new wxFlexGridSizer( 2, 0, 0 );
    item17->AddGrowableCol( 0 );
    item17->AddGrowableRow( 0 );

    wxTreeCtrl *item18 = new wxTreeCtrl( parent, ID_TREECTRL, wxDefaultPosition, wxSize(350,160), wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxSUNKEN_BORDER );
    item17->Add( item18, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item2->Add( item17, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL, 5 );

    item1->Add( item2, 0, wxGROW, 5 );

    wxStaticBox *item20 = new wxStaticBox( parent, -1, wxT("Transaction") );
    wxStaticBoxSizer *item19 = new wxStaticBoxSizer( item20, wxHORIZONTAL );

    wxFlexGridSizer *item21 = new wxFlexGridSizer( 1, 0, 0 );
    item21->AddGrowableCol( 0 );
    item21->AddGrowableRow( 0 );

    wxListCtrl *item22 = new wxListCtrl( parent, ID_SALE_TRANS, wxDefaultPosition, wxSize(260,120), wxLC_REPORT|wxSUNKEN_BORDER );
    item21->Add( item22, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxWindow *item23 = parent->FindWindow( ID_SALE_TRASH );
    wxASSERT( item23 );
    item21->Add( item23, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item19->Add( item21, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item1->Add( item19, 0, wxGROW|wxALL, 5 );

    item0->Add( item1, 0, wxGROW, 5 );

    YardFooter *item24 = new YardFooter( parent, ID_PANEL, wxDefaultPosition, wxSize(200,90), 0 );
    item0->Add( item24, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *NumberPad( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 1, 0, 0 );
    item0->AddGrowableCol( 0 );

    wxTextCtrl *item1 = new wxTextCtrl( parent, ID_CALC_SCREEN, wxT(""), wxDefaultPosition, wxSize(80,40), wxTE_READONLY );
    item1->SetFont( wxFont( 22, wxROMAN, wxNORMAL, wxNORMAL ) );
    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxFlexGridSizer *item2 = new wxFlexGridSizer( 4, 0, 0 );

    wxButton *item3 = new wxButton( parent, ID_CALC_1, wxT("1"), wxDefaultPosition, wxSize(64,64), 0 );
    item3->SetFont( wxFont( 25, wxROMAN, wxNORMAL, wxNORMAL ) );
    item2->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item4 = new wxButton( parent, ID_CALC_2, wxT("2"), wxDefaultPosition, wxSize(64,64), 0 );
    item4->SetFont( wxFont( 25, wxROMAN, wxNORMAL, wxNORMAL ) );
    item2->Add( item4, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item5 = new wxButton( parent, ID_CALC_3, wxT("3"), wxDefaultPosition, wxSize(64,64), 0 );
    item5->SetFont( wxFont( 25, wxROMAN, wxNORMAL, wxNORMAL ) );
    item2->Add( item5, 0, wxALIGN_CENTER|wxALL, 5 );

    wxWindow *item6 = parent->FindWindow( ID_CALC_PLUS );
    wxASSERT( item6 );
    item2->Add( item6, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item7 = new wxButton( parent, ID_CALC_4, wxT("4"), wxDefaultPosition, wxSize(64,64), 0 );
    item7->SetFont( wxFont( 25, wxROMAN, wxNORMAL, wxNORMAL ) );
    item2->Add( item7, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item8 = new wxButton( parent, ID_CALC_5, wxT("5"), wxDefaultPosition, wxSize(64,64), 0 );
    item8->SetFont( wxFont( 25, wxROMAN, wxNORMAL, wxNORMAL ) );
    item2->Add( item8, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item9 = new wxButton( parent, ID_CALC_6, wxT("6"), wxDefaultPosition, wxSize(64,64), 0 );
    item9->SetFont( wxFont( 25, wxROMAN, wxNORMAL, wxNORMAL ) );
    item2->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );

    wxWindow *item10 = parent->FindWindow( ID_CALC_MINUS );
    wxASSERT( item10 );
    item2->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item11 = new wxButton( parent, ID_CALC_7, wxT("7"), wxDefaultPosition, wxSize(64,64), 0 );
    item11->SetFont( wxFont( 25, wxROMAN, wxNORMAL, wxNORMAL ) );
    item2->Add( item11, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item12 = new wxButton( parent, ID_CALC_8, wxT("8"), wxDefaultPosition, wxSize(64,64), 0 );
    item12->SetFont( wxFont( 25, wxROMAN, wxNORMAL, wxNORMAL ) );
    item2->Add( item12, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item13 = new wxButton( parent, ID_CALC_9, wxT("9"), wxDefaultPosition, wxSize(64,64), 0 );
    item13->SetFont( wxFont( 25, wxROMAN, wxNORMAL, wxNORMAL ) );
    item2->Add( item13, 0, wxALIGN_CENTER|wxALL, 5 );

    wxWindow *item14 = parent->FindWindow( ID_CALC_EQUALS );
    wxASSERT( item14 );
    item2->Add( item14, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item15 = new wxButton( parent, ID_CALC_CLEAR, wxT("C"), wxDefaultPosition, wxSize(50,64), 0 );
    item15->SetFont( wxFont( 25, wxROMAN, wxNORMAL, wxNORMAL ) );
    item2->Add( item15, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item16 = new wxButton( parent, ID_CALC_0, wxT("0"), wxDefaultPosition, wxSize(64,64), 0 );
    item16->SetFont( wxFont( 25, wxROMAN, wxNORMAL, wxNORMAL ) );
    item2->Add( item16, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    wxButton *item17 = new wxButton( parent, ID_CALC_DOT, wxT("."), wxDefaultPosition, wxSize(50,64), 0 );
    item17->SetFont( wxFont( 25, wxROMAN, wxNORMAL, wxNORMAL ) );
    item2->Add( item17, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item2, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT|wxBOTTOM, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *Employee( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 1, 0, 0 );
    item0->AddGrowableCol( 0 );
    item0->AddGrowableRow( 0 );

    wxFlexGridSizer *item1 = new wxFlexGridSizer( 2, 0, 0 );
    item1->AddGrowableCol( 1 );
    item1->AddGrowableRow( 0 );

    wxTreeCtrl *item2 = new wxTreeCtrl( parent, ID_EMPLOY_TREE, wxDefaultPosition, wxSize(120,160), wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxSUNKEN_BORDER );
    item1->Add( item2, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    wxFlexGridSizer *item3 = new wxFlexGridSizer( 1, 0, 0 );
    item3->AddGrowableCol( 0 );
    item3->AddGrowableRow( 1 );

    wxFlexGridSizer *item4 = new wxFlexGridSizer( 2, 0, 0 );

    wxWindow *item5 = parent->FindWindow( ID_EMPLOY_PICTURE );
    wxASSERT( item5 );
    item4->Add( item5, 0, wxALL, 5 );

    wxBoxSizer *item6 = new wxBoxSizer( wxVERTICAL );

    wxStaticText *item7 = new wxStaticText( parent, ID_EMPLOY_HIRE, wxT("Hire date: 1/8/81"), wxDefaultPosition, wxDefaultSize, 0 );
    item6->Add( item7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item8 = new wxStaticText( parent, ID_EMPLOY_POSITION, wxT("Title: Manager"), wxDefaultPosition, wxDefaultSize, 0 );
    item6->Add( item8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item4->Add( item6, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item3->Add( item4, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxFlexGridSizer *item9 = new wxFlexGridSizer( 4, 0, 0 );
    item9->AddGrowableCol( 1 );
    item9->AddGrowableCol( 3 );

    wxStaticText *item10 = new wxStaticText( parent, ID_TEXT, wxT("First Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item9->Add( item10, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item11 = new wxTextCtrl( parent, ID_EMPLOY_FIRST, wxT(""), wxDefaultPosition, wxSize(100,-1), 0 );
    item9->Add( item11, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item12 = new wxStaticText( parent, ID_TEXT, wxT("ID"), wxDefaultPosition, wxDefaultSize, 0 );
    item9->Add( item12, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item13 = new wxTextCtrl( parent, ID_EMPLOY_ID, wxT(""), wxDefaultPosition, wxSize(100,-1), 0 );
    item9->Add( item13, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item14 = new wxStaticText( parent, ID_TEXT, wxT("Middle"), wxDefaultPosition, wxDefaultSize, 0 );
    item9->Add( item14, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item15 = new wxTextCtrl( parent, ID_EMPLOY_MIDDLE, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item9->Add( item15, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item16 = new wxStaticText( parent, ID_TEXT, wxT("Tax ID"), wxDefaultPosition, wxDefaultSize, 0 );
    item9->Add( item16, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item17 = new wxTextCtrl( parent, ID_EMPLOY_TAX_ID, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item9->Add( item17, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item18 = new wxStaticText( parent, ID_TEXT, wxT("Last Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item9->Add( item18, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item19 = new wxTextCtrl( parent, ID_EMPLOY_LAST, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item9->Add( item19, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item20 = new wxStaticText( parent, ID_TEXT, wxT("Phone"), wxDefaultPosition, wxDefaultSize, 0 );
    item9->Add( item20, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item21 = new wxTextCtrl( parent, ID_EMPLOY_PHONE, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item9->Add( item21, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item22 = new wxStaticText( parent, ID_TEXT, wxT("Address"), wxDefaultPosition, wxDefaultSize, 0 );
    item9->Add( item22, 0, wxALIGN_RIGHT|wxALL, 5 );

    wxTextCtrl *item23 = new wxTextCtrl( parent, ID_EMPLOY_ADDRESS, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_MULTILINE );
    item9->Add( item23, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item3->Add( item9, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item1->Add( item3, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item0->Add( item1, 0, 0, 5 );

    YardFooter *item24 = new YardFooter( parent, ID_PANEL, wxDefaultPosition, wxSize(200,90), 0 );
    item0->Add( item24, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *DebugScreen( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 1, 0, 0 );
    item0->AddGrowableCol( 0 );
    item0->AddGrowableRow( 0 );
    item0->AddGrowableRow( 1 );

    YardLog *item1 = new YardLog( parent, ID_DEBUG_LOG, wxDefaultPosition, wxSize(160,120), wxLC_REPORT|wxSUNKEN_BORDER );
    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item2 = new wxTextCtrl( parent, ID_DEBUG_SQL, wxT(""), wxDefaultPosition, wxSize(80,40), wxTE_MULTILINE|wxTE_READONLY );
    item0->Add( item2, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxFlexGridSizer *item3 = new wxFlexGridSizer( 4, 0, 0 );

    wxButton *item4 = new wxButton( parent, ID_DEBUG_DB_CONNECT, wxT("Connect to DB"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->SetDefault();
    item3->Add( item4, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item5 = new wxButton( parent, ID_DEBUG_DB_DISC, wxT("Disconnect"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item5, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticText *item6 = new wxStaticText( parent, ID_TEXT, wxT("User"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item6, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item7 = new wxTextCtrl( parent, ID_DEBUG_USER, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item3->Add( item7, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticText *item8 = new wxStaticText( parent, ID_TEXT, wxT("DSN"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item8, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item9 = new wxTextCtrl( parent, ID_DEBUG_DSN, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item3->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticText *item10 = new wxStaticText( parent, ID_TEXT, wxT("Password"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item10, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item11 = new wxTextCtrl( parent, ID_DEBUG_PASS, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_PASSWORD );
    item3->Add( item11, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *InfoFooter( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 7, 0, 0 );
    item0->AddGrowableCol( 4 );

    wxWindow *item1 = parent->FindWindow( ID_FOOTER_BACK );
    wxASSERT( item1 );
    item0->Add( item1, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( 15, 20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxWindow *item2 = parent->FindWindow( ID_FOOTER_CALC );
    wxASSERT( item2 );
    item0->Add( item2, 0, wxALIGN_CENTER|wxALL, 5 );

    wxWindow *item3 = parent->FindWindow( ID_FOOTER_KEY );
    wxASSERT( item3 );
    item0->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( 20, 20, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item4 = new wxStaticText( parent, ID_FOOTER_TIME, wxT("9:24 pm"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->SetFont( wxFont( 18, wxROMAN, wxNORMAL, wxNORMAL ) );
#if defined(__WXMSW__) && !(wxCHECK_VERSION(2,3,0))
    item4->SetSize( item4->GetBestSize() );
#endif
    item0->Add( item4, 0, wxALIGN_CENTER|wxALL, 5 );

    wxWindow *item5 = parent->FindWindow( ID_FOOTER_UNDO );
    wxASSERT( item5 );
    item0->Add( item5, 0, wxALIGN_CENTER|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *Config( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 1, 0, 0 );
    item0->AddGrowableCol( 0 );
    item0->AddGrowableRow( 0 );

    wxNotebook *item2 = new wxNotebook( parent, ID_NOTEBOOK, wxDefaultPosition, wxSize(200,160), wxNB_LEFT );
    wxNotebookSizer *item1 = new wxNotebookSizer( item2 );

    wxPanel *item3 = new wxPanel( item2, -1 );
    ConfigDB( item3, FALSE );
    item2->AddPage( item3, wxT("Database") );

    wxPanel *item4 = new wxPanel( item2, -1 );
    ConfigLog( item4, FALSE );
    item2->AddPage( item4, wxT("Log") );

    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxFlexGridSizer *item5 = new wxFlexGridSizer( 2, 0, 0 );

    wxButton *item6 = new wxButton( parent, ID_CONFIG_SAVE, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item6, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item7 = new wxButton( parent, ID_CONFIG_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item7, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item5, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *ConfigDB( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 2, 0, 0 );

    wxStaticText *item1 = new wxStaticText( parent, ID_TEXT, wxT("Username"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item1, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item2 = new wxTextCtrl( parent, ID_CONFIG_DB_USER, wxT(""), wxDefaultPosition, wxSize(130,-1), 0 );
    item0->Add( item2, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item3 = new wxStaticText( parent, ID_TEXT, wxT("Password"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item3, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item4 = new wxTextCtrl( parent, ID_CONFIG_DB_PWORD, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_PASSWORD );
    item0->Add( item4, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item0->Add( 20, 20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxString strs5[] = 
    {
        wxT("ODBC"), 
        wxT("ODBC (MySQL)")
    };
    wxRadioBox *item5 = new wxRadioBox( parent, ID_CONFIG_DB_TYPE, wxT("Database"), wxDefaultPosition, wxDefaultSize, 2, strs5, 1, wxRA_SPECIFY_COLS );
    item0->Add( item5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item6 = new wxStaticText( parent, ID_TEXT, wxT("Driver"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item6, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxFlexGridSizer *item7 = new wxFlexGridSizer( 3, 0, 0 );

    wxTextCtrl *item8 = new wxTextCtrl( parent, ID_CONFIG_DB_DRIVER, wxT(""), wxDefaultPosition, wxSize(110,-1), 0 );
    item7->Add( item8, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item9 = new wxButton( parent, ID_CONFIG_DB_BROWSE, wxT("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
    item7->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item7, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxStaticText *item10 = new wxStaticText( parent, ID_TEXT, wxT("Datasource"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item10, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item11 = new wxTextCtrl( parent, ID_CONFIG_DB_DSN, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item0->Add( item11, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item12 = new wxStaticText( parent, ID_TEXT, wxT("Server"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item12, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item13 = new wxTextCtrl( parent, ID_CONFIG_DB_SERVER, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item0->Add( item13, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item14 = new wxStaticText( parent, ID_TEXT, wxT("Port"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item14, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxSpinCtrl *item15 = new wxSpinCtrl( parent, ID_CONFIG_DB_PORT, wxT("0"), wxDefaultPosition, wxSize(100,-1), wxSP_WRAP, 1, 64000, 0 );
    item0->Add( item15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *ConfigLog( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 1, 0, 0 );
    item0->AddGrowableCol( 0 );
    item0->AddGrowableRow( 0 );

    wxListCtrl *item1 = new wxListCtrl( parent, ID_LISTCTRL, wxDefaultPosition, wxSize(160,120), wxLC_REPORT|wxSUNKEN_BORDER );
    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

// Implement menubar functions

// Implement toolbar functions

// Implement bitmap functions


// End of generated file
