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
#ifndef SKUNK_NEW_CUST_H
#define SKUNK_NEW_CUST_H
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

/**
 * The new customer wizard.
 * \image html customer_wizard.png
 * @author Jesse Lovelace
*/
class YardNewCustomer: public wxWizard
{
 public:
     YardNewCustomer(wxWindow* parent, int id = -1, const wxString& title = wxEmptyString, 
        const wxBitmap& bitmap = wxNullBitmap, const wxPoint& pos = wxDefaultPosition)
        :wxWizard(parent, id, title, bitmap, pos) 
    {
        wxXmlResource::Get()->Load("res/new_customer.xrc");
    }
    
    YardCustType& GetCustomer() { return m_cust; }
    
  private:
    YardCustType m_cust;      
};

class YardNewCustomer1: public wxWizardPageSimple
{
 public:
    YardNewCustomer1(YardNewCustomer *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "NewCust1");
        m_first = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_FIRST")));
        m_middle = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_MIDDLE")));
        m_last = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_LAST")));
    }

    virtual bool TransferDataFromWindow()
    {
        m_parent->GetCustomer().SetFirstName(m_first->GetValue().c_str());
        m_parent->GetCustomer().SetMiddleName(m_middle->GetValue().c_str());
        m_parent->GetCustomer().SetLastName(m_last->GetValue().c_str());
        return true;
    }

 private:
    YardNewCustomer * m_parent;
    wxTextCtrl * m_first;
    wxTextCtrl * m_middle;
    wxTextCtrl * m_last;
      
};

class YardNewCustomer2: public wxWizardPageSimple
{
 public:
    YardNewCustomer2(YardNewCustomer *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "NewCust2");
        m_address = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_ADDRESS")));
        m_city = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_CITY")));
        m_state = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_STATE")));
        m_zip = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_ZIP"))); 
        m_phone = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_PHONE")));
                
    }

    virtual bool TransferDataFromWindow()
    {
        m_parent->GetCustomer().SetAddress(m_address->GetValue().c_str());
        m_parent->GetCustomer().SetCity(m_city->GetValue().c_str());
        m_parent->GetCustomer().SetState(m_state->GetValue().c_str());
        m_parent->GetCustomer().SetZip(m_zip->GetValue().c_str());
        m_parent->GetCustomer().SetPhone(m_phone->GetValue().c_str());
        return true;
    }

 private:
    YardNewCustomer * m_parent;
    wxTextCtrl * m_address;
    wxTextCtrl * m_city;
    wxTextCtrl * m_state;
    wxTextCtrl * m_zip;
    wxTextCtrl * m_phone;
      
};

class YardNewCustomer3: public wxWizardPageSimple
{
 public:
    YardNewCustomer3(YardNewCustomer *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "NewCust3");
        m_ccNum = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_CC")));
        m_ccName = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_CC_NAME")));
        m_ccExp = static_cast<wxTextCtrl *>(FindWindow(XRCID("ID_CUST_CC_EXP")));
                
    }

    virtual bool TransferDataFromWindow()
    {
        m_parent->GetCustomer().SetCreditCardNumber(m_ccNum->GetValue().c_str());
        m_parent->GetCustomer().SetCreditCardName(m_ccName->GetValue().c_str());
        m_parent->GetCustomer().SetCreditCardExpiration(m_ccExp->GetValue().c_str());
        return true;
    }

 private:
    YardNewCustomer * m_parent;
    wxTextCtrl * m_ccNum;
    wxTextCtrl * m_ccName;
    wxTextCtrl * m_ccExp;
      
};

class YardNewCustomer4: public wxWizardPageSimple
{
 public:
    YardNewCustomer4(YardNewCustomer *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "NewCust4");
        m_min = panel->GetSizer()->CalcMin();
        m_pic = static_cast<wxStaticBitmap *>(FindWindow(XRCID("ID_CUST_PIC")));
        m_sig = static_cast<wxStaticBitmap *>(FindWindow(XRCID("ID_CUST_SIG")));
               
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
        m_parent->GetCustomer().SetSignature(m_sigloc.c_str());
        m_parent->GetCustomer().SetPicture(m_picloc.c_str());
        return true;
    }
    
    wxSize GetMin() { return m_min; }

 private:
    wxSize m_min;
    YardNewCustomer * m_parent;
    wxStaticBitmap * m_pic;
    wxStaticBitmap * m_sig;
    wxString m_sigloc;
    wxString m_picloc;
    DECLARE_EVENT_TABLE()
      
};

BEGIN_EVENT_TABLE(YardNewCustomer4, wxWizardPageSimple)
    EVT_BUTTON(XRCID("ID_CUST_PIC_SELECT"), YardNewCustomer4::OnPic)
    EVT_BUTTON(XRCID("ID_CUST_SELECT_SIG"), YardNewCustomer4::OnSig)
END_EVENT_TABLE()

#endif
