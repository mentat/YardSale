/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004  Jesse Lovelace <jllovela@ncsu.edu>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#ifndef YS_CALC_H
#define YS_CALC_H
/**
* ys_calc.h The calculator dialog 
* @author Jay Johnston
*
*/
#include <stack>

class YardCalc: public wxPanel {
    public:
     
    /**
     * The constructor for the class, nothing special
     */    
    YardCalc(wxWindow* parent, wxWindowID id = -1, 
        const wxPoint& pos = wxDefaultPosition, 
        const wxSize& size = wxDefaultSize, 
        long style = wxTAB_TRAVERSAL, 
        const wxString& name = "YardCalc");
    
    virtual ~YardCalc();
    
    private:
   	
    DECLARE_EVENT_TABLE()
	
    /**
     * Runs whenever an operator is pressed such as "+" or "-" or "="
     * It calculates the existing stack with EvaluateStack()
     * Then pushes its own new operator onto the stack, and 
     * pushes a blank number on.
     * @param wxCommandEvent & event - reference to the button pushed
     */
	void OnOperator(wxCommandEvent & event); 
    
	/**
	* Runs whenever the clear button is pressed. Simply clears the
    * stack off, and pushes a dummy number 0
    * @param wxCommandEvent & event - reference to the button pushed
	*/
	void OnClear(wxCommandEvent & event);
    
    /**
     * Runs whenever a number is pressed. Checks the number on the top
     * of the stack and concatonates the pressed number onto it 
     * @param wxCommandEvent & event - reference to the button pushed
     */
	void OnNumber(wxCommandEvent & event);
    
	/**
	* Put whatever number is on the top of the stack onto the screen
	*/
	void RefreshScreen();
    
    /** Clear the screen of the calculator
    */
    void ClearScreen();
	
    /** Takes the existing stack and essentially evaluates it. Pops off the top
     * 3 values, which should be number, operator, number, and computes the 
     * result. Then pushes the result back onto the stack_t
     */
    void EvaluateStack();
    
    /** 
     * Simply pushes a number '0' onto the stack. This number is assumed to 
     * be later replaced when the user starts pushing numbers again
     */
    void PushBlankNumber();
    
    /**
     * Converts a Double to a string
     * @param double num the number to convert
     * @returns wxString the string equivalent
     */
	wxString DoubleToString(double num);
	
    /**
     * Converts a String to a double
     * @param str the string to convert
     * @returns double the number equivalent
     */
    double StringToDouble(wxString str);
    
    void DumpStack();
    
    /**
     * Enumeration of the possible calculator operations
     */
	enum CalcOperator
	{
		Addition,
		Subtraction,
		Multiplication,
		Division,
	};

    /**
     * A union of either type operator or a numbers
     * these are the two possible types we push to the stack
     */
	struct CalcType
	{
		CalcOperator m_op;
		wxString m_number;
	};

    /**
     * This is the actual type we push to the stack
     */
	struct CalcInstance
	{
		bool m_isNumber;
		CalcType m_type;
	};
	
    /** This is the stack for the class
    */
	std::stack<CalcInstance> m_calcstack;

	double m_tempnumber;
	wxString m_screenstring;
    wxTextCtrl * m_screen;
	wxString m_state;
	wxString m_operand;
};

#endif
