
#ifndef SKUNK_NEW_EMPLOY_H
#define SKUNK_NEW_EMPLOY_H

#include "wx/wx.h"
#include "wx/wizard.h"
#include "wx/image.h"
#include "wx/filedlg.h"
#include "extra/xrc/xmlres.h"

class SkunkNewEmployee: public wxWizard
{
 public:
     SkunkNewEmployee(wxWindow* parent, int id = -1, const wxString& title = wxEmptyString, 
        const wxBitmap& bitmap = wxNullBitmap, const wxPoint& pos = wxDefaultPosition)
        :wxWizard(parent, id, title, bitmap, pos) 
    {
        wxXmlResource::Get()->Load("res/new_employee.xrc");
    }
    
    YardEmployeeType GetEmployee() { return m_employ; }
    
  private:
    YardEmployeeType m_employ;      
};

class SkunkNewEmployee1: public wxWizardPageSimple
{
 public:
    SkunkNewEmployee1(SkunkNewEmployee *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "NewEmploy1");
        m_first = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_FIRST")));
        m_middle = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_MIDDLE")));
        m_last = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_LAST")));
        m_phone = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_PHONE")));        
    }

    virtual bool TransferDataFromWindow()
    {
        m_parent->m_employ.SetFirst(m_first->GetValue().c_str());
        m_parent->m_employ.SetMiddle(m_middle->GetValue().c_str());
        m_parent->m_employ.SetLast(m_last->GetValue().c_str());
        m_parent->m_employ.SetPhone(m_phone->GetValue().c_str());
        return true;
    }

 private:
    SkunkNewEmployee * m_parent;
    wxTextCtrl * m_first;
    wxTextCtrl * m_middle;
    wxTextCtrl * m_last;
    wxTextctrl * m_phone;
      
};
class SkunkNewEmployee2: public wxWizardPageSimple
{
 public:
    SkunkNewEmployee2(SkunkNewEmployee *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "NewEmploy2");
        m_address = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_ADDRESS")));
        m_city = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_CITY")));
        m_state = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_STATE")));
        m_zip = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_ZIP")));        
    }

    virtual bool TransferDataFromWindow()
    {
        m_parent->m_employ.SetAddress(m_address->GetValue().c_str());
        m_parent->m_employ.SetCity(m_city->GetValue().c_str());
        m_parent->m_employ.SetState(m_state->GetValue().c_str());
        m_parent->m_employ.SetZip(m_zip->GetValue().c_str());
        return true;
    }

 private:
    SkunkNewEmployee * m_parent;
    wxTextCtrl * m_address;
    wxTextCtrl * m_city;
    wxTextCtrl * m_state;
    wxTextctrl * m_zip;
      
};

class SkunkNewEmployee3: public wxWizardPageSimple
{
 public:
    SkunkNewEmployee3(SkunkNewEmployee *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "NewEmploy3");
        m_pic = static_cast<wxStaticBitmap *>(FindWindow(XRCID("ID_EMP_PIC")));
        m_sig = static_cast<wxStaticBitmap *>(FindWindow(XRCID("ID_EMP_SIG")));
               
    }
    
    void OnSig(wxCommandEvent& event)
    {
        m_sigloc = wxFileSelector(wxT("Select a signature file"), "", "",
            ".jpg", "*.jpg", wxFILE_MUST_EXIST, this);
        
        wxImage sig(m_sigloc, wxBITMAP_TYPE_JPEG);
        if (sig.Ok())
        {
            sig.Rescale(200,50);
            m_sig->SetBitmap(sig);
        }
        else
        {
            m_sigloc = "";
            wxLogDebug(wxT("Bad image data."));
        }
    }
    
    void OnPic(wxCommandEvent& event)
    {
        m_picloc = wxFileSelector(wxT("Select a picture file"), "", "",
            ".jpg", "*.jpg", wxFILE_MUST_EXIST, this);
        
        wxImage pic(m_picloc, wxBITMAP_TYPE_JPEG);
        if (pic.Ok())
        {
            pic.Rescale(128,128);
            m_sig->SetBitmap(pic);
        }
        else
        {
            m_picloc = "";
            wxLogDebug(wxT("Bad image data."));
        }
    }

    virtual bool TransferDataFromWindow()
    {
        m_parent->m_employ.SetSig(m_sigloc.c_str());
        m_parent->m_employ.SetPicture(m_picloc.c_str());
        return true;
    }

 private:
    SkunkNewEmployee * m_parent;
    wxStaticBitmap * m_pic;
    wxStaticBitmap * m_sig;
    wxString m_sigloc;
    wxString m_picloc;
    DECLARE_EVENT_TABLE()
      
};

BEGIN_EVENT_TABLE(SkunkNewEmployee3, wxWizardPageSimple)
    EVT_BUTTON(XRCID("ID_EMP_PIC_SELECT"), SkunkNewEmployee3::OnPic)
    EVT_BUTTON(XRCID("ID_EMP_SELECT_SIG"), SkunkNewEmployee3::OnSig)
END_EVENT_TABLE()

#endif
