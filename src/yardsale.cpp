#include "wx/wx.h"
#include "wx/config.h"

#include "yardsale.h"
#include "ys_splash.h"
#include "ys_main.h"
#include "ys_login.h"
#include "ys_exception.h"
#include "ys_database.h"
#include "ys_bitmaps.h"
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
