#include "ys_about_gl.h"
#include "wx/wx.h"

#include "ys_build.h"

enum { ID_ABOUT_OK = 14050, ID_TIMER };

BEGIN_EVENT_TABLE(YardAboutGL, wxDialog)
    EVT_BUTTON(ID_ABOUT_OK, YardAboutGL::OnOK)
    EVT_TIMER(ID_TIMER, YardAboutGL::OnTimer)
    EVT_PAINT(YardAboutGL::OnPaint)
    EVT_IDLE(YardAboutGL::OnIdle)
END_EVENT_TABLE()

int GetLines(const wxString& str)
{
    int lines = 0;
    for (int i = 0; i < str.length(); i++)
        if (str[i] == '\n')
            lines++;
    lines++;
    return lines;
}

int GetWidth(const wxString& str)
{
    int width = 0;
    int cur = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != '\n')
            cur++;
        else
            if (cur > width)
                width = cur;
        cur = 0;
    }
            
    return width;
  
}

YardAboutGL::YardAboutGL(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style, const wxString& name)
:wxDialog(parent, id, title, pos, size, style, name), m_timer(0)
{

    //m_bitmap.LoadFile("res/flower.jpg", wxBITMAP_TYPE_JPEG);
    m_cpy.LoadFile("res/flower.jpg", wxBITMAP_TYPE_JPEG);
    SetSize(wxSize(500,400));
    m_font.SetPointSize(20);
    m_y = 400;
    Centre();
    m_text.Printf("YardSale %.3f (%s)\n\nCopyright 2004 ASLS"
                  "\nGNU Public License\n\n"
                  "\nJesse Lovelace\nAdam Parish\nMike Swigon\n"
                  "\nJay Johnston\nJohn Lamb\nCameron Watts\n\n"
                  "\nYardSale uses:\n\nwxWindows\nMySQL\n"
                  "unixODBC\nGDChart\nSablotron", GetVersion(), YS_CODENAME);
    
    wxClientDC  dc(this);
    dc.SetFont(m_font);
    dc.GetTextExtent(m_text, &m_txtWidth, &m_txtHeight);
    /*
    wxLogDebug("1");
    wxMemoryDC memDC;
    wxLogDebug("2");
    
    m_textBmp.Create(m_txtWidth, m_txtHeight);
    memDC.SelectObject(m_textBmp);
    wxBrush brush(*wxBLACK, wxTRANSPARENT);
    memDC.SetBackground(brush);
    memDC.SetBackgroundMode( wxTRANSPARENT);
    memDC.SetTextForeground(*wxWHITE);
    memDC.SetFont(m_font);
    
    wxLogDebug("3");  
    memDC.DrawText(m_text, 0,0);
   // wxMask mask(m_textBmp, *wxBLACK);
    */

    m_timer = new wxTimer(this, ID_TIMER);
    m_timer->Start(50);
       
}

YardAboutGL::~YardAboutGL()
{
    if (m_timer)
    {
        m_timer->Stop();
    }
    
}

void YardAboutGL::OnIdle(wxIdleEvent& event)
{
    
   // Refresh(false);
}

void YardAboutGL::OnTimer(wxTimerEvent& event)
{

    Refresh(false);
}

void YardAboutGL::OnPaint(wxPaintEvent& event)
{

    wxPaintDC dc(this);
    PrepareDC(dc);

    wxMemoryDC memDC;
    memDC.SelectObject(m_cpy);
    //wxMemoryDC txtDC;
    //txtDC.SelectObject(m_textBmp);
  
    int x = 500 - m_txtWidth; // this is start of text

    int bottom = 0;
    
    if ((m_y + m_txtHeight) > 400)
        bottom = 400;
    else
        bottom = m_y + m_txtHeight;
    
    int height = m_txtHeight;
    height += 400; // make height 400 bigger to wrap text
    
    //memDC.Blit(100,m_y, width, vheight, &origDC, 0, 0); // blit in "clear" from orig
    //memDC.Blit(x,0, 500, 400, &origDC, x,0);  
    
    //memDC.SetBackgroundMode( wxTRANSPARENT);
    //memDC.SetTextForeground(*wxWHITE);
    
    m_y = (m_y - 1);
    if (m_y < ((400 - (height))))
        m_y = 400;
    
    wxRegionIterator upd(GetUpdateRegion()); // get the update rect list
    wxRegion mask(0,0,500,400);
    
    while (upd)
    {
        mask.Subtract(upd.GetRect());
        
        upd ++ ;
    }
    mask.Subtract(wxRect(x,m_y,500, bottom));
    
    wxBrush brush(*wxBLACK, wxTRANSPARENT);
    dc.SetBackground(brush);
    dc.DestroyClippingRegion();
    dc.SetClippingRegion(mask);
  
    dc.Blit(0,0, 500, 400, &memDC,0, 0, wxCOPY, true);
    dc.SetBackgroundMode( wxTRANSPARENT);
    dc.SetTextForeground(*wxWHITE);
    dc.SetFont(m_font);
    //dc.SetLogicalFunction(wxINVERT);
    dc.DrawText(m_text, x, m_y);
    //dc.Blit(x,m_y, 500, 400, &txtDC, 0, m_y, wxCOPY, true); 
    //dc.DrawBitmap(m_textBmp, x, m_y, true);
}

void YardAboutGL::OnOK(wxCommandEvent& event)
{
    EndModal(0);
}
