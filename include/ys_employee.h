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
#ifndef YS_EMPLOYEE_H
#define YS_EMPLOYEE_H

#include "wx/statbmp.h"

/**
 * YardEmployee is the employee managment screen for YardSale.
 * Depending on access level, users may insert/modify employee 
 * information via this screen.
 *
 * @see YardEmployeeType
 * @author Jesse Lovelace
 */
class YardEmployee: public wxFrame
{
    public:
        
    YardEmployee(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE, const wxString& name = wxT("YardEmployee"));
    
    virtual ~YardEmployee();

    private:
        
   // DECLARE_EVENT_TABLE()

};

#endif
