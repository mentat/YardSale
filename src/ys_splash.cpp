#include "wx/frame.h"
#include "wx/image.h"
#include "wx/statbmp.h"

#include "yardsale_wdr.h"
#include "ys_splash.h"

enum {
    ID_SPLASH_TIMER = 22330
};

BEGIN_EVENT_TABLE(YardSplash, wxFrame)
    EVT_TIMER(ID_SPLASH_TIMER, YardSplash::OnTimer)
    EVT_LEFT_DOWN(YardSplash::OnClick)
END_EVENT_TABLE()

YardSplash::YardSplash(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style)
:wxFrame(parent, id, title, pos, size, style) {
    
    wxPanel * panel = new wxPanel(this);
    
    wxImage::AddHandler(new wxPNGHandler);
    //wxBitmap logo("logo.png", wxBITMAP_TYPE_PNG); 
    m_logo = new wxBitmap("images/logo.png", wxBITMAP_TYPE_PNG); 
    m_bitmap = new wxStaticBitmap(panel, ID_SPLASH_LOGO, *m_logo, wxDefaultPosition);
    
    wxSizer * sizer = Splash(panel, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    {   // write the version number to the bitmap, its cute
        wxMemoryDC fun;
        wxString txt;
        fun.SelectObject(*m_logo);
        fun.SetTextForeground(*wxWHITE);
        wxFont font(10, wxSWISS, wxNORMAL, wxBOLD);
        fun.SetFont(font);
        txt.Printf(wxT("YardSale: %.3f %s"), 0.111, "alpha");
        fun.DrawText(txt,75,180);

    }
    
    int y;
    GetClientSize(&m_limit, &y);
    
    m_progress=20;
    m_limit-=35;
    
    m_timer = new wxTimer(this, ID_SPLASH_TIMER);
    m_timer->Start(50);
    
}

YardSplash::~YardSplash() {
    delete m_logo;
}

void YardSplash::Bump(unsigned int amount) {

   
}

void YardSplash::OnClick(wxMouseEvent& event) {
    //m_gauge->SetValue(m_gauge->GetValue() + 10);

}

void YardSplash::OnTimer(wxTimerEvent& event) {
    
    if (m_progress >= m_limit) {
        m_timer->Stop();
        Destroy();
    }
    
    wxMemoryDC fun;
    fun.SelectObject(*m_logo);
    //wxClientDC fun(m_bitmap);

    fun.SetPen(*wxGREEN_PEN);
    fun.DrawRectangle(m_progress, 150, 1, 20);
    m_progress++;
    Refresh(false);
}
