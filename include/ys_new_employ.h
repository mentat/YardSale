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
#ifndef SKUNK_NEW_EMPLOY_H
#define SKUNK_NEW_EMPLOY_H
#include <string>
#include <map>

#include "wx/wx.h"
#include "wx/wizard.h"
#include "wx/image.h"
#include "wx/filedlg.h"
#include "extra/xrc/xmlres.h"
#include "yardsale.h"
#include "ys_exception.h"

using namespace std;

DECLARE_APP(YardSale)

class YardNewEmployee: public wxWizard
{
 public:
     YardNewEmployee(wxWindow* parent, int id = -1, const wxString& title = wxEmptyString, 
        const wxBitmap& bitmap = wxNullBitmap, const wxPoint& pos = wxDefaultPosition)
        :wxWizard(parent, id, title, bitmap, pos) 
    {
        wxXmlResource::Get()->Load("res/new_employee.xrc");
    }
    
    YardEmployeeType& GetEmployee() { return m_employ; }
    
  private:
    YardEmployeeType m_employ;      
};

class YardNewEmployee1: public wxWizardPageSimple
{
 public:
    YardNewEmployee1(YardNewEmployee *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "NewEmploy1");
        m_first = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_FIRST")));
        m_middle = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_MIDDLE")));
        m_last = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_LAST")));
        m_taxid = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_TAXID")));          
    }

    virtual bool TransferDataFromWindow()
    {
        m_parent->GetEmployee().SetFirstName(m_first->GetValue().c_str());
        m_parent->GetEmployee().SetMiddleName(m_middle->GetValue().c_str());
        m_parent->GetEmployee().SetLastName(m_last->GetValue().c_str());
        
        wxString id = m_taxid->GetValue().c_str();
        id.Replace("-",""); // try to take out all dashes
        long lId;
        if (id.ToLong(&lId))
            m_parent->GetEmployee().SetTaxId(lId);
        else
        {
            wxMessageBox("The Tax ID must only contain numbers and dashes.", "TAX ID",
                            wxOK, GetParent());
            return false;
        }
        return true;
    }

 private:
    YardNewEmployee * m_parent;
    wxTextCtrl * m_first;
    wxTextCtrl * m_middle;
    wxTextCtrl * m_last;
    wxTextCtrl * m_taxid;
   
      
};
class YardNewEmployee2: public wxWizardPageSimple
{
 public:
    YardNewEmployee2(YardNewEmployee *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "NewEmploy2");
        m_address = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_ADDRESS")));
        m_city = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_CITY")));
        m_state = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_STATE")));
        m_zip = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_ZIP"))); 
        m_phone = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_EMP_PHONE")));
        m_position = static_cast<wxComboBox*>(FindWindow(XRCID("ID_EMP_POSITION")));
        
        map<string, string> acl;
        try {
            acl = wxGetApp().DB().ACLGetAll();
        }
        catch (YardDBException& e)
        { wxLogDebug(wxT("Could not load ACLs")); return; }
        for (map<string, string>::iterator it = acl.begin(); it != acl.end(); it++)
            m_position->Append(it->first.c_str());
                
    }

    virtual bool TransferDataFromWindow()
    {
        m_parent->GetEmployee().SetAddress(m_address->GetValue().c_str());
        m_parent->GetEmployee().SetCity(m_city->GetValue().c_str());
        m_parent->GetEmployee().SetState(m_state->GetValue().c_str());
        m_parent->GetEmployee().SetZip(m_zip->GetValue().c_str());
        m_parent->GetEmployee().SetPhone(m_phone->GetValue().c_str());
        if (m_position->GetStringSelection() == "")
        {
            wxMessageBox("The position field must not be empty.", "Position",
                            wxOK, this);
            return false;
        }
        m_parent->GetEmployee().SetACL(m_position->GetStringSelection().c_str());
        return true;
    }

 private:
    YardNewEmployee * m_parent;
    wxTextCtrl * m_address;
    wxTextCtrl * m_city;
    wxTextCtrl * m_state;
    wxTextCtrl * m_zip;
    wxTextCtrl * m_phone;
    wxComboBox * m_position;
      
};

class YardNewEmployee3: public wxWizardPageSimple
{
 public:
    YardNewEmployee3(YardNewEmployee *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "NewEmploy3");
        m_min = panel->GetSizer()->CalcMin();
        m_pic = static_cast<wxStaticBitmap *>(FindWindow(XRCID("ID_EMP_PIC")));
        m_sig = static_cast<wxStaticBitmap *>(FindWindow(XRCID("ID_EMP_SIG")));
               
    }
    
    void OnSig(wxCommandEvent& event)
    {
        m_sigloc = wxFileSelector(wxT("Select a signature file"), "", "",
            ".jpg", "*.jpg", wxFILE_MUST_EXIST, GetParent());
        
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
            ".jpg", "*.jpg", wxFILE_MUST_EXIST, GetParent());
        
        wxImage pic(m_picloc, wxBITMAP_TYPE_JPEG);
        if (pic.Ok())
        {
            pic.Rescale(128,128);
            m_pic->SetBitmap(pic);
        }
        else
        {
            m_picloc = "";
            wxLogDebug(wxT("Bad image data."));
        }
    }

    virtual bool TransferDataFromWindow()
    {
        m_parent->GetEmployee().SetSig(m_sigloc.c_str());
        m_parent->GetEmployee().SetPicture(m_picloc.c_str());
        return true;
    }
    
    wxSize GetMin() { return m_min; }

 private:
    wxSize m_min;
    YardNewEmployee * m_parent;
    wxStaticBitmap * m_pic;
    wxStaticBitmap * m_sig;
    wxString m_sigloc;
    wxString m_picloc;
    DECLARE_EVENT_TABLE()
      
};

BEGIN_EVENT_TABLE(YardNewEmployee3, wxWizardPageSimple)
    EVT_BUTTON(XRCID("ID_EMP_PIC_SELECT"), YardNewEmployee3::OnPic)
    EVT_BUTTON(XRCID("ID_EMP_SELECT_SIG"), YardNewEmployee3::OnSig)
END_EVENT_TABLE()

#endif
