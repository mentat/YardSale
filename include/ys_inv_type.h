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

#include <vector>
#include <string>
#include <sstream>
#include "xmlnode.h"
#include "ys_build.h" // compile time settings
#include "ys_date.h"

using namespace std;

class YardDatabase;

/**
 * The YardSale Inventory Type is a OO representation of the datebase
 * inventory table.
 *
 * @include INV_Table.sql
 * @ingroup database 
 * @see XMLNode
 * @author Jesse Lovelace
 * @version \$Revision: 1.22 $$
 */

class YardInvType: public XMLNode
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
  
    YardInvType() { setName("Inventory_Table"); }
    YardInvType(const string& xml): XMLNode(xml, XMLNode::Str) {}
    
    string GetKeyS() const 
        { return child("INV_Item_ID"); }
    long GetKey() const 
        { return ToLong(GetKeyS()); }
        
    /// Get SKU
    string GetSKU() const 
        { return child("INV_SKU_Number").data(); }
    /// Get barcode
    string GetBarCode() const 
        { return child("INV_Bar_Code_Number").data(); }
    /// Get item description
    string GetDescription() const 
        { return child("INV_Item_Description").data(); }
    /// Get department
    string GetDepartment() const 
        { return child("INV_Item_Department").data(); }
    
    /// Get quantity on hand string then integer
    string GetQuantOnHandS() const 
        { return child("INV_Quantity_On_Hand").data(); }
    unsigned long GetQuantOnHand() const 
        { return ToLong(GetQuantOnHandS()); }
    /// Get quantity on order
    string GetQuantOnOrderS() const
        { return child("INV_Quantity_On_Order").data(); }
    unsigned long GetQuantOnOrder() const 
        {return ToLong(GetQuantOnOrderS()); }
    /// Get reorder level
    string GetReorderLevelS() const
        { return child("INV_Reorder_Level").data(); }
    unsigned long GetReorderLevel() const 
        { return ToLong(GetReorderLevelS()); }
    string GetReorderQuantityS() const
        { return child("INV_Reorder_Quantity").data(); }
    unsigned long GetReorderQuantity() const
        { return ToLong(GetReorderQuantityS()); }
    /// Get item type
    string GetType() const 
        { return child("INV_Item_Type").data(); }
    /// Get weight in pounds
    string GetWeightLbsS() const
        { return child("INV_Weight_Pounds").data(); }
    double GetWeightLbs() const 
        { return ToDouble(GetWeightLbsS()); } 
    /// Get index of tax type, see tax table in DB
    string GetTaxTypeS() const
        { return child("INV_REF_TAX_Tax_Type").data(); }
    int GetTaxType() const 
        { return ToInt(GetTaxTypeS()); }
    /// Get vendor ID, see vendor table in DB
    string GetVendorIdS() const
        { return child("INV_REF_VND_Vendor_ID").data(); }
    long int GetVendorId() const 
        { return ToLong(GetVendorIdS()); }
    /// Get retail price
    string GetRetailPriceS() const
        { return child("INV_Retail_Price").data(); }
    double GetRetailPrice() const 
        { return ToDouble(GetRetailPriceS()); }
    /// Get wholesale price
    string GetWholesalePriceS() const
        { return child("INV_Wholesale_Price").data(); }
    double GetWholesalePrice() const 
        { return ToDouble(GetWholesalePriceS()); }
    
    /// Return oversized status of item
    /// @return True if item is oversized
    char IsOverSizedS() const
        { return (child("INV_Oversized_Flag").data() == "T") ? 'T' : 'F'; }
    bool IsOverSized() const 
        { return (child("INV_Oversized_Flag").data() == "T") ? true : false; }
    /// Return if item must be shipped by freight
    /// @return True if item must be shipped by freight
    char MustShipFreightS() const
        { return (child("INV_Ship_By_Freight").data() == "T") ? 'T' : 'F'; }
    bool MustShipFreight() const 
        { return (child("INV_Ship_By_Freight").data() == "T") ? true : false; }
	/// Return the group ID
    string GetGroupIdS() const
        { return child("INV_REF_INVGRP_Group_ID").data(); }
	int GetGroupId() const
        { return ToInt(GetGroupIdS()); }
        
    /// @todo Make this an XMLNode type.    
    string GetBulkPricing() const
        {  
            stringstream ret;
            vector<XMLNode> prices = child("INV_Bulk_Price").const_children();
            for (unsigned int i = 0; i < prices.size(); i++)
                ret << prices[i] << '\n';
            return ret.str();
        }
        
    double GetBulkPrice(unsigned int quant)
        { return ToDouble(child("INV_Bulk_Price").child(ToStr(quant)).data()); }
    
    string GetComment() const
        { return child("INV_Comment").data(); }
        
    YardDate GetDateLastReceived() const
        { return YardDate(child("INV_Date_Last_Received")); }
            
   
    /* settors */
    /* @throws YardDBIntegrityException if you try to overwrite
              a value set by the DB */
    /*void SetID(long key)
        { child("INV_Item_ID").setData(ToStr(key)); }*/
    /// Set the bar code
    void SetSKU(const string& sku)
        { child("INV_SKU_Number").setData(sku); }
    void SetBarCode(const string& str)
        { child("INV_Bar_Code_Number").setData(str); }
    /// Set item description
    void SetDescription(const string& str) 
        { child("INV_Item_Description").setData(str); }
    /// Set department
    void SetDepartment(const string& str)
        { child("INV_Item_Department").setData(str); }
    /// Set quantity on hand
    void SetQuantOnHand(unsigned long num) 
        { child("INV_Quantity_On_Hand").setData(ToStr(num)); }
    /// Set quantity on order
    void SetQuantOnOrder(unsigned long num) 
        { child("INV_Quantity_On_Order").setData(ToStr(num)); }
    /// Set reorder level
    void SetReorderLevel(unsigned long num) 
        { child("INV_Reorder_Level").setData(ToStr(num)); }
    void SetReorderQuant(unsigned long num)
        { child("INV_Reorder_Quantity").setData(ToStr(num)); }
	/// Set the group id, references Inventory_Group_Table
    /// @see YardInvGroup
	void SetGroupID(int a_num)
        { child("INV_REF_INVGRP_Group_ID").setData(ToStr(a_num)); }
        
    /// Set general item type
    void SetType(const string& str)
        { child("INV_Item_Type").setData(str); }
    /// Set weight in pounds
    void SetWeightLbs(double num) 
        { child("INV_Weight_Pounds").setData(ToStr(num, YS_DEFAULT_WEIGHT_PRECISION)); }
    /// Set tax type
    void SetTaxType(int num) 
        { child("INV_REF_TAX_Tax_Type").setData(ToStr(num)); }
    /// Set vendor ID
    void SetVendorId(long int num) 
        { child("INV_REF_VND_Vendor_ID").setData(ToStr(num)); }
    /// Set retail price
    /// @todo Some systems might need differing fractional nums, put this in compile config
    void SetRetailPrice(double num) 
        { child("INV_Retail_Price").setData(ToStr(num, YS_DEFAULT_MONEY_PRECISION)); }
    /// Set wholesale price
    void SetWholesalePrice(double num) 
        { child("INV_Wholesale_Price").setData(ToStr(num, YS_DEFAULT_MONEY_PRECISION)); }
   
    /* bulk pricing addition... 
        XML Makes this sooooo easy */
   
    /// Add a bulk type to the object
    void AddBulkPrice(long quantity, float discount)
        { child("INV_Bulk_Price").child(ToStr(quantity)).setData(ToStr(discount, YS_BULK_DISCOUNT_PRECISION)); }
    /// Remove a bulk price from vector
    void RemoveBulkPrice(long quantity)
        { child("INV_Bulk_Price").delChild(ToStr(quantity)); }
   
    /// Set oversized flag
    void SetOverSized(bool cond)
        { (cond) ? child("INV_Oversized_Flag").setData("T") : child("INV_Oversized_Flag").setData("F"); }
 
    /// Set ship by freight flag
    void SetShipFreight(bool cond) 
        { (cond) ? child("INV_Ship_By_Freight").setData("T") : child("INV_Ship_By_Freight").setData("F"); }
    
    void SetLastReceived(YardDate& date)
        {
            date.setName("INV_Date_Last_Recieved");
            child("INV_Date_Last_Recieved") = date;
        }
        
    void SetComment(const string& str)
        { child("INV_Comment").setData(str); }
    /**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = ",", bool quotes = true) const;
        
};

#endif
