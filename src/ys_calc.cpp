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
	//the last number on the screen, before the new one entered
	m_savednumber = 0;
	m_tempnumber = 0;

	//keeps track of the current state of the machine
   	m_state = wxString("#");	
	m_operand = wxString("=");

    wxSizer * sizer = NumberPad(this, false, true);
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
    
    //initialize a way to get to the screen
    m_screen = (wxTextCtrl *)FindWindow(ID_CALC_SCREEN);
    
    //make sure that the pointer is active
    wxASSERT(m_screen);
    
    //initialize the screen
    stringstream num;
    num << m_savednumber;
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
   
   	//if the screen has '0' on it, replace it with the digit typed 
	if (m_screen->GetValue() == wxT("0"))
        m_screen->SetValue(ch);
    else
	
	if (ch == '.'){
		if (! m_screen->GetValue().Contains(".") )	
			m_screen->SetValue(m_screen->GetValue() + ch);
	}else
		//if we get here, we entered a number
	
		//test to see if we are still entering a number
		//or if we just got done entering a different state
		//in which case we need to save the old number and clear the screen
		if (m_state.CompareTo("#") == 0){
			m_screen->SetValue(m_screen->GetValue() + ch);
		}else{
			//save the old number
			m_screen->GetValue().ToLong(&m_savednumber);
			//clear the screen	
			m_screen->SetValue(ch);
			
			//set the state to # -- NOTE this is killing my addition state
			m_state = "#";
		}
		
}

//here we evaluate an expression based upon:
//		what is on the screen
//		what is in the memory
//		the operator (indicated by the state)
void YardCalc::Evaluate(){

	m_tempnumber = 0;
	m_screen->GetValue().ToLong(&m_tempnumber);
	
	//addition
	if (m_operand.CompareTo("+") == 0){
		m_savednumber += m_tempnumber;		
	}

	//subtraction

	//division

	//multiplication

	//now refresh
    stringstream num;
    num << m_savednumber;
    m_screen->SetValue(num.str().c_str());

}

void YardCalc::OnPlus(wxCommandEvent & event)
{
	//now we're not in a number state
	m_state = "!"; 

	//if the last operand was an equals, 
	//we need to not evaluate anything, but set the mode and clear
	//the screen but not evaluate
	if (m_operand.CompareTo("=") == 0){
		m_screen->GetValue().ToLong(&m_savednumber);
		m_operand = "+";
	}else{
		//set the operand value	
		m_operand = "+";
		Evaluate();
	}
}

void YardCalc::OnClear(wxCommandEvent & event){
	
	m_savednumber = 0;
	m_screen->SetValue("0");
	m_state = "#";
	m_operand = "=";
}

void YardCalc::OnAllClear(wxCommandEvent & event){
	m_screen->SetValue("0");
}

void YardCalc::OnEqual(wxCommandEvent & event)
{
	Evaluate();
}
