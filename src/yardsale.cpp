#include "wx/wx.h"
#include "yardsale.h"
#include "ys_splash.h"

IMPLEMENT_APP(YardSale)

bool YardSale::OnInit()
{
    wxFrame * frame = new YardSplash(NULL, -1, "YardSale");
    frame->Show(true);
    SetTopWindow(frame);
    
    return true;
    
}
