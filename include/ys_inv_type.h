#ifndef YS_INVENTORY_TYPE_H
#define YS_INVENTORY_TYPE_H

#include "ys_dbtype.h"
#include "wx/string.h"
#include <vector>

using namespace std;

class YardDatabase;

/**
 * The YardSale Inventory Type is a OO representation of the datebase
 * inventory table.
 * @author Jesse Lovelace
 * @version $Revision: 1.3 $
 * @see YardDBType
 */

class YardInvType: public YardDBType
{
 public:
   
    friend class YardDatabase;
    struct BulkPricing 
    {
        unsigned long quantity;
        float percent;
    };
  
    YardInvType() {}
    
    /**
     * Copy constructor
     */
    YardInvType(const YardInvType& obj);
    
    YardInvType& operator=(const YardInvType& obj);
    
    wxString GetBarCode() const { return m_barCode; }
    wxString GetDescription() const { return m_itemDescription; }
    wxString GetDepartment() const { return m_itemDepartment; }
    
    unsigned long GetQuantOnHand() const { return m_quantityOnHand; }
    unsigned long GetQuantOnOrder() const { return m_quantityOnOrder; }
    unsigned long GetReorderLevel() const { return m_reorderLevel; }
    
    wxString GetItemType() const { return m_itemType; }
    float GetItemWeightLbs() const { return m_itemWeight; } 
    float GetTaxType() const { return m_taxType; }
    long int GetVendorId() const { return m_vendorId; }
    float GetRetailPrice() const { return m_retailPrice; }
    float GetWholesalePrice() const { return m_wholesalePrice; }
    
    vector<BulkPricing> GetBulkPricing() const { return m_bulkPricing; }
    
    bool IsOverSized() const { return m_oversized; }
    bool MustShipFreight() const { return m_mustShipFreight; }
  
  /* settors */
  
   void SetBarCode(const wxString& str);
   void SetDescription(const wxString& str) { m_itemDescription = str; }
   void SetDepartment(const wxString& str);
   void SetQuantOnHand(unsigned long num) { m_quantityOnHand = num; }
   void SetQuantOnOrder(unsigned long num) { m_quantityOnOrder = num; }
   void SetReorderLevel(unsigned long num) { m_reorderLevel = num; }
   
   void SetItemType(const wxString& str);
   void SetItemWeightLbs(float num) { m_itemWeight = num; }
   void SetTaxType(float num) { m_taxType = num; }
   void SetVentorId(long int num) { m_vendorId = num; }
   void SetRetailPrice(float num) { m_retailPrice = num; }
   void SetWholesalePrice(float num) { m_wholesalePrice = num; }
   
   /* bulk pricing addition... */
   
   bool AddBulkPrice(const BulkPricing& price);
   bool RemoveBulkPrice(unsigned int level);
   
   void SetOverSized(bool cond) { m_oversized = cond; }
   void SetShipFreight(bool cond) { m_mustShipFreight = cond; }
   
 private:
        
    long int m_skuNumber;
    wxChar m_barCode[30+1];
    wxString m_itemDescription;
    wxChar m_itemDepartment[30+1];
    unsigned long m_quantityOnHand;
    unsigned long m_quantityOnOrder;
    unsigned long m_reorderLevel;
    unsigned long m_reorderQuantity;
    wxChar m_itemType[30+1];
    float m_itemWeight;
    float m_taxType;
    long int m_vendorId;
    float m_retailPrice;
    float m_wholesalePrice;
    
    /*   struct BulkPricing  */
    /*     { */
    /*         unsigned long quantity; */
    /*         float percent; */
    /*     }; */
    vector<BulkPricing> m_bulkPricing;
    
    DateTime m_dateLastReceived;
    
    bool m_oversized;
    bool m_mustShipFreight;
    
};

#endif
