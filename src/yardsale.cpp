#include "wx/wx.h"
#include "wx/config.h"
#include "wx/fs_zip.h"
#include "extra/xrc/xmlres.h"

#include "yardsale.h"
#include "ys_splash.h"
#include "ys_main.h"
#include "ys_login.h"
#include "ys_exception.h"
#include "ys_database.h"
#include "ys_log.h"
#include "ys_config.h"

IMPLEMENT_APP(YardSale)

bool YardSale::OnInit()
{
    SetVendorName(_T("ASLS"));
    SetAppName(_T("YardSale"));
    
    m_db = 0;
    m_db = new YardDatabase();
    
    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);     
    wxFileSystem::AddHandler(new wxZipFSHandler);
    wxXmlResource::Get()->InitAllHandlers();

    YardLogin * login = new YardLogin(NULL, -1, "YardSale");
    if (login->ShowModal() == 1)
    {
        login->Destroy();
        return false;
    }
    /// Get username and password from dialog
    m_user = login->GetUser();
    m_pass = login->GetPass();
    login->Destroy();
    
    /// Load misc config settings from system
    LoadConfig();
    
    /// Load main frame
    wxFrame * frame = new YardMain(NULL, -1, "YardSale");
    
    frame->Show(true);
    SetTopWindow(frame);
    
    return true;
}

void YardSale::LoadConfig()
{
    wxConfigBase *pConfig = wxConfigBase::Get();

    bool tryLogin = true;
  
    if (!pConfig)
    {
        wxLogError(wxT("No Config pointer"));
        tryLogin = false;
    } 
    else
        if (!pConfig->HasGroup(wxT("DB")))
        {
            tryLogin = false;
            wxLogDebug(wxT("No DB group in config."));
            int answer = wxMessageBox("No configuration exists on this computer,"
                " would you like to create one?", "Create Config",
                                wxYES_NO);
            if (answer == wxNO)
            {
                wxLogDebug(wxT("Answer was no."));
            }
            else
            {
                YardConfig * conf = new YardConfig(NULL, -1, wxT("YardSale Configuration"));
                conf->ShowModal();
                conf->Destroy();
                tryLogin = true;
            }
        }
        else wxLogDebug(wxT("Config found, reading..."));

    if (tryLogin) {
        wxLogDebug(wxT("Trying to login..."));
        
        //wxString user = pConfig->Read(wxT("/DB/User"), wxString());
        //wxString pass = pConfig->Read(wxT("/DB/Pass"), wxString());
        wxString dsn = pConfig->Read(wxT("/DB/DSN"), wxString());
    
        try {
            DB().Init(m_user.c_str(), m_pass.c_str(), dsn.c_str());
        } catch (YardDBException &e) {
            wxLogDebug(e.GetWhat().c_str());
        }
        
        try { 
            DB().connect();
            wxLogDebug(wxT("Connected to %s"), dsn.c_str());
        } catch (YardDBException &e) {
            wxLogDebug(e.GetWhat().c_str());
        }
        
    }
}

int YardSale::OnExit() {
    delete wxConfigBase::Set((wxConfigBase *) NULL);
    delete m_db;
	return 0;
}

YardDatabase& YardSale::DB() {
    
    if (!m_db)
        throw YardException("Database not allocated.");
    
    return *m_db;
}
