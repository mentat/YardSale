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
#ifndef YS_SHIPPING_TYPE_H
#define YS_SHIPPING_TYPE_H

#include "ys_dbtype.h"
#include <vector>
#include <string>

using namespace std;

class YardDatabase;
class otl_stream;

/**
 * The YardSale Shipping Type is a OO representation of the datebase
 * package table.
 *
 * @include SHP_Table.sql
 * @ingroup database 
 * @see YardShipType
 * @author Michael Swigon	
 * @version \$Revision: 1.3 $$
 * @see YardDBType
 */

class YardShipType: public YardDBType
{
 public:
   
    friend class YardDatabase;

	  
    YardShipType() {}
    
    /**
     * Copy constructor
     */
    YardShipType(const YardShipType& obj);
    
    YardShipType& operator=(const YardShipType& obj);

	/* gettors */

	/// Get shipping type
    string GetShipType() const { return m_shipType; }
	/// Get carrier id
	int GetCarrierID() const { return m_carrierID; }
	/// Get shipping cost
	float GetCost() const { return m_cost; }
	/// Get enabled flag
	int GetEnabled() const { return m_enabled; }

	/* settors */

	/// Set the shipping type
	void SetShipType(const string& str) { m_shipType = str; }
	/// Set the carrier id
	void SetCarrierID(const int num) { m_carrierID = num; }
	/// Set the shipping cost
	void SetCost(const float num) { m_cost = num; }
	/// Set enabled flag
	void SetEnabled(const int flag) { m_enabled = flag; }


	/**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = ",") const;
    
    virtual void FillFromStream(otl_stream * stream);
   
 private:
    
    /* These variables directly correspond with the database */
    string m_shipType;
    int m_carrierID;
	float m_cost;
	int m_enabled;

};

#endif
