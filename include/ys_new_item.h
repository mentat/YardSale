#ifndef YS_NEW_ITEM_H
#define YS_NEW_ITEM_H
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

class YardNewItem: public wxWizard
{
 public:
     YardNewItem(wxWindow* parent, int id = -1, const wxString& title = wxEmptyString, 
        const wxBitmap& bitmap = wxNullBitmap, const wxPoint& pos = wxDefaultPosition)
        :wxWizard(parent, id, title, bitmap, pos) 
    {
        wxXmlResource::Get()->Load("res/new_inv_wiz_wdr.xrc");
    }
    
    YardInvType& GetItem() { return m_item; }
    
  private:
    YardInvType m_item;      
};

class YardNewItem1: public wxWizardPageSimple
{
 public:
    YardNewItem1(YardNewItem *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "InvDetailsW");
        
        m_det_sku = static_cast<wxTextCtrl *>(FindWindow(XRCID("WID_INV_SKU")));
        m_det_name = static_cast<wxTextCtrl *>(FindWindow(XRCID("WID_INV_ITEMNAME")));
        m_det_desc = static_cast<wxTextCtrl *>(FindWindow(XRCID("WID_INV_DESC")));
        m_det_barcode = static_cast<wxTextCtrl *>(FindWindow(XRCID("WID_INV_BARCODE")));
        m_det_dept = static_cast<wxComboBox *>(FindWindow(XRCID("WID_INV_DEPARTMENT")));
        m_dep_group = static_cast<wxComboBox *>(FindWindow(XRCID("WID_INV_GROUP")));
        m_dep_image = static_cast<wxStaticBitmap *>(FindWindow(XRCID("WID_INV_IMAGE")));
        m_dep_vendor = static_cast<wxComboBox *>(FindWindow(XRCID("WID_INV_VENDOR")));
                  
    }

    virtual bool TransferDataFromWindow()
    {
        return true;
    }

 private:
    YardNewItem * m_parent;
    wxTreeCtrl * m_tree;
    wxTextCtrl * m_det_sku;
    wxTextCtrl * m_det_name;
    wxTextCtrl * m_det_desc;
    wxTextCtrl * m_det_barcode;
    wxComboBox * m_det_dept;
    wxComboBox * m_dep_group;
    wxStaticBitmap * m_dep_image;
    wxComboBox * m_dep_vendor;
   
      
};

class YardNewItem2: public wxWizardPageSimple
{
 public:
    YardNewItem2(YardNewItem *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "InvPricingW");
        
        m_price_retail = static_cast<wxTextCtrl *>(FindWindow(XRCID("WID_INV_PRICE")));
        m_price_wholesale = static_cast<wxTextCtrl *>(FindWindow(XRCID("WID_INV_WHOLESALE")));
        m_price_bulk = static_cast<wxListCtrl *>(FindWindow(XRCID("WID_INV_BULK_TALBE")));
        m_price_tax = static_cast<wxComboBox *>(FindWindow(XRCID("WID_INV_TAX")));
         
    }

    virtual bool TransferDataFromWindow()
    {

        //m_parent->GetEmployee().SetACL(m_position->GetStringSelection().c_str());
        return true;
    }

 private:
    YardNewItem * m_parent;
    wxTextCtrl * m_price_retail;
    wxTextCtrl * m_price_wholesale;
    wxListCtrl * m_price_bulk;
    wxComboBox * m_price_tax;
      
};

class YardNewItem3: public wxWizardPageSimple
{
 public:
    YardNewItem3(YardNewItem *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "InvShippingW");
        m_ship_weight = static_cast<wxTextCtrl *>(FindWindow(XRCID("WID_INV_ITEM_WEIGHT")));
        m_ship_date_rec = static_cast<wxTextCtrl *>(FindWindow(XRCID("WID_INV_DATE_RECEIVED")));
        m_ship_oversized = static_cast<wxCheckBox *>(FindWindow(XRCID("WID_INV_OVERSIZED")));
        m_ship_freight = static_cast<wxCheckBox *>(FindWindow(XRCID("WID_INV_FREIGHT_ONLY")));
                
    }

    virtual bool TransferDataFromWindow()
    {

        //m_parent->GetEmployee().SetACL(m_position->GetStringSelection().c_str());
        return true;
    }

 private:
    YardNewItem * m_parent;
    wxTextCtrl * m_ship_weight;
    wxTextCtrl * m_ship_date_rec;
    wxCheckBox * m_ship_oversized;
    wxCheckBox * m_ship_freight;
      
};

class YardNewItem4: public wxWizardPageSimple
{
 public:
    YardNewItem4(YardNewItem *parent) : wxWizardPageSimple(parent), m_parent(parent)
    {
        wxPanel * panel = wxXmlResource::Get()->LoadPanel(this, "InvStockW");
        m_stock_onhand = static_cast<wxSpinCtrl *>(FindWindow(XRCID("WID_INV_ON_HAND")));
        m_stock_onorder = static_cast<wxSpinCtrl *>(FindWindow(XRCID("WID_INV_ON_ORDER")));
        m_stock_reorder_lvl = static_cast<wxSpinCtrl *>(FindWindow(XRCID("WID_INV_REORDER_LEVEL")));
        m_stock_reorder_quant = static_cast<wxSpinCtrl *>(FindWindow(XRCID("WID_REORDER_QUANT")));
          
    }
    
    virtual bool TransferDataFromWindow()
    {
        return true;
    }
    
    wxSize GetMin() { return m_min; }

 private:
    wxSize m_min;
    YardNewItem * m_parent;
    wxSpinCtrl * m_stock_onhand;
    wxSpinCtrl * m_stock_onorder;
    wxSpinCtrl * m_stock_reorder_lvl;
    wxSpinCtrl * m_stock_reorder_quant;
      
};


#endif
