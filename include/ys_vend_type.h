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

#include "ys_dbtype.h"
#include <vector>
#include <string>

using namespace std;

class YardDatabase;
class otl_stream;

/**
 * The YardSale Vendor Type is a OO representation of the datebase
 * vendor table.
 *
 * @include Vendor_Table.sql
 * @ingroup database 
 * @see YardVendType
 * @author Michael Swigon	
 * @version \$Revision: 1.1 $$
 * @see YardDBType
 */

class YardVendType: public YardDBType
{
 public:
   
    friend class YardDatabase;

	  
    YardVendType() {}
    
    /**
     * Copy constructor
     */
    YardVendType(const YardVendType& obj);
    
    YardVendType& operator=(const YardVendType& obj);

	/// Get vendor id
    int GetVendID() const { return m_vendID; }
    /// Get vendor name
    string GetVendName() const { return m_vendName; }
    /// Return vector of vendor address
    vector<string> GetVendAddress() const { return m_vendAddress; }
	/// Get vendor city
    string GetVendCity() const { return m_vendCity; }
	/// Get vendor state
    string GetVendState() const { return m_vendState; }
	/// Get vendor zip code
    string GetVendZip() const { return m_vendZip; }
	/// Get vendor phone number
    string GetVendPhone() const { return m_vendPhone; }
	/// Get vendor sales representative
    string GetVendSalesRep() const { return m_vendSalesRep; }
	/// Get vendor specialty
    string GetVendSpecialty() const { return m_vendSpecialty; }
	/// Get vendor email address
    string GetVendEmail() const { return m_vendEmail; }
	/// Get vendor homepage
    string GetVendHomePage() const { return m_vendHomePage; }

	/* settors */
  
    /// Set the vendor name
	void SetVendName(const string& str) { m_vendName = str; }
    /// Set the vendor 
    void SetVendAddress(const vector<string>& addr) { m_vendAddress = addr; }
	/// Set the vendor city
	void SetVendCity(const string& str) { m_vendCity = str; }
	/// Set the vendor state
	void SetVendState(const string& str) { m_vendCity = str; }
	/// Set the vendor zip code
	void SetVendZip(const string& str) { m_vendZip = str; }
	/// Set the vendor phone number
	void SetVendPhone(const string& str) { m_vendPhone = str; }
	/// Set the vendor sales representative
	void SetVendSalesRep(const string& str) { m_vendSalesRep = str; }
	/// Set the vendor specialty
	void SetVendSpecialty(const string& str) { m_vendSpecialty = str; }
	/// Set the vendor email address
	void SetVendEmail(const string& str) { m_vendEmail = str; }
	/// Set the vendot homepage
	void SetVendHomePage(const string& str) { m_vendHomePage = str; }


	/**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = ",") const;
    
    virtual void FillFromStream(otl_stream * stream);

private:
    
    /* These variables directly correspond with the database */
    int m_vendID;
    string m_vendName;
    
	//vendor address
	
	string m_vendCity;
    string m_vendState;
	string m_vendZip;
	string m_vendPhone;
	string m_vendSalesRep;
	string m_vendSpecialty;
	string m_vendEmail;
	string m_vendHomePage;

	string m_vendAddr;
    vector<string> m_vendAddress;


};

#endif
	


