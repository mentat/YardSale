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

#include "ys_dbtype.h"
#include <vector>
#include <string>

using namespace std;

class YardDatabase;
class otl_stream;
    
class YardCustType: public YardDBType
{
 public:
   
    friend class YardDatabase;
      
    YardCustType() {}
    
    /**
     * Copy constructor
     */
    YardCustType(const YardCustType& obj);
    
    YardCustType& operator=(const YardCustType& obj);
    
    /* Getters */
    
    /// Get Customer Account Number
    int GetAccountNumber() const { return m_accountNumber; }
    /// Get Customer First Name
    string GetCustFirstName() const { return m_custFirstName; }
    /// Get Customer Middle Name
    string GetCustMiddleName() const { return m_custMiddleName; }
    /// Get Customer Last Name
    string GetCustLastName() const { return m_custLastName; }
    /// Get Customer Address
    /// should return a vector of address lines
    /*vector<string>*/ string GetCustomerAddress() const{ return m_custAddress; }
    /// Get Customer Phone
    string GetCustomerPhone() const{ return m_custPhone; }
    /// Get Customer City
    string GetCustomerCity() const{ return m_custCity; }
    /// Get Customer ZIP 
    string GetCustomerZip() const{ return m_custZip; }
    /// Get Customer Credit Card Number 
    string GetCustomerCreditCardNumber() const{ return m_custCCNumber; }
    /// Get Customer Credit Card Expiration 
    string GetCustomerCreditCardExpiration() const{ return m_custCCExpiration; }
    /// Get Customer Credit Card Name 
    string GetCustomerCreditCardName() const{ return m_custCCName; }
    /// Get Customer Signature 
    string GetCustomerSignaturePath() const{ return m_custSigPath; }
    /// Get Customer Photo
    string GetCustomerPhoto() const{ return m_custPhoto; }
      
    /* setters */
  
    /// Set the account number - this may need to be removed since account
    /// numbers are handled internally by the RDBMS
    void SetAccountNumber(const int& a_num) const { return m_accountNumber = a_num; }
    /// Set the customer first name
    void SetCustFirstName(const string& str) { m_custFirstName = str; }
    /// Set the customer middle name
    void SetCustMiddleName(const string& str) { m_custMiddleName = str; }
    /// Set the customer last name
    void SetCustLastName(const string& str) { m_custLastName = str; }
    /// Set the Customer Address
    void SetCustAddress(const string& addr) { m_custAddress = addr; }
    /// Set the Customer Phone numbers
    void SetCustPhoneNumber(const string& str) { m_custPhone = str; }
    /// Set the Customer City 
    void SetCustCity(const string& str) { m_custCity =  str; }
    /// Set the Customer Zip
    void SetCustZip(const string& str) { m_custZip = str; }
    /// Set the Customer Credit Card Number 
    void SetCustCreditCardNumber(const string& str) { m_custCCNumber = str; }
    /// Set the Customer Credit Card Expiration 
    void SetCustCreditCardExpiration(const string& str) { m_custCCExpiration = str; }
    /// Set the Name on the Customer Credit Card  
    void SetCustCreditCardName(const string& str) { m_custCCName = str; }
  

   
    /**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = "\n") const;
    
    void FillFromStream(otl_stream * stream);
   
 private:
    
    /* These variables directly correspond with the database */
    int m_accountNumber;
    string m_custFirstName;
    string m_custMiddleName; 
    string m_custLastName;
    string m_custAddress
    string m_custPhone
    string m_custCity
    string m_custZip
    string m_custCCNumber
    string m_custCCExpiration
    string m_custCCName

};

#endif
