#ifndef YARDSALE_MAIN_H
#define YARDSALE_MAIN_H

/**
 * YardMain is the main menu screen for YardSale, it displays
 * graphical buttons for accessing the inventory, employees, sales,
 * etc.
 */
class YardMain: public wxFrame {
    public:
 
    /**
     * Constructor
     */
    YardMain(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxSIMPLE_BORDER|wxFRAME_NO_TASKBAR);
        
    virtual ~YardMain();
    
    /*-------------Event Handlers------------*/
    /// Logout button event handler
    void OnLogout(wxCommandEvent & event);
    /// Maximize handler
    void OnMax(wxCommandEvent & event);
    /// Inventory button handler
    void OnInventory(wxCommandEvent & event);
    
    private:
        
    /*----------Pointers for Windows---------*/
    
    wxFrame * m_inventory;
    
    /*--------------Debug Stuff--------------*/
        
    wxBitmap * m_enlarge;
    wxBitmap * m_shrink;
    wxBitmapButton * m_maxButt;
    bool m_max; // is the screen maxed
        
    DECLARE_EVENT_TABLE()
};

#endif
