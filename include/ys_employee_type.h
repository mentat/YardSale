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
#include "ys_dbtype.h"

class YardDatabase;
    
using namespace std;

/**
 * This is a datatype to represent an Employee record.
 * See Database Tables.
 *
 * @include EMP_Table.sql
 * @ingroup database
 * @author Jesse Lovelace
 * @version $Revision: 1.5 $
 * @see YardDBType
 */
class YardEmployeeType: public YardDBType {
 public:
    friend class YardDatabase;
    
    /// Default constructor
    YardEmployeeType(){}
        
    /// Copy constructor - always deep copy
    YardEmployeeType(const YardEmployeeType& copy);
    
    /// Assignment operator overload
    YardEmployeeType& operator=(const YardEmployeeType & copy);
        
    virtual string ToString(const string& delim="\n") const;
        
    //----------------Getors--------------------
    
    /// Return DB ID for employee
    unsigned long GetId() const { return m_id; }
    /// Return Tax ID, usually SS
    string GetTaxId() const { return m_taxId; }
    /// Return first name
    string GetFirst() const { return m_firstName; }
    /// Return middle name
    string GetMiddle() const { return m_middleName; }
    /// Return last name
    string GetLast() const { return m_lastName; }
    /// Return address
    string GetAddress() const { return m_address; }
    /// Return city
    string GetCity() const { return m_city; }
    /// Return state
    string GetState() const { return m_state; }
    /// Return zip code
    string GetZip() const { return m_zip; }
    /// Return phone number
    string GetPhone() const { return m_phone; }
    
    /// Returns location of employee picture on datacenter
    /// @todo Define what a datacenter is
    string GetPicLocal() const { return m_picture; }
    
    /// Returns the location of the employee signature file
    string GetSigLocal() const { return m_signature; }
    
    //-----------------Settors-------------------
    /// @note You cannot set the employee ID, it is set by the DB
    /// @todo Maybe have all these return boolean which says if the set
    ///  violates size limitations.
    void SetTaxId(const string& id);
    /// Set first name
    void SetFirstName(const string& name);
    /// Set middle name
    void SetMiddleName(const string& name);
    /// Set last name
    void SetLastName(const string& name);
    /// Set address
    void SetAddress(const string& add);
    /// Set city
    void SetCity(const string& city);
    /// Set state
    void SetState(const string& state);
    /// Set zip
    void SetZip(const string& zip);
    /// Set phone
    void SetPhone(const string& phone);
    /// Set picture
    void SetPicture(const string& loc);
    /// Set sig location
    void SetSig(const string& loc);
    /// Set job title
    void SetTitle(const string& title);

 private:
    
    unsigned long m_id; // employee id number
     
    string m_taxId; // social in many cases
    string m_firstName; //first name
    string m_middleName; //middle name
    string m_lastNmae; //last name
    string m_address; 
    string m_city;
    string m_zip;
    string m_state;
    string m_phone;
 
    string m_picture;
    string m_signature;

    string m_title; // for grouping
    
};

#endif
