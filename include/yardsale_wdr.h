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
#define ID_INV_FREIGHT 10024
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
#define ID_CALC_DONE 10059
wxSizer *NumberPad( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_EMPLOY_TREE 10060
#define ID_EMPLOY_PICTURE 10061
#define ID_EMPLOY_HIRE 10062
#define ID_EMPLOY_POSITION 10063
#define ID_EMPLOY_FIRST 10064
#define ID_EMPLOY_ID 10065
#define ID_EMPLOY_MIDDLE 10066
#define ID_EMPLOY_TAX_ID 10067
#define ID_EMPLOY_LAST 10068
#define ID_EMPLOY_PHONE 10069
#define ID_EMPLOY_ADDRESS 10070
wxSizer *Employee( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_DEBUG_LOG 10071
#define ID_DEBUG_SQL 10072
#define ID_DEBUG_DB_CONNECT 10073
#define ID_DEBUG_DB_DISC 10074
#define ID_DEBUG_USER 10075
#define ID_DEBUG_DSN 10076
#define ID_DEBUG_PASS 10077
wxSizer *DebugScreen( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_FOOTER_BACK 10078
#define ID_FOOTER_CALC 10079
#define ID_FOOTER_KEY 10080
#define ID_FOOTER_TIME 10081
#define ID_FOOTER_UNDO 10082
wxSizer *InfoFooter( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_NOTEBOOK 10083
#define ID_CONFIG_SAVE 10084
#define ID_CONFIG_CANCEL 10085
wxSizer *Config( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_CONFIG_DB_USER 10086
#define ID_CONFIG_DB_PWORD 10087
#define ID_CONFIG_DB_TYPE 10088
#define ID_CONFIG_DB_DRIVER 10089
#define ID_CONFIG_DB_BROWSE 10090
#define ID_CONFIG_DB_DSN 10091
#define ID_CONFIG_DB_SERVER 10092
#define ID_CONFIG_DB_PORT 10093
wxSizer *ConfigDB( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_LISTCTRL 10094
wxSizer *ConfigLog( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_KBD_SCREEN 10095
#define ID_KBD_1 10096
#define ID_KBD_2 10097
#define ID_KBD_3 10098
#define ID_KBD_4 10099
#define ID_KBD_5 10100
#define ID_KBD_6 10101
#define ID_KBD_7 10102
#define ID_KBD_8 10103
#define ID_KBD_9 10104
#define ID_KBD_0 10105
#define ID_KBD_Q 10106
#define ID_KBD_W 10107
#define ID_KBD_E 10108
#define ID_KBD_R 10109
#define ID_KBD_T 10110
#define ID_KBD_Y 10111
#define ID_KBD_U 10112
#define ID_KBD_I 10113
#define ID_KBD_O 10114
#define ID_KBD_P 10115
#define ID_KBD_A 10116
#define ID_KBD_S 10117
#define ID_KBD_D 10118
#define ID_KBD_F 10119
#define ID_KBD_G 10120
#define ID_KBD_H 10121
#define ID_KBD_J 10122
#define ID_KBD_K 10123
#define ID_KBD_L 10124
#define ID_KBD_CAPS 10125
#define ID_KBD_Z 10126
#define ID_KBD_X 10127
#define ID_KBD_C 10128
#define ID_KBD_V 10129
#define ID_KBD_B 10130
#define ID_KBD_N 10131
#define ID_KBD_M 10132
#define ID_KBD_COMMA 10133
#define ID_KBD_PERIOD 10134
#define ID_KBD_DELETE 10135
#define ID_KBD_CLEAR 10136
#define ID_KBD_SPACE 10137
#define ID_KBD_DONE 10138
wxSizer *Keyboard( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

// Declare toolbar functions

// Declare bitmap functions

#endif

// End of generated file
