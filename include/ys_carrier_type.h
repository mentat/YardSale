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
#ifndef YS_CARRIER_TYPE_H
#define YS_CARRIER_TYPE_H

#include "ys_dbtype.h"
#include <vector>
#include <string>

using namespace std;

class YardDatabase;
class otl_stream;

/**
 * The YardSale Carrier Type is a OO representation of the datebase
 * package table.
 *
 * @include CRR_Table.sql
 * @ingroup database 
 * @see YardCarrierType
 * @author Michael Swigon	
 * @version \$Revision: 1.1 $$
 * @see YardDBType
 */

class YardCarrierType: public YardDBType
{
 public:
   
    friend class YardDatabase;

	  
    YardCarrierType() {}
    
    /**
     * Copy constructor
     */
    YardCarrierType(const YardCarrierType& obj);
    
    YardCarrierType& operator=(const YardCarrierType& obj);

	/* gettors */

	/// Get carrier id
    int GetCarrierID() const { return m_carrierID; }
	/// Get carrier name
	string GetCarrierName() const { return m_carrierName; }
	/// Get pickup location
	string GetPickupLoc() const { return m_pickupLoc; }
	/// Get carrier phone number
	string GetPhoneNum() const { return m_phoneNum; }

	/* settors */
	/// Set the carrier name
	void SetCarrierName(const string& str) { m_carrierName = str; }
	/// Set the pickup location
	void SetPickupLoc(const string& str) { m_pickupLoc = str; }
	/// Set the phone number
	void SetPhoneNum(const string& str) { m_phoneNum = str; }

	/**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = ",") const;
    
    virtual void FillFromStream(otl_stream * stream);
   
 private:
    
    /* These variables directly correspond with the database */
    int m_carrierID;
	string m_carrierName;
	string m_pickupLoc;
	string m_phoneNum;


};

#endif

