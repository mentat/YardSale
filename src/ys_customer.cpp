#include "extra/xrc/xmlres.h"
#include "wx/app.h"
#include "wx/listctrl.h"
#include "wx/treectrl.h"
#include "wx/sizer.h"
#include "wx/log.h"
#include "wx/stattext.h"

#include "ys_customer.h"
#include "ys_exception.h"
#include "ys_database.h"
#include "ys_new_cust.h"
#include "yardsale.h"

#include "images/worker_16x16.xpm"

DECLARE_APP(YardSale)

class custItemData: public wxTreeItemData
{
 public:
    custItemData(long id): 
        wxTreeItemData(), m_id(id) {}
	~custItemData() {}
	
	const long GetID() { return m_id; }

 private:
	long m_id;	
};

BEGIN_EVENT_TABLE(YardCustomer, wxDialog)
    EVT_TREE_SEL_CHANGED(XRCID("ID_CUST_TREE"), YardCustomer::OnChange)
    EVT_BUTTON(XRCID("ID_CUST_NEW"), YardCustomer::OnNew)
    EVT_BUTTON(XRCID("ID_CUST_EXIT"), YardCustomer::OnExit)
   // EVT_CLOSE(YardCustomer::OnClose)
    EVT_TEXT(-1, YardCustomer::OnModify)
    EVT_BUTTON(XRCID("ID_CUST_SAVE"), YardCustomer::OnSave)
END_EVENT_TABLE()

YardCustomer::YardCustomer(wxWindow* parent, wxWindowID id, 
    const wxString& title, const wxPoint& pos,
    const wxSize& size, long style, const wxString& name)
