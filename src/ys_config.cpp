#include "wx/config.h"
#include "wx/msgdlg.h"
#include "ys_config.h"
#include "yardsale_wdr.h"


BEGIN_EVENT_TABLE(YardConfig, wxFrame)
    EVT_BUTTON(ID_CONFIG_SAVE, YardConfig::OnSave)
    EVT_BUTTON(ID_CONFIG_CANCEL, YardConfig::OnCancel)
    EVT_MENU(ID_CONFIG_EXIT, YardConfig::OnExit)
    EVT_MENU(ID_CONFIG_DELETE, YardConfig::OnDeleteConfig)
END_EVENT_TABLE()

YardConfig::YardConfig(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos, const wxSize& size, long style)

:wxFrame(parent, id, title, pos, size, style)
{    
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
            wxLogDebug(wxT("Answer was no, deleting trace."));
            pConfig->DeleteAll();
            Destroy();
            return;
        }
        
        pConfig->SetPath("/DB");
        pConfig->SetPath("..");
    }
        
    
    Show();
}
 
YardConfig::~YardConfig()
{}
 
void YardConfig::OnCancel(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnCancel"));
    Close();
}

void YardConfig::OnSave(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnSave"));
}

void YardConfig::OnExit(wxCommandEvent& event)
{
    
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
