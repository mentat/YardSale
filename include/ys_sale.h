#ifndef YS_SALE_H
#define YS_SALE_H

class YardSaleScreen: public wxFrame{
    public:
        
    YardSaleScreen(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxRESIZE_BORDER);
        
    virtual ~YardSaleScreen();
    
    void OnExitButton(wxCommandEvent & event);
    
    private:
        
    DECLARE_EVENT_TABLE()
        
};

#endif
