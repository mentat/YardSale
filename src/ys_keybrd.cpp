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
BEGIN_EVENT_TABLE(YardCalc, wxPanel)
    EVT_BUTTON(ID_CALC_CLEAR, YardCalc::OnClear)
    EVT_BUTTON(-1, YardCalc::OnKey)
END_EVENT_TABLE()

DECLARE_APP(YardSale)

YardKeybrd::YardKeybrd(wxWindow* parent, wxWindowID id, 
        const wxPoint& pos, const wxSize& size, 
        long style, const wxString& name)
        :wxPanel(parent, id, pos, size, style, name)
{
    wxSizer * sizer = NumberPad(this, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    //initialize a way to get to the screen
    m_screen = (wxTextCtrl *)FindWindow(ID_KEYBOARD_SCREEN);
    
    //make sure that the pointer is active
    wxASSERT(m_screen);
   	
}

YardKeybrd::~YardKeybrd()
{
    
}
  
//recieve input and keep adding it to
//the current number, each time refreshing the screen

void YardCalc::OnKey(wxCommandEvent & event)
{
}

void YardCalc::ClearScreen(){
    m_screen->SetValue("");
}

/**
* Put whatever number is on top of the stack onto the calculator's screen
*/
void YardCalc::RefreshScreen(){
}
