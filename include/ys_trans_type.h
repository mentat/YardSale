    /*
    YardSale - The Open Point of Sale
    Copyright (C) 2004 - Adam Parrish <waparris@ncsu.edu>
 
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
#ifndef YS_TRANSACTION_TYPE_H
#define YS_TRANSACTION_TYPE_H

#include "xmlnode.h"
#include "ys_inv_type.h"
#include "ys_cust_type.h"
#include "ys_employee_type.h"
#include <vector>
#include <string>

using namespace std;
class YardDatabase;
    
class YardTransType: public XMLNode
{
 public:
   
    friend class YardDatabase;
      
    YardTransType() { setName("Transaction_Log_Table"); }
    YardTransType(const string& xml): XMLNode(xml, XMLNode::Str) {}
    
    /* Getters */
    string GetEmployeeIdS() const 
        { return child("TRANS_REF_EMP_ID_Number").data(); }
    
    long GetEmployeeId() const
        { return ToLong(GetEmployeeIdS()); }
        
    vector<long> GetItemsId() const
    {
        vector<long> ret;
        for (NodeMap::const_iterator it = m_xmlData->m_children.begin();
             it != m_xmlData->m_children.end(); it++)
            ret.push_back(YardInvType(it->second).GetKey());
        return ret;
    }
        
    vector<YardInvType> GetItems() const
    {   // oh the sexiness of templates!
        return child("items").children<YardInvType>("Inventory_Table");
    }
    
    unsigned int CountItems() const
        { return child("items").numChildren("Inventory_Table"); }
    
    string GetCustomerIdS() const
        { return child("TRANS_REF_CUST_Account_Number").data(); }
    long GetCustomerId() const
        { return ToLong(GetCustomerIdS()); }
    
    string GetIdS() const
        { return child("TRANS_ID").data(); }
    long GetId() const
        { return ToLong(GetIdS()); }
        
    string GetQuantityS(long index) const
        { return child("items").child("Inventory_Table", index).child("Count").data(); }
    long GetQuantity(long index) const
        { return ToLong(GetQuantityS(index)); }

    string GetComment(long index) const
        { return child("items").child("Inventory_Table", index).child("Comment").data(); }
        
    string GetSalePrice(long index) const
        { return YardInvType(child("items").child("Inventory_Table", index)).GetRetailPriceS(); }
        
    string GetTime(long index) const
        { return child("items").child("Inventory_Table", index).child("Time").data(); }
        
    string GetOldTransRefS() const
        { return child("TRANS_REF_TRANS_Old_Trans").data(); }
        
    long GetOldTransRef() const
        { return ToLong(GetOldTransRefS()); }
        
    /* member functions */
    double SubTotal(const vector<YardTransType> transVect);
    
    map<string, float> GetTaxes() const
        {
            map<string, float> tax;
            return tax;
        }
        
    /**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = ",", bool quotes = true) const;   

};

#endif
