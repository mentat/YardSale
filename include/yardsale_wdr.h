//------------------------------------------------------------------------------
// Header generated by wxDesigner from file: yardsale.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifndef __WDR_yardsale_H__
#define __WDR_yardsale_H__

#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma interface "yardsale_wdr.h"
#endif

// Include wxWindows' headers

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/image.h>
#include <wx/statline.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/grid.h>

// Declare window functions

#define ID_SPLASH_LOGO 10000
wxSizer *Splash( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_TEXT 10001
#define ID_TEXTCTRL 10002
#define ID_LOGIN_PASSWORD 10003
#define ID_LOGIN_LIST 10004
#define ID_LOGIN_EXIT 10005
#define ID_LOGIN_LOGIN 10006
wxSizer *Login( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_MAIN_INVENTORY 10007
#define ID_MAIN_SALES 10008
#define ID_MAIN_CUSTOMER 10009
#define ID_MAIN_REPORTS 10010
#define ID_MAIN_EMPLOYEE 10011
#define ID_MAIN_LOGOUT 10012
wxSizer *MainText( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_BUTTON 10013
#define ID_LINE 10014
#define ID_LISTCTRL 10015
#define ID_INVENTORY_EXIT 10016
wxSizer *Inventory( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_MAIN_LOGO 10017
wxSizer *Main( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_SALE_DONE 10018
#define ID_SALE_REMOVE 10019
#define ID_SALE_CANCEL 10020
#define ID_SALE_BACK 10021
wxSizer *Sale( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_BITMAPBUTTON 10022
wxSizer *NumberPad( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

// Declare toolbar functions

// Declare bitmap functions

wxBitmap YardBitmaps( size_t index );

#endif

// End of generated file
