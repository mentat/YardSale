#include <sstream>
#include <stack>
#include <iostream>

#include "wx/app.h"

#include "yardsale.h"
#include "ys_bitmaps.h"
#include "yardsale_wdr.h"
#include "ys_keybrd.h"

using namespace std;

//when a button is pressed, it's ID matches up here with a function
BEGIN_EVENT_TABLE(YardKeybrd, wxPanel)
    EVT_BUTTON(-1, YardKeybrd::OnButton)
    EVT_CHAR(YardKeybrd::OnChar)
END_EVENT_TABLE()

DECLARE_APP(YardSale)

YardKeybrd::YardKeybrd(wxWindow* parent, wxWindowID id, 
        const wxPoint& pos, const wxSize& size, 
        long style, const wxString& name)
        :wxPanel(parent, id, pos, size, style, name)
{
    wxSizer * sizer = Keyboard(this, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    screencontents = wxString("");
    
    //initialize a way to get to the screen
    m_screen = (wxTextCtrl *)FindWindow(ID_KBD_SCREEN);
    
    //make sure that the pointer is active
    wxASSERT(m_screen);
   
}

YardKeybrd::~YardKeybrd()
{
    
}

void YardKeybrd::OnChar(wxCommandEvent & event){
 
    
    
}

void YardKeybrd::AddString(wxString string){
    screencontents += string;
	m_screen->SetValue(screencontents + string);
}

void YardKeybrd::OnButton(wxCommandEvent & event)
{   
    wxButton * temp = (wxButton *)FindWindow(event.GetId());
    
    AddString(temp->GetLabel());
}

void YardKeybrd::ClearScreen(){
    m_screen->SetValue("");
}

/**
* Put whatever number is on top of the stack onto the calculator's screen
*/
void YardKeybrd::RefreshScreen(){
}
