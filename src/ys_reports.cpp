#include <string>

#include "extra/xrc/xmlres.h"
#include "wx/wx.h"
#include "wx/app.h"
#include "wx/calctrl.h"
#include "wx/html/htmlwin.h"

#include "yardsale.h"
#include "ys_database.h"
#include "ys_date.h"
#include "ys_reports.h"
#include "sablot.h"

DECLARE_APP(YardSale)

using namespace std;

class YardHTML: public wxDialog
{
 public:
    YardHTML(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString& name = wxT("YardHTML"))
    :wxDialog(parent, id, title, pos, size, style, name)
    {
        wxPanel * panel = new wxPanel(this);
        m_html = new wxHtmlWindow(panel, -1, wxDefaultPosition, wxSize(400,300));
        
        wxFlexGridSizer *item0 = new wxFlexGridSizer( 1, 0, 0 );
        item0->AddGrowableCol( 0 );
        item0->AddGrowableRow( 0 );
        item0->Add( m_html, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
        panel->SetAutoLayout( TRUE );
        panel->SetSizer( item0 );
        
        item0->SetSizeHints(this);
        SetSize(item0->GetMinSize());   
        Centre();
        
    }
    
    void SetPage(const wxString& html) { m_html->SetPage(html); }
    
   
 private:
    wxHtmlWindow * m_html;     
    
};



BEGIN_EVENT_TABLE(YardReports, wxDialog)
    EVT_BUTTON(XRCID("ID_REPORT_EMP_HOURS"), YardReports::OnReportEmpHours)
    EVT_BUTTON(XRCID("ID_REPORT_EMP_SALES"), YardReports::OnReportEmpSales)
    EVT_BUTTON(XRCID("ID_REPORT_HOURLY_REV"), YardReports::OnReportHourlyRev)
END_EVENT_TABLE()

YardReports::YardReports(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos,const wxSize& size, long style,
               const wxString& name): wxDialog(parent, id, title, pos, size, style, name)
{
    wxXmlResource::Get()->Load("res/reports.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "Reports");
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());   
    Centre();
    
    m_to = static_cast<wxCalendarCtrl*>(FindWindow(XRCID("ID_REPORT_TO")));
    m_to->SetHighlightColours(*wxRED, *wxBLACK); 
    m_from = static_cast<wxCalendarCtrl*>(FindWindow(XRCID("ID_REPORT_FROM")));
    m_from->SetHighlightColours(*wxRED, *wxBLACK); 
}

YardReports::~YardReports() {}
    
void YardReports::OnReportEmpHours(wxCommandEvent& event)
{
    YardDate to(m_to->GetDate());
    YardDate from(m_from->GetDate());
    
    stringstream sql;
    sql << "SELECT EMP_ID_Number AS ID_Number , EMP_First_Name AS First_Name, Emp_Last_Name AS Last_Name, "
            "EXTRACT(HOUR FROM LOG_Time_Out - LOG_Time_In) AS Time_Worked_Hours, "
            "EXTRACT(HOUR_MINUTE FROM LOG_Time_Out - LOG_Time_In)%100 AS Time_Worked_Minutes, "
            "DATE_FORMAT(Log_Time_Out, '%W %M %D' ) AS Worked_On_Date "
            "FROM Login_Table JOIN Employee_Table ON LOG_REF_EMP_ID = EMP_ID_Number "
            "WHERE LOG_Count = 0 AND "
            "LOG_Time_In BETWEEN '" << from.DayString() << "' AND '" 
            << to.DayString() << "'; ";
    
    string xml("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<root>\n");
    
    long count = 0;
    try
    {
        xml += wxGetApp().DB().ReportXML(sql.str(), count);
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (report): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    wxLogDebug(wxT("Count: %d"), count);
    
    if (count == 0)
    {
        wxMessageBox("No data was found in that time range.", "No Data",
                            wxOK, this);   
        return;
    }
    
    xml += "\n</root>\n";
    
    string html = ProcessXSLT(xml, "res/report.xsl");
    
    YardHTML * prev = new YardHTML(this, -1, wxT("Report Preview"));
    prev->SetPage(html.c_str());
    prev->ShowModal();
    prev->Destroy();
}
void YardReports::OnReportEmpSales(wxCommandEvent& event)
{
    
    YardDate to(m_to->GetDate());
    YardDate from(m_from->GetDate());
    
    stringstream sql;
    sql << "SELECT TRANS_REF_EMP_ID_Number AS Employee_ID, "
           "EMP_First_Name AS First_Name, EMP_Last_Name AS Last_Name, "
           "SUM((TRANS_Quantity * (TRANS_Sale_Price - INV_Wholesale_Price))) AS PROFIT, "
           "SUM(TRANS_Sale_Price * TRANS_Quantity) AS RETAIL_TOTAL, "
           "SUM(INV_Wholesale_Price * TRANS_Quantity) AS TOTAL_WHOLESALE_COST "
           "FROM Transaction_Log_Table JOIN Employee_Table "
           "ON Transaction_Log_Table.TRANS_REF_EMP_ID_Number = Employee_Table.EMP_ID_Number  JOIN Customer_Table "
           "ON Transaction_Log_Table.TRANS_REF_CUST_Account_Number = Customer_Table.Cust_Account_Number JOIN Inventory_Table "
           "ON Transaction_Log_Table.TRANS_REF_INV_Item_ID = Inventory_Table.INV_Item_ID "
           "WHERE "
           "TRANS_Time BETWEEN '"
           << from.ToString() << "' AND '" << to.ToString() << "' "
           "GROUP BY TRANS_REF_EMP_ID_Number;";
    
    string xml("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<root>\n");
    
    long count = 0;
    try
    {
        xml += wxGetApp().DB().ReportXML(sql.str(), count);
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (report): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    wxLogDebug(wxT("Count: %d"), count);
    
    if (count == 0)
    {
        wxMessageBox("No data was found in that time range.", "No Data",
                            wxOK, this);   
        return;
    }
    
    xml += "\n</root>\n";
    
    string html = ProcessXSLT(xml, "res/report_employee_sales.xsl");
    
    YardHTML * prev = new YardHTML(this, -1, wxT("Report Preview"));
    prev->SetPage(html.c_str());
    prev->ShowModal();
    prev->Destroy();
    
}

void YardReports::OnReportHourlyRev(wxCommandEvent& event)
{

   YardDate to(m_to->GetDate());
    YardDate from(m_from->GetDate());
    
    stringstream sql;
    sql << "SELECT EXTRACT(HOUR FROM TRANS_Time) AS Hour, "
           "SUM((TRANS_Quantity * (TRANS_Sale_Price - INV_Wholesale_Price))) AS PROFIT "
           "FROM Transaction_Log_Table  JOIN Inventory_Table "
           "ON Transaction_Log_Table.TRANS_REF_INV_Item_ID = Inventory_Table.INV_Item_ID "
           "WHERE "
           "TRANS_Time BETWEEN '"
           << from.ToString() << "' AND '" << to.ToString() << "' "
           "GROUP BY EXTRACT(HOUR FROM TRANS_Time) "
           "UNION "
           "SELECT EXTRACT(HOUR FROM TRANS_Time)  AS Hour,  "
           "SUM((TRANS_Quantity * (TRANS_Sale_Price - INV_Wholesale_Price))) AS PROFIT "
           "FROM Transaction_Log_Table  JOIN Inventory_Table "
           "ON Transaction_Log_Table.TRANS_REF_INV_Item_ID = Inventory_Table.INV_Item_ID "
           "WHERE "
           "TRANS_Time BETWEEN '"
           << from.ToString() << "' AND '" << to.ToString() << "' "
           "GROUP BY TRANS_Always_Null;";
    
    string xml("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<root>\n");
    
    long count = 0;
    try
    {
        xml += wxGetApp().DB().ReportXML(sql.str(), count);
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (report): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    wxLogDebug(wxT("Count: %d"), count);
    
    if (count == 0)
    {
        wxMessageBox("No data was found in that time range.", "No Data",
                            wxOK, this);   
        return;
    }
    
    xml += "\n</root>\n";
    
    string html = ProcessXSLT(xml, "res/report_hourly_profit.xsl");
    
    YardHTML * prev = new YardHTML(this, -1, wxT("Report Preview"));
    prev->SetPage(html.c_str());
    prev->ShowModal();
    prev->Destroy();    
    
    
}    
    
string YardReports::ProcessXSLT(const string& xml_str, const string& xsl_file)
{
    string ret;
    try {
        SablotSituation S;
        SablotHandle proc; 
        SDOM_Document xml;
    
        SablotCreateSituation(&S);
       // SablotParseStylesheetBuffer(S, xslt_str.str().c_str(), &xsl);
        SablotParseBuffer(S, xml_str.c_str(), &xml);
    
        SablotCreateProcessorForSituation(S, &proc);
       // SablotAddArgTree(S, proc, "sheet", xsl);
        SablotAddArgTree(S, proc, "data", xml);
    
        SablotRunProcessorGen(S, proc, xsl_file.c_str(), "arg:/data", "arg:/out");
    
        char * result;
        SablotGetResultArg(proc, "arg:/out", &result);
        ret = result;
            
        SablotFree(result);
        SablotDestroyDocument(S, xml);
        SablotDestroyProcessor(proc);
        SablotDestroySituation(S);
    }
    catch (...)
    {
        wxLogDebug("Sablot exception...");
    }
    
    return ret;
}