:wxDialog(parent, id, title, pos, size, style, name), m_loading(true) {
    wxBusyCursor busy();
    wxXmlResource::Get()->Load("res/customer.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "Customer");
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(wxSize(600,400));
    Centre();  
    
    
    m_pic = static_cast<wxStaticBitmap *>(FindWindow(XRCID("ID_CUST_PICTURE")));
    m_sig = static_cast<wxStaticBitmap *>(FindWindow(XRCID("ID_CUST_SIG")));
    m_tree = static_cast<wxTreeCtrl *>(FindWindow(XRCID("ID_CUST_TREE")));
    m_first = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_FIRST")));
    m_middle = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_MIDDLE")));
    m_last = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_LAST")));
    m_address = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_ADDRESS")));
    m_ccNum = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_CC")));
    m_ccName = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_CC_NAME")));
    m_ccExp = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_CC_EXP")));
    m_phone = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_PHONE")));
    m_custSince = static_cast<wxStaticText *>(FindWindow(XRCID("ID_CUST_SINCE")));
    m_save = static_cast<wxButton *>(FindWindow(XRCID("ID_CUST_SAVE")));
    
    CreateImageList(m_tree);
    LoadTreeItems(m_tree);
    //ID_CUST_PICTURE
    m_loading = false;
    
}

void YardCustomer::LoadTreeItems(wxTreeCtrl * tree)
{
    //tree->SetWindowStyleFlag(wxTR_NO_LINES | wxTR_HIDE_ROOT | wxTR_FULL_ROW_HIGHLIGHT);
    tree->AddRoot(wxT("Root"));
    tree->SetIndent(10);
	tree->SetSpacing(3);
    
    vector<YardCustType> customers;
    
    try {
        customers = wxGetApp().DB().CustomerGetAll();
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (cust load): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    wxLogDebug(wxT("Got %d customers"), customers.size());
    for (unsigned int i = 0; i < customers.size(); i++)
    {
        wxTreeItemId groupid = tree->AppendItem(tree->GetRootItem(),
            customers[i].GetFirstLast().c_str(), 0,0,
            new custItemData(customers[i].GetAccountNumber()));
    }
    
}

void YardCustomer::OnModify(wxCommandEvent& event)
{
 
    if (!m_loading) 
    {        
        wxLogDebug(wxT("OnModify"));
        m_save->Show(true);
    }
}

void YardCustomer::OnSave(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnSave")); 
       
    m_cust.SetFirstName(m_first->GetValue().c_str());
    m_cust.SetMiddleName(m_middle->GetValue().c_str());
    m_cust.SetLastName(m_last->GetValue().c_str());
    m_cust.SetAddress(m_address->GetValue().c_str());
    m_cust.SetPhone(m_phone->GetValue().c_str());
    
    try {
        //wxGetApp().DB().CustomerUpdate(m_cust);
    }
    catch (YardDBException& e)
    {
        wxMessageBox(wxT("Could not save information."), 
            wxT("Save Error"), wxOK, this);
        return;
    }

    m_save->Show(false);
    
}

void YardCustomer::OnClose(wxCloseEvent& event)
{ 
    if (event.CanVeto()) // if this isnt a forced close, load login
        GetParent()->Show();
    Destroy();
}

void YardCustomer::OnExit(wxCommandEvent& event)
{
    wxLogDebug(wxT("OnExit"));
    EndModal(0);
}
    
YardCustomer::~YardCustomer()
{
   

}

void YardCustomer::CreateImageList(wxTreeCtrl * tree)
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

void YardCustomer::OnChange(wxTreeEvent& event)
{
    m_loading = true;
    custItemData * data = static_cast<custItemData *>(m_tree->GetItemData(event.GetItem()));

    if (!data)
        return;
    
    try {
        m_cust = wxGetApp().DB().CustomerGet(data->GetID());
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (customer not loaded): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
        
    if (m_cust.GetPicLocal() != "")
    {
        wxImage pic(m_cust.GetPicLocal().c_str());
        if (pic.Ok())
            m_pic->SetBitmap(pic);
        else
            wxLogDebug(wxT("Bad image data (pic)."));
    }
    else
        m_pic->SetBitmap(wxImage("res/personal.png"));
    
    if (m_cust.GetSigLocal() != "")
    {
        wxImage sig(m_cust.GetSigLocal().c_str());
        if (sig.Ok())
            m_sig->SetBitmap(sig);
        else
            wxLogDebug(wxT("Bad image data (sig)."));
    }
    else
        m_sig->SetBitmap(wxNullBitmap);
    
    m_first->SetValue(m_cust.GetFirstName().c_str());
    m_middle->SetValue(m_cust.GetMiddleName().c_str());
    m_last->SetValue(m_cust.GetLastName().c_str());
    m_address->SetValue(m_cust.GetAddress().c_str());
    m_ccNum->SetValue(m_cust.GetCreditCardNumber().c_str());
    m_ccName->SetValue(m_cust.GetCreditCardName().c_str());
    m_ccExp->SetValue(m_cust.GetCreditCardExpiration().c_str());
    m_phone->SetValue(m_cust.GetPhone().c_str());
    wxString pos;
    pos.Printf(wxT("Customer Since: %s"), m_cust.GetSince().c_str());
    m_custSince->SetLabel(pos);
    
    m_loading = false;
}

void YardCustomer::OnNew(wxCommandEvent& event)
{
    wxBitmap logo("res/yast_sysadmin.png", wxBITMAP_TYPE_PNG);
    YardNewCustomer * wizard = new YardNewCustomer(this, -1, 
        wxT("New Customer Wizard"), logo);
    
    YardNewCustomer1 * page1 = new YardNewCustomer1(wizard);
    YardNewCustomer2 * page2 = new YardNewCustomer2(wizard);
    YardNewCustomer3 * page3 = new YardNewCustomer3(wizard);
    YardNewCustomer4 * page4 = new YardNewCustomer4(wizard);
    
    wxWizardPageSimple::Chain(page1, page2);
    wxWizardPageSimple::Chain(page2, page3);
    wxWizardPageSimple::Chain(page3, page4);
    
    wxSize min = page4->GetMin();
    wizard->SetPageSize(min);

    if ( wizard->RunWizard(page1) )
    {
        wxLogDebug(wxT("Wizard completed OK"));
        
        YardCustType temp = wizard->GetCustomer();
        YardDate now(wxDateTime::Now());
        temp.SetSince(now);
        try {
            wxGetApp().DB().CustomerAdd(temp);
        }
        catch (YardDBException& e)
        {
            wxLogDebug(wxT("Error (customer not added): %s, %s"),e.what(), e.GetSQL().c_str());
        }
    }
    wizard->Destroy();
    
}
