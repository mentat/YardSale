#include <vector>

#include "extra/xrc/xmlres.h"
#include "wx/app.h"
#include "wx/listctrl.h"
#include "wx/treectrl.h"
#include "wx/sizer.h"
#include "wx/log.h"

#include "yardsale.h"
#include "ys_exception.h"
#include "ys_group.h"
#include "ys_inv_type.h"
#include "ys_sale.h"
#include "ys_database.h"

#include "images/sprocket_32x32.xpm"
#include "images/paperclip_32x32.xpm"
#include "images/package_32x32.xpm"
#include "images/electronics_32x32.xpm"

using namespace std;

BEGIN_EVENT_TABLE(YardSaleScreen, wxDialog)
    //EVT_BUTTON(ID_SALE_BACK, YardSaleScreen::OnExitButton)
    EVT_TREE_SEL_CHANGED(XRCID("ID_SALE_TREE"), YardSaleScreen::OnChange)
END_EVENT_TABLE()

DECLARE_APP(YardSale)

// -1 is group
class invItemData: public wxTreeItemData
{
 public:
    invItemData(long id): 
        wxTreeItemData(), m_id(id) {}
	~invItemData() {}
	
	const long GetID() { return m_id; }

 private:
	long m_id;	
};

YardSaleScreen::YardSaleScreen(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style, const wxString& name)
:wxDialog(parent, id, title, pos, size, style, name) {
    
    wxXmlResource::Get()->Load("res/sale.xrc");
    wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "Sale");
    wxSizer * sizer = panel->GetSizer();
    sizer->SetSizeHints(this);
    SetSize(sizer->GetMinSize());   
    Centre();
    
    m_list = static_cast<wxListCtrl *>(FindWindow(XRCID("ID_SALE_TRANS")));
    m_list->InsertColumn(0, wxT("Count"));
    m_list->InsertColumn(1, wxT("Description"));
    m_list->InsertColumn(2, wxT("Price"));
    m_list->SetColumnWidth(0, wxLIST_AUTOSIZE);
    m_list->SetColumnWidth(1, wxLIST_AUTOSIZE);
    m_list->SetColumnWidth(2, wxLIST_AUTOSIZE);
    
    m_tree = static_cast<wxTreeCtrl *>(FindWindow(XRCID("ID_SALE_TREE")));
    
    CreateImageList(m_tree);
    LoadTreeItems(m_tree);
    
}

void YardSaleScreen::CreateImageList(wxTreeCtrl * tree)
{
 	// Make an image list containing small icons
    wxImageList *images = new wxImageList(32, 32, true);

    wxIcon icons[4];
	
    icons[0] = wxIcon(sprocket_32x32_xpm);
    icons[1] = wxIcon(paperclip_32x32_xpm);
    icons[2] = wxIcon(package_32x32_xpm);
    icons[3] = wxIcon(electronics_32x32_xpm);
	
    for ( size_t i = 0; i < WXSIZEOF(icons); i++ )
    { 
		images->Add(wxBitmap(icons[i]));
    }

    tree->AssignImageList(images);
    m_list->SetImageList(images,wxIMAGE_LIST_NORMAL); // the list wont delete them
}

void YardSaleScreen::LoadTreeItems(wxTreeCtrl * tree)
{
    tree->SetWindowStyleFlag(wxTR_NO_LINES | wxTR_HIDE_ROOT | wxTR_FULL_ROW_HIGHLIGHT);
    tree->AddRoot(wxT("Root"));
    tree->SetIndent(10);
	tree->SetSpacing(3);
    // load groups first
    
    vector<YardGroup> groups;
    
    try {
        groups = wxGetApp().DB().GroupGetAll();
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (grp load): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    
    for (unsigned int i = 0; i < groups.size(); i++)
    {
        wxTreeItemId groupid = tree->AppendItem(tree->GetRootItem(),
            groups[i].GetName().c_str(), 2,2,new invItemData(-1));
        
        vector<YardInvType> items;
        try {
            items = wxGetApp().DB().InventoryGetInGroup(groups[i].GetId());
        }
        catch (YardDBException& e)            
        {
            wxLogDebug(wxT("Error (item load): %s, %s"),e.what(), e.GetSQL().c_str());
            return;
        }
        for (int k = 0; k < items.size(); k++)
        {
            int img = items[k].GetGroupId() %  4;
            tree->AppendItem(groupid, items[k].GetName().c_str(), img, img,
                new invItemData(items[k].GetKey()));
        }
    }
}

void YardSaleScreen::OnChange(wxTreeEvent& event)
{
    invItemData * data = static_cast<invItemData *>(m_tree->GetItemData(event.GetItem()));

    if (!data)
        return;
    
    YardInvType temp;
    try {
        temp = wxGetApp().DB().InventoryGet(data->GetID());
    }
    catch (YardDBException& e)
    {
        wxLogDebug(wxT("Error (item not loaded): %s, %s"),e.what(), e.GetSQL().c_str());
        return;
    }
    
    m_items.push_back(temp);
    m_list->InsertItem(0, temp.GetName().c_str(), temp.GetGroupId() % 4);
     
    
    
}

YardSaleScreen::~YardSaleScreen()
{
    
}

void YardSaleScreen::OnExitButton(wxCommandEvent & event)
{
    EndModal(0);
}
