#ifndef YS_DEBUG_SCREEN_H
#define YS_DEBUG_SCREEN_H

#include "wx/frame.h"

class YardDebugScreen: public wxFrame {
 public:
        
    YardDebugScreen(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxRESIZE_BORDER|wxFRAME_NO_TASKBAR);
        
    virtual ~YardDebugScreen();
    
    void OnConnect(wxCommandEvent& event);
    void OnDisc(wxCommandEvent& event);
    
 private:
        
    DECLARE_EVENT_TABLE()
    
};

#endif
