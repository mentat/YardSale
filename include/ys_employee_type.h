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
#ifndef YS_EMPLOY_TYPE_H
#define YS_EMPLOY_TYPE_H

#include <string>
#include "xmlnode.h"

class YardDatabase;
    
using namespace std;

/**
 * This is a datatype to represent an Employee record.
 * See Database Tables.
 * This class is an XML DOM tree.
 *
 * @include EMP_Table.sql
 * @ingroup database
 * @author Jesse Lovelace
 * @version $Revision: 1.13 $
 * @see XMLNode
 */
class YardEmployeeType: public XMLNode {
 public:
    friend class YardDatabase;
    
    /// Default constructor
    YardEmployeeType() { setName("Employee_Table"); }
    YardEmployeeType(const string& xml): XMLNode(xml, XMLNode::Str) {}
        
    virtual ~YardEmployeeType() {}
 
    virtual string ToString(const string& delim=",", bool quotes = true) const;
        
    //----------------Getors--------------------
    
    /// Return DB ID for employee
    string GetIdS() const
        { return child("EMP_ID_Number").data(); }
    long GetId() const 
        { return ToLong(GetIdS()); }
    /// Return Tax ID, usually SS
    string GetTaxIdS() const
        { return child("EMP_Social_Security_Number").data(); }
    long GetTaxId() const 
        { return ToLong(GetTaxIdS()); }
    /// Return first name
    string GetFirst() const 
        { return child("EMP_First_Name").data(); }
    /// Return middle name
    string GetMiddle() const 
        { return child("EMP_Middle_Name").data(); }
    /// Return last name
    /// @todo Standardize this Last/LastName naming scheme
    string GetLast() const 
        { return child("EMP_Last_Name").data(); }
    /// Get both first and last
    string GetFirstLast() const
        { return GetFirst() + string(" ") + GetLast(); }
    /// Return address
    string GetAddress() const 
        { return child("EMP_Address").data(); }
    /// Return city
    string GetCity() const 
        { return child("EMP_City").data(); }
    /// Return state
    string GetState() const 
        { return child("EMP_State").data(); }
    /// Return zip code
    string GetZip() const 
        { return child("EMP_Zip").data(); }
    /// Return phone number
    string GetPhone() const 
        { return child("EMP_Phone_Number").data(); }
    
    /// Returns location of employee picture on datacenter
    /// @todo Define what a datacenter is
    string GetPicLocal() const 
        { return child("EMP_Picture").data(); }
    
    /// Returns the location of the employee signature file
    string GetSigLocal() const 
        { return child("EMP_Signature").data(); }
    
    /// Check enabled
    int GetEnabled() const 
        { return ToInt(child("EMP_Enabled").data()); }
    
    //-----------------Settors-------------------
    /// @note You cannot set the employee ID, it is set by the DB
    /// @todo Maybe have all these return boolean which says if the set
    ///  violates size limitations.
    void SetTaxId(long id)
        { child("EMP_Social_Security_Number").setData(ToStr(id)); }
    /// Set first name
    void SetFirstName(const string& name)
        { child("EMP_First_Name").setData(name); }
    /// Set middle name
    void SetMiddleName(const string& name)
        { child("EMP_Middle_Name").setData(name); }
    /// Set last name
    void SetLastName(const string& name) 
        { child("EMP_Last_Name").setData(name); }
    /// Set address
    void SetAddress(const string& add)
        { child("EMP_Address").setData(add); }
    /// Set city
    void SetCity(const string& city)
        { child("EMP_City").setData(city); }
    /// Set state
    void SetState(const string& state)
        { child("EMP_State").setData(state); }
    /// Set zip
    void SetZip(const string& zip)
        { child("EMP_Zip").setData(zip); }
    /// Set phone
    void SetPhone(const string& phone)
        { child("EMP_Phone").setData(phone); }
    /// Set picture
    void SetPicture(const string& loc)
        { child("EMP_Picture").setData(loc); }
    /// Set sig location
    void SetSig(const string& loc)
        { child("EMP_Signature").setData(loc); }
    /// Set job title
    //void SetTitle(const string& title);
    /// Set Enabled
    void SetEnabled(bool yes = true)
        { (yes) ? child("EMP_Enabled").setData("1") : child("EMP_Enabled").setData("0"); }
 
};

#endif
