#ifndef YARDSALE_MAIN_H
#define YARDSALE_MAIN_H

class YardMain: public wxFrame {
    public:
        
    YardMain(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxSIMPLE_BORDER|wxFRAME_NO_TASKBAR);
        
    ~YardMain();
    
    void OnLogout(wxCommandEvent & event);
    void OnMax(wxCommandEvent & event);
    
    private:
        
    wxBitmap * m_enlarge;
    wxBitmap * m_shrink;
    wxBitmapButton * m_maxButt;
    bool m_max; // is the screen maxed
        
    DECLARE_EVENT_TABLE()
};

#endif
