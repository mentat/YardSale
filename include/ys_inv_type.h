#ifndef YS_INVENTORY_TYPE_H
#define YS_INVENTORY_TYPE_H

#include "ys_dbtype.h"

/**
 * The YardSale Inventory Type is a OO representation of the datebase
 * inventory table.
 * @author Jesse Lovelace
 * @version $Revision: 1.1 $
 * @see YardDBType
 */

class YardInvType: public YardDBType
{
    public:
        
    YardInvType();
    
    /**
     * Copy constructor
     */
    YardInvType(const YardInvType& obj);
    
    YardInvType& operator=(const YardInvType& obj);
    
    string GetBarCode() const;
    string GetDescription() const;
    string GetDepartment() const;
    
    unsigned long GetQuantOnHand() const;
    unsigned long GetQuantOnOrder() const;
    unsigned long GetReorderLevel() const;
    
    string GetItemType() const;
    float GetItemWeightLbs() const;
    float GetTaxType() const;
    long int GetVendorId() const;
    float GetRetailPrice() const;
    float GetWholesalePrice() const;
    
    vector<BulkPricing> GetBulkPricing() const;
    
    bool IsOverSized() const;
    bool MustShipFreight() const;
  
    private:
        
    long int m_autoIncrement;
    char[30] m_barCode;
    string m_description;
    char[30] m_department;
    unsigned long m_quantityOnHand;
    unsigned long m_quantityOnOrder;
    unsigned long m_reorderLevel;
    char[20] m_itemType;
    float m_itemWeight;
    float m_taxType;
    long int m_vendorId;
    float m_retailPrice;
    float m_wholesalePrice;
    
    struct BulkPricing 
    {
        unsigned long quantity;
        float percent;
    };
    vector<BulkPricing> m_bulkPricing;
    
    DateTime m_dateLastReceived;
    
    bool m_oversized;
    bool m_mustShipFreight;
    
};

#endif
