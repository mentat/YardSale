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
    
 private:
     
    string ProcessXSLT(const string& xml, const string& xsl);
    DECLARE_EVENT_TABLE()
    wxCalendarCtrl * m_from;
    wxCalendarCtrl * m_to;

};

#endif
