#include <sstream>
#include <stack>
#include <iostream>

#include "wx/app.h"
#include "wx/wx.h"
#include "extra/xrc/xmlres.h"

#include "yardsale.h"
#include "ys_calc.h"

using namespace std;

IMPLEMENT_DYNAMIC_CLASS(YardCalc, wxPanel)
//when a button is pressed, it's ID matches up here with a function
BEGIN_EVENT_TABLE(YardCalc, wxPanel)
    EVT_BUTTON(XRCID("ID_CALC_CLEAR"), YardCalc::OnClear)
	//EVT_BUTTON(XRCID("ID_CALC_DOT"), YardCalc::OnNumber)
    EVT_BUTTON(XRCID("ID_CALC_DOT"), YardCalc::OnDoubleZero)
	EVT_BUTTON(XRCID("ID_CALC_PLUS"), YardCalc::OnOperator)
	EVT_BUTTON(XRCID("ID_CALC_MINUS"), YardCalc::OnOperator)
	EVT_BUTTON(XRCID("ID_CALC_EQUALS"), YardCalc::OnOperator)
    EVT_BUTTON(-1, YardCalc::OnNumber)
END_EVENT_TABLE()

DECLARE_APP(YardSale)

YardCalc::YardCalc(wxWindow* parent, wxWindowID id, 
        const wxPoint& pos, const wxSize& size, 
        long style, const wxString& name)
        :wxPanel(parent, id, pos, size, style, name)
{
    
    wxXmlResource::Get()->Load("res/calc_wdr.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "NumberPad");
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
        
    //initialize a way to get to the screen
    m_screen = (wxTextCtrl *)FindWindow(XRCID("ID_CALC_SCREEN"));
    
    //make sure that the pointer is active
    wxASSERT(m_screen);
   	
	PushBlankNumber();
    
    CalcInstance m_tempstackitem;

	m_tempstackitem.m_isNumber = false;
	m_tempstackitem.m_type.m_op = Addition;
	m_calcstack.push(m_tempstackitem);
    
    PushBlankNumber();
    
    //so now the stack should have a number pushed onto it, and an operator
	RefreshScreen();
    Show();
    //DumpStack();
}

bool YardCalc::Create(wxWindow* parent, wxWindowID id, 
     const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    if ( !wxPanel::Create(parent, id, pos, size, style, name) )
        return false;
    
    wxXmlResource::Get()->Load("res/calc_wdr.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "NumberPad");
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());
        
    //initialize a way to get to the screen
    m_screen = (wxTextCtrl *)FindWindow(XRCID("ID_CALC_SCREEN"));
    
    //make sure that the pointer is active
    wxASSERT(m_screen);
   	
	PushBlankNumber();
    
    CalcInstance m_tempstackitem;

	m_tempstackitem.m_isNumber = false;
	m_tempstackitem.m_type.m_op = Addition;
	m_calcstack.push(m_tempstackitem);
    
    PushBlankNumber();
    
    //so now the stack should have a number pushed onto it, and an operator
	RefreshScreen();
}

void YardCalc::PushBlankNumber()
{
    CalcInstance m_tempstackitem;

	m_tempstackitem.m_isNumber = true;
	m_tempstackitem.m_type.m_number = "";
	m_calcstack.push(m_tempstackitem);

}

void YardCalc::DumpStack()
{
    std::stack<CalcInstance> m_calcstack2;
    m_calcstack2 = m_calcstack;
    
    while (!m_calcstack2.empty()){
        if (m_calcstack2.top().m_isNumber){
   //         cout << "STACK: number->" << m_calcstack2.top().m_type.m_number << "\n";
        }else
    //        cout << "STACK: operator->" << "\n";
        
        m_calcstack2.pop();
    }
     //           cout << "\n\n";

    
}

YardCalc::~YardCalc()
{
    
}
  
void YardCalc::OnDoubleZero(wxCommandEvent & event){
    m_calcstack.top().m_type.m_number = DoubleToString(StringToDouble(m_calcstack.top().m_type.m_number) * .01);
    
    RefreshScreen();
}

//recieve input and keep adding it to
//the current number, each time refreshing the screen

void YardCalc::OnNumber(wxCommandEvent & event)
{
    wxChar ch;
	wxString m_tempstring;
	CalcInstance m_tempstackinstance;

    if (event.GetId() == XRCID("ID_CALC_1"))
        ch = '1';
     if (event.GetId() == XRCID("ID_CALC_2"))
        ch = '2';
      if (event.GetId() == XRCID("ID_CALC_3"))
        ch = '3';
       if (event.GetId() == XRCID("ID_CALC_4"))
        ch = '4';
        if (event.GetId() == XRCID("ID_CALC_5"))
        ch = '5';
         if (event.GetId() == XRCID("ID_CALC_6"))
        ch = '6';
         if (event.GetId() == XRCID("ID_CALC_7"))
        ch = '7'; 
         if (event.GetId() == XRCID("ID_CALC_8"))
        ch = '8'; 
         if (event.GetId() == XRCID("ID_CALC_9"))
        ch = '9'; 
         if (event.GetId() == XRCID("ID_CALC_0"))
        ch = '0'; 
                    
    //check to see if we need to clear the screen
    //aka, we just previously hit an operator
   // if (!m_calcstack.top().m_isNumber)
    //    ClearScreen();
        
    
   	//if the screen has '0' on it, replace it with the digit typed 
	if (m_calcstack.top().m_type.m_number.CompareTo("0") == 0 && m_calcstack.size() == 1){
		m_tempstring = ch;
		m_calcstack.top().m_type.m_number = m_tempstring;
	}
	else{
		if (ch == '.'){
			if (! m_calcstack.top().m_type.m_number.Contains(".") ){
				m_calcstack.top().m_type.m_number.Append(ch);
			}
		}
		else
		//if we get here, we entered a number
		m_calcstack.top().m_type.m_number.Append(ch);
	}

	RefreshScreen();
}

double YardCalc::GetCalcContents(){
    return StringToDouble(m_calcstack.top().m_type.m_number);
}

//here we evaluate an expression based upon:
//		what is on the screen
//		what is in the memory
//		the operator (indicated by the state)
void YardCalc::EvaluateStack(){
    CalcInstance arg2 = m_calcstack.top();
    m_calcstack.pop();

    //In the case that there is only one item on the stack, the stack is 
    //considered to be evaluated, so just leave it alone and return
    if (m_calcstack.empty()){
        m_calcstack.push(arg2);
        return;
    }        

    CalcInstance op = m_calcstack.top();
    m_calcstack.pop();
    CalcInstance arg1 = m_calcstack.top();
    m_calcstack.pop();
    
    switch (op.m_type.m_op) {
        case (Addition): 
            arg1.m_type.m_number = DoubleToString(StringToDouble(arg1.m_type.m_number) + StringToDouble(arg2.m_type.m_number)); break;
        case (Subtraction):
            arg1.m_type.m_number = DoubleToString(StringToDouble(arg1.m_type.m_number) - StringToDouble(arg2.m_type.m_number)); break;
    }
  
    //now push back the result
    m_calcstack.push(arg1);
    
    RefreshScreen();
    //DumpStack();
}

void YardCalc::ClearScreen(){
    m_screen->SetValue("");
}

//need to have this function actually push onto the stack?
void YardCalc::SetCalcContents(double contents){
    m_screen->SetValue(DoubleToString(contents));
    //do more stuff here
}

wxString YardCalc::DoubleToString(double num){
	
	stringstream numbah;
	numbah << num;
	return wxString(numbah.str().c_str());
	
}

double YardCalc::StringToDouble(wxString str){
	double  tempvalue;
	str.ToDouble(&tempvalue);
	return tempvalue;
}

/**
* Put whatever number is on top of the stack onto the calculator's screen
*/
void YardCalc::RefreshScreen(){
	stringstream num;
	num << m_calcstack.top().m_type.m_number;
	m_screen->SetValue(num.str().c_str());
}

void YardCalc::OnOperator(wxCommandEvent & event){
	
	CalcInstance m_tempinstance;
	m_tempinstance.m_isNumber = false;
#if 0
	switch (event.GetId()) {
        case (XRCID("ID_CALC_PLUS")): m_tempinstance.m_type.m_op = Addition; break;
        case (XRCID("ID_CALC_MINUS")): m_tempinstance.m_type.m_op = Subtraction; break;
        case (XRCID("ID_CALC_EQUALS")): EvaluateStack(); return;
        }
#endif
    //first, evaluate the old stack        
    EvaluateStack();
    //next, push on my operator
	m_calcstack.push(m_tempinstance);
    //now push a blank number, to be replaced by the real one
    PushBlankNumber();
        
}

void YardCalc::OnClear(wxCommandEvent & event){
	while (!m_calcstack.empty()){
		m_calcstack.pop();
	}
		
	PushBlankNumber();

	RefreshScreen();
}
