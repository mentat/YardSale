#include "wx/wx.h"
#include "yardsale.h"
#include "ys_splash.h"
#include "ys_main.h"
#include "ys_login.h"
#include "yardsale_wdr.h"

IMPLEMENT_APP(YardSale)

bool YardSale::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler);
//    wxDialog * startup = new YardSplash(NULL, -1, "YardSale");
    
 //   startup->ShowModal();
    // load here!
  //  wxDialog * login = new YardLogin(NULL, -1, "YardSale");
    wxFrame * frame = new YardMain(NULL, -1, "YardSale");
    
   // SetTopWindow(login);
    // end loading
    /*startup->Destroy();
    if (login->ShowModal() == 1)
    {
        frame->Destroy();
        login->Destroy();
        return false;
    }        */
    
    SetTopWindow(frame);
    
    //login->Destroy();
    
    frame->Show(true);
    
    return true;
    
}

wxBitmap * GetBitmap(int id)
{
    wxBitmap * bitmap = 0;
    
    switch (id) {
        case (ID_EMPLOY_PICTURE): 
            bitmap = new wxBitmap("images/ys_employee_128x128.png", wxBITMAP_TYPE_PNG);
            break;
        case (ID_SPLASH_LOGO):
            bitmap = new wxBitmap("images/logo.png", wxBITMAP_TYPE_PNG);
            break;
        default: break;
    }
        
    return bitmap;
}
