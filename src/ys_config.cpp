#include "wx/config.h"
#include "wx/msgdlg.h"
#include "ys_config.h"
#include "yardsale_wdr.h"


BEGIN_EVENT_TABLE(YardConfig, wxFrame)
    EVT_BUTTON(ID_CONFIG_SAVE, YardConfig::OnSave)
    EVT_BUTTON(ID_CONFIG_CANCEL, YardConfig::OnCancel)
    EVT_BUTTON(ID_CONFIG_DB_BROWSE, YardConfig::OnBrowse)
    EVT_MENU(ID_CONFIG_EXIT, YardConfig::OnExit)
    EVT_MENU(ID_CONFIG_DELETE, YardConfig::OnDeleteConfig)
    EVT_TEXT(-1, YardConfig::OnChange)
    EVT_RADIOBOX(-1, YardConfig::OnChange)
    EVT_SPINCTRL(-1, YardConfig::OnChange)
END_EVENT_TABLE()

YardConfig::YardConfig(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos, const wxSize& size, long style)

:wxFrame(parent, id, title, pos, size, style)
{    
    m_construct = true;
    SetMenuBar(ConfigBar());
    wxPanel * panel = new wxPanel(this);
    
    wxSizer * sizer = Config(panel, false, true);
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
    {
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
        }
        
        pConfig->Write(wxT("/DB/User"), wxT(""));
        pConfig->Write(wxT("/DB/Pass"), wxT(""));
        //All we have is 
        pConfig->Write(wxT("/DB/Type"), (long) ODBC_MYSQL);
        pConfig->Write(wxT("/DB/Driver"), wxT(""));
        pConfig->Write(wxT("/DB/DSN"), wxT(""));
        pConfig->Write(wxT("/DB/Server"), wxT(""));
        pConfig->Write(wxT("/DB/Port"), (long)0);
    }
    
    wxButton * save = (wxButton *)FindWindow(ID_CONFIG_SAVE);
    
    wxTextCtrl * user = (wxTextCtrl *)FindWindow(ID_CONFIG_DB_USER);
    wxTextCtrl * pass = (wxTextCtrl *)FindWindow(ID_CONFIG_DB_PWORD);
    wxRadioBox * type = (wxRadioBox *)FindWindow(ID_CONFIG_DB_TYPE);
    wxTextCtrl * driver = (wxTextCtrl *)FindWindow(ID_CONFIG_DB_DRIVER);
    wxTextCtrl * dsn = (wxTextCtrl *)FindWindow(ID_CONFIG_DB_DSN);
    wxTextCtrl * server = (wxTextCtrl *)FindWindow(ID_CONFIG_DB_SERVER);
    wxSpinCtrl * port = (wxSpinCtrl *)FindWindow(ID_CONFIG_DB_PORT);
    wxASSERT(save);
    wxASSERT(user);
    wxASSERT(pass);
    wxASSERT(type);
    wxASSERT(driver);
    wxASSERT(dsn);
    wxASSERT(server);
    wxASSERT(port);
    
    user->SetValue(pConfig->Read(wxT("/DB/User"), wxString()));
    pass->SetValue(pConfig->Read(wxT("/DB/Pass"), wxString()));
     
    type->SetSelection(pConfig->Read(wxT("/DB/Type"), 0l));
    driver->SetValue(pConfig->Read(wxT("/DB/Driver"), wxString()));
    dsn->SetValue(pConfig->Read(wxT("/DB/DSN"), wxString()));
    server->SetValue(pConfig->Read(wxT("/DB/Server"), wxString()));
    wxLogDebug(wxT("Port is: %d"), (int)pConfig->Read(wxT("/DB/Port"), 0l));
    port->SetValue((int)pConfig->Read(wxT("/DB/Port"), 0l));
        
    save->Disable();
    m_saved = true;
    
    Show();
    m_construct = false;
}
 
YardConfig::~YardConfig()
{}

void YardConfig::OnBrowse(wxCommandEvent& event) {
    
}
    
void YardConfig::OnCancel(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnCancel"));
    Close();
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
    wxTextCtrl * user = (wxTextCtrl *)FindWindow(ID_CONFIG_DB_USER);
    wxTextCtrl * pass = (wxTextCtrl *)FindWindow(ID_CONFIG_DB_PWORD);
    wxRadioBox * type = (wxRadioBox *)FindWindow(ID_CONFIG_DB_TYPE);
    wxTextCtrl * driver = (wxTextCtrl *)FindWindow(ID_CONFIG_DB_DRIVER);
    wxTextCtrl * dsn = (wxTextCtrl *)FindWindow(ID_CONFIG_DB_DSN);
    wxTextCtrl * server = (wxTextCtrl *)FindWindow(ID_CONFIG_DB_SERVER);
    wxSpinCtrl * port = (wxSpinCtrl *)FindWindow(ID_CONFIG_DB_PORT);
    wxASSERT(user);
    wxASSERT(pass);
    wxASSERT(type);
    wxASSERT(driver);
    wxASSERT(dsn);
    wxASSERT(server);
    wxASSERT(port);
    
    pConfig->Write(wxT("/DB/User"), user->GetValue());
    pConfig->Write(wxT("/DB/Pass"), pass->GetValue());
    //All we have is 
    pConfig->Write(wxT("/DB/Type"), (long) type->GetSelection());
    pConfig->Write(wxT("/DB/Driver"), driver->GetValue());
    pConfig->Write(wxT("/DB/DSN"), dsn->GetValue());
    pConfig->Write(wxT("/DB/Server"), server->GetValue());
    pConfig->Write(wxT("/DB/Port"), (long) port->GetValue());

        
    wxButton * save = (wxButton *)FindWindow(ID_CONFIG_SAVE);
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
            
        wxButton * save = (wxButton *)FindWindow(ID_CONFIG_SAVE);
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
