#include "wx/panel.h"
#include "wx/textctrl.h"
#include "wx/log.h"
#include "wx/sizer.h"
#include "wx/dcmemory.h"
#include "wx/statbmp.h"
#include "wx/bitmap.h"
#include "extra/xrc/xmlres.h"

#include "yardsale.h"
#include "ys_build.h"
#include "ys_login.h"
#include "ys_about_gl.h"
#include "ys_config.h"

#define LOGO_OFFSET_FROM_BOTTOM 30
#define LOGO_OFFSET_FROM_LEFT 10

BEGIN_EVENT_TABLE(YardLogin, wxDialog)
    EVT_BUTTON(XRCID("ID_LOGIN_LOGIN"), YardLogin::OnLogin)
    EVT_BUTTON(XRCID("ID_LOGIN_EXIT"), YardLogin::OnExitButton)
    EVT_BUTTON(XRCID("ID_LOGIN_CONFIG"), YardLogin::OnConfig)
END_EVENT_TABLE()

YardLogin::YardLogin(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style)
:wxDialog(parent, id, title, pos, size, style) {
    
    wxXmlResource::Get()->Load("res/login.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "Login");
    wxSizer * sizer = panel->GetSizer();

    
    {
        wxStaticBitmap* bitmap = static_cast<wxStaticBitmap*>(FindWindow(XRCID("ID_LOGIN_LOGO")));
        wxBitmap logo = bitmap->GetBitmap();
        wxMemoryDC fun;
        wxString txt;
        fun.SelectObject(logo);
        fun.SetTextForeground(*wxWHITE);
        txt.Printf(wxT("YardSale: %.3f \"%s\" (%s, %s)"), 
            GetVersion(), YS_CODENAME, YS_OS, YS_BUILD_MODE);
        fun.DrawText(txt, LOGO_OFFSET_FROM_LEFT,logo.GetHeight() - LOGO_OFFSET_FROM_BOTTOM);
    }
    
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
   
    Centre();
    
    YardAboutGL * about = new YardAboutGL(this, -1, wxT("About YardSale"));
    about->ShowModal();
    about->Destroy();
}

YardLogin::~YardLogin()
{
    
}

void YardLogin::OnExitButton(wxCommandEvent & event)
{
    wxLogDebug(wxT("OnExitButton"));
    EndModal(1);
    
}

void YardLogin::OnConfig(wxCommandEvent & event)
{
    wxLogDebug(wxT("OnConfig"));
    YardConfig * conf = new YardConfig(this, -1, wxT("YardSale Configuration"));
    conf->ShowModal();
    conf->Destroy();
    
}

void YardLogin::OnLogin(wxCommandEvent & event)
{
    wxLogDebug(wxT("OnLogin"));
    
    /// @todo This will segfault if the XRC is modified to a diff ID string
    m_user = static_cast<wxTextCtrl*>(FindWindow(XRCID("ID_LOGIN_USER")))->GetValue();
    m_pass = static_cast<wxTextCtrl*>(FindWindow(XRCID("ID_LOGIN_PASSWORD")))->GetValue();

    if (m_user.length() == 0)
    {
        wxLogDebug(wxT("Empty username"));
        // show message box saying cant have empty username/pass
        //wxMessageBox(
        return;
    }
    if (m_pass.length() == 0)
    {
        wxLogDebug(wxT("Empty password"));
        return;
    }
    
    EndModal(0);
    
}
