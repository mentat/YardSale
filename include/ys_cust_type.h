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
#ifndef YS_CUSTOMER_TYPE_H
#define YS_CUSTOMER_TYPE_H

#include "ys_date.h"
#include "xmlnode.h"
#include <vector>
#include <string>

using namespace std;

class YardDatabase;
    
class YardCustType: public XMLNode
{
 public:
   
    friend class YardDatabase;
      
    YardCustType() { setName("Customer_Table"); }
    YardCustType(const string& xml): XMLNode(xml, Str) {}
        
    static const char * GetUnique() { return "CUST_Account_Number"; }
    
    /* Getters */
    
    /// Get Customer Account Number
    long GetAccountNumber() const 
        { return ToLong(child("CUST_Account_Number").data()); }
    /// Get Customer First Name
    string GetFirstName() const 
        { return child("CUST_First_Name").data(); }
    /// Get Customer Middle Name
    string GetMiddleName() const
        { return child("CUST_Middle_Name").data(); }
    string GetFirstLast() const
        { return GetFirstName() + string(" ") + GetLastName(); }
    /// Get Customer Last Name
    string GetLastName() const 
        { return child("CUST_Last_Name").data(); }
    /// Get Customer Address
    /// should return a vector of address lines
    /*vector<string>*/ 
    string GetAddress() const
        { return child("CUST_Address").data(); }
    /// Get Customer Phone
    string GetPhone() const
        { return child("CUST_Phone").data(); }
    /// Get Customer City
    string GetCity() const
        { return child("CUST_City").data(); }
    string GetState() 
        { return child("CUST_State").data(); }
    /// Get Customer ZIP 
    string GetZip() const
        { return child("CUST_Zip").data(); }
    /// Get Customer Credit Card Number 
    string GetCreditCardNumber() const
        { return child("CUST_Credit_Card_Number").data(); }
    /// Get Customer Credit Card Expiration 
    string GetCreditCardExpiration() const
        { return child("CUST_CC_Exp_Date").data(); }
    /// Get Customer Credit Card Name 
    string GetCreditCardName() const
        { return child("CUST_Name_On_CC").data(); }
    /// Get Customer Signature 
    string GetSigLocal() const
        { return child("CUST_Signature").data(); }
    /// Get Customer Photo
    string GetPicLocal() const
        { return child("CUST_Photo").data(); }
    YardDate GetSince() const
        { return YardDate(child("CUST_Since_Date")); }
        
    string GetHashS() const
        { return child("CUST_HASH").data(); }
    long GetHash() const
        { return ToLong(GetHashS()); }
      
    /* setters */
  
    /// Set the account number - this may need to be removed since account
    /// numbers are handled internally by the RDBMS
    void SetAccountNumber(const long a_num) 
        { child("CUST_Account_Number").setData(ToStr(a_num)); }
    /// Set the customer first name
    void SetFirstName(const string& str) 
        { child("CUST_First_Name").setData(str); }
    /// Set the customer middle name
    void SetMiddleName(const string& str) 
        { child("CUST_Middle_Name").setData(str); }
    /// Set the customer last name
    void SetLastName(const string& str) 
        { child("CUST_Last_Name").setData(str); }
    /// Set the Customer Address
    void SetAddress(const string& addr) 
        { child("CUST_Address").setData(addr); }
    /// Set the Customer Phone numbers
    void SetPhone(const string& str) 
        { child("CUST_Phone").setData(str); }
    /// Set the Customer City 
    void SetCity(const string& str) 
        { child("CUST_City").setData(str); }
    void SetState(const string& str) 
        { child("CUST_State").setData(str); }
    /// Set the Customer Zip
    void SetZip(const string& str) 
        { child("CUST_Zip").setData(str); }
    /// Set the Customer Credit Card Number 
    void SetCreditCardNumber(const string& str) 
        { child("CUST_Credit_Card_Number").setData(str); }
    /// Set the Customer Credit Card Expiration 
    void SetCreditCardExpiration(const string& str) 
        { child("CUST_CC_Exp_Date").setData(str); }
    /// Set the Name on the Customer Credit Card  
    void SetCreditCardName(const string& str) 
        { child("CUST_Name_On_CC").setData(str); }
    void SetSignature(const string& str)
        { child("CUST_Signature").setData(str); }
    void SetPicture(const string& str)
        { child("CUST_Photo").setData(str); }
        
    void SetSince(YardDate& date)
        {   date.setName("CUST_Since_Date");
            child("CUST_Since_Date") = date;
        }
        
    void SetHash(long hash)
        { child("CUST_HASH").setData(ToStr(hash)); }
    /**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = ",", bool quotes = true) const;
};

#endif
