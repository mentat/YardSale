#include "wx/wx.h"
#include "yardsale.h"
#include "ys_splash.h"
#include "ys_main.h"

IMPLEMENT_APP(YardSale)

bool YardSale::OnInit()
{
    wxDialog * startup = new YardSplash(NULL, -1, "YardSale");
    
    startup->ShowModal();
    startup->Destroy();
    
    wxFrame * frame = new YardMain(NULL, -1, "YardSale");
    frame->Show(true);
    
    SetTopWindow(frame);
    
    
    return true;
    
}
