#include "extra/xrc/xmlres.h"
#include "wx/config.h"
#include "wx/panel.h"
#include "wx/button.h"
#include "wx/msgdlg.h"
#include "wx/sizer.h"
#include "wx/log.h"
#include "wx/textctrl.h"
#include "wx/radiobox.h"
#include "wx/spinctrl.h"
#include "wx/filedlg.h"

#include "ys_config.h"

BEGIN_EVENT_TABLE(YardConfig, wxDialog)
    EVT_BUTTON(XRCID("ID_CONFIG_SAVE"), YardConfig::OnSave)
    EVT_BUTTON(XRCID("ID_CONFIG_CANCEL"), YardConfig::OnCancel)
    EVT_BUTTON(XRCID("ID_CONFIG_DB_BROWSE"), YardConfig::OnBrowse)
    //EVT_MENU(ID_CONFIG_EXIT, YardConfig::OnExit)
    //EVT_MENU(ID_CONFIG_DELETE, YardConfig::OnDeleteConfig)
    EVT_TEXT(-1, YardConfig::OnChange)
    EVT_RADIOBOX(-1, YardConfig::OnChange)
    EVT_SPINCTRL(-1, YardConfig::OnChange)
END_EVENT_TABLE()

YardConfig::YardConfig(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos, const wxSize& size, long style)

