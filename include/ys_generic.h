#ifndef YS_GENERIC_EDIT_H
#define YS_GENERIC_EDIT_H

#include <vector>
#include "wx/wx.h"
#include "wx/listbox.h"
#include "extra/xrc/xmlres.h"

using namespace std;

template <typename T>
class YardGenericEdit: public wxDialog
{
 public:
     /// This is the constructor you will most commonly use.
    YardGenericEdit(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString& name = wxT("YardGenericEdit"))
        :wxDialog(parent, id, title, pos, size, style, name)
    {
        if (!wxXmlResource::Get()->Load("res/generic_wdr.xrc"))
        {
            wxLogError(wxT("Can't load resource"));
            return;
        }
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "Generic");
        if (!panel)
        {
            wxLogError(wxT("Can't load resource"));
            return;
        } 
        m_list = static_cast<wxListBox *>(FindWindow(XRCID("ID_GEN_LIST")));
        wxSizer * sizer = panel->GetSizer();
        sizer->SetSizeHints(this);
        SetSize(sizer->GetMinSize());   
        Centre();
        wxLogDebug(wxT("OnGeneric!"));
   
    }
    
    /// @todo Check for creation status or throw in constructor
    
    void OnAdd(wxCommandEvent& event)
    {
        T temp();
       // wxMessageBox
        
        
    }  
    void OnEnable(wxCommandEvent& event){}
    void OnDisable(wxCommandEvent& event){}
    void OnOK(wxCommandEvent& event){ EndModal(0); }
    void OnEdit(wxCommandEvent& event){}        
  
    void SetObjects(const vector<T>& objs)
    { 
        m_objects=objs;
        // lets find out whats up biatch
        
        m_list->Clear();
        wxString label;
        // type discovery
        
        
        
        for (unsigned int i = 0; i < objs.size(); i++)
        {   //fuck
            string t = objs[i].child(T::GetUnique()).property("type");
            m_list->Append(objs[i].child(T::GetUnique()).data().c_str());
                    
            wxLogDebug(wxT("Type is %s"), t.c_str());
            
            //label.Printf(wxT("%s (%3f/%"), objs[i].child(T::Get
        }
        //m_list->InsertColumn(0, T::GetUnique());
                
    }
    
    vector<T>& GetObjects() { return m_objects; }       
    
    /// Destructor
    virtual ~YardGenericEdit() {}
 private:
     DECLARE_EVENT_TABLE()
     wxListBox * m_list;
     vector<T> m_objects;
};

#define BEGIN_EVENT_TABLE_T(theClass,theType, baseClass) \
    template <typename theType> \
    const wxEventTable *theClass<theType>::GetEventTable() const \
        { return &theClass<theType>::sm_eventTable; } \
    template <typename theType> \
    const wxEventTable theClass<theType>::sm_eventTable = \
        { &baseClass::sm_eventTable, &theClass<theType>::sm_eventTableEntries[0] }; \
    template <typename theType> \
    const wxEventTableEntry theClass<theType>::sm_eventTableEntries[] = { \

BEGIN_EVENT_TABLE_T(YardGenericEdit, T, wxDialog)
    EVT_BUTTON(XRCID("ID_GEN_ADD"), YardGenericEdit::OnAdd)
    EVT_BUTTON(XRCID("ID_GEN_EDIT"), YardGenericEdit::OnEdit)
    EVT_BUTTON(XRCID("ID_GEN_ENABLE"), YardGenericEdit::OnEnable)
    EVT_BUTTON(XRCID("ID_GEN_DISABLE"), YardGenericEdit::OnDisable)
    EVT_BUTTON(XRCID("ID_GEN_OK"), YardGenericEdit::OnOK)
END_EVENT_TABLE()

#endif
