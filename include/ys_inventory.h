#ifndef YS_INVENTORY_H
#define YS_INVENTORY_H

#include "wx/wx.h"

class YardInventory: public wxFrame{
    public:
        
    YardInventory(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxSIMPLE_BORDER|wxFRAME_NO_TASKBAR);
        
    virtual ~YardInventory();
    
    void OnExitButton(wxCommandEvent & event);
    
    private:
        
    DECLARE_EVENT_TABLE()
        
};

#endif
