#ifndef YS_CALC_H
#define YS_CALC_H

class YardCalc: public wxPanel {
    public:
        
    YardCalc(wxWindow* parent, wxWindowID id = -1, 
        const wxPoint& pos = wxDefaultPosition, 
        const wxSize& size = wxDefaultSize, 
        long style = wxTAB_TRAVERSAL, 
        const wxString& name = "YardCalc");
    
    virtual ~YardCalc();
    
    void OnNumber(wxCommandEvent & event);
    void OnPlus(wxCommandEvent & event);
    void OnEqual(wxCommandEvent & event);
    
    private:
        
    DECLARE_EVENT_TABLE()
    
    long int m_number;
    bool m_inAdd;
    wxTextCtrl * m_screen;
};


#endif
