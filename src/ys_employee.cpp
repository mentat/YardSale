#include "extra/xrc/xmlres.h"
#include "wx/app.h"
#include "wx/listctrl.h"
#include "wx/treectrl.h"
#include "wx/sizer.h"
#include "wx/log.h"
#include "wx/stattext.h"

#include "ys_employee.h"
#include "ys_exception.h"
#include "ys_database.h"
#include "ys_new_employ.h"
#include "yardsale.h"

#include "images/worker_16x16.xpm"

DECLARE_APP(YardSale)

class empItemData: public wxTreeItemData
{
 public:
    empItemData(long id): 
        wxTreeItemData(), m_id(id) {}
	~empItemData() {}
	
	const long GetID() { return m_id; }

 private:
	long m_id;	
};

BEGIN_EVENT_TABLE(YardEmployee, wxDialog)
    EVT_TREE_SEL_CHANGED(XRCID("ID_EMPLOY_TREE"), YardEmployee::OnChange)
    EVT_BUTTON(XRCID("ID_EMPLOY_NEW"), YardEmployee::OnNew)
    EVT_BUTTON(XRCID("ID_EMPLOY_EXIT"), YardEmployee::OnClose)
END_EVENT_TABLE()

YardEmployee::YardEmployee(wxWindow* parent, wxWindowID id, 
    const wxString& title, const wxPoint& pos,
    const wxSize& size, long style, const wxString& name)
:wxDialog(parent, id, title, pos, size, style, name) {
    wxBusyCursor busy();
    wxXmlResource::Get()->Load("res/employee.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "Employee");
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());  
    Centre();
    if (wxGetApp().Full())
        ShowFullScreen(true);
    
    m_pic = static_cast<wxStaticBitmap *>(FindWindow(XRCID("ID_EMPLOY_PICTURE")));
    m_sig = static_cast<wxStaticBitmap *>(FindWindow(XRCID("ID_EMPLOY_SIG")));
    m_tree = static_cast<wxTreeCtrl *>(FindWindow(XRCID("ID_EMPLOY_TREE")));
    m_first = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMPLOY_FIRST")));
    m_middle = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMPLOY_MIDDLE")));
    m_last = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMPLOY_LAST")));
    m_address = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMPLOY_ADDRESS")));
    m_id = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMPLOY_ID")));
    m_taxid = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMPLOY_TAX_ID")));
    m_phone = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMPLOY_PHONE")));
    m_position = static_cast<wxStaticText *>(FindWindow(XRCID("ID_EMPLOY_POSITION")));
    
    m_id->Enable(false);
    
    CreateImageList(m_tree);
    LoadTreeItems(m_tree);
    //ID_EMPLOY_PICTURE
    
}

void YardEmployee::LoadTreeItems(wxTreeCtrl * tree)
{
    tree->SetWindowStyleFlag(wxTR_NO_LINES | wxTR_HIDE_ROOT | wxTR_FULL_ROW_HIGHLIGHT);
    tree->AddRoot(wxT("Root"));
    tree->SetIndent(10);
	tree->SetSpacing(3);
    
    vector<YardEmployeeType> employees;
    
    try {
        employees = wxGetApp().DB().EmployeeGetAll();
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (emp load): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    wxLogDebug(wxT("Got %d employees"), employees.size());
    for (unsigned int i = 0; i < employees.size(); i++)
    {
        wxTreeItemId groupid = tree->AppendItem(tree->GetRootItem(),
            employees[i].GetFirstLast().c_str(), 0,0,
            new empItemData(employees[i].GetId()));
    }
    
}

void YardEmployee::OnClose(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnClose"));
    EndModal(0);
    
}
    
YardEmployee::~YardEmployee()
{
   

}

void YardEmployee::CreateImageList(wxTreeCtrl * tree)
{
 	// Make an image list containing small icons
    wxImageList *images = new wxImageList(16, 16, true);

    wxIcon icons[1];
	
    icons[0] = wxIcon(worker_16x16_xpm);
	
    for ( size_t i = 0; i < WXSIZEOF(icons); i++ )
    { 
		images->Add(wxBitmap(icons[i]));
    }

    tree->AssignImageList(images);
}

void YardEmployee::OnChange(wxTreeEvent& event)
{
    empItemData * data = static_cast<empItemData *>(m_tree->GetItemData(event.GetItem()));

    if (!data)
        return;
    
    try {
        m_emp = wxGetApp().DB().EmployeeGet(data->GetID());
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (employee not loaded): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
        
    if (m_emp.GetPicLocal() != "")
    {
        wxImage pic(m_emp.GetPicLocal().c_str());
        if (pic.Ok())
            m_pic->SetBitmap(pic);
        else
            wxLogDebug(wxT("Bad image data (pic)."));
    }
    else
        m_pic->SetBitmap(wxImage("res/ys_employee_128x128.png"));
    
    if (m_emp.GetSigLocal() != "")
    {
        wxImage sig(m_emp.GetSigLocal().c_str());
        if (sig.Ok())
            m_sig->SetBitmap(sig);
        else
            wxLogDebug(wxT("Bad image data (sig)."));
    }
    else
        m_sig->SetBitmap(wxImage("res/empty_200x50.png"));
    
    m_first->SetValue(m_emp.GetFirst().c_str());
    m_middle->SetValue(m_emp.GetMiddle().c_str());
    m_last->SetValue(m_emp.GetLast().c_str());
    m_address->SetValue(m_emp.GetAddress().c_str());
    m_id->SetValue(m_emp.GetIdS().c_str());
    m_taxid->SetValue(m_emp.GetTaxIdS().c_str());
    m_phone->SetValue(m_emp.GetPhone().c_str());
    wxString pos;
    pos.Printf(wxT("Title: %s"), m_emp.GetACL().c_str());
    m_position->SetLabel(pos);
}

void YardEmployee::OnNew(wxCommandEvent& event)
{
    wxBitmap logo("res/yast_sysadmin.png", wxBITMAP_TYPE_PNG);
    YardNewEmployee * wizard = new YardNewEmployee(this, -1, 
        wxT("New Employee Wizard"), logo);
    
    YardNewEmployee1 * page1 = new YardNewEmployee1(wizard);
    YardNewEmployee2 * page2 = new YardNewEmployee2(wizard);
    YardNewEmployee3 * page3 = new YardNewEmployee3(wizard);
    
    wxWizardPageSimple::Chain(page1, page2);
    wxWizardPageSimple::Chain(page2, page3);
    
    wxSize min = page3->GetMin();
    wizard->SetPageSize(min);

    if ( wizard->RunWizard(page1) )
    {
        wxLogDebug(wxT("Wizard completed OK"));
        
        YardEmployeeType temp = wizard->GetEmployee();
        
        try {
            wxGetApp().DB().EmployeeAdd(temp);
        }
        catch (YardDBException& e)
        {
            wxLogDebug(wxT("Error (employee not added): %s, %s"),e.what(), e.GetSQL().c_str());
        }
    }
    wizard->Destroy();
    
}
