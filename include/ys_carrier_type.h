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

#include "xmlnode.h"
#include "ys_build.h" // compile time settings
#include <vector>
#include <string>

using namespace std;

class YardDatabase;

/**
 * The YardSale Carrier Type is a OO representation of the datebase
 * package table.
 *
 * @include CRR_Table.sql
 * @ingroup database 
 * @see YardCarrierType
 * @author Michael Swigon	
 * @version \$Revision: 1.4 $$
 * @see XMLNode
 */

class YardCarrierType: public XMLNode
{
 public:
   
    friend class YardDatabase;
  
    YardCarrierType() { setName("Carrier_Table"); }
        
    YardCarrierType(const string& xml):XMLNode(xml, XMLNode::Str) {}
        
    ~YardCarrierType();
    
	/* gettors */

	/// Get carrier id
    long GetID() const 
        { return ToLong(child("CRR_ID").data()); }
	/// Get carrier name
	string GetName() const 
        { return child("CRR_Name").data(); }
	/// Get pickup location
	string GetPickupLoc() const 
        { return child("CRR_Pickup_Location").data(); }
	/// Get carrier phone number
	string GetPhone() const 
        { return child("CRR_Phone_Number").data(); }

	/* settors */
	/// Set the carrier name
	void SetName(const string& str) 
        { child("CRR_Name").setData(str); }
	/// Set the pickup location
	void SetPickupLoc(const string& str) 
        { child("CRR_Pickup_Location").setData(str); }
	/// Set the phone number
	void SetPhone(const string& str) 
        { child("CRR_Phone_Number").setData(str); }

	/**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */

    virtual string ToString(const string& delim=",", bool quotes = true) const;
};

#endif
