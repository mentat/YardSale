#include <string>

#include "extra/xrc/xmlres.h"
#include "wx/wx.h"
#include "wx/app.h"
#include "wx/calctrl.h"
#include "wx/html/htmlwin.h"
#include "wx/html/htmprint.h"

#include "yardsale.h"
#include "ys_database.h"
#include "ys_date.h"
#include "ys_reports.h"
#include "xmlnode.h"
#include "sablot.h"

// testing: gdc
#ifdef YS_CHART
extern "C" {
#include "extra/gdc/gdc.h"
#include "extra/gdc/gdcpie.h"
}
#endif

DECLARE_APP(YardSale)

using namespace std;

enum { ID_HTML_PAGESETUP = 13500, ID_HTML_PRINTSETUP, ID_HTML_PRINT,
        ID_HTML_PREVIEW, ID_HTML_QUIT };

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
        m_html = new wxHtmlWindow(panel, -1, wxDefaultPosition, wxSize(480,350),
            wxSUNKEN_BORDER | wxHW_SCROLLBAR_AUTO );
       
        wxButton * preview = new wxButton(panel, ID_HTML_PREVIEW, "Preview", wxDefaultPosition);
        wxButton * page_setup = new wxButton(panel, ID_HTML_PAGESETUP, "Page Setup", wxDefaultPosition);
        wxButton * print_setup = new wxButton(panel, ID_HTML_PRINTSETUP, "Print Setup", wxDefaultPosition);
        wxButton * print = new wxButton(panel, ID_HTML_PRINT, "Print", wxDefaultPosition);
        wxButton * quit = new wxButton(panel, ID_HTML_QUIT, "Quit", wxDefaultPosition);
      
        wxBoxSizer * butts = new wxBoxSizer(wxHORIZONTAL);
        butts->Add(preview);
        butts->Add(page_setup);
        butts->Add(print_setup);
        butts->Add(print);
        butts->Add(quit);
        
        wxFlexGridSizer *item0 = new wxFlexGridSizer( 1, 0, 0 );
        item0->AddGrowableCol( 0 );
        item0->AddGrowableRow( 0 );
        item0->Add( m_html, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
        item0->Add( butts, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
        panel->SetAutoLayout( TRUE );
        panel->SetSizer( item0 );
        
        m_Prn = new wxHtmlEasyPrinting(_("YardSale Report"), NULL);
        m_Prn -> SetHeader(m_Name + wxT("(@PAGENUM@/@PAGESCNT@)<hr>"), wxPAGE_ALL);

        item0->SetSizeHints(this);
        SetSize(item0->GetMinSize());  
        Centre();        
        if (wxGetApp().Full())
            ShowFullScreen(true);
        
    }
    ~YardHTML() { delete m_Prn; }
    
    void OnPrintSetup(wxCommandEvent& event)
    { m_Prn -> PrinterSetup(); }
    void OnPageSetup(wxCommandEvent& event)
    { m_Prn -> PageSetup(); }
    void OnPrint(wxCommandEvent& event)
    { m_Prn -> PrintText(m_Name); }
    void OnPreview(wxCommandEvent& event)
    { m_Prn -> PreviewText(m_Name); }
    void OnQuit(wxCommandEvent& event)
    { Close(TRUE); }
   /* void OnMenu(wxMouseEvent& event)
    {
        wxLogDebug(wxT("OnRight"));
        wxMenu menuFile(wxT("Printing Menu"));
        menuFile.Append(ID_HTML_PAGESETUP, _("Page Setup"));
        menuFile.Append(ID_HTML_PRINTSETUP, _("Printer Setup"));
        menuFile.Append(ID_HTML_PRINT, _("Print..."));
        menuFile.Append(ID_HTML_PREVIEW, _("Preview..."));
        menuFile.AppendSeparator();
        menuFile.Append(ID_HTML_QUIT, _("&Exit"));
        wxPoint pt = event.GetPosition();
        PopupMenu(&menuFile, pt);
    }*/
    void SetPage(const wxString& html) { m_Name = html; m_html->SetPage(html); }
    
   
 private:
    wxString m_Name; // the html to display/print
    wxHtmlEasyPrinting *m_Prn;
    wxHtmlWindow * m_html;     
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(YardHTML, wxDialog)
    EVT_BUTTON(ID_HTML_QUIT, YardHTML::OnQuit)
    EVT_BUTTON(ID_HTML_PRINT, YardHTML::OnPrint)
    EVT_BUTTON(ID_HTML_PREVIEW, YardHTML::OnPreview)
    EVT_BUTTON(ID_HTML_PAGESETUP, YardHTML::OnPageSetup)
    EVT_BUTTON(ID_HTML_PRINTSETUP, YardHTML::OnPrintSetup)
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(YardReports, wxDialog)
    EVT_BUTTON(XRCID("ID_REPORT_EMP_HOURS"), YardReports::OnReportEmpHours)
    EVT_BUTTON(XRCID("ID_REPORT_EMP_SALES"), YardReports::OnReportEmpSales)
    EVT_BUTTON(XRCID("ID_REPORT_HOURLY_REV"), YardReports::OnReportHourlyRev)
    EVT_BUTTON(XRCID("ID_REPORT_LEAVE"), YardReports::OnLeave)
END_EVENT_TABLE()

YardReports::YardReports(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos,const wxSize& size, long style,
               const wxString& name): wxDialog(parent, id, title, pos, size, style, name)
{
    wxBusyCursor busy();
    wxXmlResource::Get()->Load("res/reports.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "Reports");
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());  
    Centre();    
    if (wxGetApp().Full())
        ShowFullScreen(true);
    
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
    
    GenerateGraph(xml,"Last_Name", "PROFIT"); 
    
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
    
    GenerateGraph(xml,"HOUR", "PROFIT"); 
    
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

void YardReports::GenerateGraph(const string& xml, const string& labelname, const string& data)
{
#ifdef YS_CHART
    wxLogDebug(wxT("Creating chart..."));
    XMLNode node(xml, XMLNode::Str);
    
    unsigned int numlabels = node.numChildren("record");
   // unsigned int numdata = node.numChildren(data);
    
   // if (numlabels != numdata)
  //  {
   //     wxLogDebug(wxT("Data mismatch, can't continue."));
  //      return;
   // }
    
    wxLogDebug(wxT("%d labels."), numlabels);
    
    char ** labels = new char*[numlabels];
    float * fl_data = new float[numlabels];
    for (int i = 0; i < numlabels; i++)
    {
        labels[i] = new char[node.child("record", i).child(labelname).data().length() + 1];
        strcpy(labels[i], node.child("record", i).child(labelname).data().c_str());
        labels[i][node.child("record", i).child(labelname).data().length()]='\0';
        
        fl_data[i] = XMLNode::ToDouble(node.child("record", i).child(data).data());
        
        wxLogDebug(wxT("Label: %s, Data: %f"), labels[i], fl_data[i]);
    }

    
    /* labels */
    /*
	char		*lbl[] = { "CPQ\n(DEC)",
						   "HP",
						   "SCO",
						   "IBM",
						   "SGI",
						   "SUN\nSPARC",
						   "other" }; */
	/* values to chart */
/*	float		 p[] = { 12.5,
						 20.1,
						 2.0,
						 22.0,
						 5.0,
						 18.0,
						 13.0 };*/

	FILE		*fp = fopen( "res/report.png", "wb" );

	/* set which slices to explode, and by how much */
	/*int				expl[] = { 0, 0, 0, 0, 0, 20, 0 };*/

	/* set missing slices */
	//unsigned char	missing[] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE };

	/* colors */
	unsigned long	clr[] = { 0xFF4040L, 0x80FF80L, 0x8080FFL, 0xFF80FFL, 0xFFFF80L, 0x80FFFFL, 0x0080FFL };

	/* set options  */
	/* a lot of options are set here for illustration */
	/* none need be - see gdcpie.h for defaults */
	GDCPIE_title = "YardSale Report"; 
	GDCPIE_label_line = TRUE;
	GDCPIE_label_dist = 15;				/* dist. labels to slice edge */
										/* can be negative */
	GDCPIE_LineColor = 0x000000L;
	GDCPIE_label_size = GDC_SMALL;
	GDCPIE_3d_depth  = 25;
	GDCPIE_3d_angle  = 180;				/* 0 - 359 */
	GDCPIE_perspective = 70;				/* 0 - 99 */
	//GDCPIE_explode   = expl;			/* default: NULL - no explosion */
	GDCPIE_Color     = clr;
	GDCPIE_BGColor   = 0xFFFFFFL;
/*	GDCPIE_EdgeColor = 0x000000L;		   default is GDCPIE_NOCOLOR */ 
										/* for no edging */
	//GDCPIE_missing   = missing;			/* default: NULL - none missing */

										/* add percentage to slice label */
										/* below the slice label */
	GDCPIE_percent_labels = GDCPIE_PCT_BELOW;
	GDC_image_type     = GDC_PNG;
	/* call the lib */
	GDC_out_pie( 300,			/* width */
				 200,			/* height */
				 fp,			/* open file pointer */
				 GDC_3DPIE,		/* or GDC_2DPIE */
				 numlabels,				/* number of slices */
				 labels,			/* can be NULL */
				 fl_data );			/* data array */

	fclose( fp );
    
    
    // fuckme  i hate char arrays
    for (int i = 0; i < numlabels; i++)
        delete [] labels[i];
    
    delete [] labels;
    delete [] fl_data;

#endif
    
}

 void YardReports::OnLeave(wxCommandEvent& event)
{
    EndModal(0);
    
}
