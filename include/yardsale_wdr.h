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
#define ID_LOGIN_LOGIN 10005
#define ID_LOGIN_EXIT 10006
wxSizer *Login( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_MAIN_INVENTORY 10007
#define ID_MAIN_SALES 10008
#define ID_MAIN_CUSTOMER 10009
#define ID_MAIN_REPORTS 10010
#define ID_MAIN_EMPLOYEE 10011
#define ID_MAIN_LOGOUT 10012
wxSizer *MainText( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_INV_SKU 10013
#define ID_INV_ITEMNAME 10014
#define ID_INV_DEPARTMENT 10015
#define ID_INV_TYPE 10016
#define ID_INV_PRICE 10017
#define ID_INV_WHOLESALE 10018
#define ID_INV_WEIGHT 10019
#define ID_INV_VENDOR 10020
#define ID_INV_TAX_TYPE 10021
#define ID_INV_BARCODE 10022
#define ID_INV_DESC 10023
#define ID_INV_FRIEGHT 10024
#define ID_INV_OVERSIZE 10025
#define ID_INV_ONHAND 10026
#define ID_INV_ONORDER 10027
#define ID_INV_REORDER_LEVEL 10028
#define ID_INV_NEW 10029
#define ID_INV_SEARCH 10030
#define ID_INV_CLEAR 10031
#define ID_LINE 10032
#define ID_INV_SAVE 10033
#define ID_INV_CANCEL 10034
#define ID_INV_CLEAR_RESULTS 10035
#define ID_INV_LIST 10036
#define ID_PANEL 10037
wxSizer *Inventory( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_MAIN_LOGO 10038
wxSizer *Main( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_BUTTON 10039
#define ID_TREECTRL 10040
#define ID_SALE_TRANS 10041
#define ID_SALE_TRASH 10042
wxSizer *Sale( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_CALC_SCREEN 10043
#define ID_CALC_1 10044
#define ID_CALC_2 10045
#define ID_CALC_3 10046
#define ID_CALC_PLUS 10047
#define ID_CALC_4 10048
#define ID_CALC_5 10049
#define ID_CALC_6 10050
#define ID_CALC_MINUS 10051
#define ID_CALC_7 10052
#define ID_CALC_8 10053
#define ID_CALC_9 10054
#define ID_CALC_EQUALS 10055
#define ID_CALC_CLEAR 10056
#define ID_CALC_0 10057
#define ID_CALC_DOT 10058
wxSizer *NumberPad( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_EMPLOY_TREE 10059
#define ID_EMPLOY_PICTURE 10060
#define ID_EMPLOY_HIRE 10061
#define ID_EMPLOY_POSITION 10062
#define ID_EMPLOY_FIRST 10063
#define ID_EMPLOY_ID 10064
#define ID_EMPLOY_MIDDLE 10065
#define ID_EMPLOY_TAX_ID 10066
#define ID_EMPLOY_LAST 10067
#define ID_EMPLOY_PHONE 10068
#define ID_EMPLOY_ADDRESS 10069
wxSizer *Employee( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_DEBUG_LOG 10070
#define ID_DEBUG_SQL 10071
#define ID_DEBUG_DB_CONNECT 10072
#define ID_DEBUG_DB_DISC 10073
#define ID_DEBUG_USER 10074
#define ID_DEBUG_DSN 10075
#define ID_DEBUG_PASS 10076
wxSizer *DebugScreen( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_FOOTER_BACK 10077
#define ID_FOOTER_CALC 10078
#define ID_FOOTER_KEY 10079
#define ID_FOOTER_TIME 10080
#define ID_FOOTER_UNDO 10081
wxSizer *InfoFooter( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_NOTEBOOK 10082
#define ID_CONFIG_SAVE 10083
#define ID_CONFIG_CANCEL 10084
wxSizer *Config( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_CONFIG_DB_USER 10085
#define ID_CONFIG_DB_PWORD 10086
#define ID_CONFIG_DB_TYPE 10087
#define ID_CONFIG_DB_DRIVER 10088
#define ID_CONFIG_DB_BROWSE 10089
#define ID_CONFIG_DB_DSN 10090
#define ID_CONFIG_DB_SERVER 10091
#define ID_CONFIG_DB_PORT 10092
wxSizer *ConfigDB( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

#define ID_MENU 10093
#define ID_MAIN_MENU_CONFIG 10094
wxMenuBar *MainBar();

#define ID_CONFIG_DELETE 10095
#define ID_CONFIG_EXIT 10096
wxMenuBar *ConfigBar();

// Declare toolbar functions

// Declare bitmap functions

#endif

// End of generated file
