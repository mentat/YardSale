#include "ys_about_gl.h"
#include "wx/wx.h"

#ifdef YS_OGL_ABOUT
#include "extra/glbutton.h"
enum { ID_ABOUT_OK = 14050 };

BEGIN_EVENT_TABLE(YardAboutGL, wxDialog)
    EVT_BUTTON(ID_ABOUT_OK, YardAboutGL::OnOK)
END_EVENT_TABLE()


YardAboutGL::YardAboutGL(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style, const wxString& name)
:wxDialog(parent, id, title, pos, size, style, name) 
{

    wxPanel * panel = new wxPanel(this);
    
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 1, 0, 0 );
    item0->AddGrowableCol( 0 );
    item0->AddGrowableRow( 1 );

    wxStaticText *item1 = new wxStaticText( panel, -1, wxT("YardSale: The Open Point of Sale"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->SetFont( wxFont( 12, wxMODERN, wxNORMAL, wxNORMAL ) );
#if defined(__WXMSW__) && !(wxCHECK_VERSION(2,3,0))
    item1->SetSize( item1->GetBestSize() );
#endif
    item0->Add( item1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
    
    m_gl = new TestGLCanvas(panel, -1, wxDefaultPosition,
      wxSize(400,300));
    
    item0->Add( m_gl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxButton *item3 = new wxButton( panel, ID_ABOUT_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );


    panel->SetAutoLayout( TRUE );
    panel->SetSizer( item0 );
    
    m_gl->LoadLWO("res/flower.lwo" );
    
    item0->SetSizeHints(this);
    SetSize(item0->GetMinSize());

    Centre();
       
}

void YardAboutGL::OnOK(wxCommandEvent& event)
{
    EndModal(0);
}

#endif //YS_OGL_ABOUT
