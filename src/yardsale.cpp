#include "wx/wx.h"
#include "yardsale.h"
#include "ys_splash.h"
#include "ys_main.h"
#include "ys_login.h"

IMPLEMENT_APP(YardSale)

bool YardSale::OnInit()
{
    wxDialog * startup = new YardSplash(NULL, -1, "YardSale");
    
    startup->ShowModal();
    // load here!
    wxDialog * login = new YardLogin(NULL, -1, "YardSale");
    wxFrame * frame = new YardMain(NULL, -1, "YardSale");
    
    SetTopWindow(login);
    // end loading
    startup->Destroy();
    if (login->ShowModal() == 1)
    {
        frame->Destroy();
        login->Destroy();
        return false;
    }        
    
    SetTopWindow(frame);
    
    login->Destroy();
    
    frame->Show(true);
    
    return true;
    
}
