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
#ifndef YS_VEND_TYPE_H
#define YS_VEND_TYPE_H

#include "xmlnode.h"
#include <vector>
#include <string>

using namespace std;

class YardDatabase;

/**
 * The YardSale Vendor Type is a OO representation of the datebase
 * vendor table.
 *
 * @include Vendor_Table.sql
 * @ingroup database 
 * @see YardVendType
 * @author Michael Swigon	
 * @version \$Revision: 1.3 $$
 * @see XMLNode
 */

class YardVendType: public XMLNode
{
 public:
   
    friend class YardDatabase;

    YardVendType() { setName("Vendor_Table"); }
    YardVendType(const string& xml): XMLNode(xml, Str) {}

	/// Get vendor id
    string GetIdS() const
        { return child("VND_ID").data(); }
    long GetId() const 
        { return ToLong(GetIdS()); }
    /// Get vendor name
    string GetName() const 
        { return child("VND_Name").data(); }
    /// Return vector of vendor address
    string GetAddress() const 
        { return child("VND_Address").data(); }
	/// Get vendor city
    string GetCity() const 
        { return child("VND_City").data(); }
	/// Get vendor state
    string GetState() const 
        { return child("VND_State").data(); }
	/// Get vendor zip code
    string GetZip() const 
        { return child("VND_Zip_Code").data(); }
	/// Get vendor phone number
    string GetPhone() const 
        { return child("VND_Phone_Number").data(); }
	/// Get vendor sales representative
    string GetSalesRep() const 
        { return child("VND_Sales_Representative").data(); }
	/// Get vendor specialty
    string GetSpecialty() const 
        { return child("VND_Specialty").data(); }
	/// Get vendor email address
    string GetEmail() const 
        { return child("VND_Email_Address").data(); }
	/// Get vendor homepage
    string GetHomePage() const 
        { return child("VND_Home_Page").data(); }

	/* settors */
  
    /// Set the vendor name
	void SetName(const string& str) 
        { child("VND_Name").setData(str); }
    /// Set the vendor 
    void SetAddress(const string& add) 
        { child("VND_Address").setData(add); }
	/// Set the vendor city
	void SetCity(const string& str) 
        { child("VND_City").setData(str); }
	/// Set the vendor state
	void SetState(const string& str) 
        { child("VND_State").setData(str); }
	/// Set the vendor zip code
	void SetZip(const string& str) 
        { child("VND_Zip_Code").setData(str); }
	/// Set the vendor phone number
	void SetPhone(const string& str) 
        { child("VND_Phone_Number").setData(str); }
	/// Set the vendor sales representative
	void SetSalesRep(const string& str) 
        { child("VND_Sales_Representative").setData(str); }
	/// Set the vendor specialty
	void SetSpecialty(const string& str) 
        { child("VND_Specialty").setData(str); }
	/// Set the vendor email address
	void SetEmail(const string& str) 
        { child("VND_Email_Address").setData(str); }
	/// Set the vendot homepage
	void SetHomePage(const string& str) 
        { child("VND_Home_Page").setData(str); }

	/**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = ",", bool quote = true) const;

};

#endif
