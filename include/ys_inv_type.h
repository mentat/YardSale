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
#ifndef YS_INVENTORY_TYPE_H
#define YS_INVENTORY_TYPE_H

#include "ys_dbtype.h"
#include <vector>
#include <string>

using namespace std;

class YardDatabase;

/**
 * The YardSale Inventory Type is a OO representation of the datebase
 * inventory table.
 *
 * @include INV_Table.sql
 * @ingroup database 
 * @see YardInvType
 * @author Jesse Lovelace
 * @version \$Revision: 1.14 $$
 * @see YardDBType
 */

class YardInvType: public YardDBType
{
 public:
   
    friend class YardDatabase;
    
    /// This struct associates a quantity with a percentage for
    /// bulk pricing.
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
    
    /// Get SKU
    long int GetSKU() const { return m_skuNumber; }
    /// Get barcode
    string GetBarCode() const { return m_barCode; }
    /// Get item description
    string GetDescription() const { return m_itemDescription; }
    /// Get department
    string GetDepartment() const { return m_itemDepartment; }
    /// Get quantity on hand
    unsigned long GetQuantOnHand() const { return m_quantityOnHand; }
    /// Get quantity on order
    unsigned long GetQuantOnOrder() const { return m_quantityOnOrder; }
    /// Get reorder level
    unsigned long GetReorderLevel() const { return m_reorderLevel; }
    /// Get item type
    string GetItemType() const { return m_itemType; }
    /// Get weight in pounds
    float GetItemWeightLbs() const { return m_itemWeight; } 
    /// Get index of tax type, see tax table in DB
    int GetTaxType() const { return m_taxType; }
    /// Get vendor ID, see vendor table in DB
    long int GetVendorId() const { return m_vendorId; }
    /// Get retail price
    float GetRetailPrice() const { return m_retailPrice; }
    /// Get wholesale price
    float GetWholesalePrice() const { return m_wholesalePrice; }
    /// Return vector of bulk pricings
    vector<BulkPricing> GetBulkPricing() const { return m_bulkPricing; }
    /// Return oversized status of item
    /// @return True if item is oversized
    bool IsOverSized() const { return m_oversized; }
    /// Return if item must be shipped by freight
    /// @return True if item must be shipped by freight
    bool MustShipFreight() const { return m_mustShipFreight; }
  
    /* settors */
  
    /// Set the bar code
    void SetBarCode(const string& str);
    /// Set item description
    void SetDescription(const string& str) { m_itemDescription = str; }
    /// Set department
    void SetDepartment(const string& str);
    /// Set quantity on hand
    void SetQuantOnHand(unsigned long num) { m_quantityOnHand = num; }
    /// Set quantity on order
    void SetQuantOnOrder(unsigned long num) { m_quantityOnOrder = num; }
    /// Set reorder level
    void SetReorderLevel(unsigned long num) { m_reorderLevel = num; }
   
    /// Set general item type
    void SetItemType(const string& str);
    /// Set weight in pounds
    void SetItemWeightLbs(float num) { m_itemWeight = num; }
    /// Set tax type
    void SetTaxType(int num) { m_taxType = num; }
    /// Set vendor ID
    void SetVendorId(long int num) { m_vendorId = num; }
    /// Set retail price
    void SetRetailPrice(float num) { m_retailPrice = num; }
    /// Set wholesale price
    void SetWholesalePrice(float num) { m_wholesalePrice = num; }
   
    /* bulk pricing addition... */
   
    /// Add a bulk type to the object
    bool AddBulkPrice(const BulkPricing& price);
    /// Remove a bulk price from vector
    bool RemoveBulkPrice(unsigned int level);
   
    /// Set oversized flag
    void SetOverSized(bool cond) { m_oversized = cond; }
    /// Set ship by freight flag
    void SetShipFreight(bool cond) { m_mustShipFreight = cond; }
   
    /**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = "\n") const;
   
 private:
    
    /* These variables directly correspond with the database */
    long int m_skuNumber;
    string m_barCode;
    string m_itemDescription;
    string m_itemDepartment;
    long int m_quantityOnHand;
    long int m_quantityOnOrder;
    long int m_reorderLevel;
    long int m_reorderQuantity;
    string m_itemType;

    float m_itemWeight;
    long int m_taxType;
    long int m_vendorId;
    float m_retailPrice;
    float m_wholesalePrice;
 
    string m_bulkPrice;
    vector<BulkPricing> m_bulkPricing;
    
    DateTime m_dateLastReceived;
    string m_comment;
    
    bool m_oversized;
    bool m_mustShipFreight;
    
    
    /* Database       
    INV_SKU_Number			INT	NOT NULL,
	INV_Bar_Code_Number		varchar(30),
	INV_Item_Description		TEXT,
	INV_Item_Department		varchar(30),
	INV_Quantity_On_Hand		INT,
	INV_Quantity_On_Order		INT,
	INV_Reorder_Level		INT,
	INV_Reorder_Quantity		INT,
	INV_Item_Type			varchar(20),
	INV_REF_TAX_Tax_Type            INT NOT NULL,
	INV_REF_VND_Vendor_ID           INT NOT NULL,	
	INV_Retail_Price		DECIMAL(7,2),
	INV_Wholesale_Price		DECIMAL(7,2),
	INV_Bulk_Price			TEXT,
	INV_Date_Last_Received		DATETIME,
	INV_Weight_Pounds		FLOAT,
	INV_Oversized_Flag		enum('T','F'),
	INV_Ship_By_Freight		enum('T','F'),
	INV_Comment			TEXT,

    */
    
};

#endif