:wxDialog(parent, id, title, pos, size, style)
{        
    m_construct = true;
    wxXmlResource::Get()->Load("res/config.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "Config");
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    Centre();
    
    wxConfigBase *pConfig = wxConfigBase::Get();
    if (!pConfig)
    {
        wxLogError(wxT("No Config pointer"));
        Destroy(); 
        return;
    }
    
    if (!pConfig->HasGroup(wxT("DB")))
    {/*
        wxLogDebug(wxT("No DB group in config."));
        int answer = wxMessageBox("No configuration exists on this computer,"
            " would you like to create one?", "Create Config",
                            wxYES_NO, this);
        if (answer == wxNO)
        {
            wxLogDebug(wxT("Answer was no."));
            //pConfig->DeleteAll();
            Destroy();
            return;
        }*/
#ifdef __WXDEBUG__
        pConfig->Write(wxT("/DB/User"), wxT(""));
        pConfig->Write(wxT("/DB/Pass"), wxT(""));
#endif
        //All we have is 
        pConfig->Write(wxT("/DB/Type"), (long) ODBC_MYSQL);
        pConfig->Write(wxT("/DB/Driver"), wxT(""));
        pConfig->Write(wxT("/DB/DSN"), wxT(""));
        pConfig->Write(wxT("/DB/Server"), wxT(""));
        pConfig->Write(wxT("/DB/Port"), (long)0);
    }
    
    wxButton * save = static_cast<wxButton *>(FindWindow(XRCID("ID_CONFIG_SAVE")));
    wxTextCtrl * user = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CONFIG_DB_USER")));
    wxTextCtrl * pass = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CONFIG_DB_PWORD")));
    wxRadioBox * type = static_cast<wxRadioBox *>(FindWindow(XRCID("ID_CONFIG_DB_TYPE")));
    wxTextCtrl * driver = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CONFIG_DB_DRIVER")));
    wxTextCtrl * dsn = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CONFIG_DB_DSN")));
    wxTextCtrl * server = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CONFIG_DB_SERVER")));
    wxSpinCtrl * port = static_cast<wxSpinCtrl *>(FindWindow(XRCID("ID_CONFIG_DB_PORT")));

#ifdef __WXDEBUG__    
    user->SetValue(pConfig->Read(wxT("/DB/User"), wxString()));
    pass->SetValue(pConfig->Read(wxT("/DB/Pass"), wxString()));
#else
    /// Disables these if not in debug mode (cause then we login all the time)
    ///  via the login screen
    user->Disable();
    pass->Disable();
#endif
    type->SetSelection(pConfig->Read(wxT("/DB/Type"), 0l));
    driver->SetValue(pConfig->Read(wxT("/DB/Driver"), wxString()));
    dsn->SetValue(pConfig->Read(wxT("/DB/DSN"), wxString()));
    server->SetValue(pConfig->Read(wxT("/DB/Server"), wxString()));
    wxLogDebug(wxT("Port is: %d"), (int)pConfig->Read(wxT("/DB/Port"), 0l));
    port->SetValue((int)pConfig->Read(wxT("/DB/Port"), 0l));
     
    wxButton * cancel = (wxButton *)FindWindow(XRCID("ID_CONFIG_CANCEL"));
    cancel->SetLabel("Close");
        
    save->Disable();
    m_saved = true;
    
    Show();
    m_construct = false;
}
 
YardConfig::~YardConfig()
{}

void YardConfig::OnBrowse(wxCommandEvent& event) {
 
    wxString driver = wxFileSelector(wxT("Select your ODBC driver"), "",
        wxT(""), wxT(""), wxT("*.*"), 0, this);    
}
    
void YardConfig::OnCancel(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnCancel"));
    EndModal(0);
}

void YardConfig::OnSave(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnSave"));
    
    wxConfigBase *pConfig = wxConfigBase::Get();
    if (!pConfig)
    {
        wxLogError(wxT("OnSave::No Config pointer"));
        return;
    }

    wxLogDebug(wxT("Saving DB"));
#ifdef __WXDEBUG__ // only using these fields in debug mode
    wxTextCtrl * user = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CONFIG_DB_USER")));
    wxTextCtrl * pass = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CONFIG_DB_PWORD")));
#endif
    wxRadioBox * type = static_cast<wxRadioBox *>(FindWindow(XRCID("ID_CONFIG_DB_TYPE")));
    wxTextCtrl * driver = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CONFIG_DB_DRIVER")));
    wxTextCtrl * dsn = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CONFIG_DB_DSN")));
    wxTextCtrl * server = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CONFIG_DB_SERVER")));
    wxSpinCtrl * port = static_cast<wxSpinCtrl *>(FindWindow(XRCID("ID_CONFIG_DB_PORT")));

#ifdef __WXDEBUG__
    pConfig->Write(wxT("/DB/User"), user->GetValue());
    pConfig->Write(wxT("/DB/Pass"), pass->GetValue());
#endif
    //All we have is 
    pConfig->Write(wxT("/DB/Type"), (long) type->GetSelection());
    pConfig->Write(wxT("/DB/Driver"), driver->GetValue());
    pConfig->Write(wxT("/DB/DSN"), dsn->GetValue());
    pConfig->Write(wxT("/DB/Server"), server->GetValue());
    pConfig->Write(wxT("/DB/Port"), (long) port->GetValue());

        
    wxButton * save = (wxButton *)FindWindow(XRCID("ID_CONFIG_SAVE"));
    wxButton * cancel = (wxButton *)FindWindow(XRCID("ID_CONFIG_CANCEL"));
    cancel->SetLabel("Close");
    
    save->Disable();
    m_saved = true;
}

void YardConfig::OnExit(wxCommandEvent& event)
{
}


void YardConfig::OnChange(wxCommandEvent& event)
{
    if (m_construct)
        return;
    
    if (m_saved)
    {
        wxLogDebug(wxT("Something changed"));
            
        wxButton * save = (wxButton *)FindWindow(XRCID("ID_CONFIG_SAVE"));
        wxButton * cancel = (wxButton *)FindWindow(XRCID("ID_CONFIG_CANCEL"));
        cancel->SetLabel("Cancel");
    
        save->Enable();
        m_saved = false;
    }
    
}

void YardConfig::OnDeleteConfig(wxCommandEvent& event)
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    if ( pConfig == NULL )
    {
        wxLogError(_T("No config to delete!"));
        return;
    }

    if ( pConfig->DeleteAll() )
    {
        wxLogMessage(_T("Config file/registry key successfully deleted."));

        //delete wxConfigBase::Set(NULL);
        //wxConfigBase::DontCreateOnDemand();
    }
    else
    {
        wxLogError(_T("Deleting config file/registry key failed."));
    }
    
}
