/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004 - Jesse Lovelace <jllovela@ncsu.edu>
 
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
#ifndef YARD_REPORTS_H
#define YARD_REPORTS_H

#include <string>
#include "wx/dialog.h"

using namespace std;

class wxCalendarCtrl;
class YardReports: public wxDialog
{
    public:
    /// This is the constructor you will most commonly use.
    YardReports(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString& name = wxT("YardReports"));
    /// Destructor
    virtual ~YardReports();
    
    void OnReportEmpHours(wxCommandEvent& event);
    void OnReportEmpSales(wxCommandEvent& event);
    void OnReportHourlyRev(wxCommandEvent& event);
    void OnLeave(wxCommandEvent& event);
    
 private:
     
    void GenerateGraph(const string& xml, const string& labels, const string& data);
     
    string ProcessXSLT(const string& xml, const string& xsl);
    DECLARE_EVENT_TABLE()
    wxCalendarCtrl * m_from;
    wxCalendarCtrl * m_to;

};

#endif
