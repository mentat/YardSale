#ifndef YARDSALE_SPLASH_H
#define YARDSALE_SPLASH_H

#include "wx/wx.h"

class YardSplash: public wxDialog {
    public:
        
    YardSplash(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxSTAY_ON_TOP);
        
    ~YardSplash();
    
    void OnClick(wxMouseEvent& event);
    void OnTimer(wxTimerEvent& event);
    
    void Bump(unsigned int amount = 10);
    
    private:
        
    int m_progress;
    int m_limit;
    
    wxBitmap * m_logo;
    
    wxStaticBitmap * m_bitmap;
    wxTimer * m_timer;
    
    DECLARE_EVENT_TABLE()
};


#endif
