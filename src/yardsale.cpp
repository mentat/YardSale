#include "wx/wx.h"
#include "wx/config.h"

#include "yardsale.h"
#include "ys_splash.h"
#include "ys_main.h"
#include "ys_login.h"
#include "ys_exception.h"
#include "ys_database.h"
#include "ys_bitmaps.h"
#include "ys_log.h"
#include "ys_config.h"
#include "yardsale_wdr.h"

IMPLEMENT_APP(YardSale)

bool YardSale::OnInit()
{
    SetVendorName(_T("ASLS"));
    SetAppName(_T("YardSale"));
    
    m_db = 0;
    
    m_db = new YardDatabase();
    
    wxImage::AddHandler(new wxPNGHandler);    
    
    m_bitmaps = new YardBitmaps();
    
    try {
        while(m_bitmaps->LoadBitmaps() != 0)
        {}
    } catch (YardException &e)
    {
        wxLogError("Exception in OnInit: %s", e.what());
        return false;
    }
    catch (exception &e)
    {
        wxLogError("Exception in OnInit: %s", e.what());
        return false;
    }
    catch(...)
    {
        wxLogError("Exception in OnInit: Unknown.");
        return false;
    }
#if 0
    wxDialog * startup = new YardSplash(NULL, -1, "YardSale");
    
    startup->ShowModal();
    // load here!
    wxDialog * login = new YardLogin(NULL, -1, "YardSale");
    
    
     SetTopWindow(login);
    // end loading
    startup->Destroy();
    if (login->ShowModal() == 1)
    {
        frame->Destroy();
        login->Destroy();
        return false;
    }
    
#endif
    
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
        
        wxString user = pConfig->Read(wxT("/DB/User"), wxString());
        wxString pass = pConfig->Read(wxT("/DB/Pass"), wxString());
        wxString dsn = pConfig->Read(wxT("/DB/DSN"), wxString());
    
        try {
            DB().Init(user.c_str(), pass.c_str(), dsn.c_str());
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

    
    wxFrame * frame = 0;
    try {
        frame = new YardMain(NULL, -1, "YardSale");
    
        frame->Show(true);
        SetTopWindow(frame);
    }
    catch (...)
    {
        wxLogError(wxT("Fatal! Top Level Exception."));
        return false;
    }
    
    return true;
    
}

int YardSale::OnExit() {
    delete wxConfigBase::Set((wxConfigBase *) NULL);
    delete m_db;
    delete m_bitmaps;
	return 0;
}

YardDatabase& YardSale::DB() {
    
    if (!m_db)
        throw YardException("Database not allocated.");
    
    return *m_db;
}

YardBitmaps& YardSale::Images() {
    
    if (!m_bitmaps)
        throw YardException("Bitmap manager not allocated.");
    
    return *m_bitmaps;
}
