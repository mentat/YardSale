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
#include "ys_date.h"
#include "ys_build.h"
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
    
    void SetCustomer(long id)
        { child("TRANS_REF_CUST_Account_Number").setData(ToStr(id)); }
    void SetEmployee(long id)
        { child("TRANS_REF_EMP_ID_Number").setData(ToStr(id)); }
    void SetItem(long id)
        { child("TRANS_REF_INV_Item_ID").setData(ToStr(id)); }
    void SetQuantity(long num)
        { child("TRANS_Quantity").setData(ToStr(num)); }   
    void SetSalePrice(double price)
        { child("TRANS_Sale_Price").setData(ToStr(price,YS_DEFAULT_MONEY_PRECISION)); } 
    void SetTime(YardDate& time)
        { 
            time.setName("TRANS_Time");
            addChild(time);
        }
        
    /* Getters */
    string GetSalePriceS() const
        { return child("TRANS_Sale_Price").data(); }
    double GetSalePrice() const
        { return ToDouble(GetSalePriceS()); }  
        
    string GetEmployeeIdS() const 
        { return child("TRANS_REF_EMP_ID_Number").data(); }
    long GetEmployeeId() const
        { return ToLong(GetEmployeeIdS()); }

    string GetItemS() const
        { return child("TRANS_REF_INV_Item_ID").data(); }
    long GetItem() const
        { return ToLong(GetItemS()); } 

    string GetQuantityS() const
        { return child("TRANS_Quantity").data(); }
    long GetQuantity() const
        { return ToLong(GetQuantityS()); }        
    
    string GetCustomerIdS() const
        { return child("TRANS_REF_CUST_Account_Number").data(); }
    long GetCustomerId() const
        { return ToLong(GetCustomerIdS()); }
    
    string GetIdS() const
        { return child("TRANS_ID").data(); }
    long GetId() const
        { return ToLong(GetIdS()); }   
        
    string GetOldTransRefS() const
        { return child("TRANS_REF_TRANS_Old_Trans").data(); }   
    long GetOldTransRef() const
        { return ToLong(GetOldTransRefS()); }
        
    string GetComment() const
        { return child("TRANS_Comment").data(); }
        
    YardDate GetTime() const
        { return YardDate(child("TRANS_Time")); }
        
        
    /**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = ",", bool quotes = true) const;   

};

#endif
