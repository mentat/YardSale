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

#include "ys_employee_type.h"
#include "wx/statbmp.h"
#include "wx/treebase.h"
class wxStaticBitmap;
class wxTreeCtrl;
class wxTextCtrl;
class wxStaticText;
/**
 * YardEmployee is the employee managment screen for YardSale.
 * Depending on access level, users may insert/modify employee 
 * information via this screen.
 *
 * @see YardEmployeeType
 * @author Jesse Lovelace
 */
class YardEmployee: public wxDialog
{
 public:
        
    YardEmployee(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE, const wxString& name = wxT("YardEmployee"));
    
    virtual ~YardEmployee();
 
    void OnChange(wxTreeEvent& event);
    void OnNew(wxCommandEvent& event);
    void OnClose(wxCommandEvent& event);
 
 private:
    DECLARE_EVENT_TABLE()
    void LoadTreeItems(wxTreeCtrl * tree);
    void CreateImageList(wxTreeCtrl * tree);
 
    wxStaticBitmap * m_pic;
    wxStaticBitmap * m_sig;
    wxTreeCtrl * m_tree;
    wxTextCtrl * m_first;
    wxTextCtrl * m_middle;
    wxTextCtrl * m_last;
    wxTextCtrl * m_address;
    wxTextCtrl * m_id;
    wxTextCtrl * m_taxid;
    wxTextCtrl * m_phone;
    wxStaticText * m_position;
 
    YardEmployeeType m_emp;
};

#endif
