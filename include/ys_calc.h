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
*	The calculator dialog. It is a generic on-screen calculator the user employs to enter prices.
*		This calculator uses a stack-based method of storing numbers and operators. The basic way this works is:
*		A user types a number
*		when the user hits an operand (+,-,=,etc) then the number entered previously is pushed onto the stack, and then the operand entered is pushed onto the stack.
*		At this point stack is evaluated, and the operation is run on the numbers. 
*
*		Obviously the first time that this is run, there arent enough numbers on the stack (user presses 4 then +, the stack is evaluated but with not enough numbers), so in the constructor of the class the stack is "preloaded" with a number 0 and operator +.
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
	 * 
	 * The blank number will be replaced when the next number is pressed
	 * in the OnNumber function
	 * @todo JAY get multiplication and division working
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
	 * 
	 * If the top of the stack is a number and it is '0' it just goes ahead
	 * and starts by replacing the 0.
	 *
	 * One tricky part of this class is that I am having to store the numbers
	 * on the stack represented by strings instead of doubles. This is because
	 * if the user enters a '.', it will be lost when the next number is pressed 
	 * because each time a number or a '.' is entered it is concatonated onto the 
	 * string representation of the number, then converted back to a double and pushed
	 * but in the string->double conversion the '.' is lost. Therefore they are stored
	 * on the stack as strings. So there are StringToDouble and DoubleToString functions 
	 * used liberally throughout this function
     * @param wxCommandEvent & event - reference to the button pushed
     */
	void OnNumber(wxCommandEvent & event);
    
	/**
	* Put whatever number is on the top of the stack onto the screen
	*/
	void RefreshScreen();
    
    /** 
	* Clear the screen of the calculator
    */
    void ClearScreen();
	
    /** 
	 * Takes the existing stack and essentially evaluates it. Pops off the top
     * 3 values, which should be number, operator, number, and computes the 
     * result. Then pushes the result back onto the stack_t
	 *
	 * This function is run when we press '=' as well, so if there is just one item 
	 * we just pop it off and push it back on.
     */
    void EvaluateStack();
    
    /** 
     * Simply pushes a number '0' onto the stack. This number is assumed to 
     * be later replaced when the user starts pushing numbers again
     */
    void PushBlankNumber();
    
    /**
     * Converts a Double to a string
     * @param  num the number to convert
     * @returns wxString the string equivalent
     */
	wxString DoubleToString(double num);
	
    /**
     * Converts a String to a double
     * @param str the string to convert
     * @returns double the number equivalent
     */
    double StringToDouble(wxString str);
   
   	/**
     * Simply dumps the stack contents to the console. Used for debugging.
	 */
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
     * A struct of either type operator or a numbers
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
	
    /** 
	 * This is the stack for the class
     */
	std::stack<CalcInstance> m_calcstack;

	/**
	 * A pointer to the screen widget
	 */
    wxTextCtrl * m_screen;
};

#endif
