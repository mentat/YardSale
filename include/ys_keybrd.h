/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004  Jesse Lovelace <jllovela@ncsu.edu>
    Copyright (C) 2004  Jay Johnston <jkjohnst@ncsu.edu>
 
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

#include <stack>
#include "wx/panel.h"

class wxTextCtrl;

class YardKeybrd: public wxPanel {
 public:
     
    /**
     * The constructor for the class, nothing special
     */    
    YardKeybrd(wxWindow* parent, wxWindowID id = -1, 
        const wxPoint& pos = wxDefaultPosition, 
        const wxSize& size = wxDefaultSize, 
        long style = wxTAB_TRAVERSAL, 
        const wxString& name = "YardCalc");
    
    /// Destructor
    virtual ~YardKeybrd();
    
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
	void OnKey(wxCommandEvent & event);
    
	/**
	* Put whatever number is on the top of the stack onto the screen
	*/
	void RefreshScreen();
    
    /** 
	* Clear the screen of the calculator
    */
    void ClearScreen();
	
	/**
	 * A pointer to the screen widget
	 */
    wxTextCtrl * m_screen;
};

#endif
