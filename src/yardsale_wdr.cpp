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

    wxStaticText *item2 = new wxStaticText( parent, ID_TEXT, wxT("SKU"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->Add( item2, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item3 = new wxTextCtrl( parent, ID_INV_SKU, wxT(""), wxDefaultPosition, wxSize(150,-1), 0 );
    item1->Add( item3, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item4 = new wxStaticText( parent, ID_TEXT, wxT("Bar Code"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->Add( item4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item5 = new wxTextCtrl( parent, ID_INV_BARCODE, wxT(""), wxDefaultPosition, wxSize(120,-1), 0 );
    item1->Add( item5, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item6 = new wxStaticText( parent, ID_TEXT, wxT("Item Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->Add( item6, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item7 = new wxTextCtrl( parent, ID_INV_ITEMNAME, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item1->Add( item7, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item8 = new wxStaticText( parent, ID_TEXT, wxT("Price"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->Add( item8, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item9 = new wxTextCtrl( parent, ID_INV_PRICE, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item1->Add( item9, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item10 = new wxStaticText( parent, ID_TEXT, wxT("Description"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->Add( item10, 0, wxALIGN_RIGHT|wxALL, 5 );

    wxTextCtrl *item11 = new wxTextCtrl( parent, ID_INV_DESC, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_MULTILINE );
    item1->Add( item11, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item12 = new wxStaticText( parent, ID_TEXT, wxT("Wholesale"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->Add( item12, 0, wxALIGN_RIGHT|wxALL, 5 );

    wxFlexGridSizer *item13 = new wxFlexGridSizer( 1, 0, 0 );
    item13->AddGrowableCol( 0 );

    wxTextCtrl *item14 = new wxTextCtrl( parent, ID_INV_WHOLESALE, wxT(""), wxDefaultPosition, wxSize(160,-1), 0 );
    item13->Add( item14, 0, wxGROW|wxALL, 5 );

    wxBoxSizer *item15 = new wxBoxSizer( wxHORIZONTAL );

    wxButton *item16 = new wxButton( parent, ID_INV_NEW, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
    item15->Add( item16, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item17 = new wxButton( parent, ID_INV_SEARCH, wxT("Search"), wxDefaultPosition, wxDefaultSize, 0 );
    item15->Add( item17, 0, wxALIGN_CENTER|wxALL, 5 );

    item13->Add( item15, 0, wxALIGN_CENTER, 5 );

    item1->Add( item13, 0, wxGROW, 5 );

    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticLine *item18 = new wxStaticLine( parent, ID_LINE, wxDefaultPosition, wxSize(20,-1), wxLI_HORIZONTAL );
    item0->Add( item18, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxListCtrl *item19 = new wxListCtrl( parent, ID_INV_LIST, wxDefaultPosition, wxSize(160,120), wxLC_REPORT|wxSUNKEN_BORDER );
    item0->Add( item19, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

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

    item0->Add( item1, 0, wxALL, 5 );

    wxPanel *item9 = new wxPanel( parent, ID_PANEL, wxDefaultPosition, wxSize(200,90), 0 );
    item9->SetBackgroundColour( *wxBLUE );
    item0->Add( item9, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

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
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 2, 0, 0 );
    item0->AddGrowableRow( 0 );

    wxFlexGridSizer *item1 = new wxFlexGridSizer( 1, 0, 0 );

    wxStaticBox *item3 = new wxStaticBox( parent, -1, wxT("Customer") );
    wxStaticBoxSizer *item2 = new wxStaticBoxSizer( item3, wxVERTICAL );

    wxFlexGridSizer *item4 = new wxFlexGridSizer( 2, 0, 0 );

    wxStaticText *item5 = new wxStaticText( parent, ID_TEXT, wxT("First Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item6 = new wxStaticText( parent, ID_TEXT, wxT("William"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item7 = new wxStaticText( parent, ID_TEXT, wxT("Middle Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item8 = new wxStaticText( parent, ID_TEXT, wxT("Joe"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item9 = new wxStaticText( parent, ID_TEXT, wxT("Last Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item10 = new wxStaticText( parent, ID_TEXT, wxT("Smith"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item11 = new wxStaticText( parent, ID_TEXT, wxT("Address 1"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item12 = new wxStaticText( parent, ID_TEXT, wxT("256 Elderberry Lane"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item12, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item13 = new wxStaticText( parent, ID_TEXT, wxT("Address 2"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item14 = new wxStaticText( parent, ID_TEXT, wxT("Apt 33"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item14, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item2->Add( item4, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxButton *item15 = new wxButton( parent, ID_BUTTON, wxT("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
    item2->Add( item15, 0, wxALIGN_CENTER|wxALL, 5 );

    item1->Add( item2, 0, wxGROW|wxALL, 5 );

    wxFlexGridSizer *item16 = new wxFlexGridSizer( 2, 0, 0 );
    item16->AddGrowableRow( 0 );

    wxFlexGridSizer *item17 = new wxFlexGridSizer( 1, 0, 0 );

    wxWindow *item18 = parent->FindWindow( ID_SALE_DONE );
    wxASSERT( item18 );
    item17->Add( item18, 0, wxALIGN_CENTER|wxALL, 5 );

    wxWindow *item19 = parent->FindWindow( ID_SALE_REMOVE );
    wxASSERT( item19 );
    item17->Add( item19, 0, wxALIGN_CENTER|wxALL, 5 );

    wxWindow *item20 = parent->FindWindow( ID_SALE_CANCEL );
    wxASSERT( item20 );
    item17->Add( item20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxWindow *item21 = parent->FindWindow( ID_SALE_BACK );
    wxASSERT( item21 );
    item17->Add( item21, 0, wxALIGN_CENTER|wxALL, 5 );

    item16->Add( item17, 0, wxALIGN_CENTER|wxALL, 5 );

    YardCalc *item22 = new YardCalc( parent, ID_SALE_CALC, wxDefaultPosition, wxDefaultSize, 0 );
    item16->Add( item22, 0, wxALIGN_CENTER|wxALL, 5 );

    item1->Add( item16, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL, 5 );

    item0->Add( item1, 0, wxALIGN_CENTER, 5 );

    wxStaticBox *item24 = new wxStaticBox( parent, -1, wxT("Transaction") );
    wxStaticBoxSizer *item23 = new wxStaticBoxSizer( item24, wxHORIZONTAL );

    wxFlexGridSizer *item25 = new wxFlexGridSizer( 1, 0, 0 );
    item25->AddGrowableCol( 0 );
    item25->AddGrowableRow( 0 );

    wxListCtrl *item26 = new wxListCtrl( parent, ID_SALE_TRANS, wxDefaultPosition, wxSize(260,120), wxLC_REPORT|wxSUNKEN_BORDER );
    item25->Add( item26, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item23->Add( item25, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item0->Add( item23, 0, wxGROW|wxALL, 5 );

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
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 2, 0, 0 );
    item0->AddGrowableCol( 1 );
    item0->AddGrowableRow( 0 );

    wxTreeCtrl *item1 = new wxTreeCtrl( parent, ID_EMPLOY_TREE, wxDefaultPosition, wxSize(120,160), wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxSUNKEN_BORDER );
    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    wxFlexGridSizer *item2 = new wxFlexGridSizer( 1, 0, 0 );
    item2->AddGrowableCol( 0 );
    item2->AddGrowableRow( 1 );

    wxFlexGridSizer *item3 = new wxFlexGridSizer( 2, 0, 0 );

    wxWindow *item4 = parent->FindWindow( ID_EMPLOY_PICTURE );
    wxASSERT( item4 );
    item3->Add( item4, 0, wxALL, 5 );

    wxBoxSizer *item5 = new wxBoxSizer( wxVERTICAL );

    wxStaticText *item6 = new wxStaticText( parent, ID_EMPLOY_HIRE, wxT("Hire date: 1/8/81"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item7 = new wxStaticText( parent, ID_EMPLOY_POSITION, wxT("Title: Manager"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item3->Add( item5, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item2->Add( item3, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxFlexGridSizer *item8 = new wxFlexGridSizer( 4, 0, 0 );
    item8->AddGrowableCol( 1 );
    item8->AddGrowableCol( 3 );

    wxStaticText *item9 = new wxStaticText( parent, ID_TEXT, wxT("First Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item8->Add( item9, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item10 = new wxTextCtrl( parent, ID_EMPLOY_FIRST, wxT(""), wxDefaultPosition, wxSize(100,-1), 0 );
    item8->Add( item10, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item11 = new wxStaticText( parent, ID_TEXT, wxT("ID"), wxDefaultPosition, wxDefaultSize, 0 );
    item8->Add( item11, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item12 = new wxTextCtrl( parent, ID_EMPLOY_ID, wxT(""), wxDefaultPosition, wxSize(100,-1), 0 );
    item8->Add( item12, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item13 = new wxStaticText( parent, ID_TEXT, wxT("Middle"), wxDefaultPosition, wxDefaultSize, 0 );
    item8->Add( item13, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item14 = new wxTextCtrl( parent, ID_EMPLOY_MIDDLE, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item8->Add( item14, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item15 = new wxStaticText( parent, ID_TEXT, wxT("Tax ID"), wxDefaultPosition, wxDefaultSize, 0 );
    item8->Add( item15, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item16 = new wxTextCtrl( parent, ID_EMPLOY_TAX_ID, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item8->Add( item16, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item17 = new wxStaticText( parent, ID_TEXT, wxT("Last Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item8->Add( item17, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item18 = new wxTextCtrl( parent, ID_EMPLOY_LAST, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item8->Add( item18, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item19 = new wxStaticText( parent, ID_TEXT, wxT("Phone"), wxDefaultPosition, wxDefaultSize, 0 );
    item8->Add( item19, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item20 = new wxTextCtrl( parent, ID_EMPLOY_PHONE, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item8->Add( item20, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item21 = new wxStaticText( parent, ID_TEXT, wxT("Address"), wxDefaultPosition, wxDefaultSize, 0 );
    item8->Add( item21, 0, wxALIGN_RIGHT|wxALL, 5 );

    wxTextCtrl *item22 = new wxTextCtrl( parent, ID_EMPLOY_ADDRESS, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_MULTILINE );
    item8->Add( item22, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item2->Add( item8, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item0->Add( item2, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

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
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 5, 0, 0 );
    item0->AddGrowableCol( 2 );

    wxWindow *item1 = parent->FindWindow( ID_FOOTER_CALC );
    wxASSERT( item1 );
    item0->Add( item1, 0, wxALIGN_CENTER|wxALL, 5 );

    wxWindow *item2 = parent->FindWindow( ID_FOOTER_KEY );
    wxASSERT( item2 );
    item0->Add( item2, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( 20, 20, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText *item3 = new wxStaticText( parent, ID_FOOTER_TIME, wxT("9:24 pm"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->SetFont( wxFont( 18, wxROMAN, wxNORMAL, wxNORMAL ) );
#if defined(__WXMSW__) && !(wxCHECK_VERSION(2,3,0))
    item3->SetSize( item3->GetBestSize() );
#endif
    item0->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );

    wxWindow *item4 = parent->FindWindow( ID_FOOTER_UNDO );
    wxASSERT( item4 );
    item0->Add( item4, 0, wxALIGN_CENTER|wxALL, 5 );

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
