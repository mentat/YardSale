#include <sstream>

#include "yardsale_wdr.h"
#include "ys_calc.h"

using namespace std;


//when a button is pressed, it's ID matches up here with a function
BEGIN_EVENT_TABLE(YardCalc, wxPanel)
    EVT_BUTTON(ID_CALC_PLUS, YardCalc::OnPlus)
    EVT_BUTTON(ID_CALC_EQUALS, YardCalc::OnEqual)
    EVT_BUTTON(ID_CALC_CLEAR, YardCalc::OnClear)
    EVT_BUTTON(ID_CALC_AC, YardCalc::OnAllClear)
    EVT_BUTTON(ID_CALC_DOT, YardCalc::OnNumber)
    EVT_BUTTON(-1, YardCalc::OnNumber)
END_EVENT_TABLE()

YardCalc::YardCalc(wxWindow* parent, wxWindowID id, 
        const wxPoint& pos, const wxSize& size, 
        long style, const wxString& name)
        :wxPanel(parent, id, pos, size, style, name)
{
    m_number = 0;

	//the last number on the screen, before the new one entered
	m_savednumber = 0;

	//are we in an add loop?
    m_inAdd = false;
    
    wxSizer * sizer = NumberPad(this, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    //initialize a way to get to the screen
    m_screen = (wxTextCtrl *)FindWindow(ID_CALC_SCREEN);
    
    //make sure that the pointer is active
    wxASSERT(m_screen);
    
    //initialize the screen
    stringstream num;
    num << m_number;
    m_screen->SetValue(num.str().c_str());
}

YardCalc::~YardCalc()
{
    
}
    
void YardCalc::OnNumber(wxCommandEvent & event)
{
    wxChar ch;

	switch (event.GetId()) {
        case (ID_CALC_1): ch = '1'; break;
        case (ID_CALC_2): ch = '2'; break;
        case (ID_CALC_3): ch = '3'; break;
        case (ID_CALC_4): ch = '4'; break;
        case (ID_CALC_5): ch = '5'; break;
        case (ID_CALC_6): ch = '6'; break;
        case (ID_CALC_7): ch = '7'; break;
        case (ID_CALC_8): ch = '8'; break;
        case (ID_CALC_9): ch = '9'; break;
        case (ID_CALC_0): ch = '0'; break;
        case (ID_CALC_DOT): ch = '.'; break;
   
   	default: wxLogError(wxT("Should not see me")); return;
    }
   
    if (m_screen->GetValue() == wxT("0"))
        m_screen->SetValue(ch);
    else
    	// set the value of the screen to origional concatonated with new char

	// if the current char is a ., we only want to add it to the screen
	// if there is not already one there
	// but if it isnt a dot dont worry about it and add it to the screen
	if (ch == '.'){
		if (! m_screen->GetValue().Contains(".") )	
			m_screen->SetValue(m_screen->GetValue() + ch);
	}else
		//now clear the screen if we are wanting to enter a new number
		if (!m_readyfornewnumber)
			m_screen->SetValue(m_screen->GetValue() + ch);
		else{
			m_screen->GetValue().ToLong(&m_savednumber);
			m_screen->SetValue(ch);
			m_readyfornewnumber = true;
		}
}

void YardCalc::OnPlus(wxCommandEvent & event)
{
    
    long int tmp = 0;

	//indicate that when the next number is pressed that 
	//we need to clear the screen and read in a new number
	m_readyfornewnumber = true;
    
    // try to convert
    if (!m_screen->GetValue().ToLong(&m_savednumber)) {
    	//error    
        wxLogDebug(wxT("Error in conversion"));
        m_screen->SetValue(wxT("Error in conversion"));
        m_inAdd = false;
        return;
    }
   
   	//converted the screen contents successfully
    if (m_inAdd)
        m_number += m_savednumber;
    else{
        m_number = m_savednumber;
		m_inAdd = true;
	}
        
}

void YardCalc::OnClear(wxCommandEvent & event){
	
	m_screen->SetValue("0");
}

void YardCalc::OnAllClear(wxCommandEvent & event){
	m_screen->SetValue("0");
}

//may not need this
void YardCalc::OnDot(wxCommandEvent & event){

}

void YardCalc::OnEqual(wxCommandEvent & event)
{
    long int tmp = 0;
   	
    if (m_screen->GetValue().ToLong(&tmp))
        m_number += tmp;
    else {
        m_screen->SetValue(wxT("Error in conversion"));
        m_inAdd = false;
        return;
    }
    
    if (m_inAdd) {
        m_number += tmp;

		//write back to the screen
		stringstream num;
        num << m_number;
        m_screen->SetValue(num.str().c_str());
       
	   	m_inAdd = false;
    }
}
